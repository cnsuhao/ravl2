
#include "Ravl/Text/TextFile.hh"
#include "Ravl/Text/TextCursor.hh"
#include "Ravl/Text/TemplateFile.hh"
#include "Ravl/StrStream.hh"

using namespace RavlN;

int testTextFile();

int main() {
  int ln;
  if((ln = testTextFile()) != 0) {
    cerr << "Error line " << ln << "\n";
    return 1;
  }
  return 0;
}


int testTextFile() {
  StringC tmp("Greetings");
  StrOStreamC oss;  
  {
    TextFileC txtf(tmp,true,true);
    TemplateFileC tf(txtf ,oss);
    while(tf.IsElm()) {
      StringC &ip = tf.Next();
      if(ip.IsEmpty())
	break;
      cerr << "Got arg! " << ip << "\n";
      return __LINE__;
    }
    oss << flush;
  }
  StringC to = oss.String();
  cerr << "Out='" << to << "'\n";
  if(to != tmp) return __LINE__;  
  return 0;
}
