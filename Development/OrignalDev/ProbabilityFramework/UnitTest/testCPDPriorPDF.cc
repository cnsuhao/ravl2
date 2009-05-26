#include <cppunit/extensions/HelperMacros.h>

#include "Ravl/Prob/CPDPriorPDF.hh"
#include "Ravl/Prob/PDFUniform.hh"

using namespace RavlProbN;
	
class CPDPriorPDFTest: public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE( CPDPriorPDFTest );
	CPPUNIT_TEST( testConditionalDistribution );
	CPPUNIT_TEST( testConditionalDistribution_Invalid );
	CPPUNIT_TEST_SUITE_END();
private:
	VariableC m_temperature;
	ProbabilityDistributionC m_pdf;
	CPDPriorPDFC m_cpd;
public:
	void setUp() {
		m_temperature = VariableContinuousC("Temperature", RealRangeC(-273.0, 100.0));
		m_pdf = PDFUniformC(m_temperature, RealRangeC(-273.0, 100.0));
		m_cpd = CPDPriorPDFC(m_pdf);
	}
	
	void tearDown() {
	}
	
	void testConditionalDistribution() {
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.027, m_cpd.ConditionalDistribution(PropositionSetC()).MeasureProbability(VariablePropositionContinuousC(m_temperature, RealRangeC(0.0, 10.0))), 0.001 );
		HSetC<VariableC> tmpVarSet;
		VariableSetC emptyVarSet(tmpVarSet);
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.027, m_cpd.ConditionalDistribution(PropositionSetC(emptyVarSet, HSetC<VariablePropositionC>())).MeasureProbability(VariablePropositionContinuousC(m_temperature, RealRangeC(0.0, 10.0))), 0.001 );
	}
	
	void testConditionalDistribution_Invalid() {
		CPPUNIT_ASSERT_THROW( m_cpd.ConditionalDistribution(PropositionSetC(VariablePropositionContinuousC(m_temperature, RealRangeC(0.0, 10.0)))), ExceptionC );
	}
	
};

CPPUNIT_TEST_SUITE_REGISTRATION( CPDPriorPDFTest );
