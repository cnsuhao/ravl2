#include <cppunit/extensions/HelperMacros.h>

#include "Ravl/Prob/CPDDiscreteDiscrete.hh"
#include "Ravl/Prob/VariablePropositionBoolean.hh"

using namespace RavlProbN;
	
class CPDDiscreteDiscreteTest: public CppUnit::TestCase {
  CPPUNIT_TEST_SUITE( CPDDiscreteDiscreteTest );
  CPPUNIT_TEST( testCreate_Invalid );
  CPPUNIT_TEST( testConditionalProbability );
  CPPUNIT_TEST( testConditionalProbability_Invalid );
  CPPUNIT_TEST( testConditionalDistribution );
  CPPUNIT_TEST( testConditionalDistribution_Invalid );
  CPPUNIT_TEST( testVariable );
  CPPUNIT_TEST( testParentVariableSet );
  CPPUNIT_TEST_SUITE_END();
  
private:
  DomainDiscreteC m_domain;
  VariableC m_variable;
  VariablePropositionC m_sunny,m_rain,m_cloudy,m_snow,m_summer,m_notSummer;
  VariableSetC m_parentVariables;
  RCHashC<PropositionSetC,PDFDiscreteC> m_probabilityDistributionTable;
  CPDDiscreteDiscreteC m_cpd;
  
public:
  void setUp() {
    m_domain = DomainDiscreteC();
    m_domain.Insert("sunny");
    m_domain.Insert("rain");
    m_domain.Insert("cloudy");
    m_domain.Insert("snow");
    
    m_variable = VariableDiscreteC("Weather", m_domain);
    m_parentVariables = VariableSetC(VariableBooleanC("Summer"));
    VariableBooleanC varSummer("Summer");
    m_summer = VariablePropositionBooleanC(varSummer, true);
    
    RCHashC<VariablePropositionDiscreteC,RealT> probabilityLookupTableSummer;
    m_sunny = VariablePropositionDiscreteC(m_variable, "sunny");
    m_rain = VariablePropositionDiscreteC(m_variable, "rain");
    m_cloudy = VariablePropositionDiscreteC(m_variable, "cloudy");
    m_snow = VariablePropositionDiscreteC(m_variable, "snow");
    probabilityLookupTableSummer.Insert(m_sunny, 0.5);
    probabilityLookupTableSummer.Insert(m_rain, 0.2);
    probabilityLookupTableSummer.Insert(m_cloudy, 0.3);
    probabilityLookupTableSummer.Insert(m_snow, 0.0);
    PDFDiscreteC pdfSummer(m_variable, probabilityLookupTableSummer);
    
    m_probabilityDistributionTable.Insert(PropositionSetC(m_parentVariables, m_summer), pdfSummer);
    m_notSummer = VariablePropositionBooleanC(varSummer, false);
    
    RCHashC<VariablePropositionDiscreteC,RealT> probabilityLookupTableNotSummer;
    probabilityLookupTableNotSummer.Insert(m_sunny, 0.1);
    probabilityLookupTableNotSummer.Insert(m_rain, 0.2);
    probabilityLookupTableNotSummer.Insert(m_cloudy, 0.4);
    probabilityLookupTableNotSummer.Insert(m_snow, 0.3);
    PDFDiscreteC pdfNotSummer(m_variable, probabilityLookupTableNotSummer);
    
    m_probabilityDistributionTable.Insert(PropositionSetC(m_parentVariables, m_notSummer), pdfNotSummer);
    m_cpd = CPDDiscreteDiscreteC(m_variable, m_parentVariables, m_probabilityDistributionTable);
  }
	
  void tearDown() {
  }
  
  void testCreate_Invalid() {
    CPPUNIT_ASSERT_THROW( CPDDiscreteDiscreteC(VariableC(), m_parentVariables, m_probabilityDistributionTable), ExceptionC );
    CPPUNIT_ASSERT_THROW( CPDDiscreteDiscreteC(m_variable, VariableSetC(), m_probabilityDistributionTable), ExceptionC );
    CPPUNIT_ASSERT_THROW( CPDDiscreteDiscreteC(m_variable, m_parentVariables, RCHashC<PropositionSetC,PDFDiscreteC>()), ExceptionC );
  }
	
  void testConditionalProbability() {
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.5, m_cpd.ConditionalProbability(m_sunny, m_summer), 0.01 );
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.2, m_cpd.ConditionalProbability(m_rain, m_notSummer), 0.01 );
  }
    
  void testConditionalProbability_Invalid() {
    CPPUNIT_ASSERT_THROW( m_cpd.ConditionalProbability(m_summer, m_sunny), ExceptionC );
  }
    
  void testConditionalDistribution() {
    CPPUNIT_ASSERT_EQUAL( StringC("Weather=<sunny,rain,cloudy,snow>=<0.500000,0.200000,0.300000,0.000000>"), m_cpd.ConditionalDistribution(m_summer).ToString() );
  }
    
  void testConditionalDistribution_Invalid() {
    CPPUNIT_ASSERT_THROW( m_cpd.ConditionalDistribution(m_sunny), ExceptionC );
  }
    
  void testVariable() {
    CPPUNIT_ASSERT_EQUAL( (VariableC)m_variable, m_cpd.Variable() );
  }
	
  void testParentVariableSet() {
    CPPUNIT_ASSERT( m_cpd.ParentVariableSet().Size() == 1 );
  }
    
};

CPPUNIT_TEST_SUITE_REGISTRATION( CPDDiscreteDiscreteTest );
