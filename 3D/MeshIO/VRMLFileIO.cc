// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#include "Ravl/3D/VRMLFileIO.hh"
#include "Ravl/SArray1dIter.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/DP/FileFormatIO.hh"
//! rcsid="$Id$"
//! lib=Ravl3DIO

namespace Ravl3DN {

  // TriMesh VRML File IO /////////////////////////////////////////////

  //: Open file.
  DPIVRMLFileBodyC::DPIVRMLFileBodyC(const StringC &fn)
    : inf(fn),
      done(false)
  {}
  
  //: Open file.
  DPIVRMLFileBodyC::DPIVRMLFileBodyC(IStreamC &is)
    : inf(is),
      done(false)
  {}
  
  //: Is valid data ?
  bool DPIVRMLFileBodyC::IsGetEOS() const {
    return !done && inf;
  }
  
  //: Get next piece of data.
  TriMeshC DPIVRMLFileBodyC::Get() {
    if(done)
      return TriMeshC();

    // TO BE IMPLEMENTED
    cerr << "Error: not implemented yet!\n";
    return TriMeshC();

    // Done
    return TriMeshC();
  }

  ////////////////////////////////////////////////////////////////////////////////////////

  //: Open file.
  DPOVRMLFileBodyC::DPOVRMLFileBodyC(const StringC &fn)
    : outf(fn),
      done(false)
  {}
  
  //: Open file.
  DPOVRMLFileBodyC::DPOVRMLFileBodyC(OStreamC &is)
    : outf(is),
      done(false)
  {}
  
  //: Put data.
  bool DPOVRMLFileBodyC::Put(const TriMeshC &dat) {
    if(done || !outf)
      return false;

    // TO BE IMPLEMENTED
    cerr << "Error: not implemented yet!\n";
    return false;

    // Done
    return true;
  }
  
  //: Is port ready for data ?
  bool DPOVRMLFileBodyC::IsPutReady() const 
  { return !done && outf; }

  // TexTriMesh VRML File IO /////////////////////////////////////////////

  //: Open file.
  DPITexVRMLFileBodyC::DPITexVRMLFileBodyC(const StringC &fn)
    : inf(fn),
      done(false)
  {
    path = FilenameC(fn).PathComponent();
    if (!path.IsEmpty()) path += filenameSeperator ;
  }
  
  //: Is valid data ?
  bool DPITexVRMLFileBodyC::IsGetEOS() const {
    return !done && inf;
  }
  
  //: Get next piece of data.
  TexTriMeshC DPITexVRMLFileBodyC::Get() {
    if(done)
      return TexTriMeshC();

    // TO BE IMPLEMENTED
    cerr << "Error: not implemented yet!\n";
    return TexTriMeshC();


    // Done
    return TexTriMeshC();
  }

  ////////////////////////////////////////////////////////////////////////////////////////

  //: Open file.
  DPOTexVRMLFileBodyC::DPOTexVRMLFileBodyC(const StringC &fn)
    : outf(fn),
      done(false)
  {
    path = FilenameC(fn).PathComponent();
    if (!path.IsEmpty()) path += filenameSeperator ;
  }
  
  //: Put data.
  bool DPOTexVRMLFileBodyC::Put(const TexTriMeshC &dat) 
  {
    if(done || !outf)
      return false;

    // TO BE IMPLEMENTED
    cerr << "Error: not implemented yet!\n";
    return false;

    // Done
    return true;
  }
  
  //: Is port ready for data ?
  bool DPOTexVRMLFileBodyC::IsPutReady() const 
  { return !done && outf; }

}
