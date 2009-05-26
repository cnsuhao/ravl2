#include <cppunit/extensions/HelperMacros.h>

#include "Ravl/Prob/VariableContinuous.hh"

using namespace RavlProbN;
	
class VariableContinuousTest: public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE( VariableContinuousTest );
	CPPUNIT_TEST( testToString );
	CPPUNIT_TEST( testInterval );
	CPPUNIT_TEST_SUITE_END();
private:
	VariableContinuousC m_variable;
public:
	void setUp() {
		m_variable = VariableContinuousC("variable", RealRangeC(0.0, 1.0));
	}
	
	void tearDown() {
	}
	
	void testToString() {
	    CPPUNIT_ASSERT_EQUAL( StringC("Variable=[0.000000,1.000000]"), m_variable.ToString() );
	}
	
	void testInterval() {
		CPPUNIT_ASSERT_EQUAL( RealRangeC(0.0,1.0), m_variable.Interval() );
	}
	
};

CPPUNIT_TEST_SUITE_REGISTRATION( VariableContinuousTest );
