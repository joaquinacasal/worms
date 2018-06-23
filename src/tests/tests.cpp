/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_WormTest_init = false;
#include "MyTestSuite.h"

static WormTest suite_WormTest;

static CxxTest::List Tests_WormTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_WormTest( "MyTestSuite.h", 12, "WormTest", suite_WormTest, Tests_WormTest );

static class TestDescription_suite_WormTest_testConstructorDelGusano : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_WormTest_testConstructorDelGusano() : CxxTest::RealTestDescription( Tests_WormTest, suiteDescription_WormTest, 21, "testConstructorDelGusano" ) {}
 void runTest() { suite_WormTest.testConstructorDelGusano(); }
} testDescription_suite_WormTest_testConstructorDelGusano;

static class TestDescription_suite_WormTest_testCaidaPorLaGravedad : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_WormTest_testCaidaPorLaGravedad() : CxxTest::RealTestDescription( Tests_WormTest, suiteDescription_WormTest, 43, "testCaidaPorLaGravedad" ) {}
 void runTest() { suite_WormTest.testCaidaPorLaGravedad(); }
} testDescription_suite_WormTest_testCaidaPorLaGravedad;

static class TestDescription_suite_WormTest_testSaltoParaAdelante : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_WormTest_testSaltoParaAdelante() : CxxTest::RealTestDescription( Tests_WormTest, suiteDescription_WormTest, 59, "testSaltoParaAdelante" ) {}
 void runTest() { suite_WormTest.testSaltoParaAdelante(); }
} testDescription_suite_WormTest_testSaltoParaAdelante;

static class TestDescription_suite_WormTest_testSaltoParaAtras : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_WormTest_testSaltoParaAtras() : CxxTest::RealTestDescription( Tests_WormTest, suiteDescription_WormTest, 81, "testSaltoParaAtras" ) {}
 void runTest() { suite_WormTest.testSaltoParaAtras(); }
} testDescription_suite_WormTest_testSaltoParaAtras;

static class TestDescription_suite_WormTest_testMoverseALaDerecha : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_WormTest_testMoverseALaDerecha() : CxxTest::RealTestDescription( Tests_WormTest, suiteDescription_WormTest, 104, "testMoverseALaDerecha" ) {}
 void runTest() { suite_WormTest.testMoverseALaDerecha(); }
} testDescription_suite_WormTest_testMoverseALaDerecha;

static class TestDescription_suite_WormTest_testMoverseALaIzquierda : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_WormTest_testMoverseALaIzquierda() : CxxTest::RealTestDescription( Tests_WormTest, suiteDescription_WormTest, 123, "testMoverseALaIzquierda" ) {}
 void runTest() { suite_WormTest.testMoverseALaIzquierda(); }
} testDescription_suite_WormTest_testMoverseALaIzquierda;

static class TestDescription_suite_WormTest_testCaerSobreUnaViga : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_WormTest_testCaerSobreUnaViga() : CxxTest::RealTestDescription( Tests_WormTest, suiteDescription_WormTest, 141, "testCaerSobreUnaViga" ) {}
 void runTest() { suite_WormTest.testCaerSobreUnaViga(); }
} testDescription_suite_WormTest_testCaerSobreUnaViga;

static class TestDescription_suite_WormTest_testDescuentoDeVidaPorCaida : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_WormTest_testDescuentoDeVidaPorCaida() : CxxTest::RealTestDescription( Tests_WormTest, suiteDescription_WormTest, 158, "testDescuentoDeVidaPorCaida" ) {}
 void runTest() { suite_WormTest.testDescuentoDeVidaPorCaida(); }
} testDescription_suite_WormTest_testDescuentoDeVidaPorCaida;

static class TestDescription_suite_WormTest_testMuertePorCaidaAlAgua : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_WormTest_testMuertePorCaidaAlAgua() : CxxTest::RealTestDescription( Tests_WormTest, suiteDescription_WormTest, 184, "testMuertePorCaidaAlAgua" ) {}
 void runTest() { suite_WormTest.testMuertePorCaidaAlAgua(); }
} testDescription_suite_WormTest_testMuertePorCaidaAlAgua;

static BeamTest suite_BeamTest;

static CxxTest::List Tests_BeamTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_BeamTest( "MyTestSuite.h", 204, "BeamTest", suite_BeamTest, Tests_BeamTest );

