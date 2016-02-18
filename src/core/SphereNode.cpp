/*
 * Sphere.cpp
 *
 *  Created on: 17-Feb-2016
 *      Author: user
 */

#include "SphereNode.h"

namespace core
{

SphereNode::SphereNode(UT_BoundingSphere sphere, GEO_PrimPoly* poly) :
		sphere(sphere), poly(poly)
{
	parent = NULL;
	child1 = NULL;
	child2 = NULL;
}

SphereNode::~SphereNode()
{
	// TODO Auto-generated destructor stub
}

SphereNode* SphereNode::merge(SphereNode* sphereNodeB, UT_BoundingSphere sphereAB)
{
	SphereNode* mergedNode = new SphereNode(sphereAB, NULL);
	mergedNode->child1 = this;
	mergedNode->child2 = sphereNodeB;
	this->parent = mergedNode;
	sphereNodeB->parent = mergedNode;
	return mergedNode;
}

bool SphereNode::canMerge(SphereNode* sphereNodeB, double threshold, UT_BoundingSphere& sphereAB)
{
	double rA = sphere.getRadius();
	double rB = sphereNodeB->sphere.getRadius();
	sphereAB.addSphere(sphere);
	sphereAB.addSphere(sphereNodeB->sphere);
	double rAB = sphereAB.getRadius();
	double dS = (rAB * rAB * rAB) / ((rA * rA * rA) + (rB * rB * rB));
	return (dS < threshold);
}

} /* namespace core */
