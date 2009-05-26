#include <cppunit/extensions/HelperMacros.h>

#include "Ravl/Prob/VariableBoolean.hh"

using namespace RavlProbN;
	
class VariableBooleanTest: public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE( VariableBooleanTest );
	CPPUNIT_TEST( testValue );
	CPPUNIT_TEST_SUITE_END();
private:
	VariableBooleanC m_variable;
public:
	void setUp() {
		m_variable = VariableBooleanC("variable");
	}
	
	void tearDown() {
	}
	
	void testValue() {
		CPPUNIT_ASSERT_EQUAL( StringC("variable"), m_variable.Value(true) );
		CPPUNIT_ASSERT_EQUAL( StringC("¬variable"), m_variable.Value(false) );
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( VariableBooleanTest );
