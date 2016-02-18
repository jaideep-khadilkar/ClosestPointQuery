/*
 * SphereTree.h
 *
 *  Created on: 18-Feb-2016
 *      Author: user
 */

#ifndef CORE_SPHERETREE_H_
#define CORE_SPHERETREE_H_

#include "GU/GU_Detail.h"
#include "SphereNode.h"

namespace core
{

class SphereTree
{
public:
	SphereTree(const GU_Detail* mesh);
	virtual ~SphereTree();
	const std::vector<UT_BoundingSphere>& getSphereVec() const;
	void setSphereVec(const std::vector<UT_BoundingSphere>& sphereVec);

private:
	std::vector<UT_BoundingSphere> sphereVec;
	std::vector<SphereNode*> leafNodes;
	std::vector<SphereNode*> workingList;
	const GU_Detail* mesh;

	void buildLeafNodes();
	void buildTree();
};

} /* namespace core */

#endif /* CORE_SPHERETREE_H_ */
