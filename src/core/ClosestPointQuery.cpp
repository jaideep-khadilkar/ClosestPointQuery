/*
 * ClosestPointQuery.cpp
 *
 *  Created on: 17-Feb-2016
 *      Author: user
 */

#include "ClosestPointQuery.h"
#include "GEO/GEO_PrimPoly.h"

namespace core
{

ClosestPointQuery::ClosestPointQuery(const GU_Detail* mesh) :
		mesh(mesh)
{
	// TODO Auto-generated constructor stub

}

ClosestPointQuery::~ClosestPointQuery()
{
	// TODO Auto-generated destructor stub
}

float clamp(float val, float min, float max)
{
	if (val < min)
		val = min;
	if (val > max)
		val = max;
	return val;
}

UT_Vector3 ClosestPointQuery::getClosestPoint(UT_Vector3 P, double maxDist)
{
	int primNum = 0;




	GEO_PrimPoly* poly = (GEO_PrimPoly*) mesh->getPrimitiveByIndex(primNum);

	UT_Vector3 p0 = poly->getPos3(0);
	UT_Vector3 p1 = poly->getPos3(1);
	UT_Vector3 p2 = poly->getPos3(2);

	UT_Vector3 edge0 = p1 - p0;
	UT_Vector3 edge1 = p2 - p0;
	UT_Vector3 v0 = p0 - P;

	float a = edge0.dot(edge0);
	float b = edge0.dot(edge1);
	float c = edge1.dot(edge1);
	float d = edge0.dot(v0);
	float e = edge1.dot(v0);

	float det = a * c - b * b;
	float s = b * e - c * d;
	float t = b * d - a * e;

	if (s + t < det)
	{
		if (s < 0.f)
		{
			if (t < 0.f)
			{
				if (d < 0.f)
				{
					s = clamp(-d / a, 0.f, 1.f);
					t = 0.f;
				}
				else
				{
					s = 0.f;
					t = clamp(-e / c, 0.f, 1.f);
				}
			}
			else
			{
				s = 0.f;
				t = clamp(-e / c, 0.f, 1.f);
			}
		}
		else if (t < 0.f)
		{
			s = clamp(-d / a, 0.f, 1.f);
			t = 0.f;
		}
		else
		{
			float invDet = 1.f / det;
			s *= invDet;
			t *= invDet;
		}
	}
	else
	{
		if (s < 0.f)
		{
			float tmp0 = b + d;
			float tmp1 = c + e;
			if (tmp1 > tmp0)
			{
				float numer = tmp1 - tmp0;
				float denom = a - 2 * b + c;
				s = clamp(numer / denom, 0.f, 1.f);
				t = 1 - s;
			}
			else
			{
				t = clamp(-e / c, 0.f, 1.f);
				s = 0.f;
			}
		}
		else if (t < 0.f)
		{
			if (a + d > b + e)
			{
				float numer = c + e - b - d;
				float denom = a - 2 * b + c;
				s = clamp(numer / denom, 0.f, 1.f);
				t = 1 - s;
			}
			else
			{
				s = clamp(-e / c, 0.f, 1.f);
				t = 0.f;
			}
		}
		else
		{
			float numer = c + e - b - d;
			float denom = a - 2 * b + c;
			s = clamp(numer / denom, 0.f, 1.f);
			t = 1.f - s;
		}
	}

	UT_Vector3 projP = p0 + s * edge0 + t * edge1;


	return projP;

}

} /* namespace core */
