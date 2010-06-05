// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, Omniperception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_GNOME_HEADER
#define RAVLGUI_GNOME_HEADER 1
//! rcsid="$Id: Gnome.hh 4816 2005-03-01 17:08:51Z craftit $"
//! lib=RavlGUIGnome

#include "Ravl/GUI/Widget.hh"

namespace RavlGUIN {
  
  bool GnomeInit(const StringC &appName,const StringC &appVersion,int &nargs,char *args[]);
  //: Initialise gnome library.
  
}


#endif
