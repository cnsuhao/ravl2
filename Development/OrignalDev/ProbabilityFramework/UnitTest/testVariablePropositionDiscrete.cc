#include <cppunit/extensions/HelperMacros.h>

#include "Ravl/Prob/VariablePropositionDiscrete.hh"

using namespace RavlProbN;
	
class VariablePropositionDiscreteTest: public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE( VariablePropositionDiscreteTest );
	CPPUNIT_TEST( testCreate );
	CPPUNIT_TEST( testStringValue );
	CPPUNIT_TEST( testToString );
	CPPUNIT_TEST( testIndex );
	CPPUNIT_TEST( testEquality );
	CPPUNIT_TEST_SUITE_END();
private:
	VariableDiscreteC m_variable;
	VariablePropositionDiscreteC m_valueA;
	VariablePropositionDiscreteC m_valueB;
public:
	void setUp() {
		DomainDiscreteC domain;
		domain.Insert("a");
		domain.Insert("b");
		domain.Insert("c");
		m_variable = VariableDiscreteC("variable", domain);
		m_valueA = VariablePropositionDiscreteC(m_variable, "a");
		m_valueB = VariablePropositionDiscreteC(m_variable, "b");
	}
	
	void tearDown() {
	}
	
	void testCreate() {
		CPPUNIT_ASSERT_THROW( VariablePropositionDiscreteC v(m_variable, "d"), ExceptionC );
	}
	
	void testStringValue() {
		CPPUNIT_ASSERT_EQUAL( StringC("a"), m_valueA.Value() );
		CPPUNIT_ASSERT_EQUAL( StringC("b"), m_valueB.Value() );
	}
	
	void testToString() {
		CPPUNIT_ASSERT_EQUAL( StringC("a"), m_valueA.ToString() );
		CPPUNIT_ASSERT_EQUAL( StringC("b"), m_valueB.ToString() );
	}
	
	void testIndex() {
		CPPUNIT_ASSERT_EQUAL( m_valueA.Value(), m_variable.Value(m_valueA.Index()) );
		CPPUNIT_ASSERT_EQUAL( m_valueB.Value(), m_variable.Value(m_valueB.Index()) );
	}
	
	void testEquality() {
		VariablePropositionDiscreteC secondValueA(m_variable, "a");
		CPPUNIT_ASSERT( m_valueA == m_valueA );
		CPPUNIT_ASSERT( m_valueA == secondValueA );
		CPPUNIT_ASSERT( !(m_valueA == m_valueB) );
		CPPUNIT_ASSERT( m_valueA != m_valueB );
		CPPUNIT_ASSERT( !(m_valueA != m_valueA) );
		CPPUNIT_ASSERT( !(m_valueA != secondValueA) );
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( VariablePropositionDiscreteTest );
