#include "SphereTree.h"


/*
 * SphereTree is the main acceleration structure that we use here.
 * This approach creates Bounding Volume Hierarchy using Bottom-Up construction.
 * It creates a minimum bounding sphere for each triangle on the mesh.
 * Then tries to combine two spheres using a criterion which depends on radii
 * of both the spheres, and the radius of the combined sphere.
 * While applying this criterion, it uses a threshold value to decide whether to apply the merge operation or not.
 * It repeats the process on the old and new spheres and forms a tree structure.
 */

namespace core
{

SphereTree::SphereTree()
{
	highestLevel = 0;
}

void SphereTree::initialize(const GU_Detail* inputMesh, double threshold)
{
	mesh = inputMesh;
	buildLeafNodes();
	buildTree(threshold);
}

void SphereTree::buildLeafNodes()
{
	for (int primNum = 0; primNum < mesh->getNumPrimitives(); primNum++)
	{
		GEO_PrimPoly* poly = (GEO_PrimPoly*) (mesh->getPrimitiveByIndex(primNum));
		UT_BoundingSphere boundingSphere;
		boundingSphere.addPoint(poly->getPos3(0));
		boundingSphere.addPoint(poly->getPos3(1));
		boundingSphere.addPoint(poly->getPos3(2));
		SphereNode* sphereNode = new SphereNode(boundingSphere, poly, 0);
		leafNodes.push_back(sphereNode);
		completeNodeList.push_back(sphereNode);
	}
}

void SphereTree::buildTree(double threshold)
{

	workingList = leafNodes;

	for (size_t iA = 0; iA < workingList.size(); ++iA)
	{
		SphereNode* nodeA = workingList[iA];
		if (nodeA == NULL)
			continue;
		for (size_t iB = 0; iB < workingList.size(); ++iB)
		{
			SphereNode* nodeB = workingList[iB];
			if (nodeB == NULL)
				continue;
			if (nodeA == nodeB)
				continue;
			if (iA == iB)
				continue;
			UT_BoundingSphere sphereAB;
			if (nodeA->canItMerge(nodeB, threshold, sphereAB))
			{
				SphereNode* mergedNode = nodeA->doMerge(nodeB, sphereAB);
				highestLevel = std::max(highestLevel, mergedNode->level);
				completeNodeList.push_back(mergedNode);
				workingList.push_back(mergedNode);
				workingList[iA] = NULL;
				workingList[iB] = NULL;
				break;
			}
		}
	}
}

SphereTree::~SphereTree()
{
	for (std::vector<SphereNode*>::iterator it = completeNodeList.begin();
			it != completeNodeList.end(); ++it)
	{
		delete *it;
	}
}

const std::vector<SphereNode*>& SphereTree::getCompleteNodeList() const
{
	return completeNodeList;
}

void SphereTree::distanceTest(SphereNode* parent, UT_Vector3 P, double& minUpperBound,
		std::vector<SphereNode*>& filterdList)
{
	if (parent->level == 0)
	{
		filterdList.push_back(parent);
	}
	else
	{
		double localMinUpperBound = std::min(parent->child1->upperBound(P),
				parent->child2->upperBound(P));
		if (localMinUpperBound < minUpperBound)
			minUpperBound = localMinUpperBound;
		if (parent->child1->lowerBound(P) < minUpperBound)
			distanceTest(parent->child1, P, minUpperBound, filterdList);
		if (parent->child2->lowerBound(P) < minUpperBound)
			distanceTest(parent->child2, P, minUpperBound, filterdList);
	}
}

void SphereTree::getFilteredPrimList(UT_Vector3 P, std::vector<SphereNode*>& filteredNodeList,
		std::vector<GEO_PrimPoly*>& filteredPrimList)
{
	double minUpperBound = DBL_MAX;
	std::vector<SphereNode*> filterdList;

	/*
	 * For all the nodes at the highest level (or without parent), find the minimum upper bound.
	 */
	for (std::vector<core::SphereNode*>::iterator it = workingList.begin(); it != workingList.end();
			++it)
	{
		if ((*it) == NULL)
			continue;
		{
			double upperBound = (*it)->upperBound(P);
			if (upperBound < minUpperBound)
				minUpperBound = upperBound;
		}
	}
	/*
	 * For any of the nodes at the highest level (or without parent), if the lower_bound is less than minUpperBound,
	 * we need to check that node and it's children. If lower_bound is greater than min_upper_bound, we can ignore that
	 * node and all it's children.
	 */
	for (std::vector<core::SphereNode*>::iterator it = workingList.begin(); it != workingList.end();
			++it)
	{
		if ((*it) == NULL)
			continue;
		{
			double lowerBound = (*it)->lowerBound(P);
			if (lowerBound < minUpperBound)
			{
				distanceTest((*it), P, minUpperBound, filterdList);
			}
		}

	}

	/*
	 * Second pass of filtering. As the minUpperBound is an evolving quantity, we compare its final value with the
	 * lowerBounds of remaining spheres. It helps to reduce the number of spheres to be checked.
	 */
	for (std::vector<core::SphereNode*>::iterator it = filterdList.begin(); it != filterdList.end();
			++it)
	{
		if ((*it)->lowerBound(P) < minUpperBound)
		{
			filteredNodeList.push_back((*it));
			filteredPrimList.push_back((*it)->poly);
		}
	}

	return;
}

} /* namespace core */
