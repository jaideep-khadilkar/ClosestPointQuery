/*
 * SphereTree.h
 *
 *  Created on: 18-Feb-2016
 *      Author: user
 */

#ifndef CORE_SPHERENODETREE_H_
#define CORE_SPHERENODETREE_H_

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
	const GU_Detail* mesh;

};

} /* namespace core */

#endif /* CORE_SPHERENODETREE_H_ */
