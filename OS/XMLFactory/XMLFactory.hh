// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2009, OmniPerception Ltd
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_XMLFACTORY_HEADER
#define RAVL_XMLFACTORY_HEADER 1
//! lib=RavlXMLFactory
//! author=Charles Galambos
//! docentry=Ravl.API.Core.IO.XMLFactory

#include "Ravl/Exception.hh"
#include "Ravl/XMLTree.hh"
#include "Ravl/SmartPtr.hh"
#include "Ravl/DList.hh"
#include "Ravl/RCAbstract.hh"
#include "Ravl/SmartLayerPtr.hh"
#include "Ravl/Threads/RWLock.hh"

namespace RavlN {
  using namespace RavlN;

  class XMLFactoryC;
  class XMLFactoryHC;
  
  //! uselevel=Develop
  //: Node in the build tree.
  
  class XMLFactoryNodeC 
    : public RCLayerBodyC
  {
  public:
    XMLFactoryNodeC()
      : m_xmlNode(true)
    {}
    //: Default constructor.
    
    explicit XMLFactoryNodeC(const XMLTreeC &xmlNode)
      : m_xmlNode(xmlNode)
    {}
    //: Constructor.
    
    XMLFactoryNodeC(const XMLTreeC &xmlNode,const XMLFactoryNodeC &parent)
      : m_xmlNode(xmlNode),
        m_parent(&parent)
    {}
    //: Constructor.
    
    XMLFactoryNodeC(const XMLTreeC &xmlNode,const XMLFactoryNodeC &parent,const RCWrapAbstractC &component)
      : m_xmlNode(xmlNode),
        m_component(component),
        m_parent(&parent)
    {}
    //: Constructor.

    ~XMLFactoryNodeC();
    //: Destructor.
    
    typedef SmartOwnerPtrC<XMLFactoryNodeC> RefT;
    //: Owner reference
    
    typedef SmartCallbackPtrC<XMLFactoryNodeC> CBRefT;
    //: Callback reference.
    
    const StringC &Name() const
    { return m_xmlNode.Name(); }
    //: Access node name.
    
    RCWrapAbstractC Component() const
    { 
      RWLockHoldC hold(m_access,RWLOCK_READONLY);
      RCWrapAbstractC ret = m_component; 
      hold.Unlock();
      return ret;
    }
    //: Component
    
    void SetComponent(const RCWrapAbstractC &comp) { 
      RWLockHoldC hold(m_access,RWLOCK_WRITE);
      m_component = comp; 
    }
    //: Set component at node.
    
    bool FollowPath(const StringC &path,RefT &node,bool verbose = false) const;
    //: Follow path to child node.
    
    bool FollowPath(const DListC<StringC> &path,RefT &node,bool verbose = false) const;
    //: Follow path to child node.
    
    bool UsePath(const StringC &path,RefT &node,bool restrictToXMLTree = true,bool verbose = false);
    //: Follow path to child node, create nodes where needed
    
    bool UsePath(const DListC<StringC> &path,RefT &node,bool restrictToXMLTree = true,bool verbose = false);
    //: Follow path to child node, create nodes where needed
    
    bool FindChild(const StringC &name,RefT &child) const;
    //: Find named child.
    
    bool UseChild(const StringC &name,RefT &child,bool restrictToXMLTree = true,bool verbose = false);
    //: Find child and create one if it doesn't exist.
    
    bool AddChild(const StringC &name,XMLFactoryNodeC &child);
    //: Add a child to this node.
    // Note: This will overwrite any existing node of the name
    
    bool DelChild(const StringC &name);
    //: Remove a child.
    
    template<class DataT>
    bool SetComponent(const StringC &name,const DataT &data) {
      RCWrapC<DataT> handle(data);
      return SetComponentInternal(name,handle);
    }
    //: Get named component.
    
    XMLTreeC &XMLNode()
    { return m_xmlNode; }
    //: XML Node
    
    const XMLTreeC &XMLNode() const
    { return m_xmlNode; }
    //: XML Node
    
    StringC Path() const;
    //: Get path to this node.
    
    bool CreateComponent(XMLFactoryC &factory);
    //: Create component in node.
    
    bool HasParent() const
    { return m_parent.IsValid(); }
    //: Has node got a parent ?
    
    bool Dump(std::ostream &strm,int level = 0);
    //: Dump node tree in human readable form.
  protected:
    
    bool GetComponentInternal(const StringC &name,const std::type_info &to,RCWrapAbstractC &handle,bool silentError=false) const;
    //: Get named component.

    bool UseComponentInternal(XMLFactoryC &factory,
                              const StringC &name,
                              const std::type_info &to,
                              RCWrapAbstractC &handle,
                              bool silentError = false
                              );
    //: Get named component.
    
    bool SetComponentInternal(const StringC &name,const RCWrapAbstractC &handle);
    //: Set named component.
    
    virtual void ZeroOwners();
    //: Called when owner handles drop to zero.
    
    RWLockC m_access;
    XMLTreeC m_xmlNode;
    RCWrapAbstractC m_component;
    HashC<StringC,RefT> m_children;
    
    CBRefT m_parent; // Parent node.
    
  private:
    XMLFactoryNodeC(const XMLFactoryNodeC &other)    
    { RavlAssert(0); }
    
    friend class XMLFactoryC;
  };
  
