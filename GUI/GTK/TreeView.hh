// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_TREEVIEW_HEADER
#define RAVLGUI_TREEVIEW_HEADER 1
//! rcsid="$Id$"
//! docentry="Ravl.GUI.Control"
//! author="Charles Galambos"
//! example=exTreeStore.cc
//! lib=RavlGUI
//! date="23/9/2003"

#include "Ravl/config.h"

#if RAVL_USE_GTK2

#include "Ravl/GUI/Widget.hh"
#include "Ravl/GUI/TreeModel.hh"
#include "Ravl/Threads/Signal1.hh"

extern "C" {
  typedef struct _GtkTreeSelection  GtkTreeSelection;
  typedef struct _GtkCellRenderer   GtkCellRenderer;
  typedef struct _GtkTreeViewColumn GtkTreeViewColumn;
}

namespace RavlGUIN {

  class TreeViewBodyC;
  class TreeViewC;
  
  //: Renderer information.
  //! userlevel=Develop
  
  class TreeViewColumnRendererC {
  public:    
    TreeViewColumnRendererC()
      : expand(false),
	renderer(0),
	treeViewBody(0)
    {}
    //: Default constructor.
    
    TreeViewColumnRendererC(const StringC &_renderType)
      : expand(false),
	renderType(_renderType),
	renderer(0),
	treeViewBody(0)
    {}
    //: Constructor.
    
    void SetRenderType(const StringC &newType)
    { renderType = newType; }
    //: Set render type.
    
    const StringC &RenderType() const
    { return renderType; }
    //: Access render type.
    
    HashC<StringC,Tuple2C<StringC,bool> > &Attributes()
    { return attributes; }
    //: Access attributes.
    
    GtkCellRenderer *Renderer()
    { return renderer; }
    //: Access renderer
    
    bool SetRenderer(GtkCellRenderer *newRenderer)
    { renderer = newRenderer;  return true; }
    //: Access renderer
    
    bool Expand() const
    { return expand; }
    //: Enable expantion ?
    
    bool SetExpand(bool val)
    { expand = val; return true; }
    //: Enable expantion ?
    
    Signal0C &SignalChanged()
    { return signalChanged; }
    //: Signal change to cell.

    TreeViewBodyC *TreeBody()
    { return treeViewBody; }
    //: Tree view body
    // Part of hideous hack to get signals working,.
    // Internal use only!
    
    void TreeBody(TreeViewBodyC *bod)
    { treeViewBody = bod; }
    //: Tree view body
    // Part of hideous hack to get signals working,.
    // Internal use only!
    
  protected:
    bool expand;
    StringC renderType;
    HashC<StringC,Tuple2C<StringC,bool> > attributes;
    GtkCellRenderer *renderer;
    Signal0C signalChanged;
    TreeViewBodyC *treeViewBody;

  };
  
  //: Column information.
  //! userlevel=Develop
  
  class TreeViewColumnC {
  public:
    TreeViewColumnC();
    //: Default constructor.
        
    GtkTreeViewColumn *ColumnView()
    { return column; }
    //: Access column view.
    // Internal use only!

    void ColumnView(GtkTreeViewColumn *newun)
    { column = newun; }
    //: Set column view.
    // Internal use only!
    
    HashC<StringC,Tuple2C<StringC,bool> > &Attributes()
    { return renderers[0].Attributes(); }
    //: Access column attributes.
    
    void Renderer(GtkCellRenderer *newun)
    { renderers[0].SetRenderer(newun); }
    //: Set renderer.
    // Internal use only!
    
    GtkCellRenderer *Renderer()
    { return renderers[0].Renderer(); }
    //: Access renderer.
    // Internal use only!
    
    const StringC &RenderType()
    { return renderers[0].RenderType(); }
    //: Access render type.
    
    void RenderType(const StringC &rtype)
    { renderers[0].SetRenderType(rtype); }
    //: Set render type.
    
    Signal0C &SignalChanged()
    { return renderers[0].SignalChanged(); }
    //: Signal change to cell.
    
    SArray1dC<TreeViewColumnRendererC> &Renderers()
    { return renderers; }
    //: Access list of renderers for columns.
    
    bool SetRenderers(SArray1dC<TreeViewColumnRendererC> &renderInfo)
    { renderers = renderInfo; return true; }
    //: Access list of renderers for columns.
    
    const StringC &Name()
    { return name; }
    //: Access column name,
    
