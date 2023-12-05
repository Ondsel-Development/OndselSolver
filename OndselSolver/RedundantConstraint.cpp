/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "RedundantConstraint.h"

using namespace MbD;

void RedundantConstraint::removeRedundantConstraints(std::shared_ptr<std::vector<int>> redundantEqnNos)
{
	(void)redundantEqnNos;
}

bool RedundantConstraint::isRedundant()
{
	return true;
}

std::string RedundantConstraint::classname()
{
	auto str = Item::classname() + "->" + constraint->classname();
	return str;
}

ConstraintType RedundantConstraint::type()
{
	return redundant;
}

void MbD::RedundantConstraint::fillqsuddotlam(FColDsptr col)
{
	(void)col;
}

void RedundantConstraint::fillqsulam(FColDsptr col)
{
	(void)col;
}

void RedundantConstraint::postInput()
{
}

void RedundantConstraint::prePosIC()
{
}

void RedundantConstraint::fillEssenConstraints(std::shared_ptr<Constraint> sptr, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> essenConstraints)
{
	(void)sptr;(void)essenConstraints;
}

void RedundantConstraint::fillDispConstraints(std::shared_ptr<Constraint> sptr, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> dispConstraints)
{
	(void)sptr;(void)dispConstraints;
}

void RedundantConstraint::fillPerpenConstraints(std::shared_ptr<Constraint> sptr, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> perpenConstraints)
{
	(void)sptr;(void)perpenConstraints;
}

void RedundantConstraint::fillConstraints(std::shared_ptr<Constraint> sptr, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> redunConstraints)
{
	(void)sptr;(void)redunConstraints;
}

void RedundantConstraint::fillRedundantConstraints(std::shared_ptr<Constraint> sptr, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> redunConstraints)
{
	(void)redunConstraints;
	redunConstraints->push_back(sptr);
}

void RedundantConstraint::setqsulam(FColDsptr col)
{
	(void)col;
}

void RedundantConstraint::setqsudotlam(FColDsptr col)
{
	(void)col;
}

void RedundantConstraint::fillPosICError(FColDsptr col)
{
	(void)col;
}

void RedundantConstraint::fillPosKineError(FColDsptr col)
{
	(void)col;
}

void RedundantConstraint::fillPosKineJacob(SpMatDsptr mat)
{
	(void)mat;
}

void RedundantConstraint::preVelIC()
{
}

void RedundantConstraint::preAccIC()
{
}

void RedundantConstraint::fillAccICIterError(FColDsptr col)
{
	(void)col;
}

void RedundantConstraint::setqsuddotlam(FColDsptr col)
{
	(void)col;
}

void RedundantConstraint::discontinuityAtaddTypeTo(double t, std::shared_ptr<std::vector<DiscontinuityType>> disconTypes)
{
	(void)t;(void)disconTypes;
	//"Reactivate all constraints."
	assert(false);
	//| newSelf |
	//newSelf : = self constraint.
	//newSelf discontinuityAt : tstartNew addTypeTo : collection.
	//self become : newSelf
}
