/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispCompIecJecKeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

DispCompIecJecKeqc::DispCompIecJecKeqc()
{
}

DispCompIecJecKeqc::DispCompIecJecKeqc(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, int axisk) : DispCompIecJecKec(frmi, frmj, frmk, axisk)
{
}

void DispCompIecJecKeqc::initialize()
{
    priIeJeKepEK = std::make_shared<FullRow<double>>(4);
    ppriIeJeKepEKpEK = std::make_shared<FullMatrixDouble>(4, 4);
}

void DispCompIecJecKeqc::initializeGlobally()
{
    ppAjOKepEKpEK = std::static_pointer_cast<EndFrameqc>(efrmK)->ppAjOepEpE(axisK);
}

void DispCompIecJecKeqc::calcPostDynCorrectorIteration()
{
	auto frmIqc = std::static_pointer_cast<EndFrameqc>(frmI);
	auto frmJqc = std::static_pointer_cast<EndFrameqc>(frmJ);
	auto efrmKqc = std::static_pointer_cast<EndFrameqc>(efrmK);
	aAjOKe = efrmKqc->aAjOe(axisK);
	rIeJeO = frmJqc->rOeO->minusFullColumn(frmIqc->rOeO);
	riIeJeKe = aAjOKe->dotVec(rIeJeO);
	pAjOKepEKT = efrmKqc->pAjOepET(axisK);
	ppAjOKepEKpEK = efrmKqc->ppAjOepEpE(axisK);
	for (int i = 0; i < 4; i++)
	{
		priIeJeKepEK->at(i) = ((pAjOKepEKT->at(i))->dot(rIeJeO));
		auto& ppAjOKepEKipEK = ppAjOKepEKpEK->at(i);
		auto& ppriIeJeKepEKipEK = ppriIeJeKepEKpEK->at(i);
		ppriIeJeKepEKipEK->at(i) = ((ppAjOKepEKipEK->at(i))->dotVec(rIeJeO));
		for (int j = i + 1; j < 4; j++)
		{
			auto ppriIeJeKepEKipEKj = (ppAjOKepEKipEK->at(i))->dotVec(rIeJeO);
			ppriIeJeKepEKipEK->at(j) = ppriIeJeKepEKipEKj;
			ppriIeJeKepEKpEK->at(j)->at(i) = ppriIeJeKepEKipEKj;
		}
	}
}

FMatDsptr DispCompIecJecKeqc::ppvaluepEKpEK()
{
    return ppriIeJeKepEKpEK;
}

FRowDsptr MbD::DispCompIecJecKeqc::pvaluepEK()
{
	return priIeJeKepEK;
}
