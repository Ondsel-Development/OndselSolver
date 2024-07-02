#include "pch.h"
#include <ucrt/time.h>
#include <CADSystem.h>
#include <ASMTAssembly.h>

using namespace MbD;

TEST(OndselSolver, TestName) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}
TEST(OndselSolver, runOndselSinglePendulum) {
	//testing::internal::CaptureStdout();
	auto cadSystem = std::make_shared<CADSystem>();
	cadSystem->runOndselSinglePendulum();
	//std::string output = testing::internal::GetCapturedStdout();
	EXPECT_TRUE(true);
}
TEST(OndselSolver, runPreDragBackhoe3) {
	auto assembly = ASMTAssembly::assemblyFromFile("../../../testapp/runPreDragBackhoe3.asmt");
	assembly->runDraggingLog("../../../testapp/draggingBackhoe3.log");
	EXPECT_TRUE(true);
}