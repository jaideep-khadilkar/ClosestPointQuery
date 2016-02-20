
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
	ClosestPointQuery(const GU_Detail* mesh, double threshold);
	virtual ~ClosestPointQuery();
	UT_Vector3 operator()(UT_Vector3 P, double maxDist);
private:
	const GU_Detail* mesh;
	SphereTree sphereTree;
	UT_Vector3 projectOntoTriangle(const UT_Vector3& P, GEO_PrimPoly* poly);
};

} /* namespace core */

#endif /* CORE_CLOSESTPOINTQUERY_H_ */
