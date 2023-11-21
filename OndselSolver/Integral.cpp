#include "Integral.h"

using namespace MbD;

MbD::Integral::Integral(Symsptr var, Symsptr integrand)
{
    (void) var; // to suppress compiler warning of unused parameters
    (void) integrand; // to suppress compiler warning of unused parameters
	assert(false);
}

void MbD::Integral::arguments(Symsptr args)
{
	auto arguments = args->getTerms();
	xx = arguments->at(0);
	integrand = arguments->at(1);
	expression = integrand->integrateWRT(xx);
}

Symsptr MbD::Integral::expandUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>> set)
{
    (void) sptr; // to suppress compiler warning of unused parameters
	auto expand = expression->expandUntil(expression, set);
	auto answer = std::make_shared<Integral>();
	answer->xx = xx;
	answer->expression = expand;
	answer->integrand = integrand;
	answer->integrationConstant = integrationConstant;
	return answer;
}

Symsptr MbD::Integral::simplifyUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>> set)
{
    (void) sptr; // to suppress compiler warning of unused parameters
	auto simple = expression->simplifyUntil(expression, set);
	auto answer = std::make_shared<Integral>();
	answer->xx = xx;
	answer->expression = simple;
	answer->integrand = integrand;
	answer->integrationConstant = integrationConstant;
	return answer;
}

std::ostream& MbD::Integral::printOn(std::ostream& s) const
{
	s << *expression << " + ";
	s << *integrationConstant;
	return s;
}
