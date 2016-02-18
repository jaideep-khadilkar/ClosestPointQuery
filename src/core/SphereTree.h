/*
 * SphereTree.h
 *
 *  Created on: 18-Feb-2016
 *      Author: user
 */

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
	std::vector<GEO_PrimPoly*> getFilteredPrims(UT_Vector3 P);
	std::vector<SphereNode*> getFilteredSpheres(UT_Vector3 P);

	int getHighestLevel() const
	{
		return highestLevel;
	}

private:
	void distanceTest(SphereNode* parent,UT_Vector3 P);

	std::vector<SphereNode*> completeNodeList;
	std::vector<SphereNode*> leafNodes;
	std::vector<SphereNode*> workingList;
	std::vector<SphereNode*> filterdList;
	const GU_Detail* mesh;
	int highestLevel;
	double minUpperBound;

	void buildLeafNodes();
	void buildTree(double threshold);
};

} /* namespace core */

#endif /* CORE_SPHERETREE_H_ */