  //! userlevel=Normal
  //: XML Factory context. 
  // This class should be passed into the construction methods.
  // It contains a handle to the factory and the current place in the parse tree.
  // To use the class you should define RAVL type converter between an instance of
  // this class and the object you wish to construct. See XMLFactoryRegisterC for
  // an example of how to do this using a constructor.
  
  class XMLFactoryContextC 
  {
  public:
    XMLFactoryContextC()
    {}
    //: Constructor.

    XMLFactoryContextC(const XMLFactoryNodeC &iNode)
      : m_iNode(&iNode)
    {}
    //: Constructor.
    
    XMLFactoryContextC(const XMLFactoryC &factory,const XMLFactoryNodeC &iNode);
    //: Constructor.
    
    XMLFactoryContextC(const XMLFactoryContextC &context,const StringC &childName);
    //: Got a child node.
    
    explicit XMLFactoryContextC(const XMLFactoryC &factory);
    //: Construct from Factory.
    
    XMLFactoryContextC(const XMLFactoryHC &factory);
    //: Construct from Factory.
    
    const XMLTreeC &Node() const
    { return m_iNode->XMLNode(); }
    //: Access xml node.
    
    XMLTreeC &Node() 
    { return m_iNode->XMLNode(); }
    //: Access xml node.
    
    DListC<XMLTreeC> &Children() 
    { return Node().Children(); }
    //: Access a list of child nodes.
    
    const DListC<XMLTreeC> &Children() const
    { return Node().Children(); }
    //: Access a list of child nodes.
    
    const StringC &Name() const
    { return m_iNode->Name(); }
    //: Node name.
    
    StringC AttributeString(const StringC &name,const StringC &defaultValue = StringC("")) const 
    { return Node().AttributeString(name,defaultValue); }
    //: Access attribute.
    
    UIntT AttributeUInt(const StringC &name,UIntT defaultValue = 0) const 
    { return Node().AttributeUInt(name,defaultValue); }
    //: Access attribute.
    
    IntT AttributeInt(const StringC &name,IntT defaultValue = 0) const 
    { return Node().AttributeInt(name,defaultValue); }
    //: Access attribute.
    
    RealT AttributeReal(const StringC &name,RealT defaultValue = 0) const 
    { return Node().AttributeReal(name,defaultValue); }
    //: Access attribute.
    
    UInt64T AttributeUInt64(const StringC &name,UInt64T defaultValue = 0) const 
    { return Node().AttributeUInt64(name,defaultValue); }
    //: Access attribute.
    
    Int64T AttributeInt64(const StringC &name,Int64T defaultValue = 0) const 
    { return Node().AttributeInt64(name,defaultValue); }
    //: Access attribute.
    
