/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <string>
#include <cassert>
#include <fstream>	
#include <algorithm>
#include <numeric>
#include <iomanip>

#include "ASMTAssembly.h"
#include "CREATE.h"
#include "ASMTRevoluteJoint.h"
#include "ASMTCylindricalJoint.h"
#include "ASMTRotationalMotion.h"
#include "ASMTTranslationalMotion.h"
#include "ASMTMarker.h"
#include "ASMTPart.h"
#include "ASMTTranslationalJoint.h"
#include "ASMTSphericalJoint.h"
#include "ASMTFixedJoint.h"
#include "ASMTGeneralMotion.h"
#include "ASMTUniversalJoint.h"
#include "ASMTPointInPlaneJoint.h"
#include "ASMTPrincipalMassMarker.h"
#include "ASMTForceTorque.h"
#include "ASMTConstantGravity.h"
#include "ASMTSimulationParameters.h"
#include "ASMTAnimationParameters.h"
#include "Part.h"
#include "ASMTTime.h"
#include "ASMTItemIJ.h"
#include "ASMTAngleJoint.h"
#include "ASMTConstantVelocityJoint.h"
#include "ASMTCylSphJoint.h"
#include "ASMTGearJoint.h"
#include "ASMTPointInLineJoint.h"
#include "ASMTRevCylJoint.h"
#include "ASMTSphSphJoint.h"
#include "ASMTLineInPlaneJoint.h"
#include "ASMTPlanarJoint.h"
#include "ASMTNoRotationJoint.h"
#include "ASMTParallelAxesJoint.h"
#include "ASMTPerpendicularJoint.h"
#include "ASMTRackPinionJoint.h"
#include "ASMTScrewJoint.h"
#include "SimulationStoppingError.h"
#include "ASMTKinematicIJ.h"
#include "ASMTRefPoint.h"
#include "ASMTRefCurve.h"
#include "ASMTRefSurface.h"
#include "ExternalSystem.h"
#include "SystemSolver.h"

using namespace MbD;

MbD::ASMTAssembly::ASMTAssembly() : ASMTSpatialContainer()
{
	times = std::make_shared<FullRow<double>>();
}

void MbD::ASMTAssembly::runSinglePendulumSuperSimplified()
{
	//In this version we skip declaration of variables that don't need as they use default values.
	auto assembly = CREATE<ASMTAssembly>::With();

	assembly->setName("Assembly1");

	auto mkr = CREATE<ASMTMarker>::With();
	mkr->setName("Marker1");
	assembly->addMarker(mkr);

	auto part = CREATE<ASMTPart>::With();
	part->setName("Part1");
	part->setPosition3D(-0.1, -0.1, -0.1);
	assembly->addPart(part);

	mkr = CREATE<ASMTMarker>::With();
	mkr->setName("Marker1");
	mkr->setPosition3D(0.1, 0.1, 0.1);
	part->addMarker(mkr);

	auto joint = CREATE<ASMTFixedJoint>::With();
	joint->setName("Joint1");
	joint->setMarkerI("/Assembly1/Marker1");
	joint->setMarkerJ("/Assembly1/Part1/Marker1");
	assembly->addJoint(joint);

	auto simulationParameters = CREATE<ASMTSimulationParameters>::With();
	simulationParameters->settstart(0.0);
	simulationParameters->settend(0.0);	//tstart == tend Initial Conditions only.
	simulationParameters->sethmin(1.0e-9);
	simulationParameters->sethmax(1.0);
	simulationParameters->sethout(0.04);
	simulationParameters->seterrorTol(1.0e-6);
	assembly->setSimulationParameters(simulationParameters);

	assembly->runKINEMATIC();
}

void MbD::ASMTAssembly::runSinglePendulumSuperSimplified2()
{
	//In this version we skip declaration of variables that don't need as they use default values.
	auto assembly = CREATE<ASMTAssembly>::With();
	assembly->setName("OndselAssembly");

	auto mkr = CREATE<ASMTMarker>::With();
	mkr->setName("marker1");
	assembly->addMarker(mkr);

	auto part = CREATE<ASMTPart>::With();
	part->setName("part1");
	assembly->addPart(part);

	auto marker1 = CREATE<ASMTMarker>::With();
	marker1->setName("FixingMarker");
	part->addMarker(marker1);

	auto marker2 = CREATE<ASMTMarker>::With();
	marker2->setName("marker2");
	marker2->setPosition3D(20.0, 10.0, 0.0);
	part->addMarker(marker2);

	auto part2 = CREATE<ASMTPart>::With();
	part2->setName("part2");
	part2->setPosition3D(20.0, 10.0, 0.0);
	assembly->addPart(part2);

	auto marker3 = CREATE<ASMTMarker>::With();
	marker3->setName("marker2");
	marker3->setPosition3D(50.0, 10.0, 0.0);
	part2->addMarker(marker3);

	/*Ground joint*/
	auto joint = CREATE<ASMTFixedJoint>::With();
	joint->setName("Joint1");
	joint->setMarkerI("/OndselAssembly/marker1");
	joint->setMarkerJ("/OndselAssembly/part1/FixingMarker");
	assembly->addJoint(joint);

	auto joint2 = CREATE<ASMTRevoluteJoint>::With();
	joint2->setName("Joint2");
	joint2->setMarkerI("/OndselAssembly/part1/marker2");
	joint2->setMarkerJ("/OndselAssembly/part2/marker2");
	assembly->addJoint(joint2);

	auto simulationParameters = CREATE<ASMTSimulationParameters>::With();
	simulationParameters->settstart(0.0);
	simulationParameters->settend(0.0);	//tstart == tend Initial Conditions only.
	simulationParameters->sethmin(1.0e-9);
	simulationParameters->sethmax(1.0);
	simulationParameters->sethout(0.04);
	simulationParameters->seterrorTol(1.0e-6);
	assembly->setSimulationParameters(simulationParameters);

	assembly->runKINEMATIC();
}