    void Name(const StringC &nname)
    { name = nname; }
    //: Access column name,
    
#if 0
    TreeViewBodyC *TreeBody()
    { return treeViewBody; }
    //: Tree view body
    // Part of hideous hack to get signals working,.
    // Internal use only!
    
    void TreeBody(TreeViewBodyC *bod)
    { treeViewBody = bod; }
    //: Tree view body
    // Part of hideous hack to get signals working,.
    // Internal use only!
#endif    
    
    bool Sort() const
    { return sort; }
    //: Sort column ?
    
    bool SortAscending() const
    { return ascending; }
    //: Sort in ascending order.
    
    void SetSort(bool _sort,bool _ascending)
    { sort = _sort; ascending = _ascending; }
    //: Set sort order of column.
    
  protected:
    StringC name;
    SArray1dC<TreeViewColumnRendererC> renderers;
    GtkTreeViewColumn *column;
    bool sort;
    bool ascending;
    friend class TreeViewBodyC;
  };
  
  //! userlevel=Develop
  //: Tree view widget.
  // Available on GTK+-2.0 and above only.
  
  class TreeViewBodyC
    : public WidgetBodyC
  {
  public:
    TreeViewBodyC(const TreeModelC &tm,const DListC<StringC> &displayColumns, GtkSelectionMode nselMode);
    //: Constructor.
    
    TreeViewBodyC(const TreeModelC &tm,const SArray1dC<TreeViewColumnC> &displayColumns, GtkSelectionMode nselMode);
    //: Constructor.
    
    TreeViewBodyC();
    //: Default constructor.
    
    virtual bool Create();
    //: Create widget.
    
    virtual bool Create(GtkWidget *widget);
    //: Create with a widget supplied from elsewhere.
    
    TreeModelC &TreeModel()
    { return treeModel; }
    //: Access tree model.
    
    Signal1C<DListC<TreeModelIterC> > &SelectionChanged()
    { return selectionChanged; }
    //: Access selection changed signal.
    
    IntT ColumnName2Number(const StringC &name) const;
    //: Get the column number for a given name 
    // Returns -1 if not found.
    
    bool SetAttribute(IntT colNum,const StringC &key,const StringC &value,bool proxy = true);
    //: Set an attribute for a column
    // Possible keys include: "editable", "sortable", "activateable", "foreground", "background", "reorderable", "resizable"
    
    bool SetAttribute(IntT colNum,UIntT subCol,const StringC &key,const StringC &value,bool proxy = true);
    //: Set an attribute for a column
    // Possible keys include: "editable", "sortable", "activateable", "foreground", "background", "reorderable", "resizable"
    
    bool SetAttribute(const StringC &colName,const StringC &key,const StringC &value,bool proxy = true);
    //: Set an attribute for a column
    // Possible keys include: "editable", "sortable", "activateable", "foreground", "background", "reorderable", "resizable"
    
    bool SetAttribute(const StringC &colName,UIntT subCol,const StringC &key,const StringC &value,bool proxy = true);
    //: Set an attribute for a column
    // Possible keys include: "editable", "sortable", "activateable", "foreground", "background", "reorderable", "resizable"
    
    Signal0C &ChangedSignal(UIntT colNum,UIntT subColNo = 0);
    //: Access changed signal for a column
    
    TreeModelIterC Path2Iter(const char *pathName)
    { return treeModel.Path2Iter(pathName); }
    //: Get row iterator from path string.

    void Sort(UIntT colNum, bool bAscending);
    //: Sort treeview by column colNum.
        
    bool GUISort(UIntT colNum, bool bAscending);
    //: Sort treeview by column colNum.
    // GUI thread only
    
    void Sort(const StringC &colName, bool bAscending);
    //: Sort treeview by named column
    
    bool GUISort(const StringC &colName, bool bAscending);
    //: Sort treeview by named column 
    // GUI thread only
    
    void Expand(TreeModelPathC path);
    //: Expand to the specified path
    
    bool GUIExpand(TreeModelPathC path);
    //: Expand to the specified path
    // GUI thread only
    
    void Expand(TreeModelIterC iter);
    //: Expand to the specified row iterator
    
    bool GUIExpandIter(TreeModelIterC iter);
    //: Expand to the specified row iterator
    
    bool GUIExpanded(TreeModelPathC path);
    //: Is the specified path expanded?
    // GUI thread only

    bool GUIExpanded(TreeModelIterC iter);
    //: Is the specified iterator expanded?
    // GUI thread only

    void ExpandAll();
    //: Expand the entire tree

    bool GUIExpandAll();
    //: Expand the entire tree
    // GUI thread only

    void CollapseAll();
    //: Collapse the entire tree

    bool GUICollapseAll();
    //: Collapse the entire tree
    // GUI thread only

    void Select(TreeModelPathC path);
    //: Select the specified path

    void Select(TreeModelIterC iter);
    //: Select the specified row iterator

    bool GUISelectPath(TreeModelPathC path);
    //: Select the specified path
    // GUI thread only

    bool GUISelectIter(TreeModelIterC iter);
    //: Select the specified row iterator
    // GUI thread only

    bool GUISelectedPath(TreeModelPathC path);
    //: Is the specified path selected?
    // GUI thread only

    bool GUISelectedIter(TreeModelIterC iter);
    //: Is the specified row iterator deselected?
    // GUI thread only

    DListC<TreeModelIterC> GUISelected();
    //: Get list of selected rows.    
    
    void Deselect(TreeModelPathC path);
    //: Deselect the specified path

    void Deselect(TreeModelIterC iter);
    //: Deselect the specified row iterator

    bool GUIDeselectPath(TreeModelPathC path);
    //: Deselect the specified path
    // GUI thread only

    bool GUIDeselectIter(TreeModelIterC iter);
    //: Deselect the specified row iterator
    // GUI thread only

    void SelectAll();
    //: Select all rows

    bool GUISelectAll();
    //: Select all rows
    // GUI thread only
    
    void DeselectAll();
    //: Deselect all rows
    
    bool GUIDeselectAll();
    //: Deselect all rows
    // GUI thread only

    void SelectRange(TreeModelPathC from, TreeModelPathC to);
    //: Select the rows between the two paths

    bool GUISelectRange(TreeModelPathC from, TreeModelPathC to);
    //: Select the rows between the two paths
    // GUI thread only

    void DeselectRange(TreeModelPathC from, TreeModelPathC to);
    //: Deselect the rows between the two paths

    bool GUIDeselectRange(TreeModelPathC from, TreeModelPathC to);
    //: Deselect the rows between the two paths
    // GUI thread only

    void ScrollTo(TreeModelPathC path);
    //: Scroll the treeview to the specified path

    void ScrollTo(TreeModelIterC iter);
    //: Scroll the treeview to the specified row iterator

    bool GUIScrollTo(TreeModelPathC path);
    //: Scroll the treeview to the specified path
    // GUI thread only

    bool FilterFirstSelections() { 
      if (firstSelection) {
	firstSelection--;
	return true;
      }
      return false;
    }
    //: Selection filter function
    // Only used by internal functions, please leave this alone :)
    
    TreeModelPathC GUIGetPathTo(const Index2dC &pos);
    //: Get path to a position in the tree.
    // 'pos' must be widget coordinates.
    
    TreeModelIterC GUIGetIter(const Index2dC &pos);
    //: Get iter for row at position 'pos' in the tree.
    // 'pos' must be widget coordinates.
    
  protected:
    virtual bool GUIDNDSource(ModifierTypeT flags,const SArray1dC<GtkTargetEntry> &entries,DragActionT actions);
    //: Setup widget as drag and drop source.
    
    virtual bool GUIDNDSourceDisable();
    //: Disable widget as a drag and drop source.
    
    virtual bool GUIDNDTarget(DestDefaultsT flags,const SArray1dC<GtkTargetEntry> &entries,DragActionT actions);
    //: Setup widget as drag and drop target.
    
    virtual bool GUIDNDTargetDisable();
    //: Disable widget as a drag and drop source.
    
    TreeModelC treeModel;
    GtkTreeSelection *selection;
    Signal1C<DListC<TreeModelIterC> > selectionChanged;
    SArray1dC<TreeViewColumnC> displayColumns;
    IntT firstSelection;
    GtkSelectionMode  selMode;

    friend class TreeViewC;
    
  };
  
