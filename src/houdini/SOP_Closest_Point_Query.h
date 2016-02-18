#ifndef __SOP_Closest_Point_Query_h__
#define __SOP_Closest_Point_Query_h__


#include <SOP/SOP_Node.h>

#define INT_PARM(name, idx, vidx, t)	\
	    return evalInt(name, &myOffsets[idx], vidx, t);
#define FLT_PARM(name, idx, vidx, t)	\
	    return evalFloat(name, &myOffsets[idx], vidx, t);

class SOP_Closest_Point_Query: public SOP_Node
{
public:
	SOP_Closest_Point_Query(OP_Network *net, const char *name,
			OP_Operator *op);
	virtual ~SOP_Closest_Point_Query();
	static PRM_Template myTemplateList[];
	static OP_Node *myConstructor(OP_Network*, const char *, OP_Operator *);
protected:
	virtual OP_ERROR cookMySop(OP_Context &context);
	float THRESHOLD()
	{
		return evalFloat("threshold", 0, 0);
	}
};
#endif
