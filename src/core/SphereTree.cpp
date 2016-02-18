/*
 * SphereTree.cpp
 *
 *  Created on: 18-Feb-2016
 *      Author: user
 */

#include "SphereTree.h"

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

	int counter = 10000;
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
			if (counter == 0)
			{
				std::cout << "COUNTER ZERO !" << std::endl;
				continue;
			}
			if (nodeA->canMerge(nodeB, threshold, sphereAB))
			{
				SphereNode* mergedNode = nodeA->merge(nodeB, sphereAB);
				highestLevel = std::max(highestLevel, mergedNode->level);
				completeNodeList.push_back(mergedNode);
				workingList.push_back(mergedNode);
				workingList[iA] = NULL;
				workingList[iB] = NULL;
				counter--;
				break;
			}
		}
	}
}

SphereTree::~SphereTree()
{
	for (std::vector<SphereNode*>::iterator it = leafNodes.begin(); it != leafNodes.end(); ++it)
	{
		delete *it;
	}
}

const std::vector<SphereNode*>& SphereTree::getCompleteNodeList() const
{
	return completeNodeList;
}

void SphereTree::distanceTest(SphereNode* parent, UT_Vector3 P)
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
			distanceTest(parent->child1, P);
		if (parent->child2->lowerBound(P) < minUpperBound)
			distanceTest(parent->child2, P);
	}
}

std::vector<GEO_PrimPoly*> SphereTree::getFilteredPrims(UT_Vector3 P)
{
	minUpperBound = 100000;
	filterdList.clear();

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

	for (std::vector<core::SphereNode*>::iterator it = workingList.begin(); it != workingList.end();
			++it)
	{
		if ((*it) == NULL)
			continue;
		{
			double lowerBound = (*it)->lowerBound(P);
			if (lowerBound < minUpperBound)
			{
				distanceTest((*it), P);
			}
		}

	}

	std::vector<SphereNode*> fineFilterdList;
	std::vector<GEO_PrimPoly*> filterdPrims;
	for (std::vector<core::SphereNode*>::iterator it = filterdList.begin(); it != filterdList.end();
			++it)
	{
		if ((*it)->lowerBound(P) < minUpperBound)
		{
			fineFilterdList.push_back((*it));
			filterdPrims.push_back((*it)->poly);
		}
	}

	return filterdPrims;
}

std::vector<SphereNode*> SphereTree::getFilteredSpheres(UT_Vector3 P)
{
	minUpperBound = 100000;
	filterdList.clear();

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

	for (std::vector<core::SphereNode*>::iterator it = workingList.begin(); it != workingList.end();
			++it)
	{
		if ((*it) == NULL)
			continue;
		{
			double lowerBound = (*it)->lowerBound(P);
			if (lowerBound < minUpperBound)
			{
				distanceTest((*it), P);
			}
		}

	}

	std::vector<SphereNode*> fineFilterdList;
	std::vector<GEO_PrimPoly*> filterdPrims;
	for (std::vector<core::SphereNode*>::iterator it = filterdList.begin(); it != filterdList.end();
			++it)
	{
		if ((*it)->lowerBound(P) < minUpperBound)
		{
			fineFilterdList.push_back((*it));
			filterdPrims.push_back((*it)->poly);
		}
	}

	return fineFilterdList;
}

} /* namespace core */
