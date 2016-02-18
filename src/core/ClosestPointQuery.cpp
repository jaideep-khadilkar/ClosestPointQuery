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
	tree.initialize(mesh,5);
}

ClosestPointQuery::~ClosestPointQuery()
{
	// TODO Auto-generated destructor stub
}

double clamp(double val, double min, double max)
{
	if (val < min)
		val = min;
	if (val > max)
		val = max;
	return val;
}

UT_Vector3 ClosestPointQuery::getProjP(int primNum, const UT_Vector3& P)
{
	GEO_PrimPoly* poly = (GEO_PrimPoly*) (mesh->getPrimitiveByIndex(primNum));
	UT_Vector3 p0 = poly->getPos3(0);
	UT_Vector3 p1 = poly->getPos3(1);
	UT_Vector3 p2 = poly->getPos3(2);
	UT_Vector3 edge0 = p1 - p0;
	UT_Vector3 edge1 = p2 - p0;
	UT_Vector3 v0 = p0 - P;
	double a = edge0.dot(edge0);
	double b = edge0.dot(edge1);
	double c = edge1.dot(edge1);
	double d = edge0.dot(v0);
	double e = edge1.dot(v0);
	double det = a * c - b * b;
	double s = b * e - c * d;
	double t = b * d - a * e;
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
			double invDet = 1.f / det;
			s *= invDet;
			t *= invDet;
		}
	}
	else
	{
		if (s < 0.f)
		{
			double tmp0 = b + d;
			double tmp1 = c + e;
			if (tmp1 > tmp0)
			{
				double numer = tmp1 - tmp0;
				double denom = a - 2 * b + c;
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
				double numer = c + e - b - d;
				double denom = a - 2 * b + c;
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
			double numer = c + e - b - d;
			double denom = a - 2 * b + c;
			s = clamp(numer / denom, 0.f, 1.f);
			t = 1.f - s;
		}
	}
	UT_Vector3 projP = p0 + s * edge0 + t * edge1;
	return projP;
}

UT_Vector3 ClosestPointQuery::getClosestPoint(UT_Vector3 P, double maxDist)
{

	double minDist = 10000;
	int closestPrimNum = 0;
	int numPrims = mesh->getNumPrimitives();

	for (int primNum = 0; primNum < numPrims; primNum++)
	{
		UT_Vector3 projP = getProjP(primNum, P);
		double dist = projP.distance(P);
		if(dist<minDist)
		{
			minDist = dist;
			closestPrimNum = primNum;
		}
	}


	tree.getFilteredPrims(P);



	return getProjP(closestPrimNum, P);

}

} /* namespace core */
