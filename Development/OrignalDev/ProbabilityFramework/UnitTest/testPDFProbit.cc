#include <cppunit/extensions/HelperMacros.h>

#include "Ravl/Prob/PDFProbit.hh"
#include "Ravl/Prob/VariablePropositionContinuous.hh"

using namespace RavlProbN;
	
class PDFProbitTest: public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE( PDFProbitTest );
	CPPUNIT_TEST( testMeasureProbability );
	CPPUNIT_TEST( testMeasureProbability_InvalidVar );
	CPPUNIT_TEST( testToString );
	CPPUNIT_TEST_SUITE_END();
private:
	VariableContinuousC m_variableTemp;
	PDFContinuousAbstractC m_pdf;
	PDFContinuousAbstractC m_pdf1;
public:
	void setUp() {
		m_variableTemp = VariableContinuousC("Temperature", RealRangeC(-10, 100));
		m_pdf = PDFProbitC(m_variableTemp, 25.0, 9.0, false);
		m_pdf1 = PDFProbitC(m_variableTemp, 25.0, 9.0, true);
	}
	
	void tearDown() {
	}
	
	void testMeasureProbability() {
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.5, m_pdf.MeasureProbability(RealRangeC(24.0, 26.0)), 0.01 );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.5, m_pdf1.MeasureProbability(RealRangeC(24.0, 26.0)), 0.01 );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.0, m_pdf.MeasureProbability(RealRangeC(0.0, 1.0)), 0.01 );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0, m_pdf1.MeasureProbability(RealRangeC(0.0, 1.0)), 0.01 );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.98, m_pdf.MeasureProbability(RealRangeC(29.0, 30.0)), 0.01 );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.02, m_pdf1.MeasureProbability(RealRangeC(29.0, 30.0)), 0.01 );
	}
			
	void testMeasureProbability_InvalidVar() {
		CPPUNIT_ASSERT_THROW( m_pdf.MeasureProbability(VariablePropositionC()), ExceptionC );
		VariableContinuousC varTemp2("Temperature2", RealRangeC(-10, 100));
		CPPUNIT_ASSERT_THROW( m_pdf.MeasureProbability(VariablePropositionContinuousC(varTemp2, RealRangeC(24.0, 25.0))), ExceptionC );
	}
			
	void testToString() {
		CPPUNIT_ASSERT_EQUAL( StringC("Temperature=[-10.000000,100.000000]=25.000000+-3.000000/"), m_pdf.ToString() );
	}
	
};

CPPUNIT_TEST_SUITE_REGISTRATION( PDFProbitTest );
