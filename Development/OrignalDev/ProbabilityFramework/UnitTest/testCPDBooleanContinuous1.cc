#include <cppunit/extensions/HelperMacros.h>

#include "Ravl/Prob/CPDBooleanContinuous1.hh"

using namespace RavlProbN;
	
class CPDBooleanContinuous1Test: public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE( CPDBooleanContinuous1Test );
    CPPUNIT_TEST_SUITE_END();
private:
	CPDBooleanContinuous1C m_cpd;
public:
	void setUp() {
	}
	
	void tearDown() {
	}
	
};

CPPUNIT_TEST_SUITE_REGISTRATION( CPDBooleanContinuous1Test );
