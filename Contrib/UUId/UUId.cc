
#include "Ravl/MTLocks.hh"
#include "Ravl/UUId.hh"


#if RAVL_COMPILER_VISUALCPP
  #include <Rpc.h>
  #include <comutil.h>
  #include <atlbase.h>

#else
  #include <uuid/uuid.h>
#endif

namespace OmniN {
  using namespace RavlN;
  
  //: Geneate a UUId in string form.
  
  
  StringC GenerateUUId() 
  {
    
    // Not sure if these routines are thread safe, so lock to be sure.
    
    MTWriteLockC lock(4);
    StringC buffer;

#if RAVL_COMPILER_VISUALCPP    

    char* emptyString = "";
    GUID newGUID = GUID_NULL;
    if(::CoCreateGuid(&newGUID) == S_OK)
    {
      const int maxChar = 256;
      OLECHAR szGuid[maxChar]={0};
      ::StringFromGUID2(newGUID, szGuid, maxChar);
      CComBSTR strComGUID = szGuid;
   
      _bstr_t bs((BSTR)strComGUID);
      
      char* strBuff = ((char*)bs == NULL ? emptyString : (char*)bs);
      buffer = StringC(strBuff);
    }
    else
    {
      buffer = "";
    }
    

#else

    uuid_t uuid;
    uuid_generate(uuid);
    
    char strGUID[256];
    uuid_unparse(uuid,strGUID);
    buffer = StringC(strGUID);
#endif

    return buffer;
  }
  
}
