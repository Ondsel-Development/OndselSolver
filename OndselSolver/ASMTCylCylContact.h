/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ASMTContact.h"

namespace MbD {
	class ASMTCylCylContact : public ASMTContact
	{
		//
	public:
		void parseASMT(std::vector<std::string>& lines) override;
		void readDistanceIJ(std::vector<std::string>& lines);
		void createMbD(std::shared_ptr<System> mbdSys, std::shared_ptr<Units> mbdUnits) override;
		void storeOnLevel(std::ofstream& os, size_t level) override;

		double distancexyIJ = 0.0;

	};
}