    bool AttributeBool(const StringC &name,bool defaultValue = false) const 
    { return Node().AttributeBool(name,defaultValue); }
    //: Access attribute.

    template<typename DataT>
    bool Attribute(const StringC &name,DataT &value,const DataT &defaultValue = DataT()) const
    { return Node().Attribute(name,value,defaultValue); }
    //: Access generic attribute.
    // Return true if non default value has been specified.
    
    XMLFactoryC &Factory() const;
    //: Access handle to associated factory.
    
    void Invalidate() {
      m_iNode.Invalidate();
      m_factory.Invalidate();
    }
    //: Invalidate context.
    
    template<class DataT>
    bool UseComponent(const StringC &name,DataT &data,bool suppressErrorMessages = false) const;
    //: Get named component, or create it if not found.
    
    template<class DataT>
    bool CreateComponent(const StringC &name,DataT &data,bool suppressErrorMessages = false) const;
    //: Create a new instance of the named component.

    template<class DataT>
    bool GetComponent(const StringC &name,DataT &data,bool suppressErrorMessages = false) const;
    //: Get instance of the named component.
    
    void SetFactory(const XMLFactoryC &factory);
    //: Set factory to use.
    
    template<class DataT>
    bool SetComponent(const StringC &name,const DataT &data);
    //: Set component for name.
    
    bool ChildContext(const StringC &key,XMLFactoryContextC &child) const { 
      if(!m_iNode.IsValid())
        return false;
      XMLTreeC childTree;
      if(!m_iNode->XMLNode().Child(key,childTree))
        return false;
      XMLFactoryNodeC::RefT childNode = new XMLFactoryNodeC(childTree);
      child = XMLFactoryContextC(Factory(),*childNode);
      return true;
    }
    //: lookup child in tree.
    // Returns true and updates parameter 'child' if child is found.
    
    StringC Path() const
    { return m_iNode->Path(); }
    //: Get path to this node.
    
    const XMLFactoryNodeC &INode() const { 
      RavlAssert(m_iNode.IsValid());
      return *m_iNode; 
    }
    //: Access node
    
    XMLFactoryNodeC &INode() {
      RavlAssert(m_iNode.IsValid());
      return *m_iNode; 
    }
    //: Access node
    
  protected:
    XMLFactoryNodeC::RefT m_iNode;
    RCAbstractC m_factory;
  };
  
  //! userlevel=Advanced
  //: XML factory class.
  // This class holds the config parse tree, and maintains information on objects
  // That have already been constructed.
  
