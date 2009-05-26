#include <cppunit/extensions/HelperMacros.h>

#include "Ravl/Prob/Lottery.hh"
#include "Ravl/Prob/PropositionSet.hh"
#include "Ravl/Prob/VariablePropositionBoolean.hh"

using namespace RavlProbN;
	
class LotteryTest: public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE( LotteryTest );
    CPPUNIT_TEST( testType );
    CPPUNIT_TEST( testMultiply );
    CPPUNIT_TEST( testToString );
    CPPUNIT_TEST_SUITE_END();
private:
	LotteryC m_lottery;
public:
	void setUp() {
		HSetC<VariableC> variables;
		VariableBooleanC varBool("Boolean");
		variables.Insert(varBool);
		VariableSetC variableSet(variables);
		HSetC<VariablePropositionC> varPropositionsTrue;
		HSetC<VariablePropositionC> varPropositionsFalse;
		VariablePropositionBooleanC varPropBoolTrue(varBool, true);
		VariablePropositionBooleanC varPropBoolFalse(varBool, false);
		varPropositionsTrue.Insert(varPropBoolTrue);
		varPropositionsFalse.Insert(varPropBoolFalse);
		PropositionSetC propositionSetTrue(variableSet, varPropositionsTrue);
		PropositionSetC propositionSetFalse(variableSet, varPropositionsFalse);
		RCHashC<StringC,RealT> outcomes;
		outcomes.Insert(propositionSetTrue.ToString(), 0.1);
		outcomes.Insert(propositionSetFalse.ToString(), 0.3);
		m_lottery = LotteryC(propositionSetTrue.LotteryName(), outcomes);
	}
	
	void tearDown() {
	}
	
    void testType() {
    	CPPUNIT_ASSERT_EQUAL( StringC("{Boolean}->()"), m_lottery.Type() );
    }
    
	void testMultiply() {
		m_lottery *= m_lottery;
		CPPUNIT_ASSERT_EQUAL( StringC("{Boolean}->()=[(0.100000,{Boolean=boolean}),(0.900000,{Boolean=¬boolean})]"), m_lottery.ToString() );
    }
    
	void testToString() {
		CPPUNIT_ASSERT_EQUAL( StringC("{Boolean}->()=[(0.250000,{Boolean=boolean}),(0.750000,{Boolean=¬boolean})]"), m_lottery.ToString() );
    }
    
};

CPPUNIT_TEST_SUITE_REGISTRATION( LotteryTest );
