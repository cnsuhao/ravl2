#include <cppunit/extensions/HelperMacros.h>

#include "Ravl/Prob/VariableDiscrete.hh"

using namespace RavlProbN;
	
class VariableDiscreteTest: public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE( VariableDiscreteTest );
	CPPUNIT_TEST( testToString );
	CPPUNIT_TEST( testDomainSize );
	CPPUNIT_TEST( testDomain );
	CPPUNIT_TEST( testValue );
	CPPUNIT_TEST( testIndex );
	CPPUNIT_TEST_SUITE_END();
private:
	VariableDiscreteC m_variable;
public:
	void setUp() {
		DomainDiscreteC domain;
		domain.Insert("a");
		domain.Insert("b");
		domain.Insert("c");
		m_variable = VariableDiscreteC("variable", domain);
	}
	
	void tearDown() {
	}
	
	void testToString() {
		CPPUNIT_ASSERT_EQUAL( StringC("Variable=<a,b,c>"), m_variable.ToString() );
	}
	
	void testDomainSize() {
		CPPUNIT_ASSERT_EQUAL( (SizeT)3, m_variable.DomainSize() );
	}
	
	void testDomain() {
		CPPUNIT_ASSERT_EQUAL( (SizeT)3, m_variable.Domain().Size() );
		CPPUNIT_ASSERT( m_variable.Domain().Contains("a") );
		CPPUNIT_ASSERT( m_variable.Domain().Contains("b") );
		CPPUNIT_ASSERT( m_variable.Domain().Contains("c") );
		CPPUNIT_ASSERT( m_variable.Domain().Contains("d") == false );
	}
	
	void testValue() {
		CPPUNIT_ASSERT( m_variable.Value(0) != m_variable.Value(1) );
		CPPUNIT_ASSERT( m_variable.Value(1) != m_variable.Value(2) );
		CPPUNIT_ASSERT_THROW( m_variable.Value(3), ExceptionC );
		CPPUNIT_ASSERT_THROW( m_variable.Value(-1), ExceptionC );
	}
	
	void testIndex() {
		CPPUNIT_ASSERT_EQUAL( StringC("a"), m_variable.Value(m_variable.Index("a")) );
		CPPUNIT_ASSERT_EQUAL( StringC("b"), m_variable.Value(m_variable.Index("b")) );
		CPPUNIT_ASSERT_EQUAL( StringC("c"), m_variable.Value(m_variable.Index("c")) );
		CPPUNIT_ASSERT_THROW( m_variable.Index("d"), ExceptionC );
	}
	
};

CPPUNIT_TEST_SUITE_REGISTRATION( VariableDiscreteTest );