void MbD::ASMTAssembly::runSinglePendulumSimplified()
{
	auto assembly = CREATE<ASMTAssembly>::With();

	assembly->setNotes("");
	assembly->setName("Assembly1");
	assembly->setPosition3D(0, 0, 0);
	assembly->setRotationMatrix(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1);
	assembly->setVelocity3D(0, 0, 0);
	assembly->setOmega3D(0, 0, 0);

	auto massMarker = std::make_shared<ASMTPrincipalMassMarker>();
	massMarker->setMass(0.0);
	massMarker->setDensity(0.0);
	massMarker->setMomentOfInertias(0, 0, 0);
	massMarker->setPosition3D(0, 0, 0);
	massMarker->setRotationMatrix(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1);
	assembly->setPrincipalMassMarker(massMarker);

	auto mkr = CREATE<ASMTMarker>::With();
	mkr->setName("Marker1");
	mkr->setPosition3D(0, 0, 0);
	mkr->setRotationMatrix(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1);
	assembly->addMarker(mkr);

	auto part = CREATE<ASMTPart>::With();
	part->setName("Part1");
	part->setPosition3D(-0.1, -0.1, -0.1);
	part->setRotationMatrix(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1);
	part->setVelocity3D(0, 0, 0);
	part->setOmega3D(0, 0, 0);
	assembly->addPart(part);

	massMarker = std::make_shared<ASMTPrincipalMassMarker>();
	massMarker->setMass(0.2);
	massMarker->setDensity(10.0);
	massMarker->setMomentOfInertias(8.3333333333333e-4, 0.016833333333333, 0.017333333333333);
	massMarker->setPosition3D(0.5, 0.1, 0.05);
	massMarker->setRotationMatrix(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1);
	part->setPrincipalMassMarker(massMarker);

	mkr = CREATE<ASMTMarker>::With();
	mkr->setName("Marker1");
	mkr->setPosition3D(0.1, 0.1, 0.1);
	mkr->setRotationMatrix(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1);
	part->addMarker(mkr);

	auto joint = CREATE<ASMTRevoluteJoint>::With();
	joint->setName("Joint1");
	joint->setMarkerI("/Assembly1/Marker1");
	joint->setMarkerJ("/Assembly1/Part1/Marker1");
	assembly->addJoint(joint);

	auto motion = CREATE<ASMTRotationalMotion>::With();
	motion->setName("Motion1");
	motion->setMotionJoint("/Assembly1/Joint1");
	motion->setRotationZ("0.0");
	assembly->addMotion(motion);

	auto constantGravity = CREATE<ASMTConstantGravity>::With();
	constantGravity->setg(0.0, 0.0, 0.0);
	assembly->setConstantGravity(constantGravity);

	auto simulationParameters = CREATE<ASMTSimulationParameters>::With();
	simulationParameters->settstart(0.0);
	simulationParameters->settend(0.0);	//tstart == tend Initial Conditions only.
	simulationParameters->sethmin(1.0e-9);
	simulationParameters->sethmax(1.0);
	simulationParameters->sethout(0.04);
	simulationParameters->seterrorTol(1.0e-6);
	assembly->setSimulationParameters(simulationParameters);

	assembly->runKINEMATIC();
}

void MbD::ASMTAssembly::runSinglePendulum()
{
	auto assembly = CREATE<ASMTAssembly>::With();
	std::string str = "";
	assembly->setNotes(str);
	str = "Assembly1";
	assembly->setName(str);
	auto pos3D = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
	assembly->setPosition3D(pos3D);
	auto rotMat = std::make_shared<FullMatrix<double>>(ListListD{
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 }
		});
	assembly->setRotationMatrix(rotMat);
	auto vel3D = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
	assembly->setVelocity3D(vel3D);
	auto ome3D = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
	assembly->setOmega3D(ome3D);
	//
	auto massMarker = std::make_shared<ASMTPrincipalMassMarker>();
	massMarker->setMass(0.0);
	massMarker->setDensity(0.0);
	auto aJ = std::make_shared<DiagonalMatrix<double>>(ListD{ 0, 0, 0 });
	massMarker->setMomentOfInertias(aJ);
	pos3D = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
	massMarker->setPosition3D(pos3D);
	rotMat = std::make_shared<FullMatrix<double>>(ListListD{
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 }
		});
	massMarker->setRotationMatrix(rotMat);
	assembly->setPrincipalMassMarker(massMarker);
	//
	auto mkr = CREATE<ASMTMarker>::With();
	str = "Marker1";
	mkr->setName(str);
	pos3D = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
	mkr->setPosition3D(pos3D);
	rotMat = std::make_shared<FullMatrix<double>>(ListListD{
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 }
		});
	mkr->setRotationMatrix(rotMat);
	assembly->addMarker(mkr);
	//
	auto part = CREATE<ASMTPart>::With();
	str = "Part1";
	part->setName(str);
	pos3D = std::make_shared<FullColumn<double>>(ListD{ -0.1, -0.1, -0.1 });
	part->setPosition3D(pos3D);
	rotMat = std::make_shared<FullMatrix<double>>(ListListD{
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 }
		});
	part->setRotationMatrix(rotMat);
	vel3D = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
	part->setVelocity3D(vel3D);
	ome3D = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
	part->setOmega3D(ome3D);
	assembly->addPart(part);
	//
	massMarker = std::make_shared<ASMTPrincipalMassMarker>();
	massMarker->setMass(0.2);
	massMarker->setDensity(10.0);
	aJ = std::make_shared<DiagonalMatrix<double>>(ListD{ 8.3333333333333e-4, 0.016833333333333, 0.017333333333333 });
	massMarker->setMomentOfInertias(aJ);
	pos3D = std::make_shared<FullColumn<double>>(ListD{ 0.5, 0.1, 0.05 });
	massMarker->setPosition3D(pos3D);
	rotMat = std::make_shared<FullMatrix<double>>(ListListD{
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 }
		});
	massMarker->setRotationMatrix(rotMat);
	part->setPrincipalMassMarker(massMarker);
	//
	mkr = CREATE<ASMTMarker>::With();
	str = "Marker1";
	mkr->setName(str);
	pos3D = std::make_shared<FullColumn<double>>(ListD{ 0.1, 0.1, 0.1 });
	mkr->setPosition3D(pos3D);
	rotMat = std::make_shared<FullMatrix<double>>(ListListD{
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 }
		});
	mkr->setRotationMatrix(rotMat);
	part->addMarker(mkr);
	//
	auto joint = CREATE<ASMTRevoluteJoint>::With();
	str = "Joint1";
	joint->setName(str);
	str = "/Assembly1/Marker1";
	joint->setMarkerI(str);
	str = "/Assembly1/Part1/Marker1";
	joint->setMarkerJ(str);
	assembly->addJoint(joint);
	//
	auto motion = CREATE<ASMTRotationalMotion>::With();
	str = "Motion1";
	motion->setName(str);
	str = "/Assembly1/Joint1";
	motion->setMotionJoint(str);
	str = "0.0";
	motion->setRotationZ(str);
	assembly->addMotion(motion);
	//
	auto constantGravity = CREATE<ASMTConstantGravity>::With();
	auto gAcceleration = std::make_shared<FullColumn<double>>(ListD{ 0.0, 0.0, 0.0 });
	constantGravity->setg(gAcceleration);
	assembly->setConstantGravity(constantGravity);
	//
	auto simulationParameters = CREATE<ASMTSimulationParameters>::With();
	simulationParameters->settstart(0.0);
	simulationParameters->settend(0.0);	//tstart == tend Initial Conditions only.
	simulationParameters->sethmin(1.0e-9);
	simulationParameters->sethmax(1.0);
	simulationParameters->sethout(0.04);
	simulationParameters->seterrorTol(1.0e-6);
	assembly->setSimulationParameters(simulationParameters);
	//
	assembly->runKINEMATIC();
}

