/*
 * Sphere.h
 *
 *  Created on: 17-Feb-2016
 *      Author: user
 */

#ifndef CORE_SPHERE_H_
#define CORE_SPHERE_H_

#include <UT/UT_Vector3.h>

namespace core
{

class Sphere
{
public:
	Sphere();
	virtual ~Sphere();
	double radius;
	UT_Vector3 pos;
};

} /* namespace core */

#endif /* CORE_SPHERE_H_ */
