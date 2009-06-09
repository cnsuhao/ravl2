#ifndef MODULES_LIST_HH
#define MODULES_LIST_HH

//! docentry="Ravl.API.OS.Multithreading Framework.Example"
//! userlevel = "Normal"

#include "Ravl/Threads/MemModule.hh"
#include "Ravl/Threads/MemModules.hh"


DECLARE_RAVL_MEM_MODULE(UnWarp);
//: Extracts frames from video source and conditions them

DECLARE_RAVL_MEM_MODULE(ShotDet);
//: Shot detector


inline void RegisterModules()
{
  UnWarpC UnWarp("frame");
  ShotDetC ShotDet("shotBoundary");
}
//: Creates the module objects

#endif
