#ifndef __SOP_Sphere_Tree_h__
#define __SOP_Sphere_Tree_h__


#include <SOP/SOP_Node.h>
#include "UT/UT_BoundingSphere.h"

#define INT_PARM(name, idx, vidx, t)	\
	    return evalInt(name, &myOffsets[idx], vidx, t);
#define FLT_PARM(name, idx, vidx, t)	\
	    return evalFloat(name, &myOffsets[idx], vidx, t);

class SOP_Sphere_Tree: public SOP_Node
{
public:
	SOP_Sphere_Tree(OP_Network *net, const char *name,
			OP_Operator *op);
	virtual ~SOP_Sphere_Tree();
	static PRM_Template myTemplateList[];
	static OP_Node *myConstructor(OP_Network*, const char *, OP_Operator *);
protected:
	virtual OP_ERROR cookMySop(OP_Context &context);
private:
	void buildSphereFromBoundingSphere(UT_BoundingSphere boundingSphere);
};
#endif
