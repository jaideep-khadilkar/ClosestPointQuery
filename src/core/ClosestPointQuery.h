/*
 * ClosestPointQuery.h
 *
 *  Created on: 17-Feb-2016
 *      Author: user
 */

#ifndef CORE_CLOSESTPOINTQUERY_H_
#define CORE_CLOSESTPOINTQUERY_H_
#include "UT/UT_Vector3.h"
#include "GU/GU_Detail.h"
#include "SphereTree.h"

namespace core
{

class ClosestPointQuery
{
public:
	ClosestPointQuery(const GU_Detail* mesh,double threshold);
	virtual ~ClosestPointQuery();
	UT_Vector3 getClosestPoint(UT_Vector3 P, double maxDist);
private:
	const GU_Detail* mesh;
	SphereTree tree;
	UT_Vector3 getProjP(GEO_PrimPoly* poly, const UT_Vector3& P);
};

} /* namespace core */

#endif /* CORE_CLOSESTPOINTQUERY_H_ */
