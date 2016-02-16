#include "SOP_Closest_Point_Query.h"

#include <UT/UT_DSOVersion.h>
#include <PRM/PRM_Include.h>
#include <OP/OP_Director.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>
#include <OP/OP_AutoLockInputs.h>
#include <iostream>

void newSopOperator(OP_OperatorTable *table)
{
	table->addOperator(
			new OP_Operator("ns_create_sim", "NS Create Sim", SOP_Closest_Point_Query::myConstructor,
					SOP_Closest_Point_Query::myTemplateList, 0, // Min required sources
					1,	// Maximum sources
					0));
}

static PRM_Name names[] =
{ PRM_Name("reset", "Reset Frame"), PRM_Name("subSteps", "Sub Steps"), PRM_Name("maxSubSteps",
		"Max Sub Steps"), PRM_Name("sim_time_scale", "Simulation Time Scale") };

static PRM_Default defaultSubSteps(1);
static PRM_Default defaultMaxSubSteps(200);

PRM_Template SOP_Closest_Point_Query::myTemplateList[] =
{ PRM_Template(PRM_INT, 1, &names[0], PRMoneDefaults), PRM_Template(PRM_INT_J, 1, &names[1],
		&defaultSubSteps), PRM_Template(PRM_INT_J, 1, &names[2], &defaultMaxSubSteps), PRM_Template(
		PRM_FLT, 1, &names[3], PRMoneDefaults), PRM_Template(), };


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


	return error();
}
