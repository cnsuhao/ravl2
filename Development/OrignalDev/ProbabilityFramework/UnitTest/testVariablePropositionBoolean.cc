#include <cppunit/extensions/HelperMacros.h>

#include "Ravl/Prob/VariablePropositionBoolean.hh"

using namespace RavlProbN;
	
class VariablePropositionBooleanTest: public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE( VariablePropositionBooleanTest );
	CPPUNIT_TEST( testBooleanValue );
	CPPUNIT_TEST( testToString );
	CPPUNIT_TEST_SUITE_END();
private:
	VariableBooleanC m_variable;
	VariablePropositionBooleanC m_valueTrue;
	VariablePropositionBooleanC m_valueFalse;
public:
	void setUp() {
		m_variable = VariableBooleanC("variable");
		m_valueTrue = VariablePropositionBooleanC(m_variable, true);
		m_valueFalse = VariablePropositionBooleanC(m_variable, false);
	}
	
	void tearDown() {
	}
	
	void testBooleanValue() {
		CPPUNIT_ASSERT( m_valueTrue.BooleanValue() );
		CPPUNIT_ASSERT( m_valueFalse.BooleanValue() == false );
	}
	
	void testToString() {
		CPPUNIT_ASSERT_EQUAL( StringC("variable"), m_valueTrue.ToString() );
		CPPUNIT_ASSERT_EQUAL( StringC("¬variable"), m_valueFalse.ToString() );
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( VariablePropositionBooleanTest );
