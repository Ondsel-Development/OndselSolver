/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
/*****************************************************************//**
 * \file   System.h
 * \brief  Multibody system of parts, joints, forces.
 * 
 * \author askoh
 * \date   May 2023
 *********************************************************************/

#pragma once

#include <memory>
#include <vector>
#include <functional>

#include "Item.h"

#define ERR_PREMBDRUN 1000
#define ERR_PREMBDRUN_SIMPARAMETERMISSING 1001
#define ERR_CREATEMBD_DIVBY0_TIME 1100
#define ERR_CREATEMBD_DIVBY0_LENGTH 1101
#define ERR_CREATEMBD_DIVBY0_MASS 1102
#define ERR_CREATEMBD_DIVBY0_VELOCITY 1103
#define ERR_CREATEMBD_DIVBY0_OMEGA 1104
#define ERR_CREATEMBD_DIVBY0_AJ 1105
#define ERR_CREATEMBD_DIVBY0_ACCELERATION 1106
#define ERR_CREATEMBD_DIVBY0_ANGLE 1107

#define ERR_CREATEMBD_ASMTITEM 1205
#define ERR_CREATEMBD_SYMBOLIC 1205
#define ERR_CREATEMBD_TIME_XXERR 1206

namespace MbD {
	class Part;
	class Joint;
	class SystemSolver;
	class Time;
	class Constraint;
	class PrescribedMotion;
	class ForceTorqueItem;
	class ExternalSystem;

	class System : public Item
	{
		//ToDo: Needed members admSystem namedItems mbdTime parts jointsMotions forcesTorques sensors variables hasChanged mbdSystemSolver
	public:
		System();
		System(const char* str);
		System* root() override;
		void initialize() override;
		void initializeLocally() override;
		void initializeGlobally() override;
		void clear();
		int runKINEMATIC(std::shared_ptr<System> self);
		std::shared_ptr<std::vector<std::string>> discontinuitiesAtIC();
		void jointsMotionsDo(const std::function <void(std::shared_ptr<Joint>)>& f);
		void partsJointsMotionsDo(const std::function <void(std::shared_ptr<Item>)>& f);
		void partsJointsMotionsForcesTorquesDo(const std::function <void(std::shared_ptr<Item>)>& f);
		void logString(std::string& str) override;
		double mbdTimeValue();
		void mbdTimeValue(double t);
		std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> essentialConstraints();
		std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> displacementConstraints();
		std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> perpendicularConstraints();
		std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> allRedundantConstraints();
		std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> allConstraints();
		void addPart(std::shared_ptr<Part> part);
		void addJoint(std::shared_ptr<Joint> joint);
		void addMotion(std::shared_ptr<PrescribedMotion> motion);
		void addForceTorque(std::shared_ptr<ForceTorqueItem> forTor);

		double maximumMass();
		double maximumMomentOfInertia();
		double translationLimit();
		double rotationLimit();
		void outputFor(AnalysisType type);

		std::shared_ptr<ExternalSystem> externalSystem;
		std::shared_ptr<std::vector<std::shared_ptr<Part>>> parts;
		std::shared_ptr<std::vector<std::shared_ptr<Joint>>> jointsMotions;
		std::shared_ptr<std::vector<std::shared_ptr<ForceTorqueItem>>> forcesTorques;
		bool hasChanged = false;
		std::shared_ptr<SystemSolver> systemSolver;

		std::shared_ptr<Time> time;
	};
}
