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

}


SphereTree::~SphereTree()
{
	for (std::vector<SphereNode*>::iterator it = leafNodes.begin(); it != leafNodes.end();
			++it)
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

