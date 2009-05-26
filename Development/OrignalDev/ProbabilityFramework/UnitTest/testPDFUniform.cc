#include <cppunit/extensions/HelperMacros.h>

#include "Ravl/Prob/PDFUniform.hh"
#include "Ravl/Prob/VariablePropositionContinuous.hh"

using namespace RavlProbN;
	
class PDFUniformTest: public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE( PDFUniformTest );
	CPPUNIT_TEST( testMeasureProbability );
	CPPUNIT_TEST( testMeasureProbability_InvalidVar );
	CPPUNIT_TEST( testToString );
	CPPUNIT_TEST_SUITE_END();
private:
	VariableContinuousC m_variableTemp;
	PDFContinuousAbstractC m_pdf;
public:
	void setUp() {
		m_variableTemp = VariableContinuousC("Temperature", RealRangeC(-10, 100));
		m_pdf = PDFUniformC(m_variableTemp, RealRangeC(22.0, 26.0));
	}
	
	void tearDown() {
	}
	
	void testMeasureProbability() {
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0, m_pdf.MeasureProbability(VariablePropositionContinuousC(m_variableTemp, m_variableTemp.Interval())), 0.01 );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.25, m_pdf.MeasureProbability(VariablePropositionContinuousC(m_variableTemp, RealRangeC(24.0, 25.0))), 0.01 );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.25, m_pdf.MeasureProbability(RealRangeC(24.0, 25.0)), 0.01 );
	}
			
	void testMeasureProbability_InvalidVar() {
		CPPUNIT_ASSERT_THROW( m_pdf.MeasureProbability(VariablePropositionC()), ExceptionC );
		VariableContinuousC varTemp2("Temperature2", RealRangeC(-10, 100));
		CPPUNIT_ASSERT_THROW( m_pdf.MeasureProbability(VariablePropositionContinuousC(varTemp2, RealRangeC(24.0, 25.0))), ExceptionC );
	}
			
	void testToString() {
		CPPUNIT_ASSERT_EQUAL( StringC("Temperature=[-10.000000,100.000000]=[22.000000,26.000000]"), m_pdf.ToString() );
	}
	
};

CPPUNIT_TEST_SUITE_REGISTRATION( PDFUniformTest );