void MbD::ASMTAssembly::runFile(const char* fileName)
{
	std::ifstream stream(fileName);
	if (stream.fail()) {
		throw std::invalid_argument("File not found.");
	}
	std::string line;
	std::vector<std::string> lines;
	while (std::getline(stream, line)) {
		lines.push_back(line);
	}
	bool bool1 = lines[0] == "freeCAD: 3D CAD with Motion Simulation  by  askoh.com";
	bool bool2 = lines[0] == "OndselSolver";
	assert(bool1 || bool2);
	lines.erase(lines.begin());

	if (lines[0] == "Assembly") {
		lines.erase(lines.begin());
		auto assembly = CREATE<ASMTAssembly>::With();
		assembly->setFilename(fileName);
		assembly->parseASMT(lines);
		assembly->runKINEMATIC();
	}
}

void MbD::ASMTAssembly::readWriteFile(const char* fileName)
{
	std::ifstream stream(fileName);
	if (stream.fail()) {
		throw std::invalid_argument("File not found.");
	}
	std::string line;
	std::vector<std::string> lines;
	while (std::getline(stream, line)) {
		lines.push_back(line);
	}
	bool bool1 = lines[0] == "freeCAD: 3D CAD with Motion Simulation  by  askoh.com";
	bool bool2 = lines[0] == "OndselSolver";
	assert(bool1 || bool2);
	lines.erase(lines.begin());

	if (lines[0] == "Assembly") {
		lines.erase(lines.begin());
		auto assembly = CREATE<ASMTAssembly>::With();
		assembly->parseASMT(lines);
		assembly->runKINEMATIC();
		assembly->outputFile("assembly.asmt");
		ASMTAssembly::runFile("assembly.asmt");
	}
}

void MbD::ASMTAssembly::initialize()
{
	ASMTSpatialContainer::initialize();
	times = std::make_shared<FullRow<double>>();
}

ASMTAssembly* MbD::ASMTAssembly::root()
{
	return this;
}

void MbD::ASMTAssembly::setNotes(std::string str)
{
	notes = str;
}

void MbD::ASMTAssembly::parseASMT(std::vector<std::string>& lines)
{
	readNotes(lines);
	readName(lines);
	readPosition3D(lines);
	readRotationMatrix(lines);
	readVelocity3D(lines);
	readOmega3D(lines);
	initprincipalMassMarker();
	readRefPoints(lines);
	readRefCurves(lines);
	readRefSurfaces(lines);
	readParts(lines);
	readKinematicIJs(lines);
	readConstraintSets(lines);
	readForcesTorques(lines);
	readConstantGravity(lines);
	readSimulationParameters(lines);
	readAnimationParameters(lines);
	readTimeSeries(lines);
	readAssemblySeries(lines);
	readPartSeriesMany(lines);
	readJointSeriesMany(lines);
	readMotionSeriesMany(lines);
}

void MbD::ASMTAssembly::readNotes(std::vector<std::string>& lines)
{
	assert(lines[0] == "\tNotes");
	lines.erase(lines.begin());
	notes = readString(lines[0]);
	lines.erase(lines.begin());
}

void MbD::ASMTAssembly::readParts(std::vector<std::string>& lines)
{
	assert(lines[0] == "\tParts");
	lines.erase(lines.begin());
	parts->clear();
	auto it = std::find(lines.begin(), lines.end(), "\tKinematicIJs");
	std::vector<std::string> partsLines(lines.begin(), it);
	while (!partsLines.empty()) {
		readPart(partsLines);
	}
	lines.erase(lines.begin(), it);

}

void MbD::ASMTAssembly::readPart(std::vector<std::string>& lines)
{
	assert(lines[0] == "\t\tPart");
	lines.erase(lines.begin());
	auto part = CREATE<ASMTPart>::With();
	part->parseASMT(lines);
	parts->push_back(part);
	part->owner = this;
}

void MbD::ASMTAssembly::readKinematicIJs(std::vector<std::string>& lines)
{
	assert(lines[0] == "\tKinematicIJs");
	lines.erase(lines.begin());
	kinematicIJs->clear();
	auto it = std::find(lines.begin(), lines.end(), "\tConstraintSets");
	std::vector<std::string> kinematicIJsLines(lines.begin(), it);
	while (!kinematicIJsLines.empty()) {
		readKinematicIJ(kinematicIJsLines);
	}
	lines.erase(lines.begin(), it);

}

void MbD::ASMTAssembly::readKinematicIJ(std::vector<std::string>&)
{
	assert(false);
}

