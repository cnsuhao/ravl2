 #include <iostream>
 #include <cstdlib>

 using namespace std;

 const bool Test_Command(const char* const test_name,
                         const char* const command,
                         const int expected_ret_val)
 {
   // Assume we've failed!
   bool passed = false;

   cerr<<"## Start command test: "<<test_name<<endl;

   cerr<<"-- Start: Running command: "<<command<<endl;
   const int ret_val = system(command);
   cerr<<"-- End: Running command"<<endl;

   // Did we pass?
   if(ret_val == expected_ret_val) {
     passed = true;
   }

   cerr<<"Test "<<(passed?"passed":"failed")<<" with return value: "<<ret_val<<endl;

   cerr<<"## End command test: "<<test_name<<endl;

   return passed;
 }

 int main(int argc, char* argv[])
 {
   // Assume we've failed!
   bool passed = false;

   // Make sure we're called with no arguments because we're not
   // expecting any.
   if(argc == 1) {
     const char command[] = PROJECT_OUT "/bin/imgdiff \"@str:P2 2 2 255 0 255 255 0\" \"@str:P2 2 2 255 255 0 0 255\" -o /dev/null";

     passed = Test_Command("imgdiff test", command, 0);
   }

   return passed?0:1;
 }
