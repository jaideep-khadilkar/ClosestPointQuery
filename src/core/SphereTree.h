#ifndef CORE_SPHERETREE_H_
#define CORE_SPHERETREE_H_

#include "GU/GU_Detail.h"
#include "GEO/GEO_PrimPoly.h"
#include "SphereNode.h"

namespace core
{

class SphereTree
{
public:
	SphereTree();
	virtual ~SphereTree();
	void initialize(const GU_Detail* inputMesh, double threshold);
	const std::vector<SphereNode*>& getCompleteNodeList() const;
	void getFilteredPrimList(UT_Vector3 P, std::vector<SphereNode*>& fineFilterdList,
			std::vector<GEO_PrimPoly*>& filterdPrims);

	int getHighestLevel() const
	{
		return highestLevel;
	}

private:
	void distanceTest(SphereNode* parent, UT_Vector3 P, double& minUpperBound,
			std::vector<SphereNode*>& filterdList);

	std::vector<SphereNode*> completeNodeList;
	std::vector<SphereNode*> leafNodes;
	std::vector<SphereNode*> workingList;
	const GU_Detail* mesh;
	int highestLevel;

	void buildLeafNodes();
	void buildTree(double threshold);
};

} /* namespace core */

#endif /* CORE_SPHERETREE_H_ */
