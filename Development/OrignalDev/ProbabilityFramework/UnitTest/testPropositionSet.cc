#include <cppunit/extensions/HelperMacros.h>

#include "Ravl/Prob/PropositionSet.hh"
#include "Ravl/Prob/VariablePropositionBoolean.hh"
#include "Ravl/Prob/VariablePropositionContinuous.hh"
#include "Ravl/Prob/VariablePropositionDiscrete.hh"

using namespace RavlProbN;
	
class PropositionSetTest: public CppUnit::TestCase {
  CPPUNIT_TEST_SUITE( PropositionSetTest );
  CPPUNIT_TEST( testToString );
  CPPUNIT_TEST( testLotteryName );
  CPPUNIT_TEST( testVariableSet );
  CPPUNIT_TEST( testSize );
  CPPUNIT_TEST( testValues );
  CPPUNIT_TEST( testValue );
  CPPUNIT_TEST( testSubPropositionSet );
  CPPUNIT_TEST( testEquality );
  CPPUNIT_TEST_SUITE_END();

private:
  VariableSetC m_variableSet;
  PropositionSetC m_proposition;
  HSetC<VariableC> m_variables;
  HSetC<VariablePropositionC> m_values;
public:
  void setUp() {
    VariableBooleanC booleanVariable("boolean");
    m_variables.Insert(booleanVariable);
    VariableContinuousC continuousVariable("continuous", RealRangeC(0.0, 1.0));
    m_variables.Insert(continuousVariable);
    DomainDiscreteC domain;
    domain.Insert("a");
    domain.Insert("b");
    domain.Insert("c");
    m_variables.Insert(VariableDiscreteC("discrete", domain));
    m_variableSet = VariableSetC(m_variables);
    m_values.Insert(VariablePropositionBooleanC(booleanVariable, true));
    m_values.Insert(VariablePropositionContinuousC(continuousVariable, RealRangeC(0.0, 0.5)));
    m_proposition = PropositionSetC(m_variableSet, m_values);
  }
	
  void tearDown() {
  }
	
  void testToString() {
    CPPUNIT_ASSERT_EQUAL( StringC("{Boolean=boolean,Continuous=[0.000000,0.500000]}"), m_proposition.ToString() );
  }
	
  void testLotteryName() {
    CPPUNIT_ASSERT_EQUAL( StringC("{Boolean,Discrete,Continuous}->(Discrete)"), m_proposition.LotteryName() );
  }
  
  void testVariableSet() {
    CPPUNIT_ASSERT_EQUAL( m_variableSet, m_proposition.VariableSet() );
  }
	
  void testSize() {
    CPPUNIT_ASSERT_EQUAL( (SizeT)2, m_proposition.Size() );
  }
	
  void testValues() {
    CPPUNIT_ASSERT_EQUAL( (SizeT)2, m_proposition.Values().Size() );
    VariablePropositionC proposition;
    for (HSetIterC<VariablePropositionC> it(m_values); it; it++)
      CPPUNIT_ASSERT( m_proposition.FindProposition(it->Variable(),proposition) );
  }
  
  void testValue() {
    CPPUNIT_ASSERT( m_proposition.Value(0) != m_proposition.Value(1) );
    CPPUNIT_ASSERT_THROW( m_proposition.Value(2), ExceptionC );
    CPPUNIT_ASSERT_THROW( m_proposition.Value(-1), ExceptionC );
  }
  
  void testSubPropositionSet() {
    HSetC<VariableC> variables;
    variables.Insert(VariableBooleanC("boolean"));
    CPPUNIT_ASSERT_EQUAL( (SizeT)1, m_proposition.SubPropositionSet(VariableSetC(variables)).Size() );
    HSetC<VariableC> variables2;
    variables2.Insert(VariableBooleanC("invalid"));
    CPPUNIT_ASSERT_THROW( m_proposition.SubPropositionSet(VariableSetC(variables2)), ExceptionC );
  }
	
  void testEquality() {
    PropositionSetC secondPropositionSet(m_variableSet, m_values);
    HSetC<VariableC> variables;
    variables.Insert(VariableBooleanC("boolean"));
    PropositionSetC subPropositionSet = m_proposition.SubPropositionSet(VariableSetC(variables));
    CPPUNIT_ASSERT( m_proposition == m_proposition );
    CPPUNIT_ASSERT( m_proposition == secondPropositionSet );
    CPPUNIT_ASSERT( !(m_proposition == subPropositionSet) );
    CPPUNIT_ASSERT( m_proposition != subPropositionSet );
    CPPUNIT_ASSERT( !(m_proposition != secondPropositionSet) );
  }
		
};

CPPUNIT_TEST_SUITE_REGISTRATION( PropositionSetTest );
