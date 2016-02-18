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

//	double threshold = 3;

	int counter = 10000;
	size_t size = workingList.size();
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
//				std::cout << "Can Merge !" << std::endl;
//				std::cout << "iA : " << iA << std::endl;
//				std::cout << "iB : " << iB << std::endl;
				SphereNode* mergedNode = nodeA->merge(nodeB, sphereAB);
				highestLevel = std::max(highestLevel, mergedNode->level);
//				std::cout << "Level : " << mergedNode->level << std::endl;
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

const std::vector<GEO_PrimPoly*>& SphereTree::getFilteredPrims(UT_Vector3 P)
{
	double minUpperBound = 100000;
	for (std::vector<core::SphereNode*>::iterator it = completeNodeList.begin();
			it != completeNodeList.end(); ++it)
	{
		if ((*it)->level == highestLevel)
		{
			double upperBound = (*it)->upperBound(P);
			if (upperBound < minUpperBound)
				minUpperBound = upperBound;
		}
	}

	std::cout <<"minUpperBound : " << minUpperBound << std::endl;

	for (std::vector<core::SphereNode*>::iterator it = completeNodeList.begin();
			it != completeNodeList.end(); ++it)
	{
		if ((*it)->level == highestLevel)
		{
			double lowerBound = (*it)->lowerBound(P);
			if (lowerBound < minUpperBound)
			{
				std::cout << "Test this Sphere" << std::endl;
				(*it)->distanceTest(P);
			}
			else
			{
				std::cout << "DO NOT TEST" << std::endl;
			}
		}

	}

	std::vector<GEO_PrimPoly*> vec;
	return vec;
}

} /* namespace core */

