// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGIC_VAR_HEADER
#define RAVLLOGIC_VAR_HEADER 1
/////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Logic"
#include "Ravl/Logic/Literal.hh"
//! lib=RavlLogic
//! file="Ravl/Logic/Base/Var.hh"

namespace RavlLogicN {

  //! userlevel=Develop
  //: Variable body.
  
  class VarBodyC 
    : public LiteralBodyC
  {
  public:
    VarBodyC()
      {}
    //: Default constructor.
    
    virtual bool IsVariable() const
    { return true; }
    //: Is this a variable ?
    
    virtual bool IsGrounded() const
    { return false; }
    //: Is this a simple object with no variables ?

    virtual void Dump(ostream &out);
    //: Dump info in human readable format to stream 'out'.

    virtual StringC Name() const;
    //: Get the name of symbol.

  protected:    
    virtual bool Unify(const LiteralC &oth,BindSetC &bs) const;
    //: Unify with another variable.

    virtual bool UnifyLiteral(const LiteralBodyC &oth,BindSetC &bs) const;
    //: Unify 
  };
  
  //! userlevel=Normal
  //: Variable
  
  class VarC 
    : public LiteralC 
  {
  public:
    VarC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    VarC(bool)
      : LiteralC(*new VarBodyC())
    {}
    //: Constructor.
    // Construct an anonymous var.
  };
  
  inline VarC Var()
  { return VarC(true); }
  //: Creat an anonymous variable.
}

#endif
