#include "SOP_Closest_Point_Query.h"

#include <UT/UT_DSOVersion.h>
#include <PRM/PRM_Include.h>
#include <OP/OP_Director.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>
#include <OP/OP_AutoLockInputs.h>
#include <iostream>

#include "../core/ClosestPointQuery.h"

void newSopOperator(OP_OperatorTable *table)
{
	table->addOperator(
			new OP_Operator("closest_point_query", "Closest Point Query",
					SOP_Closest_Point_Query::myConstructor, SOP_Closest_Point_Query::myTemplateList,
					2, // Min required sources
					2,	// Maximum sources
					0));
}

static PRM_Name names[] =
{ PRM_Name("threshold", "Threshold") };

PRM_Template SOP_Closest_Point_Query::myTemplateList[] =
{ PRM_Template(PRM_FLT, 1, &names[0], PRMtenDefaults), PRM_Template(), };

OP_Node *
SOP_Closest_Point_Query::myConstructor(OP_Network *net, const char *name, OP_Operator *op)
{
	return new SOP_Closest_Point_Query(net, name, op);
}

SOP_Closest_Point_Query::SOP_Closest_Point_Query(OP_Network *net, const char *name, OP_Operator *op) :
		SOP_Node(net, name, op)
{
}

SOP_Closest_Point_Query::~SOP_Closest_Point_Query()
{
}

OP_ERROR SOP_Closest_Point_Query::cookMySop(OP_Context &context)
{

	OP_AutoLockInputs inputs(this);
	if (inputs.lock(context) >= UT_ERROR_ABORT)
		return error();

	duplicateSource(0, context);
	const GU_Detail* mesh = inputGeo(1);

	core::ClosestPointQuery query(mesh, THRESHOLD());

	GA_Offset ptoff;
	GA_Attribute* pscale = gdp->findPointAttribute("pscale");
	GA_ROHandleF pscale_handle(pscale);

	// For each point, find the closest point on the mesh.
	GA_FOR_ALL_PTOFF(gdp, ptoff)
	{
		UT_Vector3 pos = gdp->getPos3(ptoff);
		double maxRadius = DBL_MAX;
		if (pscale_handle.isValid())
		{
			maxRadius = pscale_handle.get(ptoff);
		}
		UT_Vector3 closest_point_pos = query(pos, maxRadius);
		gdp->setPos3(ptoff, closest_point_pos);
	}

	return error();
}
