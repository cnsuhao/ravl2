#include <cppunit/extensions/HelperMacros.h>

#include "Ravl/Prob/PDFDesignerFactory.hh"
#include "Ravl/Prob/PDFNormal.hh"
#include "Ravl/Prob/PDFUniform.hh"
#include "Ravl/Random.hh"

using namespace RavlProbN;
	
class PDFDesignerFactoryTest: public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE( PDFDesignerFactoryTest );
	CPPUNIT_TEST( testDesignPDFContinuousNormal );
	CPPUNIT_TEST( testDesignPDFContinuousUniform );
	CPPUNIT_TEST_SUITE_END();
private:
    VariableContinuousC m_variable;
public:
	void setUp() {
		m_variable = VariableContinuousC("Continuous", RealRangeC(-10.0, 10.0));
	}
	
	void tearDown() {
	}
	
	void testDesignPDFContinuousNormal() {
		DListC<RealT> realSamples;
		for (int i = 0; i < 1000; i++) {
			realSamples.InsLast(RandomGauss());
		}
		PDFNormalC pdf = PDFDesignerFactoryC::GetInstance().DesignPDFContinuous(m_variable, realSamples);
		CPPUNIT_ASSERT( pdf.IsValid() );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.0, pdf.Mean(), 0.1 );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0, Sqrt(pdf.Variance()), 0.1 );
	}
	
	void testDesignPDFContinuousUniform() {
		DListC<RealT> realSamples;
		for (int i = 0; i < 10000; i++) {
			realSamples.InsLast(Random1());
		}
		PDFUniformC pdf = PDFDesignerFactoryC::GetInstance().DesignPDFContinuous(m_variable, realSamples);
		CPPUNIT_ASSERT( pdf.IsValid() );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.0, pdf.Interval().Min(), 0.01 );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0, pdf.Interval().Max(), 0.01 );
	}
	
};

CPPUNIT_TEST_SUITE_REGISTRATION( PDFDesignerFactoryTest );
