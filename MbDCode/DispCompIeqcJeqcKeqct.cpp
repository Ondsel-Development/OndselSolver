#include "DispCompIeqcJeqcKeqct.h"
#include "EndFrameqc.h"
#include "EndFrameqct.h"

using namespace MbD;

MbD::DispCompIeqcJeqcKeqct::DispCompIeqcJeqcKeqct()
{
}

MbD::DispCompIeqcJeqcKeqct::DispCompIeqcJeqcKeqct(EndFrmcptr frmi, EndFrmcptr frmj, EndFrmcptr frmk, int axisk) : DispCompIeqcJeqcKeqc(frmi, frmj, frmk, axisk)
{
}

void MbD::DispCompIeqcJeqcKeqct::initialize()
{
	DispCompIeqcJeqcKeqc::initialize();
	ppriIeJeKepXIpt = std::make_shared<FullRow<double>>(3);
	ppriIeJeKepEIpt = std::make_shared<FullRow<double>>(4);
	ppriIeJeKepXJpt = std::make_shared<FullRow<double>>(3);
	ppriIeJeKepEJpt = std::make_shared<FullRow<double>>(4);
	ppriIeJeKepEKpt = std::make_shared<FullRow<double>>(4);
}

void MbD::DispCompIeqcJeqcKeqct::calcPostDynCorrectorIteration()
{
	//"ppAjOIepEKpEK is not longer constant and must be set before any calculation."
	auto efrmKqc = std::static_pointer_cast<EndFrameqc>(efrmK);
	ppAjOKepEKpEK = efrmKqc->ppAjOepEpE(axisK);
	DispCompIeqcJeqcKeqc::calcPostDynCorrectorIteration();
}

void MbD::DispCompIeqcJeqcKeqct::preVelIC()
{
	Item::preVelIC();
	auto pAjOKept = std::static_pointer_cast<EndFrameqct>(efrmK)->pAjOept(axisK);
	priIeJeKept = pAjOKept->dot(rIeJeO);
}

double MbD::DispCompIeqcJeqcKeqct::pvaluept()
{
	return priIeJeKept;
}
