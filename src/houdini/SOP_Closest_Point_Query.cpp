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
			new OP_Operator("closest_point_query", "Closest Point Query", SOP_Closest_Point_Query::myConstructor,
					SOP_Closest_Point_Query::myTemplateList, 2, // Min required sources
					2,	// Maximum sources
					0));
}

PRM_Template SOP_Closest_Point_Query::myTemplateList[] =
{ PRM_Template(), };


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

	core::ClosestPointQuery query;
	std::cout << query.getClosestPoint() << std::endl;

	return error();
}
