// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUITABLE_HEADER
#define RAVLGUITABLE_HEADER 1
//////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI
//! author="Charles Galambos"
//! docentry="Ravl.GUI.Layout"
//! file="Ravl/GUI/GTK/Table.hh"
//! date="23/09/99"

#include "Ravl/GUI/Widget.hh"

namespace RavlGUIN {
  //! userlevel=Develop
  //: Table body
  
  class TableBodyC
    : public WidgetBodyC
  {
  public:
    TableBodyC(int nsx,int nsy,bool homog = false)
      : sx(nsx),sy(nsy),
      homogeneous(homog)
      {}
    //: Constructor
    
    bool AddObject(const WidgetC &widge,
		   UIntT left_attach,UIntT right_attach,
		   UIntT top_attach,UIntT bottom_attach,
		   GtkAttachOptions nxoptions= (GtkAttachOptions) (GTK_FILL | GTK_EXPAND),
		   GtkAttachOptions nyoptions= (GtkAttachOptions) (GTK_FILL | GTK_EXPAND),
		   UIntT nxpadding = 0,
		   UIntT nypadding = 0
		   );
    //: Add object to table.
    // See http://www.ee.surrey.ac.uk/Docs/gtk/gtk+-1.2.7/gtk_tut-4.html#ss4.4
    // for an explanation of the options.
    
  protected:
    virtual bool Create();
    //: Create widget.
    
    virtual void Destroy();
    //: Undo all refrences.
    
    int sx,sy; // Size.
    bool homogeneous;
    
    struct WidgeInfoC {
      WidgeInfoC(const WidgetC &awidge,UIntT la,UIntT ra,UIntT ta,UIntT ba,
		 GtkAttachOptions nxoptions,GtkAttachOptions nyoptions,
		 UIntT nxpadding = 0,UIntT nypadding = 0)
	: widge(awidge),
	  left_attach(la),
	  right_attach(ra),
	  top_attach(ta),
	  bottom_attach(ba),
	  xoptions(nxoptions),
	  yoptions(nyoptions),
	  xpadding(nxpadding),
	  ypadding(nypadding)
	{}
      //: Constructor.
      
      WidgetC  widge;
      UIntT	left_attach;
      UIntT	right_attach;
      UIntT	top_attach;
      UIntT	bottom_attach;
      GtkAttachOptions xoptions;
      GtkAttachOptions yoptions;
      UIntT	xpadding;
      UIntT	ypadding;
    };
    
    DListC<WidgeInfoC> children;
  };
  
  //! userlevel=Normal
//: Table.
  
  class TableC
    : public WidgetC
  {
  public:
    TableC()
      {}
    //: Default constructor.
    // Creates an invalid handle.
    
    TableC(int nsx,int nsy,bool homogeneous = false)
      : WidgetC(* new TableBodyC(nsx,nsy,homogeneous))
      {}
    //: Constructor.
    
  protected:
    TableC(TableBodyC &bod)
      : WidgetC(bod)
      {}
    //: Body constructor.
    
    TableBodyC &Body()
      { return static_cast<TableBodyC &>(WidgetC::Body()); }
    //: Access body.
    
    const TableBodyC &Body() const
      { return static_cast<const TableBodyC &>(WidgetC::Body()); }
    //: Access body.
    
  public:
    
    bool AddObject(const WidgetC &widge,
		   UIntT left_attach,UIntT right_attach,
		   UIntT top_attach,UIntT bottom_attach,
		   GtkAttachOptions nxoptions= (GtkAttachOptions) (GTK_FILL | GTK_EXPAND),
		   GtkAttachOptions nyoptions= (GtkAttachOptions) (GTK_FILL | GTK_EXPAND),
		   UIntT nxpadding = 0,
		   UIntT nypadding = 0
		   )
      { return Body().AddObject(widge,left_attach,right_attach,top_attach,bottom_attach,
				nxoptions,nyoptions,
				nxpadding,nypadding); 
      }
  //: Add object to table.
  };

}
#endif
