#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/qt/TestRunner.h>

int main(int argc, char* argv[])
{
  CppUnit::QtUi::TestRunner runner;
  runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() );
  runner.run( true );
} 
