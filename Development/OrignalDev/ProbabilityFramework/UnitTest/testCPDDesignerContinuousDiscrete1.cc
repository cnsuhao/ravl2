#include <cppunit/extensions/HelperMacros.h>

#include "Ravl/Prob/CPDDesignerContinuousDiscrete1.hh"
#include "Ravl/Prob/VariablePropositionBoolean.hh"
#include "Ravl/Prob/VariablePropositionContinuous.hh"
#include "Ravl/Prob/PDFNormal.hh"
#include "Ravl/Random.hh"

using namespace RavlProbN;
	
class CPDDesignerContinuousDiscrete1Test: public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE( CPDDesignerContinuousDiscrete1Test );
	CPPUNIT_TEST( testCreateCPD );
    CPPUNIT_TEST_SUITE_END();
private:
	CPDDesignerContinuousDiscrete1C m_designer;
public:
	void setUp() {
		m_designer = CPDDesignerContinuousDiscrete1C::GetInstance();
	}
	
	void tearDown() {
	}
	
	void testCreateCPD() {
		DListC<Tuple2C<VariablePropositionC,PropositionSetC> > propositionPairs;
		VariableContinuousC variable("Temperature", RealRangeC(-273.0, 100.0));
		VariableBooleanC parentVariable("Hot");
		HSetC<VariableC> setVars;
		setVars.Insert(parentVariable);
		VariableSetC varSet(setVars);
		VariablePropositionBooleanC hot(parentVariable, true);
		// create normal distribution for hot
		HSetC<VariablePropositionC> setHot;
		setHot.Insert(VariablePropositionBooleanC(parentVariable, true));
		PropositionSetC propSetHot(varSet, setHot);
		for (int i = 0; i < 1000; i++) {
			RealT temp = RandomGauss() * 3.0 + 30.0;
			Tuple2C<VariablePropositionC,PropositionSetC> tuple(VariablePropositionContinuousC(variable, RealRangeC(temp-0.5, temp+0.5)), propSetHot);
			propositionPairs.InsLast(tuple);
		}
		// create normal distribution for !hot
		HSetC<VariablePropositionC> setCold;
		setCold.Insert(VariablePropositionBooleanC(parentVariable, false));
		PropositionSetC propSetCold(varSet, setCold);
		for (int i = 0; i < 1000; i++) {
			RealT temp = RandomGauss() * 10.0 + 10.0;
			Tuple2C<VariablePropositionC,PropositionSetC> tuple(VariablePropositionContinuousC(variable, RealRangeC(temp-0.5, temp+0.5)), propSetCold);
			propositionPairs.InsLast(tuple);
		}
		ConditionalProbabilityDistributionC cpd = m_designer.CreateCPD(propositionPairs);
		PDFNormalC pdf = cpd.ConditionalDistribution(propSetHot);
		CPPUNIT_ASSERT( pdf.IsValid() );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 30.0, pdf.Mean(), 0.1 );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 3.0, Sqrt(pdf.Variance()), 0.1 );
		pdf = cpd.ConditionalDistribution(propSetCold);
		CPPUNIT_ASSERT( pdf.IsValid() );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 10.0, pdf.Mean(), 0.5 );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 10.0, Sqrt(pdf.Variance()), 0.5 );
	}
	
};

CPPUNIT_TEST_SUITE_REGISTRATION( CPDDesignerContinuousDiscrete1Test );