  class XMLFactoryC 
    : public RCBodyVC
  {
  public:
    XMLFactoryC();
    //: Default constructor
    
    explicit XMLFactoryC(const XMLFactoryContextC &context);
    //: Recursive constructor.
    
    explicit XMLFactoryC(const StringC &configFile);
    //: Open a config file.
    
    XMLFactoryC(const StringC &configFileName,const XMLTreeC &configTree);
    //: Use an existing tree.
    
    typedef RCWrapAbstractC (*TypeFactoryT)(const XMLFactoryContextC &node);
    //: Factory function type
    
    const XMLTreeC &ConfigTree() const
    { return m_configTree; }
    //: Access config tree
    
    const StringC &MasterConfigFilename() const
    { return m_masterConfigFilename; }
    //: Access name of config file.
    
    template<class DataT>
    bool SetComponent(const StringC &name,const DataT &data) 
    { return m_iRoot->SetComponent(name,data); }
    //: Set named component.
    
    template<class DataT>
    bool GetComponent(const StringC &name,DataT &data) {
      RCWrapC<DataT> handle;
      if(!m_iRoot->GetComponentInternal(name,typeid(DataT),handle))
        return false;
      data = handle.Data();
      return true;
    }
    //: Get named component, returns false if the component doesn't exist.
    
    template<class DataT>
    bool UseComponent(const XMLFactoryContextC& currentContext,
                      const StringC &name,
                      DataT &data,
                      bool suppressErrorMessages = false
                      ) const
    {
      RCWrapC<DataT> handle;
      if(!const_cast<XMLFactoryNodeC &>(currentContext.INode()).UseComponentInternal(const_cast<XMLFactoryC &>(*this),
                                                                                     name,
                                                                                     typeid(DataT),
                                                                                     handle,
                                                                                     suppressErrorMessages
                                                                                     ))
        return false;
      RavlAssert(handle.IsValid());
      data = handle.Data();
      return true;
    }
    //: Get named component, or create it if not found.
    
    template<class DataT>
    bool CreateComponent(const XMLFactoryContextC &node,DataT &data) {
      RCWrapC<DataT> handle;
      if(!CreateComponentInternal(node,typeid(DataT),handle))
        return false;
      data = handle.Data();
      return true;      
    }
    //: Create a component
    
    template<class DataT>
    bool CreateComponent(const XMLFactoryContextC& currentContext,
                         const StringC &name,
                         DataT &data,
                         bool suppressErrorMessages = false
                         ) {
      RCWrapC<DataT> handle;
      XMLFactoryContextC newNode;
      
      StringC redirect = currentContext.AttributeString(name);
      if(redirect.IsEmpty())
        redirect = name;
      
      //StringC fullName = currentNode.Path() + ":" + redirect;
      
      // Does spec for component exist in this node ?
      if(!currentContext.ChildContext(redirect,newNode))
        return false;
      //newNode.SetFactory(*this);
      
      if(!CreateComponent(newNode,data))
        return false;
      
      // Store ready for reuse.
      const_cast<XMLFactoryNodeC &>(currentContext.INode()).AddChild(redirect,newNode.INode());
      return true;
    }
    //: Create named component, even if it exists already.
    
    static void RegisterTypeFactory(const std::type_info &typeInfo,TypeFactoryT typeFactoryFunc);
    //: Register a factory function.
    
    template<class DataT> 
    static RCWrapAbstractC DefaultFactoryFunc(const XMLFactoryContextC &node)
    { return RCWrapC<typename DataT::RefT>(typename DataT::RefT(*new DataT(node))); }
    //: Default factory function.
    
    bool SetupClean()
    { return m_setupClean; }
    //: Check if we've been setup cleanly.

    XMLFactoryContextC RootContext()
    { return XMLFactoryContextC(*this); }
    //: Access the root context.
    
    XMLFactoryNodeC &IRoot()
    { return *m_iRoot; }
    //: Root
    
    const XMLFactoryNodeC &IRoot() const
    { return *m_iRoot; }
    //: Root
    
    bool FollowPath(const StringC &path,XMLFactoryNodeC::RefT &node);    
    //: Follow path to node.
    
    bool IsPostReadConfigDone() const
    { return !m_donePostSetup; }
    //: Check if post read of config has been done.
    
    bool PostReadConfig();
    //: Check config thats just been loaded.
    
    bool VerboseMode() const
    { return m_verbose; }
    //: Are we in verbose mode ?
    
    typedef SmartPtrC<XMLFactoryC> RefT;
    //: Reference
    
  protected:
    bool Child(const StringC &key,XMLFactoryContextC &child) const 
    { 
      XMLFactoryNodeC::RefT node;
      if(!m_iRoot->FollowPath(key,node))
        return false;
      child = XMLFactoryContextC(*this,*node);
      return true;
    }
    //: lookup child in tree.
    // Returns true and updates parameter 'child' if child is found.
    
    bool Read(const StringC &filename);
    //: Read config file.
    
    
    virtual bool CreateComponentInternal(const XMLFactoryContextC &node,const std::type_info &to,RCWrapAbstractC &handle);
    //: Create a component

    virtual bool CreateComponentInternal(const XMLFactoryNodeC &node,RCWrapAbstractC &rawHandle);
    //: Create a component
    
    void ReportUseComponentFailed(const XMLFactoryContextC &currentNode,const StringC &name,const std::type_info &type) const;
    //: Report failure in UseComponent
    
    StringC m_masterConfigFilename;
    XMLTreeC m_configRoot;
    XMLTreeC m_configTree;
    XMLFactoryNodeC::RefT m_iRoot;
    //HashC<StringC,RCWrapAbstractC> m_components;
    bool m_setupClean;
    bool m_donePostSetup;
    bool m_verbose;
    
    static HashC<StringC,TypeFactoryT> &Type2Factory();
    friend class XMLFactoryNodeC;
    
  private:
    XMLFactoryC(const XMLFactoryC &)
    { RavlAssert(0); }
  };
  