void MbD::ASMTAssembly::readConstraintSets(std::vector<std::string>& lines)
{
	assert(lines[0] == "\tConstraintSets");
	lines.erase(lines.begin());
	readJoints(lines);
	readMotions(lines);
	readGeneralConstraintSets(lines);
}

void MbD::ASMTAssembly::readJoints(std::vector<std::string>& lines)
{
	assert(lines[0] == "\t\tJoints");
	lines.erase(lines.begin());
	joints->clear();
	auto it = std::find(lines.begin(), lines.end(), "\t\tMotions");
	std::vector<std::string> jointsLines(lines.begin(), it);
	std::shared_ptr<ASMTJoint> joint;
	while (!jointsLines.empty()) {
		if (jointsLines[0] == "\t\t\tAngleJoint") {
			joint = CREATE<ASMTAngleJoint>::With();
		}
		else if (jointsLines[0] == "\t\t\tGearJoint") {
			joint = CREATE<ASMTGearJoint>::With();
		}
		else if (jointsLines[0] == "\t\t\tNoRotationJoint") {
			joint = CREATE<ASMTNoRotationJoint>::With();
		}
		else if (jointsLines[0] == "\t\t\tParallelAxesJoint") {
			joint = CREATE<ASMTParallelAxesJoint>::With();
		}
		else if (jointsLines[0] == "\t\t\tPerpendicularJoint") {
			joint = CREATE<ASMTPerpendicularJoint>::With();
		}
		else if (jointsLines[0] == "\t\t\tRackPinionJoint") {
			joint = CREATE<ASMTRackPinionJoint>::With();
		}
		else if (jointsLines[0] == "\t\t\tScrewJoint") {
			joint = CREATE<ASMTScrewJoint>::With();
		}
		//AtPointJoints
		else if (jointsLines[0] == "\t\t\tConstantVelocityJoint") {
			joint = CREATE<ASMTConstantVelocityJoint>::With();
		}
		else if (jointsLines[0] == "\t\t\tFixedJoint") {
			joint = CREATE<ASMTFixedJoint>::With();
		}
		else if (jointsLines[0] == "\t\t\tRevoluteJoint") {
			joint = CREATE<ASMTRevoluteJoint>::With();
		}
		else if (jointsLines[0] == "\t\t\tSphericalJoint") {
			joint = CREATE<ASMTSphericalJoint>::With();
		}
		else if (jointsLines[0] == "\t\t\tUniversalJoint") {
			joint = CREATE<ASMTUniversalJoint>::With();
		}
		//CompoundJoints
		else if (jointsLines[0] == "\t\t\tCylSphJoint") {
			joint = CREATE<ASMTCylSphJoint>::With();
		}
		else if (jointsLines[0] == "\t\t\tRevCylJoint") {
			joint = CREATE<ASMTRevCylJoint>::With();
		}
		else if (jointsLines[0] == "\t\t\tSphSphJoint") {
			joint = CREATE<ASMTSphSphJoint>::With();
		}
		//InLineJoints
		else if (jointsLines[0] == "\t\t\tCylindricalJoint") {
			joint = CREATE<ASMTCylindricalJoint>::With();
		}
		else if (jointsLines[0] == "\t\t\tPointInLineJoint") {
			joint = CREATE<ASMTPointInLineJoint>::With();
		}
		else if (jointsLines[0] == "\t\t\tTranslationalJoint") {
			joint = CREATE<ASMTTranslationalJoint>::With();
		}
		//InPlaneJoints
		else if (jointsLines[0] == "\t\t\tLineInPlaneJoint") {
			joint = CREATE<ASMTLineInPlaneJoint>::With();
		}
		else if (jointsLines[0] == "\t\t\tPlanarJoint") {
			joint = CREATE<ASMTPlanarJoint>::With();
		}
		else if (jointsLines[0] == "\t\t\tPointInPlaneJoint") {
			joint = CREATE<ASMTPointInPlaneJoint>::With();
		}
		else {
			assert(false);
		}
		jointsLines.erase(jointsLines.begin());
		joint->parseASMT(jointsLines);
		joints->push_back(joint);
		joint->owner = this;
	}
	lines.erase(lines.begin(), it);

}

void MbD::ASMTAssembly::readMotions(std::vector<std::string>& lines)
{
	assert(lines[0] == "\t\tMotions");
	lines.erase(lines.begin());
	motions->clear();
	auto it = std::find(lines.begin(), lines.end(), "\t\tGeneralConstraintSets");
	std::vector<std::string> motionsLines(lines.begin(), it);
	std::shared_ptr<ASMTMotion> motion;
	while (!motionsLines.empty()) {
		if (motionsLines[0] == "\t\t\tRotationalMotion") {
			motion = CREATE<ASMTRotationalMotion>::With();
		}
		else if (motionsLines[0] == "\t\t\tTranslationalMotion") {
			motion = CREATE<ASMTTranslationalMotion>::With();
		}
		else if (motionsLines[0] == "\t\t\tGeneralMotion") {
			motion = CREATE<ASMTGeneralMotion>::With();
		}
		else {
			assert(false);
		}
		motionsLines.erase(motionsLines.begin());
		motion->parseASMT(motionsLines);
		motions->push_back(motion);
		motion->owner = this;
		motion->initMarkers();
	}
	lines.erase(lines.begin(), it);

}

void MbD::ASMTAssembly::readGeneralConstraintSets(std::vector<std::string>& lines)
{
	assert(lines[0] == "\t\tGeneralConstraintSets");
	lines.erase(lines.begin());
	constraintSets->clear();
	auto it = std::find(lines.begin(), lines.end(), "\tForceTorques");
	std::vector<std::string> generalConstraintSetsLines(lines.begin(), it);
	while (!generalConstraintSetsLines.empty()) {
		assert(false);
	}
	lines.erase(lines.begin(), it);
}

