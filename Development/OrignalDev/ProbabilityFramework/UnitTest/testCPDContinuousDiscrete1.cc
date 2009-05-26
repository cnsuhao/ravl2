#include <cppunit/extensions/HelperMacros.h>

#include "Ravl/Prob/CPDContinuousDiscrete1.hh"
#include "Ravl/Prob/VariablePropositionBoolean.hh"
#include "Ravl/Prob/PDFNormal.hh"

using namespace RavlProbN;
	
class CPDContinuousDiscrete1Test: public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE( CPDContinuousDiscrete1Test );
	CPPUNIT_TEST( testCreate_Invalid );
    CPPUNIT_TEST( testConditionalProbability );
    CPPUNIT_TEST( testConditionalProbability_Invalid );
    CPPUNIT_TEST( testConditionalDistribution );
    CPPUNIT_TEST( testConditionalDistribution_Invalid );
    CPPUNIT_TEST( testVariable );
    CPPUNIT_TEST( testParentVariableSet );
    CPPUNIT_TEST_SUITE_END();
private:
	VariableContinuousC m_variable;
	VariableDiscreteC m_parentVariable;
	RCHashC<VariablePropositionDiscreteC,PDFContinuousAbstractC> m_probabilityDistributionTable;
	CPDContinuousDiscrete1C m_cpd;
public:
	void setUp() {
		m_variable = VariableContinuousC("Temperature", RealRangeC(-273.0, 100.0));
		m_parentVariable = VariableBooleanC("Hot");
		m_probabilityDistributionTable.Insert(VariablePropositionBooleanC(m_parentVariable, true), PDFNormalC(m_variable, 30.0, 9.0));
		m_probabilityDistributionTable.Insert(VariablePropositionBooleanC(m_parentVariable, false), PDFNormalC(m_variable, 10.0, 100.0));		
		m_cpd = CPDContinuousDiscrete1C(m_variable, m_parentVariable, m_probabilityDistributionTable);
	}
	
	void tearDown() {
	}
	
	void testCreate_Invalid() {
		CPPUNIT_ASSERT_THROW( CPDContinuousDiscrete1C(VariableContinuousC(), m_parentVariable, m_probabilityDistributionTable), ExceptionC );
		CPPUNIT_ASSERT_THROW( CPDContinuousDiscrete1C(m_variable, VariableBooleanC(), m_probabilityDistributionTable), ExceptionC );
		RCHashC<VariablePropositionDiscreteC,PDFContinuousAbstractC> probabilityDistributionTable;
		CPPUNIT_ASSERT_THROW( CPDContinuousDiscrete1C(m_variable, m_parentVariable, probabilityDistributionTable), ExceptionC );
		probabilityDistributionTable.Insert(VariablePropositionBooleanC(m_parentVariable, true), PDFNormalC(m_variable, 30.0, 9.0));
		CPPUNIT_ASSERT_THROW( CPDContinuousDiscrete1C(m_variable, m_parentVariable, probabilityDistributionTable), ExceptionC );		
	}
	
    void testConditionalProbability() {
    	HSetC<VariablePropositionC> values;
    	values.Insert(VariablePropositionBooleanC(m_parentVariable, true));
    	PropositionSetC parentValues(m_cpd.ParentVariableSet(), values);
    	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.0, m_cpd.ConditionalProbability(VariablePropositionContinuousC(m_variable, RealRangeC(10.0, 11.0)), parentValues), 0.01 );
    	CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0, m_cpd.ConditionalProbability(VariablePropositionContinuousC(m_variable, RealRangeC(10.0, 40.0)), parentValues), 0.01 );
    	CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.36, m_cpd.ConditionalProbability(VariablePropositionContinuousC(m_variable, RealRangeC(29.0, 31.0)), parentValues), 0.01 );
    }
    
    void testConditionalProbability_Invalid() {
    	HSetC<VariablePropositionC> values;
    	PropositionSetC parentValues(m_cpd.ParentVariableSet(), values);
    	CPPUNIT_ASSERT_THROW( m_cpd.ConditionalProbability(VariablePropositionContinuousC(m_variable, RealRangeC(10.0, 11.0)), parentValues), ExceptionC );
    	values.Insert(VariablePropositionBooleanC(m_parentVariable, true));
    	CPPUNIT_ASSERT_THROW( m_cpd.ConditionalProbability(VariablePropositionContinuousC(), parentValues), ExceptionC );
    }
    
    void testConditionalDistribution() {
    	HSetC<VariablePropositionC> values;
    	values.Insert(VariablePropositionBooleanC(m_parentVariable, true));
    	PropositionSetC parentValues(m_cpd.ParentVariableSet(), values);
    	CPPUNIT_ASSERT_EQUAL( StringC("Temperature=[-273.000000,100.000000]=30.000000+-3.000000"), m_cpd.ConditionalDistribution(parentValues).ToString() );
    }
    
    void testConditionalDistribution_Invalid() {
    	HSetC<VariablePropositionC> values;
    	PropositionSetC parentValues(m_cpd.ParentVariableSet(), values);
    	CPPUNIT_ASSERT_THROW( m_cpd.ConditionalDistribution(parentValues), ExceptionC );
    }
    
	void testVariable() {
		CPPUNIT_ASSERT_EQUAL( (VariableC)m_variable, m_cpd.Variable() );
	}
	
    void testParentVariableSet() {
    	CPPUNIT_ASSERT( m_cpd.ParentVariableSet().Size() == 1 );
    	CPPUNIT_ASSERT( m_cpd.ParentVariableSet().Contains(m_parentVariable) );
    }
    
};

CPPUNIT_TEST_SUITE_REGISTRATION( CPDContinuousDiscrete1Test );