static class TestDescription_suite_BeamTest_testConstructorDeLaViga : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_BeamTest_testConstructorDeLaViga() : CxxTest::RealTestDescription( Tests_BeamTest, suiteDescription_BeamTest, 216, "testConstructorDeLaViga" ) {}
 void runTest() { suite_BeamTest.testConstructorDeLaViga(); }
} testDescription_suite_BeamTest_testConstructorDeLaViga;

static TurnsManagerTest suite_TurnsManagerTest;

static CxxTest::List Tests_TurnsManagerTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TurnsManagerTest( "MyTestSuite.h", 246, "TurnsManagerTest", suite_TurnsManagerTest, Tests_TurnsManagerTest );

static class TestDescription_suite_TurnsManagerTest_testManejadorDeTurnos : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TurnsManagerTest_testManejadorDeTurnos() : CxxTest::RealTestDescription( Tests_TurnsManagerTest, suiteDescription_TurnsManagerTest, 255, "testManejadorDeTurnos" ) {}
 void runTest() { suite_TurnsManagerTest.testManejadorDeTurnos(); }
} testDescription_suite_TurnsManagerTest_testManejadorDeTurnos;

static class TestDescription_suite_TurnsManagerTest_testCambioDeTurnosConGusanos : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TurnsManagerTest_testCambioDeTurnosConGusanos() : CxxTest::RealTestDescription( Tests_TurnsManagerTest, suiteDescription_TurnsManagerTest, 291, "testCambioDeTurnosConGusanos" ) {}
 void runTest() { suite_TurnsManagerTest.testCambioDeTurnosConGusanos(); }
} testDescription_suite_TurnsManagerTest_testCambioDeTurnosConGusanos;

static TeletransportationTest suite_TeletransportationTest;

static CxxTest::List Tests_TeletransportationTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TeletransportationTest( "MyTestSuite.h", 324, "TeletransportationTest", suite_TeletransportationTest, Tests_TeletransportationTest );

static class TestDescription_suite_TeletransportationTest_testTeletransportacionUnSoloGusano : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TeletransportationTest_testTeletransportacionUnSoloGusano() : CxxTest::RealTestDescription( Tests_TeletransportationTest, suiteDescription_TeletransportationTest, 334, "testTeletransportacionUnSoloGusano" ) {}
 void runTest() { suite_TeletransportationTest.testTeletransportacionUnSoloGusano(); }
} testDescription_suite_TeletransportationTest_testTeletransportacionUnSoloGusano;

static class TestDescription_suite_TeletransportationTest_testTeletransportacionMuchosGusanos : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TeletransportationTest_testTeletransportacionMuchosGusanos() : CxxTest::RealTestDescription( Tests_TeletransportationTest, suiteDescription_TeletransportationTest, 386, "testTeletransportacionMuchosGusanos" ) {}
 void runTest() { suite_TeletransportationTest.testTeletransportacionMuchosGusanos(); }
} testDescription_suite_TeletransportationTest_testTeletransportacionMuchosGusanos;

static DynamiteTest suite_DynamiteTest;

static CxxTest::List Tests_DynamiteTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_DynamiteTest( "MyTestSuite.h", 559, "DynamiteTest", suite_DynamiteTest, Tests_DynamiteTest );

static class TestDescription_suite_DynamiteTest_testExplosionDinamita : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_DynamiteTest_testExplosionDinamita() : CxxTest::RealTestDescription( Tests_DynamiteTest, suiteDescription_DynamiteTest, 568, "testExplosionDinamita" ) {}
 void runTest() { suite_DynamiteTest.testExplosionDinamita(); }
} testDescription_suite_DynamiteTest_testExplosionDinamita;

static RadiocontrolledTest suite_RadiocontrolledTest;

static CxxTest::List Tests_RadiocontrolledTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_RadiocontrolledTest( "MyTestSuite.h", 619, "RadiocontrolledTest", suite_RadiocontrolledTest, Tests_RadiocontrolledTest );

static class TestDescription_suite_RadiocontrolledTest_testCaidaRadiocontrolled : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_RadiocontrolledTest_testCaidaRadiocontrolled() : CxxTest::RealTestDescription( Tests_RadiocontrolledTest, suiteDescription_RadiocontrolledTest, 628, "testCaidaRadiocontrolled" ) {}
 void runTest() { suite_RadiocontrolledTest.testCaidaRadiocontrolled(); }
} testDescription_suite_RadiocontrolledTest_testCaidaRadiocontrolled;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
