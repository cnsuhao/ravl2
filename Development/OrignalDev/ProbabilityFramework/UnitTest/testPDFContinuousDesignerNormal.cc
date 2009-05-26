#include <cppunit/extensions/HelperMacros.h>

#include "Ravl/Prob/PDFContinuousDesignerNormal.hh"
#include "Ravl/Prob/PDFNormal.hh"
#include "Ravl/Random.hh"

using namespace RavlProbN;
	
class PDFContinuousDesignerNormalTest: public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE( PDFContinuousDesignerNormalTest );
	CPPUNIT_TEST( testCreatePDF );
	CPPUNIT_TEST_SUITE_END();
private:
    VariableContinuousC m_variable;
	PDFContinuousDesignerNormalC m_designer;
public:
	void setUp() {
		m_variable = VariableContinuousC("Normal", RealRangeC(-10.0, 10.0));
		m_designer = PDFContinuousDesignerNormalC::GetInstance();
	}
	
	void tearDown() {
	}
	
	void testCreatePDF() {
		DListC<RealT> realSamples;
		for (int i = 0; i < 1000; i++) {
			realSamples.InsLast(RandomGauss());
		}
		PDFNormalC pdf = m_designer.CreatePDF(m_variable, realSamples);
		CPPUNIT_ASSERT( pdf.IsValid() );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.0, pdf.Mean(), 0.1 );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0, Sqrt(pdf.Variance()), 0.1 );
	}
	
};

CPPUNIT_TEST_SUITE_REGISTRATION( PDFContinuousDesignerNormalTest );
