// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, Omniperception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlGUIGnome

#include "Ravl/GUI/Gnome.hh"

#if !RAVL_OS_WIN32
#include <libgnome/libgnome.h>
#endif

namespace RavlGUIN {
  
  //: Initialise gnome library.
  
  bool GnomeInit(const StringC &appName,const StringC &appVersion,int &nargs,char *args[]) {
#if !RAVL_OS_WIN32    
    gnome_program_init (appName,appVersion,
                        LIBGNOME_MODULE,
                        nargs, args,
                        GNOME_PARAM_APP_PREFIX, PROJECT_OUT, 
                        GNOME_PARAM_APP_LIBDIR, PROJECT_OUT "/lib"
                        ,NULL);
#endif
    return true;
  }
  
}
