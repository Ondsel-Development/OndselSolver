/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include "MBDynElement.h"

namespace MbD {
	class MBDynDrive : public MBDynElement
	{
	public:
        void parseMBDyn(std::vector<std::string>& lines) override;
        void parseMBDyn(std::string line);
		void readFunction(std::vector<std::string>& args);
		void createASMT() override;

        std::string driveString, driveName, formula;

	};
}

