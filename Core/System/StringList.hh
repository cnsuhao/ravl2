// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLStringList_HH
#define RAVLStringList_HH
////////////////////////////////////////////////////////////////////////
//! file="Ravl/Core/System/StringList.hh"
//! lib=RavlCore
//! userlevel=Normal
//! author="Bill Christmas"
//! docentry="Ravl.Core.Lists"
//! rcsid="$Id$"
//! date="12/07/96"

#include <iostream.h>
#include "Ravl/String.hh"
#include "Ravl/DList.hh"
 
namespace RavlN {
  //: List of StringC's
  
  class StringListC 
    : public DListC<StringC> 
  {
  public:
    inline StringListC()
      {}
    //: Default constructor
    
    inline StringListC (const StringListC &oth)
      : DListC<StringC>(oth)
      {}
    //: Copy constructor
    
    inline StringListC (const DListC<StringC> &alist)
      : DListC<StringC>(alist)
      {}
    //: Constructor
    
    StringListC (const StringC &str, const char* delim = " \n\t\0");
    //: Constructor that tokenises string into string list
    
    StringListC (const StringC &str, bool fullParse,const char* delim = " \n\t\0");
    //: Constructor that tokenises string into string list  
    // If full parse is enabled double quotes are respected,
    // and escaping with '\' is supported.
    
    inline const StringListC& operator+=(const StringListC & list) {
      DListC<StringC>::operator+=(list);
      return *this;
    }
    //: Concatenation.
    // The operator moves the whole 'list to the end
    // of this list. The 'list' will be EMPTY after the operation. <p>
    // The arg is only constant so that 'list' may be a tempory without
    // causing warnings. <p> 
    // Returns this list.
    
    IndexC CasePos (const StringC &str) const;
    //: finds position of string in list - case insensitive
    
    StringC Cat (const StringC &sep = " ") const;
    //: concatenates string list into a single string
    
  private:
    
    friend ostream & operator<<(ostream & s, const StringListC & list);
  };
  
  ostream & operator<<(ostream & s, const StringListC & list);
  // Saves the string list into the output stream 's'.
  
}
  
#endif