void MbD::ASMTAssembly::readForcesTorques(std::vector<std::string>& lines)
{
	assert(lines[0] == "\tForceTorques");	//Spelling is not consistent in asmt file.
	lines.erase(lines.begin());
	forcesTorques->clear();
	auto it = std::find(lines.begin(), lines.end(), "\tConstantGravity");
	std::vector<std::string> forcesTorquesLines(lines.begin(), it);
	while (!forcesTorquesLines.empty()) {
		if (forcesTorquesLines[0] == "\t\tForceTorque") {
			forcesTorquesLines.erase(forcesTorquesLines.begin());
			auto forceTorque = CREATE<ASMTForceTorque>::With();
			forceTorque->parseASMT(forcesTorquesLines);
			forcesTorques->push_back(forceTorque);
			forceTorque->owner = this;
		}
		else {
			assert(false);
		}
	}
	lines.erase(lines.begin(), it);
}

void MbD::ASMTAssembly::readConstantGravity(std::vector<std::string>& lines)
{
	assert(lines[0] == "\tConstantGravity");
	lines.erase(lines.begin());
	constantGravity = CREATE<ASMTConstantGravity>::With();
	constantGravity->parseASMT(lines);
	constantGravity->owner = this;
}

void MbD::ASMTAssembly::readSimulationParameters(std::vector<std::string>& lines)
{
	assert(lines[0] == "\tSimulationParameters");
	lines.erase(lines.begin());
	simulationParameters = CREATE<ASMTSimulationParameters>::With();
	simulationParameters->parseASMT(lines);
	simulationParameters->owner = this;
}

void MbD::ASMTAssembly::readAnimationParameters(std::vector<std::string>& lines)
{
	assert(lines[0] == "\tAnimationParameters");
	lines.erase(lines.begin());
	animationParameters = CREATE<ASMTAnimationParameters>::With();
	animationParameters->parseASMT(lines);
	animationParameters->owner = this;
}

void MbD::ASMTAssembly::readTimeSeries(std::vector<std::string>& lines)
{
	assert(lines[0] == "TimeSeries");
	lines.erase(lines.begin());
	assert(lines[0].find("Number\tInput") != std::string::npos);
	lines.erase(lines.begin());
	readTimes(lines);
}

void MbD::ASMTAssembly::readTimes(std::vector<std::string>& lines)
{
	std::string str = lines[0];
	std::string substr = "Time\tInput";
	auto pos = str.find(substr);
	assert(pos != std::string::npos);
	str.erase(0, pos + substr.length());
	times = readRowOfDoubles(str);
	times->insert(times->begin(), times->at(0));	//The first element is the input state.
	lines.erase(lines.begin());
}

void MbD::ASMTAssembly::readPartSeriesMany(std::vector<std::string>& lines)
{
	assert(lines[0].find("PartSeries") != std::string::npos);
	auto it = std::find_if(lines.begin(), lines.end(), [](const std::string& s) {
		return s.find("JointSeries") != std::string::npos;
		});
	std::vector<std::string> partSeriesLines(lines.begin(), it);
	while (!partSeriesLines.empty()) {
		readPartSeries(partSeriesLines);
	}
	lines.erase(lines.begin(), it);
}

void MbD::ASMTAssembly::readJointSeriesMany(std::vector<std::string>& lines)
{
	assert(lines[0].find("JointSeries") != std::string::npos);
	auto it = std::find_if(lines.begin(), lines.end(), [](const std::string& s) {
		return s.find("MotionSeries") != std::string::npos;
		});
	std::vector<std::string> jointSeriesLines(lines.begin(), it);
	while (!jointSeriesLines.empty()) {
		readJointSeries(jointSeriesLines);
	}
	lines.erase(lines.begin(), it);
}

void MbD::ASMTAssembly::readAssemblySeries(std::vector<std::string>& lines)
{
	std::string str = lines[0];
	std::string substr = "AssemblySeries";
	auto pos = str.find(substr);
	assert(pos != std::string::npos);
	str.erase(0, pos + substr.length());
	auto seriesName = readString(str);
	assert(fullName("") == seriesName);
	lines.erase(lines.begin());
	//xs, ys, zs, bryxs, bryys, bryzs
	readXs(lines);
	readYs(lines);
	readZs(lines);
	readBryantxs(lines);
	readBryantys(lines);
	readBryantzs(lines);
	readVXs(lines);
	readVYs(lines);
	readVZs(lines);
	readOmegaXs(lines);
	readOmegaYs(lines);
	readOmegaZs(lines);
	readAXs(lines);
	readAYs(lines);
	readAZs(lines);
	readAlphaXs(lines);
	readAlphaYs(lines);
	readAlphaZs(lines);
}

void MbD::ASMTAssembly::readPartSeries(std::vector<std::string>& lines)
{
	std::string str = lines[0];
	std::string substr = "PartSeries";
	auto pos = str.find(substr);
	assert(pos != std::string::npos);
	str.erase(0, pos + substr.length());
	auto seriesName = readString(str);
	auto it = std::find_if(parts->begin(), parts->end(), [&](const std::shared_ptr<ASMTPart>& prt) {
		return prt->fullName("") == seriesName;
		});
	auto& part = *it;
	part->readPartSeries(lines);
}

void MbD::ASMTAssembly::readJointSeries(std::vector<std::string>& lines)
{
	std::string str = lines[0];
	std::string substr = "JointSeries";
	auto pos = str.find(substr);
	assert(pos != std::string::npos);
	str.erase(0, pos + substr.length());
	auto seriesName = readString(str);
	auto it = std::find_if(joints->begin(), joints->end(), [&](const std::shared_ptr<ASMTJoint>& jt) {
		return jt->fullName("") == seriesName;
		});
	auto& joint = *it;
	joint->readJointSeries(lines);
}

void MbD::ASMTAssembly::readMotionSeriesMany(std::vector<std::string>& lines)
{
	while (!lines.empty()) {
		assert(lines[0].find("MotionSeries") != std::string::npos);
		readMotionSeries(lines);
	}
}

void MbD::ASMTAssembly::readMotionSeries(std::vector<std::string>& lines)
{
	std::string str = lines[0];
	std::string substr = "MotionSeries";
	auto pos = str.find(substr);
	assert(pos != std::string::npos);
	str.erase(0, pos + substr.length());
	auto seriesName = readString(str);
	auto it = std::find_if(motions->begin(), motions->end(), [&](const std::shared_ptr<ASMTMotion>& jt) {
		return jt->fullName("") == seriesName;
		});
	auto& motion = *it;
	motion->readMotionSeries(lines);
}

