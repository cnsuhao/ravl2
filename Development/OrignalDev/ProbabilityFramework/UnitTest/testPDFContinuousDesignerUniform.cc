#include <cppunit/extensions/HelperMacros.h>

#include "Ravl/Prob/PDFContinuousDesignerUniform.hh"
#include "Ravl/Prob/PDFUniform.hh"
#include "Ravl/Random.hh"

using namespace RavlProbN;
	
class PDFContinuousDesignerUniformTest: public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE( PDFContinuousDesignerUniformTest );
	CPPUNIT_TEST( testCreatePDF );
	CPPUNIT_TEST_SUITE_END();
private:
    VariableContinuousC m_variable;
	PDFContinuousDesignerUniformC m_designer;
public:
	void setUp() {
		m_variable = VariableContinuousC("Uniform", RealRangeC(-10.0, 10.0));
		m_designer = PDFContinuousDesignerUniformC::GetInstance();
	}
	
	void tearDown() {
	}
	
	void testCreatePDF() {
		DListC<RealT> realSamples;
		for (int i = 0; i < 1000; i++) {
			realSamples.InsLast(Random1());
		}
		PDFUniformC pdf = m_designer.CreatePDF(m_variable, realSamples);
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 0.0, pdf.Interval().Min(), 0.01 );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0, pdf.Interval().Max(), 0.01 );
	}
	
};

CPPUNIT_TEST_SUITE_REGISTRATION( PDFContinuousDesignerUniformTest );
