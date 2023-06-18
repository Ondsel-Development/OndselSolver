#include <string>

#include "KineIntegrator.h"
#include "SystemSolver.h"

using namespace MbD;

void MbD::KineIntegrator::preRun()
{
	std::string str = "MbD: Starting kinematic analysis.";
	system->logString(str);
	QuasiIntegrator::preRun();
}

void MbD::KineIntegrator::runInitialConditionTypeSolution()
{
	system->runPosKine();
	system->runVelKine();
	system->runAccKine();
}