void MbD::ASMTAssembly::outputFor(AnalysisType)
{
	assert(false);
}

void MbD::ASMTAssembly::preMbDrun(std::shared_ptr<System> mbdSys)
{
	calcCharacteristicDimensions();
	deleteMbD();
	createMbD(mbdSys, mbdUnits);
	std::static_pointer_cast<Part>(mbdObject)->asFixed();
}

void MbD::ASMTAssembly::postMbDrun()
{
	assert(false);
}

void MbD::ASMTAssembly::calcCharacteristicDimensions()
{
	auto unitTime = this->calcCharacteristicTime();
	auto unitMass = this->calcCharacteristicMass();
	auto unitLength = this->calcCharacteristicLength();
	auto unitAngle = 1.0;
	this->mbdUnits = std::make_shared<Units>(unitTime, unitMass, unitLength, unitAngle);
	this->mbdUnits = std::make_shared<Units>(1.0, 1.0, 1.0, 1.0);	//for debug
}

double MbD::ASMTAssembly::calcCharacteristicTime()
{
	return std::abs(simulationParameters->hout);
}

double MbD::ASMTAssembly::calcCharacteristicMass()
{
	auto n = (int)parts->size();
	double sumOfSquares = 0.0;
	for (int i = 0; i < n; i++)
	{
		auto mass = parts->at(i)->principalMassMarker->mass;
		sumOfSquares += mass * mass;
	}
	auto unitMass = std::sqrt(sumOfSquares / n);
	if (unitMass <= 0) unitMass = 1.0;
	return unitMass;
}

double MbD::ASMTAssembly::calcCharacteristicLength()
{
	auto markerMap = this->markerMap();
	auto lengths = std::make_shared<std::vector<double>>();
	auto connectorList = this->connectorList();
	for (auto& connector : *connectorList) {
		auto& mkrI = markerMap->at(connector->markerI);
		lengths->push_back(mkrI->rpmp()->length());
		auto& mkrJ = markerMap->at(connector->markerJ);
		lengths->push_back(mkrJ->rpmp()->length());
	}
	auto n = (int)lengths->size();
	double sumOfSquares = std::accumulate(lengths->begin(), lengths->end(), 0.0, [](double sum, double l) { return sum + l * l; });
	auto unitLength = std::sqrt(sumOfSquares / std::max((int)n, 1));
	if (unitLength <= 0) unitLength = 1.0;
	return unitLength;
}

std::shared_ptr<std::vector<std::shared_ptr<ASMTItemIJ>>> MbD::ASMTAssembly::connectorList()
{
	auto list = std::make_shared<std::vector<std::shared_ptr<ASMTItemIJ>>>();
	list->insert(list->end(), joints->begin(), joints->end());
	list->insert(list->end(), motions->begin(), motions->end());
	list->insert(list->end(), kinematicIJs->begin(), kinematicIJs->end());
	list->insert(list->end(), forcesTorques->begin(), forcesTorques->end());
	return list;
}

std::shared_ptr<std::map<std::string, std::shared_ptr<ASMTMarker>>> MbD::ASMTAssembly::markerMap()
{
	auto answer = std::make_shared<std::map<std::string, std::shared_ptr<ASMTMarker>>>();
	for (auto& refPoint : *refPoints) {
		for (auto& marker : *refPoint->markers) {
			answer->insert(std::make_pair(marker->fullName(""), marker));
		}
	}
	for (auto& part : *parts) {
		for (auto& refPoint : *part->refPoints) {
			for (auto& marker : *refPoint->markers) {
				answer->insert(std::make_pair(marker->fullName(""), marker));
			}
		}
	}
	return answer;
}

void MbD::ASMTAssembly::deleteMbD()
{
	ASMTSpatialContainer::deleteMbD();
	constantGravity->deleteMbD();
	asmtTime->deleteMbD();
	for (auto& part : *parts) { part->deleteMbD(); }
	for (auto& joint : *joints) { joint->deleteMbD(); }
	for (auto& motion : *motions) { motion->deleteMbD(); }
	for (auto& forceTorque : *forcesTorques) { forceTorque->deleteMbD(); }


}

void MbD::ASMTAssembly::createMbD(std::shared_ptr<System> mbdSys, std::shared_ptr<Units> mbdUnits)
{
	ASMTSpatialContainer::createMbD(mbdSys, mbdUnits);
	constantGravity->createMbD(mbdSys, mbdUnits);
	asmtTime->createMbD(mbdSys, mbdUnits);
	std::sort(parts->begin(), parts->end(), [](std::shared_ptr<ASMTPart> a, std::shared_ptr<ASMTPart> b) { return a->name < b->name; });
	auto jointsMotions = std::make_shared<std::vector<std::shared_ptr<ASMTConstraintSet>>>();
	jointsMotions->insert(jointsMotions->end(), joints->begin(), joints->end());
	jointsMotions->insert(jointsMotions->end(), motions->begin(), motions->end());
	std::sort(jointsMotions->begin(), jointsMotions->end(), [](std::shared_ptr<ASMTConstraintSet> a, std::shared_ptr<ASMTConstraintSet> b) { return a->name < b->name; });
	std::sort(forcesTorques->begin(), forcesTorques->end(), [](std::shared_ptr<ASMTForceTorque> a, std::shared_ptr<ASMTForceTorque> b) { return a->name < b->name; });
	for (auto& part : *parts) { part->createMbD(mbdSys, mbdUnits); }
	for (auto& joint : *jointsMotions) { joint->createMbD(mbdSys, mbdUnits); }
	for (auto& forceTorque : *forcesTorques) { forceTorque->createMbD(mbdSys, mbdUnits); }

	auto& mbdSysSolver = mbdSys->systemSolver;
	mbdSysSolver->errorTolPosKine = simulationParameters->errorTolPosKine;
	mbdSysSolver->errorTolAccKine = simulationParameters->errorTolAccKine;
	mbdSysSolver->iterMaxPosKine = simulationParameters->iterMaxPosKine;
	mbdSysSolver->iterMaxAccKine = simulationParameters->iterMaxAccKine;
	mbdSysSolver->tstart = simulationParameters->tstart / mbdUnits->time;
	mbdSysSolver->tend = simulationParameters->tend / mbdUnits->time;
	mbdSysSolver->hmin = simulationParameters->hmin / mbdUnits->time;
	mbdSysSolver->hmax = simulationParameters->hmax / mbdUnits->time;
	mbdSysSolver->hout = simulationParameters->hout / mbdUnits->time;
	mbdSysSolver->corAbsTol = simulationParameters->corAbsTol;
	mbdSysSolver->corRelTol = simulationParameters->corRelTol;
	mbdSysSolver->intAbsTol = simulationParameters->intAbsTol;
	mbdSysSolver->intRelTol = simulationParameters->intRelTol;
	mbdSysSolver->iterMaxDyn = simulationParameters->iterMaxDyn;
	mbdSysSolver->orderMax = simulationParameters->orderMax;
	mbdSysSolver->translationLimit = simulationParameters->translationLimit / mbdUnits->length;
	mbdSysSolver->rotationLimit = simulationParameters->rotationLimit;
	//animationParameters = nullptr;
}

