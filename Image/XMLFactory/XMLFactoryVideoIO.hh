// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2009, OmniPerception Ltd
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_XMLFACTORYVIDEOIO_HEADER
#define RAVL_XMLFACTORYVIDEOIO_HEADER 1
//! lib=RavlImageXMLFactory
//! author=Charles Galambos
//! docentry=Ravl.API.Images.XMLFactory

#include "Ravl/XMLFactory.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/HashIter.hh"
#include "Ravl/OS/SysLog.hh"

namespace RavlN {
  
  template<typename PixelT>
  class XMLFactoryVideoIORegisterC {
  public:
    //! Default factory function.
    
    static RavlN::RCWrapAbstractC FactoryFunc(const XMLFactoryContextC &node)
    {
      RavlN::DPIPortC<RavlImageN::ImageC<PixelT> > iport;
      RavlN::StringC filename = node.AttributeString("filename","");
      if(!RavlN::OpenISequence(iport,filename)) {
        SysLog(SYSLOG_ERR,"Failed to open '%s' ",filename.chars());
        throw RavlN::ExceptionOperationFailedC("Failed to open file. ");
      }
      
      // Set stream attributes
      for(RavlN::HashIterC<RavlN::StringC,RavlN::StringC> it(node.Node().Data());it;it++) {
        if(it.Key() == "filename" || it.Key() == "typename")
          continue;
        iport.SetAttr(it.Key(),it.Data());
      }
      return RavlN::RCWrapC<RavlN::DPIPortC<RavlImageN::ImageC<PixelT> > >(iport);
    }
    
    //! Constructor.
    
    XMLFactoryVideoIORegisterC(const char *nameOfType)
    {
      //std::cerr << "Registering '" << nameOfType << "' \n";
      RavlN::AddTypeName(typeid(RavlN::DPIPortC<RavlImageN::ImageC<PixelT> >),nameOfType);
      XMLFactoryC::RegisterTypeFactory(typeid(RavlN::DPIPortC<RavlImageN::ImageC<PixelT> >),& XMLFactoryVideoIORegisterC<PixelT>::FactoryFunc);
    }
  };
  
  
}

#endif