  //! userlevel=Normal
  //: Handle class for XMLFactoryC
  
  class XMLFactoryHC 
    : public RCHandleC<XMLFactoryC>
  {
  public:
    XMLFactoryHC()
    {}
    //: Default constructor.
    // Creates an invalid handle.


    
    XMLFactoryHC(const StringC &configFile)
      : RCHandleC<XMLFactoryC>(new XMLFactoryC(configFile))
    { Body().PostReadConfig(); }
    //: Open a config file.
    
    XMLFactoryHC(const StringC &configFileName,const XMLTreeC &configTree)
      : RCHandleC<XMLFactoryC>(new XMLFactoryC(configFileName,configTree))
    { Body().PostReadConfig(); }
    //: Use an existing tree.
    
    const XMLTreeC &ConfigTree() const
    { return Body().ConfigTree(); }
    //: Access config tree
    
    const StringC &MasterConfigFilename() const
    { return Body().MasterConfigFilename(); }
    //: Access name of config file.

    XMLFactoryNodeC &IRoot()
    { return Body().IRoot(); }
    //: Root
    
    XMLFactoryContextC RootContext()
    { return Body().RootContext(); }
    //: Access the root context.
    
    const XMLFactoryNodeC &IRoot() const
    { return Body().IRoot(); }
    //: Root
    
    template<class DataT>
    bool SetComponent(const StringC &name,const DataT &data) 
    { return Body().SetComponent(name,data); }
    //: Set named component.
    
    template<class DataT>
    bool GetComponent(const StringC &name,DataT &data) 
    { return Body().GetComponent(name,data); }
    //: Get named component.
    
    template<class DataT>
    bool UseComponent(const StringC &name,
                      DataT &data,
                      bool suppressErrorMessages = false
                      ) const
    { 
      XMLFactoryContextC context(Body());
      return Body().UseComponent(context,name,data,suppressErrorMessages);  
    }
    //: Get named component, or create it if not found.
    
    template<class DataT>
    bool CreateComponent(const XMLFactoryContextC &node,DataT &data) 
    { return Body().CreateComponent(node,data); }
    //: Create a component
    
    template<class DataT>
    bool CreateComponent(const StringC &name,
                         DataT &data,
                         bool suppressErrorMessages = false
                         ) 
    { 
      XMLFactoryContextC context(Body());
      return Body().CreateComponent(context,name,data,suppressErrorMessages); 
    }
    //: Create named component. Event if it exists already.
    
    using RCHandleC<XMLFactoryC>::BodyPtr;
  };
  
  
  template<class DataT>
  bool XMLFactoryContextC::UseComponent(const StringC &name,DataT &data,bool suppressErrorMessages) const
  { return Factory().UseComponent(*this,name,data,suppressErrorMessages); }
  //: Get named component, or create it if not found.
  
  template<class DataT>
  bool XMLFactoryContextC::CreateComponent(const StringC &name,DataT &data,bool suppressErrorMessages) const
  { return Factory().CreateComponent(*this,name,data,suppressErrorMessages); }
  //: Create named component, or create it if not found.

  template<class DataT>
  bool XMLFactoryContextC::SetComponent(const StringC &name,const DataT &data) 
  { return Factory().SetComponent(Path() + ':' + name,data); }
  //: Get named component.

  template<class DataT>
  bool XMLFactoryContextC::GetComponent(const StringC &name,DataT &data,bool suppressErrorMessages) const
  { return Factory().GetComponent(Path() + ':' + name,data); }
  //: Get instance of the named component.
  
}

#endif