void MbD::ASMTAssembly::outputFile(std::string filename)
{
	std::ofstream os(filename);
	os << std::setprecision(static_cast<std::streamsize>(std::numeric_limits<double>::digits10) + 1);
	//	try {
	os << "OndselSolver" << std::endl;
	storeOnLevel(os, 0);
	os.close();
	//	}
	//	catch (...) {
	//		os.close();
	//	}
}

void MbD::ASMTAssembly::storeOnLevel(std::ofstream& os, int level)
{
	storeOnLevelString(os, level, "Assembly");
	storeOnLevelNotes(os, level + 1);
	storeOnLevelName(os, level + 1);
	ASMTSpatialContainer::storeOnLevel(os, level);

	storeOnLevelParts(os, level + 1);
	storeOnLevelKinematicIJs(os, level + 1);
	storeOnLevelConstraintSets(os, level + 1);
	storeOnLevelForceTorques(os, level + 1);
	constantGravity->storeOnLevel(os, level + 1);
	simulationParameters->storeOnLevel(os, level + 1);
	animationParameters->storeOnLevel(os, level + 1);
	storeOnTimeSeries(os);
}

void MbD::ASMTAssembly::solve()
{
	auto simulationParameters = CREATE<ASMTSimulationParameters>::With();
	simulationParameters->settstart(0.0);
	simulationParameters->settend(0.0);	//tstart == tend Initial Conditions only.
	simulationParameters->sethmin(1.0e-9);
	simulationParameters->sethmax(1.0);
	simulationParameters->sethout(0.04);
	simulationParameters->seterrorTol(1.0e-6);
	setSimulationParameters(simulationParameters);

	runKINEMATIC();
}

void MbD::ASMTAssembly::runKINEMATIC()
{
	auto mbdSystem = std::make_shared<System>();
	mbdObject = mbdSystem;
	mbdSystem->externalSystem->asmtAssembly = this;
	try {
		mbdSystem->runKINEMATIC(mbdSystem);
	}
	catch (SimulationStoppingError&) {

	}
}

void MbD::ASMTAssembly::initprincipalMassMarker()
{
	principalMassMarker = std::make_shared<ASMTPrincipalMassMarker>();
	principalMassMarker->mass = 0.0;
	principalMassMarker->density = 0.0;
	principalMassMarker->momentOfInertias = std::make_shared<DiagonalMatrix<double>>(3, 0);
	//principalMassMarker->position3D = std::make_shared<FullColumn<double>>(3, 0);
	//principalMassMarker->rotationMatrix = FullMatrix<double>>::identitysptr(3);
}

std::shared_ptr<ASMTSpatialContainer> MbD::ASMTAssembly::spatialContainerAt(std::shared_ptr<ASMTAssembly> self, std::string& longname)
{
	if ((self->fullName("")) == longname) return self;
	auto it = std::find_if(parts->begin(), parts->end(), [&](const std::shared_ptr<ASMTPart>& prt) {
		return prt->fullName("") == longname;
		});
	auto& part = *it;
	return part;
}

std::shared_ptr<ASMTMarker> MbD::ASMTAssembly::markerAt(std::string& longname)
{
	for (auto& refPoint : *refPoints) {
		for (auto& marker : *refPoint->markers) {
			if (marker->fullName("") == longname) return marker;
		}
	}
	for (auto& part : *parts) {
		for (auto& refPoint : *part->refPoints) {
			for (auto& marker : *refPoint->markers) {
				if (marker->fullName("") == longname) return marker;
			}
		}
	}
	return nullptr;
}

std::shared_ptr<ASMTJoint> MbD::ASMTAssembly::jointAt(std::string& longname)
{
	auto it = std::find_if(joints->begin(), joints->end(), [&](const std::shared_ptr<ASMTJoint>& jt) {
		return jt->fullName("") == longname;
		});
	auto& joint = *it;
	return joint;
}

std::shared_ptr<ASMTMotion> MbD::ASMTAssembly::motionAt(std::string& longname)
{
	auto it = std::find_if(motions->begin(), motions->end(), [&](const std::shared_ptr<ASMTMotion>& mt) {
		return mt->fullName("") == longname;
		});
	auto& motion = *it;
	return motion;
}

std::shared_ptr<ASMTForceTorque> MbD::ASMTAssembly::forceTorqueAt(std::string& longname)
{
	auto it = std::find_if(forcesTorques->begin(), forcesTorques->end(), [&](const std::shared_ptr<ASMTForceTorque>& mt) {
		return mt->fullName("") == longname;
		});
	auto& forceTorque = *it;
	return forceTorque;
}

FColDsptr MbD::ASMTAssembly::vOcmO()
{
	return std::make_shared<FullColumn<double>>(3, 0.0);
}

FColDsptr MbD::ASMTAssembly::omeOpO()
{
	return std::make_shared<FullColumn<double>>(3, 0.0);
}

std::shared_ptr<ASMTTime> MbD::ASMTAssembly::geoTime()
{
	return asmtTime;
}

