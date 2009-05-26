#include <cppunit/extensions/HelperMacros.h>

#include "Ravl/Prob/DomainDiscrete.hh"

using namespace RavlProbN;
	
class DomainDiscreteTest: public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE( DomainDiscreteTest );
    CPPUNIT_TEST( testInsert );
    CPPUNIT_TEST( testInsert_AlreadyIn );
    CPPUNIT_TEST( testRemove );
    CPPUNIT_TEST( testRemove_NotContained );
    CPPUNIT_TEST( testContains_true );
    CPPUNIT_TEST( testContains_false );
    CPPUNIT_TEST( testIndex );
    CPPUNIT_TEST( testValue );
    CPPUNIT_TEST( testSize );
    CPPUNIT_TEST( testIterator );
    CPPUNIT_TEST( testToString );
    CPPUNIT_TEST( testEquality );
	CPPUNIT_TEST_SUITE_END();
private:
	DomainDiscreteC m_domain;
public:
	void setUp() {
		m_domain = DomainDiscreteC();
		m_domain.Insert("rain");
		m_domain.Insert("cloudy");
		m_domain.Insert("sunny");
		m_domain.Insert("snow");
	}
	
	void tearDown() {
	}
	
    void testInsert() {
    	m_domain.Insert("hail");
    	CPPUNIT_ASSERT_EQUAL( (SizeT)5, m_domain.Size() );
    }
    
    void testInsert_AlreadyIn() {
    	CPPUNIT_ASSERT_THROW( m_domain.Insert("snow"), ExceptionC );
    }
    
	void testRemove() {
		m_domain.Remove("snow");
    	CPPUNIT_ASSERT_EQUAL( (SizeT)3, m_domain.Size() );
	}
	
    void testRemove_NotContained() {
    	CPPUNIT_ASSERT_THROW( m_domain.Remove("hail"), ExceptionC );
    }
    
	void testContains_true() {
		CPPUNIT_ASSERT( m_domain.Contains("rain") );
		CPPUNIT_ASSERT( m_domain.Contains("cloudy") );
		CPPUNIT_ASSERT( m_domain.Contains("sunny") );
		CPPUNIT_ASSERT( m_domain.Contains("snow") );
	}
	
	void testContains_false() {
		CPPUNIT_ASSERT_EQUAL( m_domain.Contains("hail"), false );
    }
    
    void testIndex() {
    	CPPUNIT_ASSERT_EQUAL( IndexC(0), m_domain.Index("rain") );
    	CPPUNIT_ASSERT_EQUAL( IndexC(1), m_domain.Index("cloudy") );
    	CPPUNIT_ASSERT_EQUAL( IndexC(2), m_domain.Index("sunny") );
    	CPPUNIT_ASSERT_EQUAL( IndexC(3), m_domain.Index("snow") );
    	CPPUNIT_ASSERT_THROW( m_domain.Index("hail"), ExceptionC );
    }
    
	void testValue() {
		CPPUNIT_ASSERT_EQUAL( StringC("rain"), m_domain.Value(0) );
		CPPUNIT_ASSERT_EQUAL( StringC("cloudy"), m_domain.Value(1) );
		CPPUNIT_ASSERT_EQUAL( StringC("sunny"), m_domain.Value(2) );
		CPPUNIT_ASSERT_EQUAL( StringC("snow"), m_domain.Value(3) );
    	CPPUNIT_ASSERT_THROW( m_domain.Value(-1), ExceptionC );
    	CPPUNIT_ASSERT_THROW( m_domain.Value(4), ExceptionC );
    }
    
    void testSize() {
    	CPPUNIT_ASSERT_EQUAL( (SizeT)4, m_domain.Size() );
    }
    
    void testIterator() {
    	SizeT count = 0;
    	for (SArray1dIterC<StringC> it = m_domain.Iterator(); it; it++, count++) {
    		CPPUNIT_ASSERT_EQUAL( IndexC(count), m_domain.Index(*it) );
    	}
    	CPPUNIT_ASSERT_EQUAL( m_domain.Size(), count );
    }
    
    void testToString() {
		CPPUNIT_ASSERT( m_domain.ToString() == "<rain,cloudy,sunny,snow>" );
    }
    
    void testEquality() {
		DomainDiscreteC secondDomainDiscrete;
		secondDomainDiscrete.Insert("rain");
		secondDomainDiscrete.Insert("cloudy");
		secondDomainDiscrete.Insert("sunny");
		secondDomainDiscrete.Insert("snow");
		DomainDiscreteC thirdDomainDiscrete;
		thirdDomainDiscrete.Insert("rain");
		thirdDomainDiscrete.Insert("cloudy");
		CPPUNIT_ASSERT( m_domain == m_domain );
		CPPUNIT_ASSERT( m_domain == secondDomainDiscrete );
		CPPUNIT_ASSERT( !(m_domain == thirdDomainDiscrete) );
		CPPUNIT_ASSERT( m_domain != thirdDomainDiscrete );
		CPPUNIT_ASSERT( !(m_domain != secondDomainDiscrete) );
    }
		
};

CPPUNIT_TEST_SUITE_REGISTRATION( DomainDiscreteTest );