  //! userlevel=Normal
  //: Tree view widget.
  // Available on GTK+-2.0 and above only.
  
  class TreeViewC
    : public WidgetC
  {
  public:
    TreeViewC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    TreeViewC(const TreeModelC &treeModel,const DListC<StringC> &displayColumns = DListC<StringC>(), GtkSelectionMode nselMode = GTK_SELECTION_SINGLE)
      : WidgetC(*new TreeViewBodyC(treeModel,displayColumns,nselMode))
    {}
    //: Constructor.
    // Creates an invalid handle.
    
    TreeViewC(const TreeModelC &treeModel,const SArray1dC<TreeViewColumnC> &displayColumns, GtkSelectionMode nselMode = GTK_SELECTION_SINGLE)
      : WidgetC(*new TreeViewBodyC(treeModel,displayColumns,nselMode))
    {}
    //: Constructor.
    // Creates an invalid handle.
    
  protected:
    TreeViewC(TreeViewBodyC &bod)
      : WidgetC(bod)
    {}
    //: Body constructor.
    
    TreeViewBodyC &Body()
    { return static_cast<TreeViewBodyC &>(WidgetC::Body()); }
    //: Access body.

    const TreeViewBodyC &Body() const
    { return static_cast<const TreeViewBodyC &>(WidgetC::Body()); }
    //: Access body.

    bool GUISortNamed(const StringC &colName, bool bAscending)
    { return Body().GUISort(colName,bAscending); }
    //: Sort treeview by named column 
    // GUI thread only
    
    bool GUISortNum(UIntT colNum, bool bAscending)
    { return Body().GUISort(colNum,bAscending); }
    //: Sort treeview by column colNum.
    // GUI thread only
    
  public:
    
    TreeModelC &TreeModel()
    { return Body().TreeModel(); }
    //: Access tree model.
    
    DListC<TreeModelIterC> GUISelected()
    { return Body().GUISelected(); }
    //: Get list of selected rows.
    
    Signal1C<DListC<TreeModelIterC> > &SelectionChanged()
    { return Body().SelectionChanged(); }
    //: Access selection changed signal.
    
    IntT ColumnName2Number(const StringC &name) const
    { return Body().ColumnName2Number(name); }
    //: Get the column number for a given name 
    // Returns -1 if not found.
    
    bool SetAttribute(IntT colNum,const StringC &key,const StringC &value,bool proxy = true)
    { return Body().SetAttribute(colNum,key,value,proxy); }
    //: Set an attribute for a column
    // Possible keys include: "editable", "sortable", "activateable", "foreground", "background", "reorderable", "resizable"
    
    bool SetAttribute(IntT colNum,UIntT subCol,const StringC &key,const StringC &value,bool proxy = true)
    { return Body().SetAttribute(colNum,subCol,key,value,proxy); }
    //: Set an attribute for a column
    // Possible keys include: "editable", "sortable", "activateable", "foreground", "background", "reorderable", "resizable"
    
    bool SetAttribute(const StringC &colName,const StringC &key,const StringC &value,bool proxy = true)
    { return Body().SetAttribute(colName,key,value,proxy); }
    //: Set an attribute for a column
    // Possible keys include: "editable", "sortable", "activateable", "foreground", "background", "reorderable", "resizable"
    
    bool SetAttribute(const StringC &colName,UIntT subCol,const StringC &key,const StringC &value,bool proxy = true)
    { return Body().SetAttribute(colName,subCol,key,value,proxy); }
    //: Set an attribute for a column
    // Possible keys include: "editable", "sortable", "activateable", "foreground", "background", "reorderable", "resizable"
    
    Signal0C &ChangedSignal(UIntT colNum,UIntT subColNo = 0)
    { return Body().ChangedSignal(colNum,subColNo); }
    //: Access changed signal for a column
    
    TreeModelIterC Path2Iter(const char *pathName)
    { return Body().Path2Iter(pathName); }
    //: Get row iterator from path string.

    void Sort(UIntT colNum, bool bAscending)
    { Body().Sort(colNum,bAscending); }
    //: Sort treeview by column colNum.

    bool GUISort(UIntT colNum, bool bAscending)
    { return Body().GUISort(colNum,bAscending); }
    //: Sort treeview by column colNum.
    // GUI thread only
    
    void Sort(const StringC &colName, bool bAscending)
    { Body().Sort(colName,bAscending); }
    //: Sort treeview by named column 

    bool GUISort(const StringC &colName, bool bAscending)
    { return Body().GUISort(colName,bAscending); }
    //: Sort treeview by named column.
    // GUI thread only
    
    void Expand(TreeModelPathC path)
    { Body().Expand(path); }
    //: Expand to the specified path
    
    void Expand(TreeModelIterC iter)
    { Body().Expand(iter); }
    //: Expand to the specified row iterator
    
    bool GUIExpand(TreeModelPathC path)
    { return Body().GUIExpand(path); }
    //: Expand to the specified path
    // GUI thread only
    
    bool GUIExpandIter(TreeModelIterC iter)
    { return Body().GUIExpandIter(iter); }
    //: Expand to the specified row iterator
    // GUI thread only
    
    bool GUIExpanded(TreeModelPathC path)
    { return Body().GUIExpanded(path); }
    //: Is the specified path expanded?
    // GUI thread only

    bool GUIExpanded(TreeModelIterC iter)
    { return Body().GUIExpanded(iter); }
    //: Is the specified iterator expanded?
    // GUI thread only

    void ExpandAll()
    { Body().ExpandAll(); }
    //: Expand the entire tree

    bool GUIExpandAll()
    { return Body().GUIExpandAll(); }
    //: Expand the entire tree
    // GUI thread only

    void CollapseAll()
    { Body().CollapseAll(); }
    //: Collapse the entire tree

    bool GUICollapseAll()
    { return Body().GUICollapseAll(); }
    //: Collapse the entire tree
    // GUI thread only

    void Select(TreeModelPathC path)
    { Body().Select(path); }
    //: Select the specified path

    void Select(TreeModelIterC iter)
    { Body().Select(iter); }
    //: Select the specified row iterator

    bool GUISelectPath(TreeModelPathC path)
    { return Body().GUISelectPath(path); }
    //: Select the specified path
    // GUI thread only

    bool GUISelectIter(TreeModelIterC iter)
    { return Body().GUISelectIter(iter); }
    //: Select the specified row iterator
    // GUI thread only

    bool GUISelectedPath(TreeModelPathC path)
    { return Body().GUISelectedPath(path); }
    //: Is the specified path selected?
    // GUI thread only

    bool GUISelectedIter(TreeModelIterC iter)
    { return Body().GUISelectedIter(iter); }
    //: Is the specified row iterator deselected?
    // GUI thread only

    void Deselect(TreeModelPathC path)
    { Body().Deselect(path); }
    //: Deselect the specified path

    void Deselect(TreeModelIterC iter)
    { Body().Deselect(iter); }
    //: Deselect the specified row iterator

    bool GUIDeselectPath(TreeModelPathC path)
    { return Body().GUIDeselectPath(path); }
    //: Deselect the specified path
    // GUI thread only

    bool GUIDeselectIter(TreeModelIterC iter)
    { return Body().GUIDeselectIter(iter); }
    //: Deselect the specified row iterator
    // GUI thread only

    void SelectAll()
    { Body().SelectAll(); }
    //: Select all rows

    bool GUISelectAll() 
    { return Body().GUISelectAll(); }
    //: Select all rows
    // GUI thread only

    void DeselectAll()
    { Body().DeselectAll(); }
    //: Deselect all rows

    bool GUIDeselectAll()
    { return Body().GUIDeselectAll(); }
    //: Deselect all rows
    // GUI thread only

    void SelectRange(TreeModelPathC from, TreeModelPathC to)
    { Body().SelectRange(from,to); }
    //: Select the rows between the two paths

    bool GUISelectRange(TreeModelPathC from, TreeModelPathC to)
    { return Body().GUISelectRange(from,to); }
    //: Select the rows between the two paths
    // GUI thread only

    void DeselectRange(TreeModelPathC from, TreeModelPathC to)
    { Body().DeselectRange(from,to); }
    //: Deselect the rows between the two paths

    bool GUIDeselectRange(TreeModelPathC from, TreeModelPathC to)
    { return Body().GUIDeselectRange(from,to); }
    //: Deselect the rows between the two paths
    // GUI thread only

    void ScrollTo(TreeModelPathC path)
    { Body().ScrollTo(path); }
    //: Scroll the treeview to the specified path

    void ScrollTo(TreeModelIterC iter)
    { Body().ScrollTo(iter); }
    //: Scroll the treeview to the specified row iterator

    bool GUIScrollTo(TreeModelPathC path)
    { return Body().GUIScrollTo(path); }
    //: Scroll the treeview to the specified path
    // GUI thread only
    //!bug: The GTK function this calls does not seem to do anything at the moment, not sure why.
    
    TreeModelPathC GUIGetPathTo(const Index2dC &pos)
    { return Body().GUIGetPathTo(pos); }
    //: Get path to a position in the tree.
    // 'pos' must be in widget cooridinates.
    
    TreeModelIterC GUIGetIter(const Index2dC &pos)
    { return Body().GUIGetIter(pos); }
    //: Get iter for row at position 'pos' in the tree.
    // 'pos' must be widget coordinates.
    
    friend class TreeViewBodyC;

  };
  
}
#else 
#warning TreeViewC is not supported (requires gtk2) 
#endif
#endif
