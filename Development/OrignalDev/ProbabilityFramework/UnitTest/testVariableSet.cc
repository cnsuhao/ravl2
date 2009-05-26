#include <cppunit/extensions/HelperMacros.h>

#include "Ravl/Prob/VariableSet.hh"
#include "Ravl/Prob/VariableBoolean.hh"
#include "Ravl/Prob/VariableContinuous.hh"
#include "Ravl/Prob/VariableDiscrete.hh"

using namespace RavlProbN;
	
class VariableSetTest: public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE( VariableSetTest );
	CPPUNIT_TEST( testEquality );
	CPPUNIT_TEST( testContains );
	CPPUNIT_TEST( testSize );
	CPPUNIT_TEST( testVariables );
	CPPUNIT_TEST( testVariable );
	CPPUNIT_TEST( testIndex );
	CPPUNIT_TEST( testToString );
	CPPUNIT_TEST_SUITE_END();
private:
	VariableSetC m_variableSet;
	HSetC<VariableC> m_variables;
public:
	void setUp() {
		m_variables.Insert(VariableBooleanC("boolean"));
		m_variables.Insert(VariableContinuousC("continuous", RealRangeC(0.0, 1.0)));
		DomainDiscreteC domain;
		domain.Insert("a");
		domain.Insert("b");
		domain.Insert("c");
		m_variables.Insert(VariableDiscreteC("discrete", domain));
		m_variableSet = VariableSetC(m_variables);
	}
	
	void tearDown() {
	}
	
	void testEquality() {
		VariableSetC secondVariableSet(m_variables);
		HSetC<VariableC> emptySet;
		VariableSetC thirdVariableSet(emptySet);
		CPPUNIT_ASSERT( m_variableSet == m_variableSet );
		CPPUNIT_ASSERT( m_variableSet == secondVariableSet );
		CPPUNIT_ASSERT( !(m_variableSet == thirdVariableSet) );
		CPPUNIT_ASSERT( m_variableSet != thirdVariableSet );
		CPPUNIT_ASSERT( !(m_variableSet != secondVariableSet) );
	}
	
	void testContains() {
		for (HSetIterC<VariableC> it(m_variables); it; it++)
			CPPUNIT_ASSERT( m_variableSet.Contains(*it) );
		CPPUNIT_ASSERT( m_variableSet.Contains(VariableC()) == false);
		CPPUNIT_ASSERT( m_variableSet.Contains(VariableBooleanC("bool2")) == false );
	}
	
	void testSize() {
		CPPUNIT_ASSERT_EQUAL( (SizeT)3, m_variableSet.Size() );
	}
	
	void testVariables() {
		CPPUNIT_ASSERT_EQUAL( (SizeT)3, m_variableSet.Variables().Size() );
		for (HSetIterC<VariableC> it(m_variables); it; it++)
			CPPUNIT_ASSERT( m_variableSet.Variables().Contains(*it) );
	}
	
	void testVariable() {
		CPPUNIT_ASSERT( m_variableSet.Variable(0) != m_variableSet.Variable(1) );
		CPPUNIT_ASSERT( m_variableSet.Variable(1) != m_variableSet.Variable(2) );
		CPPUNIT_ASSERT_THROW( m_variableSet.Variable(3), ExceptionC );
		CPPUNIT_ASSERT_THROW( m_variableSet.Variable(-1), ExceptionC );
	}
	
	void testIndex() {
		for (HSetIterC<VariableC> it(m_variables); it; it++)
			CPPUNIT_ASSERT_EQUAL( *it, m_variableSet.Variable(m_variableSet.Index(*it)) );
		CPPUNIT_ASSERT_THROW( m_variableSet.Index(VariableC()), ExceptionC );
		CPPUNIT_ASSERT_THROW( m_variableSet.Index(VariableBooleanC("bool3")), ExceptionC );
	}
	
	void testToString() {
		CPPUNIT_ASSERT_EQUAL( StringC("{Boolean,Discrete,Continuous}"), m_variableSet.ToString() );
	}
	
};

CPPUNIT_TEST_SUITE_REGISTRATION( VariableSetTest );
