// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlOS

#include "Ravl/OS/UserInfo.hh"
#include "Ravl/Exception.hh"

#ifndef VISUAL_CPP
#include <pwd.h>
#include <unistd.h>
#endif
#include <errno.h>
#include <stdio.h>

#define PWBUFFLEN 2048

namespace RavlN {

  // FIXME :- This code is not always re-entrant.
  
  ///////////////////////
  // Default constructor.
  
  UserInfoC::UserInfoC()
    : exists(false),
    uid(0),
    login("")
  {}
  
  ///////////////////////
  // From login.
  
  UserInfoC::UserInfoC(StringC nlogin) 
    : exists(false),
    uid(0),
    login(nlogin.Copy())
  {
    Init(nlogin);
  }
  
  ///////////////////////
  // Constructor.

  UserInfoC::UserInfoC(UIntT uid) 
    : exists(false),
    uid(0),
    login("unknown")
  {
    Init(uid);
  }
  
  ///////////////////////////
  // Make this entry invalid.
  
  void UserInfoC::NullUser() {
    exists = false;
    uid = 0;
    gid = 0;
    login = StringC("");
    fullname = StringC("");
    homedir = StringC("");
    shell = StringC("");
  }
  
  
  ////////////////////////
  // Initalise from userid.
  
  bool UserInfoC::Init(UIntT aUserid) {
#ifndef VISUAL_CPP
    struct passwd *pwentry;
#if defined(__sol2__)
    struct passwd pwbuff;
    char buff[PWBUFFLEN];
    if((pwentry = getpwuid_r(aUserid,&pwbuff,buff,PWBUFFLEN)) == 0) 
#else
    if((pwentry = getpwuid(aUserid)) == 0) 
#endif
    {
      NullUser();
#if _REENTRANT
      if(errno() == ERANGE)
#else
      if(errno == ERANGE)
#endif
	perror("UserInfoC::Init(), ERROR:Buffer to small ");
      return false;
    }
    Init(pwentry);
    return true;
#else
    throw ExceptionC("UserInfoC::Init(), Not implemented. ");
#endif
  }

////////////////////////
// Initalise from login.
  
  bool UserInfoC::Init(StringC aLogin)  {
#ifndef VISUAL_CPP
    struct passwd *pwentry;
#if defined(__sol2__)  
    struct passwd pwbuff;
    char buff[PWBUFFLEN];
    if((pwentry = getpwnam_r(aLogin,&pwbuff,buff,PWBUFFLEN)) == 0) 
#else
    if((pwentry = getpwnam(aLogin)) == 0) 
#endif
      {
	NullUser();
#if _REENTRANT
	if(errno() == ERANGE)
#else
	if(errno == ERANGE)
#endif
	  perror("UserInfoC::Init(), ERROR:Buffer to small ");
	return false;
      }
    Init(pwentry);
    return true;
#else
    throw ExceptionC("UserInfoC::Init(), Not implemented. ");
#endif
  }

  ////////////////////////
  // Initalise from a password structure.
  
  void UserInfoC::Init(struct passwd *pw)  {
#ifndef VISUAL_CPP
    exists = true;
    uid = pw->pw_uid;
    gid = pw->pw_gid;
    login = pw->pw_name;
    fullname = pw->pw_gecos;
    homedir = pw->pw_dir;
    shell = pw->pw_shell;
#else
    throw ExceptionC("UserInfoC::Init(), Not implemented. ");
#endif
  }

  //////////////////////////////
  //: Get current user.
  
  UserInfoC UserInfoC::WhoAmI()  { 
#ifndef VISUAL_CPP
    static UserInfoC itsme(getuid()); 
    return itsme;
#else
    throw ExceptionC("UserInfoC::WhoAmI(), Not implemented. ");
#endif
  }
}