void MbD::ASMTAssembly::updateFromMbD()
{
	ASMTSpatialContainer::updateFromMbD();
	auto time = asmtTime->getValue();
	times->push_back(time);
	std::cout << "Time = " << time << std::endl;
	for (auto& part : *parts) part->updateFromMbD();
	for (auto& joint : *joints) joint->updateFromMbD();
	for (auto& motion : *motions) motion->updateFromMbD();
	for (auto& forceTorque : *forcesTorques) forceTorque->updateFromMbD();
}

void MbD::ASMTAssembly::compareResults(AnalysisType type)
{
	ASMTSpatialContainer::compareResults(type);
	for (auto& part : *parts) part->compareResults(type);
	for (auto& joint : *joints) joint->compareResults(type);
	for (auto& motion : *motions) motion->compareResults(type);
	for (auto& forceTorque : *forcesTorques) forceTorque->compareResults(type);
}

void MbD::ASMTAssembly::outputResults(AnalysisType)
{
	//ASMTSpatialContainer::outputResults(type);
	//for (auto& part : *parts) part->outputResults(type);
	//for (auto& joint : *joints) joint->outputResults(type);
	//for (auto& motion : *motions) motion->outputResults(type);
	//for (auto& forceTorque : *forcesTorques) forceTorque->outputResults(type);
}

void MbD::ASMTAssembly::addPart(std::shared_ptr<ASMTPart> part)
{
	parts->push_back(part);
	part->owner = this;
}

void MbD::ASMTAssembly::addJoint(std::shared_ptr<ASMTJoint> joint)
{
	joints->push_back(joint);
	joint->owner = this;
}

void MbD::ASMTAssembly::addMotion(std::shared_ptr<ASMTMotion> motion)
{
	motions->push_back(motion);
	motion->owner = this;
	motion->initMarkers();
}

void MbD::ASMTAssembly::setConstantGravity(std::shared_ptr<ASMTConstantGravity> gravity)
{
	constantGravity = gravity;
	gravity->owner = this;
}

void MbD::ASMTAssembly::setSimulationParameters(std::shared_ptr<ASMTSimulationParameters> parameters)
{
	simulationParameters = parameters;
	parameters->owner = this;
}

std::shared_ptr<ASMTPart> MbD::ASMTAssembly::partNamed(std::string partName)
{
	auto it = std::find_if(parts->begin(), parts->end(), [&](const std::shared_ptr<ASMTPart>& prt) {
		return prt->fullName("") == partName;
		});
	auto& part = *it;
	return part;
}

std::shared_ptr<ASMTPart> MbD::ASMTAssembly::partPartialNamed(std::string partialName)
{
	auto it = std::find_if(parts->begin(), parts->end(), [&](const std::shared_ptr<ASMTPart>& prt) {
		auto fullName = prt->fullName("");
		return fullName.find(partialName) != std::string::npos;
		});
	auto& part = *it;
	return part;
}

void MbD::ASMTAssembly::storeOnLevelNotes(std::ofstream& os, int level)
{
	storeOnLevelString(os, level, "Notes");
	storeOnLevelString(os, level + 1, notes);
}

void MbD::ASMTAssembly::storeOnLevelParts(std::ofstream& os, int level)
{
	storeOnLevelString(os, level, "Parts");
	for (auto& part : *parts) {
		part->storeOnLevel(os, level + 1);
	}
}

void MbD::ASMTAssembly::storeOnLevelKinematicIJs(std::ofstream& os, int level)
{
	storeOnLevelString(os, level, "KinematicIJs");
	for (auto& kinematicIJ : *kinematicIJs) {
		kinematicIJ->storeOnLevel(os, level);
	}
}

void MbD::ASMTAssembly::storeOnLevelConstraintSets(std::ofstream& os, int level)
{
	storeOnLevelString(os, level, "ConstraintSets");
	storeOnLevelJoints(os, level + 1);
	storeOnLevelMotions(os, level + 1);
	storeOnLevelGeneralConstraintSets(os, level + 1);
}

void MbD::ASMTAssembly::storeOnLevelForceTorques(std::ofstream& os, int level)
{
	storeOnLevelString(os, level, "ForceTorques");
	for (auto& forceTorque : *forcesTorques) {
		forceTorque->storeOnLevel(os, level + 1);
	}
}

void MbD::ASMTAssembly::storeOnLevelJoints(std::ofstream& os, int level)
{
	storeOnLevelString(os, level, "Joints");
	for (auto& joint : *joints) {
		joint->storeOnLevel(os, level + 1);
	}
}

void MbD::ASMTAssembly::storeOnLevelMotions(std::ofstream& os, int level)
{
	storeOnLevelString(os, level, "Motions");
	for (auto& motion : *motions) {
		motion->storeOnLevel(os, level + 1);
	}
}

void MbD::ASMTAssembly::storeOnLevelGeneralConstraintSets(std::ofstream& os, int level)
{
	storeOnLevelString(os, level, "GeneralConstraintSets");
	//for (auto& generalConstraintSet : *generalConstraintSets) {
	//	generalConstraintSet->storeOnLevel(os, level);
	//}
}

void MbD::ASMTAssembly::storeOnTimeSeries(std::ofstream& os)
{
	if (times->empty()) return;
	os << "TimeSeries" << std::endl;
	os << "Number\tInput\t";
	for (unsigned long i = 1; i < times->size(); i++)
	{
		os << i << '\t';
	}
	os << std::endl;
	os << "Time\tInput\t";
	for (unsigned long i = 1; i < times->size(); i++)
	{
		os << times->at(i) << '\t';
	}
	os << std::endl;
	os << "AssemblySeries\t" << fullName("") << std::endl;
	ASMTSpatialContainer::storeOnTimeSeries(os);
	for (auto& part : *parts) part->storeOnTimeSeries(os);
	for (auto& joint : *joints) joint->storeOnTimeSeries(os);
	for (auto& motion : *motions) motion->storeOnTimeSeries(os);
}

void MbD::ASMTAssembly::setFilename(std::string str)
{
	std::stringstream ss;
	ss << "FileName = " << str << std::endl;
	auto str2 = ss.str();
	logString(str2);
	filename = str;
}


