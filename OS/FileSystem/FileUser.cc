//////////////////////////////////////////////////////////////
//! author="Charles Galambos"
//! rcsid="$Id$"

#include "amma/FilePerm.hh"
#include "amma/UserInfo.hh"
#include "amma/Filename.hh"
#include "amma/ChildProc.hh"
#include "amma/StrStream.hh"

#ifndef VISUAL_CPP
#include <unistd.h>
#else
#include <direct.h>
#endif

//static BooleanT gotPAWD = TRUE; // Try and use PAWD, if false don't bother.

//////////////////////////
//: Get information on owner.

UserInfoC FilePermissionC::OwnerInfo() const 
{ return UserInfoC(Owner()); }

/////////////////////////////
//: Get information on owner of file.

UserInfoC FilenameC::OwnerInfo() const 
{ return UserInfoC(Permissions().Owner()); }

/////////////////////////////////
//: Make an absolute path.
// If removeAMD is TRUE, any automount prefix will also
// be remove from the path.

FilenameC FilenameC::Absolute(BooleanT removeAMD) const 
{
  char buff[1024];
  FilenameC ret = (*this);
  if(ret.IsEmpty())
    ret = getcwd(buff,1024);
  while(ret[0] != '/') {
    if(ret == StringC(".")) {
      ret = getcwd(buff,1024);
      break;
    }
    if(ret.contains("./",0)) {
      ret = StringC(getcwd(buff,1024)) + ret.after(".");
      break;
    }
    if(ret[0] == '~') { // Relative to home directory ?
      StringC tmp = ret.after(1);
      StringC userId = tmp.before("/");
      StringC theRest = tmp.after("/");
      if(userId.IsEmpty())
	userId = tmp; // Maybe only user is defined.
      UserInfoC ui(userId);
      ret = ui.HomeDir() + '/' + theRest;
      break;
    }
    ret = StringC(getcwd(buff,1024)) + '/' + ret;
    break;
  };
  
  if(!removeAMD)
    return ret; // Done.
  if(!ret.contains(AMDPrefix,0))
    return ret; // No AMD prefix to remove.
  
  // Removee the AMD prefix. (if possible.)
  FilenameC org(ret);
  BooleanT orgExists = org.PathComponent().Exists(); // Check directory exists...
  ret = StringC(ret.after(AMDPrefix)); // Skip AMD prefix.
  ret = StringC(ret.from('/')); // Skip matchine name.
  FilenameC newun(ret);
  // Is everything ok ?
  if(orgExists) { // Only if we can tell...
    if(!newun.PathComponent().Exists()) {
#if 0
      if(!gotPAWD)
	return org; // Just go with original...
      // Try pawd.
      ChildProcessC pawd(StringC("pawd ") + org,TRUE);
      if(!pawd.IsRunning()) {
	gotPAWD = FALSE;
	cerr << "WARNING: Failed to run 'pawd'. \n";
	return org; 
      }
      // And hope 'pawd' doesn't hang...
      OStrStreamC strStrm;
      if(pawd.StdOut().CopyTo(strStrm,1000) <= 0) {
	cerr << "WARNING: Error reading results from 'pawd'. \n";
	return org;
      }     
      if(!pawd.Wait(5)) {
	gotPAWD = FALSE;
	cerr << "WARNING: Timeout waiting for 'pawd'. \n";
	pawd.Terminate(1);
	return org; 
      }
      // Give result of out investigations to user.
      return strStrm.String();
#else
      return org;
#endif
    }
  }
  return ret;
}
