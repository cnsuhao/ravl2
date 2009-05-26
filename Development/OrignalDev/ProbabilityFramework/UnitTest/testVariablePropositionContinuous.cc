#include <cppunit/extensions/HelperMacros.h>

#include "Ravl/Prob/VariablePropositionContinuous.hh"

using namespace RavlProbN;
	
class VariablePropositionContinuousTest: public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE( VariablePropositionContinuousTest );
	CPPUNIT_TEST( testCreate );
	CPPUNIT_TEST( testToString );
	CPPUNIT_TEST( testValue );
	CPPUNIT_TEST( testEquality );
	CPPUNIT_TEST_SUITE_END();
private:
	VariableContinuousC m_variable;
	VariablePropositionContinuousC m_value0, m_value0_5, m_value1;
public:
	void setUp() {
		m_variable = VariableContinuousC("variable", RealRangeC(0.0, 1.0));
		m_value0 = VariablePropositionContinuousC(m_variable, RealRangeC(0.0, 0.1));
		m_value0_5 = VariablePropositionContinuousC(m_variable, RealRangeC(0.4, 0.6));
		m_value1 = VariablePropositionContinuousC(m_variable, RealRangeC(0.9, 1.0));
	}
	
	void tearDown() {
	}
	
	void testCreate() {
		CPPUNIT_ASSERT_THROW( VariablePropositionContinuousC v1(m_variable, -0.1), ExceptionC );
		CPPUNIT_ASSERT_THROW( VariablePropositionContinuousC v2(m_variable, 1.1), ExceptionC );
	}
	
	void testToString() {
		CPPUNIT_ASSERT_EQUAL( StringC("[0.000000,0.100000]"), m_value0.ToString() );
		CPPUNIT_ASSERT_EQUAL( StringC("[0.400000,0.600000]"), m_value0_5.ToString() );
		CPPUNIT_ASSERT_EQUAL( StringC("[0.900000,1.000000]"), m_value1.ToString() );
	}
	
	void testValue() {
		CPPUNIT_ASSERT_EQUAL( RealRangeC(0.0, 0.1), m_value0.ValueRange() );
		CPPUNIT_ASSERT_EQUAL( RealRangeC(0.4, 0.6), m_value0_5.ValueRange() );
		CPPUNIT_ASSERT_EQUAL( RealRangeC(0.9, 1.0), m_value1.ValueRange() );
	}
	
	void testEquality() {
		VariablePropositionContinuousC secondValue0_5(m_variable, RealRangeC(0.4, 0.6));
		CPPUNIT_ASSERT( m_value0 == m_value0 );
		CPPUNIT_ASSERT( m_value0_5 == m_value0_5 );
		CPPUNIT_ASSERT( m_value0_5 == secondValue0_5 );
		CPPUNIT_ASSERT( !(m_value0 == m_value0_5) );
		CPPUNIT_ASSERT( m_value0 != m_value0_5 );
		CPPUNIT_ASSERT( !(m_value0 != m_value0) );
		CPPUNIT_ASSERT( !(m_value0_5 != secondValue0_5) );
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( VariablePropositionContinuousTest );
