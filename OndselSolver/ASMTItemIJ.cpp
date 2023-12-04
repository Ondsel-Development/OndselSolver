/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>	

#include "ASMTItemIJ.h"

MbD::ASMTItemIJ::ASMTItemIJ()
{
	fxs = std::make_shared<FullRow<double>>();
	fys = std::make_shared<FullRow<double>>();
	fzs = std::make_shared<FullRow<double>>();
	txs = std::make_shared<FullRow<double>>();
	tys = std::make_shared<FullRow<double>>();
	tzs = std::make_shared<FullRow<double>>();
}

void MbD::ASMTItemIJ::initialize()
{
	fxs = std::make_shared<FullRow<double>>();
	fys = std::make_shared<FullRow<double>>();
	fzs = std::make_shared<FullRow<double>>();
	txs = std::make_shared<FullRow<double>>();
	tys = std::make_shared<FullRow<double>>();
	tzs = std::make_shared<FullRow<double>>();
}

void MbD::ASMTItemIJ::setMarkerI(std::string mkrI)
{
	markerI = mkrI;
}

void MbD::ASMTItemIJ::setMarkerJ(std::string mkrJ)
{
	markerJ = mkrJ;
}

void MbD::ASMTItemIJ::readMarkerI(std::vector<std::string>& lines)
{
	assert(lines[0].find("MarkerI") != std::string::npos);
	lines.erase(lines.begin());
	markerI = readString(lines[0]);
	lines.erase(lines.begin());
}

void MbD::ASMTItemIJ::readMarkerJ(std::vector<std::string>& lines)
{
	assert(lines[0].find("MarkerJ") != std::string::npos);
	lines.erase(lines.begin());
	markerJ = readString(lines[0]);
	lines.erase(lines.begin());
}

void MbD::ASMTItemIJ::readFXonIs(std::vector<std::string>& lines)
{
	std::string str = lines[0];
	readDoublesInto(str, "FXonI", infxs);
	lines.erase(lines.begin());
}

void MbD::ASMTItemIJ::readFYonIs(std::vector<std::string>& lines)
{
	std::string str = lines[0];
	readDoublesInto(str, "FYonI", infys);
	lines.erase(lines.begin());
}

void MbD::ASMTItemIJ::readFZonIs(std::vector<std::string>& lines)
{
	std::string str = lines[0];
	readDoublesInto(str, "FZonI", infzs);
	lines.erase(lines.begin());
}

void MbD::ASMTItemIJ::readTXonIs(std::vector<std::string>& lines)
{
	std::string str = lines[0];
	readDoublesInto(str, "TXonI", intxs);
	lines.erase(lines.begin());
}

void MbD::ASMTItemIJ::readTYonIs(std::vector<std::string>& lines)
{
	std::string str = lines[0];
	readDoublesInto(str, "TYonI", intys);
	lines.erase(lines.begin());
}

void MbD::ASMTItemIJ::readTZonIs(std::vector<std::string>& lines)
{
	std::string str = lines[0];
	readDoublesInto(str, "TZonI", intzs);
	lines.erase(lines.begin());
}

void MbD::ASMTItemIJ::storeOnLevel(std::ofstream& os, int level)
{
	storeOnLevelString(os, level + 1, "MarkerI");
	storeOnLevelString(os, level + 2, markerI);
	storeOnLevelString(os, level + 1, "MarkerJ");
	storeOnLevelString(os, level + 2, markerJ);
}

void MbD::ASMTItemIJ::storeOnTimeSeries(std::ofstream& os)
{
	os << "FXonI\t";
	for (double i : *fxs)
	{
		os << i << '\t';
	}
	os << std::endl;
	os << "FYonI\t";
	for (double i : *fys)
	{
		os << i << '\t';
	}
	os << std::endl;
	os << "FZonI\t";
	for (double i : *fzs)
	{
		os << i << '\t';
	}
	os << std::endl;
	os << "TXonI\t";
	for (double i : *txs)
	{
		os << i << '\t';
	}
	os << std::endl;
	os << "TYonI\t";
	for (double i : *tys)
	{
		os << i << '\t';
	}
	os << std::endl;
	os << "TZonI\t";
	for (double i : *tzs)
	{
		os << i << '\t';
	}
	os << std::endl;
}
