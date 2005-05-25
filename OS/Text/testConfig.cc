#include "Ravl/Text/ConfigFile.hh"
#include "Ravl/Option.hh" 
#include <assert.h>


using namespace RavlN ; 


/*
int main (void) 
{
ConfigFileC config(true) ;
config["var1"] = "data1" ; 
config["var2"] = "data2" ; 
config["var3"] = "data3" ; 


config.Section("section1") = ConfigFileC(true) ; 
ConfigFileC section1 = config.Section("section1") ; 
section1["var1"] = "data1" ; 
section1["var2"] = "data1" ; 
section1["var3"] = "data1" ; 


cerr << "\nDumping config " ; 
config.Dump(cerr) ;


//ConfigFileC section1(true) ; 
//section1.AddVar( "var1", "data1", TextFragmentC() ) ; 
//section1.AddVar( "var2", "data2", TextFragmentC() ) ; 
//section1.AddVar( "var3", "data3", TextFragmentC() ) ; /
//cerr << "\nDumping Section " ; 
//section1.Dump(cerr) ; 

//config.AddSection( StringC("section1"), section1) ; 
//config.Dump(cerr) ; 

exit (0) ; 
return 0 ; 
}

*/



int main (int argc, char ** argv) 
{

OptionC opts ( argc,argv) ; 
bool binary = opts.Boolean("b", true, "binary test" ) ; 
bool write = opts.Boolean("w", false, "write (or read)" ) ; 
StringC file = opts.String("f", "-", "file") ; 
opts.Check() ; 

// write out
OStreamC out ; 
BinOStreamC binout  ;
BinIStreamC binin ; 
IStreamC in ; 
ConfigFileC config ( true ) ; 


if ( write )  {  
StringC fn ("test.config") ; 
config = ConfigFileC (fn) ; 

 if ( binary) {
   binout = BinOStreamC (file) ; 
   config.Save(binout) ;  }
 else {
   assert(0) ; 
   //out = OStreamC (file) ; 
   //config.Save(out) ;  }
  }
}
// read in 
else  { 
  if ( binary ) {
    binin = BinIStreamC (file) ; 
    config.Load(binin) ;} 
  else {
assert(0) ; 
    //    in = IStreamC (file) ; 
    // config.Load(in) ; 
}


  //cout << config.ListSections() ; 
  //config.Dump(cout,1) ; 


  //ConfigFileC tmp = config.Section("Section1") ; 
  //  if ( tmp.IsValid() ) 
cerr << "\n\n" ;   
config.Dump(cerr) ; 
  

}

return 0 ; 
}

