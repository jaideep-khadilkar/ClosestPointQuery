/*
 * SphereTree.cpp
 *
 *  Created on: 18-Feb-2016
 *      Author: user
 */

#include "SphereNodeTree.h"

namespace core
{

SphereTree::SphereTree(const GU_Detail* mesh) :
		mesh(mesh)
{
	for (int primNum = 0; primNum < mesh->getNumPrimitives(); primNum++)
	{
		GEO_PrimPoly* poly = (GEO_PrimPoly*) mesh->getPrimitiveByIndex(primNum);

		UT_BoundingSphere boundingSphere;
		boundingSphere.addPoint(poly->getPos3(0));
		boundingSphere.addPoint(poly->getPos3(1));
		boundingSphere.addPoint(poly->getPos3(2));

		sphereVec.push_back(boundingSphere);
	}
}

SphereTree::~SphereTree()
{
	// TODO Auto-generated destructor stub
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

