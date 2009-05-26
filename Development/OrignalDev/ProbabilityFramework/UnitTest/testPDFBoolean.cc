#include <cppunit/extensions/HelperMacros.h>

#include "Ravl/Prob/PDFBoolean.hh"
#include "Ravl/Prob/VariablePropositionBoolean.hh"

using namespace RavlProbN;
	
class PDFBooleanTest: public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE( PDFBooleanTest );
	CPPUNIT_TEST( testToString );
	CPPUNIT_TEST( testMeasureProbability );
	CPPUNIT_TEST_SUITE_END();
private:
	VariableBooleanC m_variableCavity;
	PDFBooleanC m_pdf;
public:
	void setUp() {
		m_variableCavity = VariableBooleanC("Cavity");
		m_pdf = PDFBooleanC(m_variableCavity, 0.2);
	}
	
	void tearDown() {
	}
	
	void testToString() {
		CPPUNIT_ASSERT_EQUAL( StringC("Cavity=<cavity,¬cavity>=<0.200000,0.800000>"), m_pdf.ToString() );
	}
	
	void testMeasureProbability() {
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.2, m_pdf.MeasureProbability(VariablePropositionBooleanC(m_variableCavity, true)), 0.01 );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.8, m_pdf.MeasureProbability(VariablePropositionBooleanC(m_variableCavity, false)), 0.01 );
		CPPUNIT_ASSERT_THROW( m_pdf.MeasureProbability(VariablePropositionC()), ExceptionC );
	}
			
};

CPPUNIT_TEST_SUITE_REGISTRATION( PDFBooleanTest );
