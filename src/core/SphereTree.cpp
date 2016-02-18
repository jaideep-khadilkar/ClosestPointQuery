/*
 * SphereTree.cpp
 *
 *  Created on: 18-Feb-2016
 *      Author: user
 */

#include "SphereTree.h"

namespace core
{

SphereTree::SphereTree(const GU_Detail* mesh) :
		mesh(mesh)
{
	buildLeafNodes();
	buildTree();
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
		allSphereList.push_back(sphereNode);
	}
}

void SphereTree::buildTree()
{

	workingList = leafNodes;

	double threshold = 2;

	int counter = 1000;
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
				continue;
			if (nodeA->canMerge(nodeB, threshold, sphereAB))
			{
				std::cout << "Can Merge !" << std::endl;
				std::cout << "iA : " << iA << std::endl;
				std::cout << "iB : " << iB << std::endl;
				SphereNode* mergedNode = nodeA->merge(nodeB, sphereAB);
				std::cout << "Level : " << mergedNode->level << std::endl;
				allSphereList.push_back(mergedNode);
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

const std::vector<SphereNode*>& SphereTree::getSphereVec() const
{
	return allSphereList;
}

void SphereTree::setSphereVec(const std::vector<SphereNode*>& sphereVec)
{
	this->allSphereList = sphereVec;
}

} /* namespace core */

