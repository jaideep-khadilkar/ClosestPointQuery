/*
 * ClosestPointQuery.h
 *
 *  Created on: 17-Feb-2016
 *      Author: user
 */

#ifndef CORE_CLOSESTPOINTQUERY_H_
#define CORE_CLOSESTPOINTQUERY_H_
#include "UT/UT_Vector3.h"

namespace core
{

class ClosestPointQuery
{
public:
	ClosestPointQuery();
	virtual ~ClosestPointQuery();
	UT_Vector3 getClosestPoint();
};

} /* namespace core */

#endif /* CORE_CLOSESTPOINTQUERY_H_ */
