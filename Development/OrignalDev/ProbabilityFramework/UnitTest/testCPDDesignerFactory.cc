#include <cppunit/extensions/HelperMacros.h>

#include "Ravl/Prob/CPDDesignerFactory.hh"
#include "Ravl/Prob/VariableBoolean.hh"
#include "Ravl/Prob/VariableContinuous.hh"
#include "Ravl/Prob/CPDDesignerContinuousDiscrete1.hh"

using namespace RavlProbN;
	
class CPDDesignerFactoryTest: public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE( CPDDesignerFactoryTest );
	CPPUNIT_TEST( testGetCPDDesigner );
	CPPUNIT_TEST( testGetCPDDesigner_Invalid );
	CPPUNIT_TEST_SUITE_END();
private:
	VariableC m_variable;
	VariableSetC m_parentVariables;
	CPDDesignerFactoryC m_factory;
public:
	void setUp() {
		m_factory = CPDDesignerFactoryC::GetInstance();
		m_variable = VariableContinuousC("Temperature", RealRangeC(-273.0, 100.0));
		HSetC<VariableC> varSet;
		varSet.Insert(VariableBooleanC("Hot"));
		m_parentVariables = VariableSetC(varSet);
	}
	
	void tearDown() {
	}
	
	void testGetCPDDesigner() {
		CPDDesignerC designer = m_factory.GetCPDDesigner(m_variable, m_parentVariables);
		CPPUNIT_ASSERT( designer.IsValid() );
		CPDDesignerContinuousDiscrete1C cd1Designer(designer);
		CPPUNIT_ASSERT( cd1Designer.IsValid() );
	}
	
	void testGetCPDDesigner_Invalid() {
		CPPUNIT_ASSERT_THROW( m_factory.GetCPDDesigner(VariableBooleanC("Yum"), m_parentVariables), ExceptionC );
	}
	
};

CPPUNIT_TEST_SUITE_REGISTRATION( CPDDesignerFactoryTest );
