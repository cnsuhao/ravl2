// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2009, OmniPerception Ltd
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! lib=RavlXMLFactory
//! author=Charles Galambos
//! docentry=Ravl.API.Core.IO.XMLFactory

#include "Ravl/IO.hh"
#include "Ravl/DP/TypeConverter.hh"
#include "Ravl/TypeName.hh"
#include "Ravl/StringList.hh"
#include "Ravl/HSet.hh"
#include "Ravl/XMLFactory.hh"
#include "Ravl/XMLFactoryAutoStart.hh"
#include "Ravl/OS/SysLog.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  using RavlN::StringC;

  //! Destructor.
  XMLFactoryNodeC::~XMLFactoryNodeC()
  {
    //SysLog(SYSLOG_DEBUG,"XMLFactoryNodeC::~XMLFactoryNodeC, Called. %p Name:'%s' ",(void *)this,m_xmlNode.Name().chars());
  }
  
  //! Follow path to child node.
  
  bool XMLFactoryNodeC::FollowPath(const StringC &path,XMLFactoryNodeC::RefT &node,bool verbose) const {
    RavlN::StringListC pathElements(path,":/");
    return FollowPath(pathElements,node,verbose);
  }
  
  //! Follow path to child node.
  
  bool XMLFactoryNodeC::FollowPath(const RavlN::DListC<StringC> &path,RefT &node,bool verbose) const {
    XMLFactoryNodeC::RefT at = this;
    for(RavlN::DLIterC<StringC> it(path);it;it++) {
      RavlN::RWLockHoldC hold(at->m_access,RavlN::RWLOCK_READONLY);
      const RefT *child = at->m_children.Lookup(*it);
      if(child == 0) {
        hold.Unlock();
        // This failed, try parent.
        if(m_parent.IsValid())
          return m_parent->FollowPath(path,node,verbose);
        return false;
      }
      RavlAssert((*child).IsValid());
      at = &(**child);
      hold.Unlock();
    }
    node = at;
    return true;
  }
  
  //! Follow path to child node, create nodes where needed
  
  bool XMLFactoryNodeC::UsePath(const StringC &path,RefT &node,bool restrictToXMLTree,bool verbose) {
    RavlN::StringListC pathElements(path,":/");
    return UsePath(pathElements,node,restrictToXMLTree,verbose);
  }
  
  //! Follow path to child node, create nodes where needed
  
  bool XMLFactoryNodeC::UsePath(const RavlN::DListC<StringC> &path,RefT &node,bool restrictToXMLTree,bool verbose) {
    XMLFactoryNodeC::RefT at = this;
    for(RavlN::DLIterC<StringC> it(path);it;it++) {
      RefT child;
      if(!at->UseChild(*it,child,restrictToXMLTree,verbose)) {
        // This failed, try parent.
        if(m_parent.IsValid()) {
          if(verbose)
            SysLog(SYSLOG_DEBUG,"Child '%s' not found in '%s', trying parent. ",it->chars(),at->Path().chars());
          return m_parent->UsePath(path,node,restrictToXMLTree,verbose);
        }
        return false;
      }
      RavlAssert(child.IsValid());
      at = child;
    }
    node = at;
    return true;
  }
  
  //! Find child and create one if it doesn't exist.
  
  bool XMLFactoryNodeC::UseChild(const StringC &name,RefT &child,bool restrictToXMLTree,bool verbose) {
    if(FindChild(name,child)) {
      RavlAssert(child.IsValid());
      return true;
    }
    XMLTreeC childNode;
    if(!m_xmlNode.IsValid() && restrictToXMLTree) {
      if(verbose)
        SysLog(SYSLOG_ERR,"Child '%s' of '%s' is out of tree.",name.chars(),Path().chars());
      return false;
    }
    if(m_xmlNode.IsValid() && !m_xmlNode.Child(name,childNode)) {
      if(restrictToXMLTree) {
        if(verbose)
          SysLog(SYSLOG_DEBUG,"Child '%s' not in tree from path '%s'. XMLNode:%s ",name.chars(),Path().chars(),m_xmlNode.Name().chars());
        return false;
      }
    }
    XMLFactoryNodeC::RefT newNode = new XMLFactoryNodeC(childNode,*this);
    RavlN::RWLockHoldC hold(m_access,RavlN::RWLOCK_WRITE);
    m_children[name] = newNode;
    child = newNode;
    return true;
  }
  
  //! Find named child.
  
  bool XMLFactoryNodeC::FindChild(const StringC &name,RefT &child) const {
    RavlN::RWLockHoldC hold(m_access,RavlN::RWLOCK_READONLY);
    const RefT *childp = m_children.Lookup(name);
    if(childp == 0 || !childp->IsValid())
      return false;
    child = *childp;
    return true;
  }
  
  //! Create component in node.
  
  bool XMLFactoryNodeC::CreateComponent(XMLFactoryC &factory) {
    return factory.CreateComponentInternal(*this,m_component);
  }
  
  
  //! Get named component.

  bool XMLFactoryNodeC::GetComponentInternal(const RavlN::StringC &name,
                                             const std::type_info &to,
                                             RavlN::RCWrapAbstractC &handle,
                                             bool silentError) const
  {
    XMLFactoryNodeC::RefT child;
    if(!FollowPath(name,child) || !child.IsValid()) {
      SysLog(SYSLOG_DEBUG,"Failed to follow path '%s' ",name.chars());
      return false;
    }
    
    if(!child->Component().IsValid()) {
      SysLog(SYSLOG_DEBUG,"No component at the leaf of path '%s' ",name.chars());
      return false;
    }
    
    const std::type_info &from = child->Component().DataType();
    if(from == to) {
      handle = child->Component();
      return true;
    }
    
    handle = RavlN::SystemTypeConverter().DoConversion(child->Component().Abstract(),from,to);
    if(!handle.IsValid()) {
      if(!silentError)
        SysLog(SYSLOG_WARNING,"Failed to convert data to requested type, from '%s' to '%s' ",RavlN::TypeName(from),RavlN::TypeName(to));
      return false;
    }
    return true;
    
  }

  //! Get named component.
  bool XMLFactoryNodeC::UseComponentInternal(XMLFactoryC &factory,
                                             const RavlN::StringC &rawname,
                                             const std::type_info &to,
                                             RavlN::RCWrapAbstractC &handle,
                                             bool silentError
                                             ) 
  {
    XMLFactoryNodeC::RefT child;
    
    // Look for redirection.
    StringC name = XMLNode().AttributeString(rawname);
    if(name.IsEmpty())
      name = rawname;
    
    if(!UsePath(name,child,true,factory.VerboseMode()) || !child.IsValid()) {
      if(!silentError) {
        SysLog(SYSLOG_ERR,"Failed to find path to requested type, '%s' from path '%s' ",name.chars(),Path().chars());
        //Dump(std::cerr);
        //XMLNode().Dump(std::cerr);
      }
      return false;
    }
    
    if(!child->Component().IsValid()) {
      if(!child->CreateComponent(factory)) {
        if(!silentError)
          SysLog(SYSLOG_ERR,"Failed to create component '%s' ",name.chars());
        return false;
      }
      RavlAssert(child->Component().IsValid());
    }
    
    const std::type_info &from = child->Component().DataType();
    if(from == to) {
      ONDEBUG(SysLog(SYSLOG_DEBUG,"UseComponentInternal, no conversion needed at '%s' for type '%s'",name.chars(),RavlN::TypeName(from)));
      handle = child->Component();
      RavlAssert(handle.IsValid());
      return true;
    }
    
    handle = RavlN::SystemTypeConverter().DoConversion(child->Component().Abstract(),from,to);
    if(!handle.IsValid()) {
      if(!silentError)
        SysLog(SYSLOG_ERR,"Failed to convert data to requested type, from '%s' to '%s' ",RavlN::TypeName(from),RavlN::TypeName(to));
      return false;
    }
    ONDEBUG(SysLog(SYSLOG_DEBUG,"UseComponentInternal, successfull @ '%s' ",name.chars()));
    return true;
  }
  
  //! Set named component.
  
  bool XMLFactoryNodeC::SetComponentInternal(const RavlN::StringC &name,const RavlN::RCWrapAbstractC &handle) {
    XMLFactoryNodeC::RefT child;
    RavlN::StringListC pathElements(name,":/");
    XMLFactoryNodeC::RefT at = this;
    for(RavlN::DLIterC<StringC> it(pathElements);it;it++) {
      XMLFactoryNodeC::RefT atNext;
      if(!at->UseChild(*it,atNext,false) || !atNext.IsValid()) {
        SysLog(SYSLOG_DEBUG,"Failed to create path. '%s' at '%s'",name.chars(),it->chars());
        return false;
      }
      at = atNext;         
    }
    at->SetComponent(handle);
    ONDEBUG(SysLog(SYSLOG_DEBUG,"Component '%s' set ok. ",name.chars()));
    return true;
  }
  
  
  static StringC Ident(int n) {
    StringC ret;
    for(int k = 0;k < n;k++)
      ret += ' ';
    return ret;
  }
  
  bool XMLFactoryNodeC::Dump(std::ostream &strm,int level) {
    strm << Ident(level*2) << " " << Name() << " : " << XMLNode().AttributeString("typename","?") << "\n";
    for(RavlN::HashIterC<StringC,RefT> it(m_children);it;it++) {
      it.Data()->Dump(strm,level+1);
    }
    
    return true;
  }
  
  //! Get path to this node.
  
  StringC XMLFactoryNodeC::Path() const {
    StringC ret;
    const XMLFactoryNodeC *at = this;
    ret = at->Name();
    while(at->m_parent.IsValid()) {
      at = &(*at->m_parent);
      ret = at->Name() + ':' + ret;
    }
    return ret;
  }
  
  //: Called when owner handles drop to zero.
  
  void XMLFactoryNodeC::ZeroOwners() {
    //SysLog(SYSLOG_DEBUG,"XMLFactoryNodeC::ZeroOwners, Called. %p '%s' ",(void *)this,Name().chars());
    //RavlAssert(0);
    RavlN::RWLockHoldC hold(m_access,RavlN::RWLOCK_WRITE);
    m_children.Empty();
    m_parent.Invalidate();
    hold.Unlock();
    RavlN::RCLayerBodyC::ZeroOwners();
  }
  
  //! Add a child to this node.
  //! Note: This will overwrite any existing node of the name
  
  bool XMLFactoryNodeC::AddChild(const StringC &name,XMLFactoryNodeC &child) {
    StringC newName = name;
    RavlN::RWLockHoldC hold(m_access,RavlN::RWLOCK_WRITE);
    if(m_children.IsElm(newName)) {
      int count = 0;
      do {
        newName = name + '-' + StringC(count++);
      } while(m_children.IsElm(newName)) ;
      
      SysLog(SYSLOG_WARNING,"Child of name '%s' already exists in '%s', using name '%s' instead ",name.chars(),Path().chars(),newName.chars());
    }
    m_children[newName] = &child; 
    child.m_parent = this;
    return true;
  }
  
  //! Remove a child.
  
  bool XMLFactoryNodeC::DelChild(const StringC &name) {
    XMLFactoryNodeC::RefT child;
    RavlN::RWLockHoldC hold(m_access,RavlN::RWLOCK_WRITE);
    if(!m_children.Lookup(name,child))
      return false; // Child not known.
    if(&(*child->m_parent) == this)
      child->m_parent.Invalidate();
    m_children.Del(name);
    return true;
  }
  
  
  //------------------------------------------------------------

  extern void linkXMLFactoryRegister();
  
  //! Construct from Factory.
  
  XMLFactoryContextC::XMLFactoryContextC(const XMLFactoryHC &factory)
    : m_iNode(&factory.IRoot()),
      m_factory(const_cast<XMLFactoryC &>(*factory.BodyPtr()))
  { }
  
  //! Constructor.
  
  XMLFactoryContextC::XMLFactoryContextC(const XMLFactoryC &factory,
                                         const XMLFactoryNodeC &iNode)
    : m_iNode(&iNode),
      m_factory(const_cast<XMLFactoryC &>(factory))
  { const_cast<XMLFactoryC &>(factory).PostReadConfig();  }

  //! Got a child node.
  XMLFactoryContextC::XMLFactoryContextC(const XMLFactoryContextC &context,const StringC &childName)
    : m_factory(context.m_factory)
  {
    if(!context.m_iNode->FindChild(childName,m_iNode))
      SysLog(SYSLOG_WARNING,"Child '%s' not found. ",childName.chars());
  }
  
  //! Factory.
  
  XMLFactoryContextC::XMLFactoryContextC(const XMLFactoryC &factory)
    : m_factory(const_cast<XMLFactoryC &>(factory))
    
  { 
    const_cast<XMLFactoryC &>(factory).PostReadConfig(); 
    m_iNode = &factory.IRoot();
  }
  
  //! Set factory to use.
  
  void XMLFactoryContextC::SetFactory(const XMLFactoryC &factory) { 
    m_factory = const_cast<XMLFactoryC &>(factory); 
    const_cast<XMLFactoryC &>(factory).PostReadConfig();
  }
  
  XMLFactoryC &XMLFactoryContextC::Factory() const { 
    RavlAssert(m_factory.IsValid());
    return const_cast<XMLFactoryC &>(static_cast<const XMLFactoryC &>(m_factory.Body())); 
  }
  
  //------------------------------------------------------------

  XMLFactoryC::XMLFactoryC()
    : m_configRoot(true),
      m_setupClean(true),
      m_verbose(false)
  {
    m_configTree = XMLTreeC(true);
    m_iRoot = new XMLFactoryNodeC(m_configTree);
  }
  
  //! Open a config file.
  
  XMLFactoryC::XMLFactoryC(const StringC &configFile)
    : m_configRoot(true),
      m_setupClean(true),
      m_donePostSetup(false),
      m_verbose(false)
  {
    SysLog(SYSLOG_DEBUG,"XMLFactoryC, Config file '%s' ",configFile.chars());
    Read(configFile);
  }

  //! Recursive constructor.
  
  XMLFactoryC::XMLFactoryC(const XMLFactoryContextC &context)
    : m_configRoot(true),
      m_setupClean(true),
      m_donePostSetup(false),
      m_verbose(false)
  {
    SysLog(SYSLOG_DEBUG,"XMLFactoryC, Sub factory. ");
    
    StringC fileName = context.AttributeString("configfile","");
    if(!fileName.IsEmpty())
      Read(fileName);
  }
  
  //! Use an existing tree.
  
  XMLFactoryC::XMLFactoryC(const StringC &configFileName,const XMLTreeC &configTree)
    : m_masterConfigFilename(configFileName),
      m_configRoot(configTree),
      m_setupClean(true),
      m_donePostSetup(false),
      m_verbose(false)
  {
    SysLog(SYSLOG_DEBUG,"Constructing from preparsed tree %s. ",configFileName.chars());
    // Setup the root.
    if(!m_configRoot.Child("Config",m_configTree)) {
      SysLog(SYSLOG_ERR,"No config section in '%s' ",m_masterConfigFilename.chars());
      m_setupClean = false;
      
    } else {
      // Setup root node.
      m_iRoot = new XMLFactoryNodeC(m_configTree);
    }
    // In verbose mode ?
    m_verbose = m_configTree.AttributeBool("verbose",false);
    if(m_verbose) {
      std::cerr << "XMLFactory config tree: \n";
      m_configRoot.Dump(std::cerr);
    }
  }
  
  //! Read config file.
  
  bool XMLFactoryC::Read(const StringC &configFile) {
    m_masterConfigFilename = configFile;
    SysLog(SYSLOG_DEBUG,"Loading config '%s' ",configFile.chars());
    RavlN::XMLIStreamC istrm(m_masterConfigFilename);
    if(!istrm) {
      SysLog(SYSLOG_ERR,"Failed to open config file '%s' ",configFile.chars());
      m_setupClean = false;
      return false;
    }
    
    m_configRoot = XMLTreeC(true);
    if(!m_configRoot.Read(istrm)) {
      SysLog(SYSLOG_ERR,"Failed to parse config file. '%s' ",configFile.chars());
      m_setupClean = false;
      return false;
    }

    // Setup the root.
    //m_configRoot.Dump(std::cerr);
    if(!m_configRoot.Child("Config",m_configTree)) {
      SysLog(SYSLOG_ERR,"No config section in '%s' ",m_masterConfigFilename.chars());
      m_setupClean = false;
      return false;
    } else {
      // Setup root node.
      m_iRoot = new XMLFactoryNodeC(m_configTree);
    }
    
    // In verbose mode ?
    m_verbose = m_configTree.AttributeBool("verbose",false);
    
    // Do post config if we can.
    
    if(References() > 0)
      PostReadConfig();
    return true;
  }
  
  //! Check config thats just been loaded.
  bool XMLFactoryC::PostReadConfig() {
    if(m_donePostSetup)
      return true;
    
    m_donePostSetup = true;    
    if(!m_configTree.IsValid()) {
      //std::cerr << "Config loaded:\n";
      //m_configRoot.Dump(std::cerr);
      
      if(!m_configRoot.Child("Config",m_configTree)) {
        SysLog(SYSLOG_ERR,"No config section in '%s' ",m_masterConfigFilename.chars());
        m_setupClean = false;
        return false;
      }
      
      // Setup root node.
      m_iRoot = new XMLFactoryNodeC(m_configTree);
    }
    
    if(m_verbose) {
      std::cerr << "XMLFactory config tree: \n";
      m_configRoot.Dump(std::cerr);
    }
    
    // Look for preload section.
    XMLTreeC preLoad;
    if(m_configTree.Child("Preload",preLoad)) {
      //UIntT count = 0;
      //SysLog(SYSLOG_DEBUG,"Found preload section. ");
      XMLFactoryNodeC::RefT preLoadNode;
      if(!m_iRoot->UseChild("Preload",preLoadNode)) {
        RavlAssertMsg(0,"Failed to create preload section.");
        SysLog(SYSLOG_ERR,"Unexpected error creating preload section. ");
        return false;
      }
      for(RavlN::DLIterC<XMLTreeC> it(preLoad.Children());it;it++) {
        const StringC xmlName = it->Name();
        
        // Make sure name is unique within preload section.
        StringC finalName = it->Name();
        XMLFactoryNodeC::RefT childNode;        
        UIntT count = 1;
        while(preLoadNode->FindChild(finalName,childNode)) {
          finalName = xmlName + '-' + StringC(count++);
        }
        
        // Create the component here in the tree.
        childNode = new XMLFactoryNodeC(*it,*preLoadNode);
        if(!CreateComponentInternal(*childNode,childNode->m_component)) 
          continue; // We failed to create the node, the reason should have already been reported.
        
        // Is this component intended for elsewhere in the tree ?
        StringC componentName = it->AttributeString("component","");
        if(!componentName.IsEmpty()) {
          // FIXME :- Do we need to do this ?
          SysLog(SYSLOG_WARNING,"Preloading components into other parts of the tree not currently supported. ");
        }
        
        preLoadNode->AddChild(finalName,*childNode);
      }
    }
    
    return true;
  }
  
  //! Report failure in UseComponent
  
  void XMLFactoryC::ReportUseComponentFailed(const XMLFactoryContextC &currentNode,
                                             const RavlN::StringC &name,
                                             const std::type_info &type) const 
  {
    SysLog(SYSLOG_ERR,"Failed to find component '%s', to create type '%s'. Path=%s ",name.chars(),RavlN::TypeName(type),currentNode.Path().chars());
  }

  //! Create a component
  
  bool XMLFactoryC::CreateComponentInternal(const XMLFactoryNodeC &node,RavlN::RCWrapAbstractC &rawHandle) {
    StringC loadFilename = node.XMLNode().AttributeString("load","");
    if(!loadFilename.IsEmpty()) {
      // ---- Load component from file ----
      
      SysLog(SYSLOG_DEBUG,"Loading component, Name='%s' ",node.Name().chars());
      if(!RavlN::LoadAbstract(loadFilename,rawHandle,"",false)) {
	SysLog(SYSLOG_ERR,"Failed to load node '%s' from '%s'",node.Name().chars(),loadFilename.chars());
	return false;
      }
      
    } else {
      // ---- Create component using factory ----
      
      StringC typeToMake = node.XMLNode().AttributeString("typename","");
      SysLog(SYSLOG_DEBUG,"Creating component, Path='%s' Type='%s' ",node.Path().chars(),typeToMake.chars());
      if(typeToMake.IsEmpty()) {
	SysLog(SYSLOG_ERR,"No type specified for node '%s'",node.Name().chars());
	return false;
      }
      TypeFactoryT *tf = Type2Factory().Lookup(typeToMake);
      if(tf == 0) {
	SysLog(SYSLOG_ERR,"Node '%s', Type '%s' unknown.",node.Name().chars(),typeToMake.chars());
	return false;
      }
      XMLFactoryContextC createNode(*this,node);
      rawHandle = (*tf)(createNode);
      
      if(!rawHandle.IsValid())
        SysLog(SYSLOG_WARNING,"Factory failed to create node of type '%s' \n",typeToMake.chars()); 
    }
    
    // Can we auto start this ?
    RavlN::RCWrapC<XMLFactoryAutoStartC::RefT> handle;
    if(node.GetComponentInternal("",typeid(XMLFactoryAutoStartC::RefT),handle,true)) {
      // Auto start...
      if(handle.IsValid())
        handle.Data()->Init();
    }
    
    return true;
  }
  
  //! Create a component
  
  bool XMLFactoryC::CreateComponentInternal(const XMLFactoryContextC &node,
                                            const std::type_info &to,
                                            RavlN::RCWrapAbstractC &handle) 
  {
    RavlN::RCWrapAbstractC rawHandle;
    if(!CreateComponentInternal(node.INode(),rawHandle)) {
      SysLog(SYSLOG_DEBUG,"CreateComponentInternal(node,handle) failed. ");
      return false;
    }
    
    // ---- Convert to requested type ----
    
    RavlAssert(rawHandle.IsValid());
    
    const std::type_info &from = rawHandle.DataType();
    if(from == to) {
      handle = rawHandle;
      return true;
    }
    
    handle = RavlN::SystemTypeConverter().DoConversion(rawHandle.Abstract(),from,to);
    if(!handle.IsValid()) {
      //RavlAssert(0);
      SysLog(SYSLOG_ERR,"Don't know how to convert from type %s to %s ",RavlN::TypeName(from),RavlN::TypeName(to));
      return false;
    }
    RavlAssert(handle.IsValid());
    return true;
  }
  
  void XMLFactoryC::RegisterTypeFactory(const std::type_info &typeInfo,TypeFactoryT typeFactoryFunc) {
    StringC typeName = RavlN::TypeName(typeInfo);
    if(Type2Factory().Lookup(typeName) != 0) {
      SysLog(SYSLOG_WARNING,"Duplicate registeration of type %s in factory.",typeName.chars());
    }
    Type2Factory()[RavlN::TypeName(typeInfo)] = typeFactoryFunc;
  }
  
  //! Follow path to node.
  
  bool XMLFactoryC::FollowPath(const StringC &path,XMLFactoryNodeC::RefT &node) {
    if(!m_iRoot.IsValid())
      return false;
    return m_iRoot->FollowPath(path,node);
  }
  
  
  RavlN::HashC<StringC,XMLFactoryC::TypeFactoryT> &XMLFactoryC::Type2Factory() {
    static RavlN::HashC<StringC,TypeFactoryT> type2factory;
    return type2factory;
  }
  
  //static RavlN::TypeNameC type1(typeid(XMLFactoryC),"RavlN::XMLFactoryC");  
  static RavlN::TypeNameC type2(typeid(RavlN::SmartPtrC<XMLFactoryC>),"RavlN::SmartPtrC<RavlN::XMLFactoryC>");  
  
  
}
