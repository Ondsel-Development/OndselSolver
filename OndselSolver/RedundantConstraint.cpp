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
    (void) redundantEqnNos; // to suppress compiler warning of unused parameters
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
    (void) col; // to suppress compiler warning of unused parameters
}

void RedundantConstraint::fillqsulam(FColDsptr col)
{
    (void) col; // to suppress compiler warning of unused parameters
}

void RedundantConstraint::postInput()
{
}

void RedundantConstraint::prePosIC()
{
}

void RedundantConstraint::fillEssenConstraints(std::shared_ptr<Constraint> sptr, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> essenConstraints)
{
    (void) sptr; // to suppress compiler warning of unused parameters
    (void) essenConstraints; // to suppress compiler warning of unused parameters
}

void RedundantConstraint::fillDispConstraints(std::shared_ptr<Constraint> sptr, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> dispConstraints)
{
    (void) sptr; // to suppress compiler warning of unused parameters
    (void) dispConstraints; // to suppress compiler warning of unused parameters
}

void RedundantConstraint::fillPerpenConstraints(std::shared_ptr<Constraint> sptr, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> perpenConstraints)
{
    (void) sptr; // to suppress compiler warning of unused parameters
    (void) perpenConstraints; // to suppress compiler warning of unused parameters
}

void RedundantConstraint::fillConstraints(std::shared_ptr<Constraint> sptr, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> redunConstraints)
{
    (void) sptr; // to suppress compiler warning of unused parameters
    (void) redunConstraints; // to suppress compiler warning of unused parameters
}

void RedundantConstraint::fillRedundantConstraints(std::shared_ptr<Constraint> sptr, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> redunConstraints)
{
	redunConstraints->push_back(sptr);
}

void RedundantConstraint::setqsulam(FColDsptr col)
{
    (void) col; // to suppress compiler warning of unused parameters
}

void RedundantConstraint::setqsudotlam(FColDsptr col)
{
    (void) col; // to suppress compiler warning of unused parameters
}

void RedundantConstraint::fillPosICError(FColDsptr col)
{
    (void) col; // to suppress compiler warning of unused parameters
}

void RedundantConstraint::fillPosKineError(FColDsptr col)
{
    (void) col; // to suppress compiler warning of unused parameters
}

void RedundantConstraint::fillPosKineJacob(SpMatDsptr mat)
{
    (void) mat; // to suppress compiler warning of unused parameters
}

void RedundantConstraint::preVelIC()
{
}

void RedundantConstraint::preAccIC()
{
}

void RedundantConstraint::fillAccICIterError(FColDsptr col)
{
    (void) col; // to suppress compiler warning of unused parameters
}

void RedundantConstraint::setqsuddotlam(FColDsptr col)
{
}

void RedundantConstraint::discontinuityAtaddTypeTo(double t, std::shared_ptr<std::vector<DiscontinuityType>> disconTypes)
{
	//"Reactivate all constraints."
    (void) t; // to suppress compiler warning of unused parameters
    (void) disconTypes; // to suppress compiler warning of unused parameters
	assert(false);
	//| newSelf |
	//newSelf : = self constraint.
	//newSelf discontinuityAt : tstartNew addTypeTo : collection.
	//self become : newSelf
}
