#include "SOP_Sphere_Tree.h"

#include <UT/UT_DSOVersion.h>
#include <PRM/PRM_Include.h>
#include <OP/OP_Director.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>
#include <OP/OP_AutoLockInputs.h>
#include <iostream>

#include "GEO/GEO_PrimPoly.h"
#include "GU/GU_PrimSphere.h"
#include "UT/UT_Matrix3.h"

#include "../core/SphereTree.h"

void newSopOperator(OP_OperatorTable *table)
{
	table->addOperator(
			new OP_Operator("sphere_tree", "Sphere Tree", SOP_Sphere_Tree::myConstructor,
					SOP_Sphere_Tree::myTemplateList, 1, // Min required sources
					1,	// Maximum sources
					0));
}

static PRM_Name names[] =
{ PRM_Name("level", "Level"), PRM_Name("threshold", "Threshold") };

PRM_Template SOP_Sphere_Tree::myTemplateList[] =
{ PRM_Template(PRM_INT, 1, &names[0], PRMzeroDefaults), PRM_Template(PRM_INT, 1, &names[1],
		PRMoneDefaults), PRM_Template(), };

OP_Node *
SOP_Sphere_Tree::myConstructor(OP_Network *net, const char *name, OP_Operator *op)
{
	return new SOP_Sphere_Tree(net, name, op);
}

SOP_Sphere_Tree::SOP_Sphere_Tree(OP_Network *net, const char *name, OP_Operator *op) :
		SOP_Node(net, name, op)
{
}

SOP_Sphere_Tree::~SOP_Sphere_Tree()
{
}

OP_ERROR SOP_Sphere_Tree::cookMySop(OP_Context &context)
{

	OP_AutoLockInputs inputs(this);
	if (inputs.lock(context) >= UT_ERROR_ABORT)
		return error();

	gdp->clearAndDestroy();
	const GU_Detail* mesh = inputGeo(0);

	core::SphereTree tree;
	tree.initialize(mesh, THRESHOLD());
	std::vector<core::SphereNode*> completeNodeList = tree.getCompleteNodeList();

	for (std::vector<core::SphereNode*>::iterator it = completeNodeList.begin();
			it != completeNodeList.end(); ++it)
	{
		if ((*it)->level == LEVEL())
		{
			UT_BoundingSphere boundingSphere = (*it)->sphere;
			buildSphereFromBoundingSphere(boundingSphere);
		}
	}

	return error();
}

void SOP_Sphere_Tree::buildSphereFromBoundingSphere(UT_BoundingSphere boundingSphere)
{
	GA_Offset ptoff = gdp->appendPoint();
	gdp->setPos3(ptoff, boundingSphere.getCenter());
	GEO_PrimSphere* sphere = (GEO_PrimSphere*) GU_PrimSphere::build(GU_PrimSphereParms(gdp, ptoff));
	UT_Matrix3 mat;
	mat.identity();
	mat.scale(boundingSphere.getRadius(), boundingSphere.getRadius(), boundingSphere.getRadius());
	sphere->setTransform(mat);
}
