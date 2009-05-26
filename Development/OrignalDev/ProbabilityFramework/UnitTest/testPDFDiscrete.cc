#include <cppunit/extensions/HelperMacros.h>

#include "Ravl/Prob/PDFDiscrete.hh"
#include "Ravl/Prob/VariablePropositionDiscrete.hh"

using namespace RavlProbN;
	
class PDFDiscreteTest: public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE( PDFDiscreteTest );
	CPPUNIT_TEST( testCreateSubset );
	CPPUNIT_TEST( testCreateNegative );
	CPPUNIT_TEST( testCreateInvalidVar );
	CPPUNIT_TEST( testCreateSum1 );
	CPPUNIT_TEST( testToString );
	CPPUNIT_TEST( testMeasureProbability );
	CPPUNIT_TEST_SUITE_END();
private:
	DomainDiscreteC m_domain;
	VariableDiscreteC m_variableWeather;
	RCHashC<VariablePropositionDiscreteC,RealT> m_probabilityLookupTable;
	PDFDiscreteC m_pdf;
public:
	void setUp() {
		m_domain = DomainDiscreteC();
		m_domain.Insert("sunny");
		m_domain.Insert("rain");
		m_domain.Insert("cloudy");
		m_domain.Insert("snow");
		m_variableWeather = VariableDiscreteC("Weather", m_domain);
		m_probabilityLookupTable[VariablePropositionDiscreteC(m_variableWeather, "sunny")] = 0.1;
		m_probabilityLookupTable[VariablePropositionDiscreteC(m_variableWeather, "rain")] = 0.2;
		m_probabilityLookupTable[VariablePropositionDiscreteC(m_variableWeather, "cloudy")] = 0.3;
		m_probabilityLookupTable[VariablePropositionDiscreteC(m_variableWeather, "snow")] = 0.4;
		m_pdf = PDFDiscreteC(m_variableWeather, m_probabilityLookupTable);
	}
	
	void tearDown() {
	}
	
	void testCreateSubset() {
		m_probabilityLookupTable.Del(VariablePropositionDiscreteC(m_variableWeather, "snow"));
		CPPUNIT_ASSERT_THROW( PDFDiscreteC(m_variableWeather, m_probabilityLookupTable), ExceptionC );
	}
	
	void testCreateNegative() {
		m_probabilityLookupTable[VariablePropositionDiscreteC(m_variableWeather, "sunny")] = -0.1;
		CPPUNIT_ASSERT_THROW( PDFDiscreteC(m_variableWeather, m_probabilityLookupTable), ExceptionC );
	}
	
	void testCreateInvalidVar() {
		m_probabilityLookupTable[VariablePropositionDiscreteC(VariableDiscreteC("Weather2", m_domain), "sunny")] = 0.1;
		CPPUNIT_ASSERT_THROW( PDFDiscreteC(m_variableWeather, m_probabilityLookupTable), ExceptionC );
	}
	
	void testCreateSum1() {
		m_probabilityLookupTable[VariablePropositionDiscreteC(m_variableWeather, "sunny")] = 0.2;
		CPPUNIT_ASSERT_THROW( PDFDiscreteC(m_variableWeather, m_probabilityLookupTable), ExceptionC );
	}
	
	void testToString() {
		CPPUNIT_ASSERT_EQUAL( StringC("Weather=<sunny,rain,cloudy,snow>=<0.100000,0.200000,0.300000,0.400000>"), m_pdf.ToString() );
	}
	
	void testMeasureProbability() {
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.1, m_pdf.MeasureProbability(VariablePropositionDiscreteC(m_variableWeather, "sunny")), 0.01 );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.2, m_pdf.MeasureProbability(VariablePropositionDiscreteC(m_variableWeather, "rain")), 0.01 );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.3, m_pdf.MeasureProbability(VariablePropositionDiscreteC(m_variableWeather, "cloudy")), 0.01 );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.4, m_pdf.MeasureProbability(VariablePropositionDiscreteC(m_variableWeather, "snow")), 0.01 );
		CPPUNIT_ASSERT_THROW( m_pdf.MeasureProbability(VariablePropositionC()), ExceptionC );
	}
			
};

CPPUNIT_TEST_SUITE_REGISTRATION( PDFDiscreteTest );
