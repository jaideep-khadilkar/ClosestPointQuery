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
		SphereNode* sphereNode = new SphereNode(boundingSphere, poly);
		leafNodes.push_back(sphereNode);
		sphereVec.push_back(boundingSphere);
	}
}

void SphereTree::buildTree()
{

	workingList = leafNodes;

	double threshold = 1;

	for (std::vector<SphereNode*>::iterator itA = workingList.begin(); itA != workingList.end();
			++itA)
	{
		if (*itA == NULL)
			continue;
		for (std::vector<SphereNode*>::iterator itB = workingList.begin(); itB != workingList.end();
				++itB)
		{
			if (*itB == NULL)
				continue;
			if (*itA == *itB)
				continue;
//			UT_BoundingSphere sphereAB;
//			if ((*itA)->canMerge(*itB, threshold, sphereAB))
//			{
//				std::cout << "Can Merge !" << std::endl;
//				SphereNode* mergedNode = (*itA)->merge(*itB, sphereAB);
////				workingList.push_back(mergedNode);
//				*itA = NULL;
//				*itB = NULL;
//			}
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

const std::vector<UT_BoundingSphere>& SphereTree::getSphereVec() const
{
	return sphereVec;
}

void SphereTree::setSphereVec(const std::vector<UT_BoundingSphere>& sphereVec)
{
	this->sphereVec = sphereVec;
}

} /* namespace core */

