/*
 * Sphere.h
 *
 *  Created on: 17-Feb-2016
 *      Author: user
 */

#ifndef CORE_SPHERENODE_H_
#define CORE_SPHERENODE_H_

#include <UT/UT_Vector3.h>
#include <GEO/GEO_PrimPoly.h>
#include <UT/UT_BoundingSphere.h>

/*
 * SphereNode is the part of the SphreTree tree structure.
 * The data it stores is the minimum bounding sphere and corresponding link to the triangle.
 */

namespace core
{

class SphereNode
{
public:
	SphereNode(UT_BoundingSphere sphere, GEO_PrimPoly* poly,int level);
	virtual ~SphereNode();
	SphereNode* doMerge(SphereNode* sphereNodeB, UT_BoundingSphere sphereAB);
	bool canItMerge(SphereNode* sphereNodeB, double threshold, UT_BoundingSphere& sphereAB);
	double lowerBound(UT_Vector3 P);
	double upperBound(UT_Vector3 P);

	UT_BoundingSphere sphere;
	SphereNode* child1;
	SphereNode* child2;
	GEO_PrimPoly* poly;
	int level;
};

} /* namespace core */

#endif /* CORE_SPHERENODE_H_ */
