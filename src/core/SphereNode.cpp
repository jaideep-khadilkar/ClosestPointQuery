/*
 * Sphere.cpp
 *
 *  Created on: 17-Feb-2016
 *      Author: user
 */

#include "SphereNode.h"

namespace core
{

SphereNode::SphereNode(UT_BoundingSphere sphere, GEO_PrimPoly* poly, int level) :
		sphere(sphere), poly(poly), level(level)
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
	SphereNode* mergedNode = new SphereNode(sphereAB, NULL,
			std::max(this->level, sphereNodeB->level) + 1);
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

void SphereNode::distanceTest(UT_Vector3 P)
{
	if (level == 0)
		std::cout << "TEST THIS NODE" << std::endl;
	else
	{
		double minUpperBound = std::min(child1->upperBound(P), child2->upperBound(P));
		if (minUpperBound > child1->lowerBound(P))
			child1->distanceTest(P);
		else
			child2->distanceTest(P);
	}
}

double SphereNode::lowerBound(UT_Vector3 P)
{
	UT_Vector3 center = sphere.getCenter();
	double upperBound = (P - center).length() - sphere.getRadius();
	return upperBound;
}

double SphereNode::upperBound(UT_Vector3 P)
{
	UT_Vector3 center = sphere.getCenter();
	double upperBound = (P - center).length() + sphere.getRadius();
	return upperBound;
}

} /* namespace core */
