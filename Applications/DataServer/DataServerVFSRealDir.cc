// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here

#include "Ravl/DataServer/DataServerVFSRealDir.hh"
#include "Ravl/OS/NetPortManager.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/DP/CacheIStream.hh"
#include "Ravl/Threads/Signal1.hh"
#include "Ravl/OS/ChildOSProcess.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace
{

  const int g_directoryPermissions = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH; // Default directory permissions.
  const int g_childProcessWait = 10; // Number of seconds to wait for the process to finish.

}

namespace RavlN {
  
  //: Constructor.
  
  DataServerVFSRealDirBodyC::DataServerVFSRealDirBodyC(const StringC &vname,const StringC& npath,const StringC &nRealDirname,bool canWrite,bool canCreate_)
    : DataServerVFSNodeBodyC(vname,npath,canWrite,true),
      realDirname(nRealDirname),
      canCreate(canCreate_)
  {
    ONDEBUG(cerr << "DataServerVFSRealDirBodyC::DataServerVFSRealDirBodyC, Called VName=" << vname << " \n");

    // Shall we create?
    if (canCreate)
    {
      // Doesn't exist, so go for it.
      if (!realDirname.Exists())
      {
        FilePermissionC permissions(g_directoryPermissions);
        if (!realDirname.MakeDir(permissions))
        {
          cerr << "DataServerVFSRealDirBodyC::DataServerVFSRealDirBodyC failed to create directory '" << nRealDirname << "'" << endl;
          // TODO(WM) Throw exception on failure?
        }
      }
    }
  }
  
  //: Destructor.
  
  DataServerVFSRealDirBodyC::~DataServerVFSRealDirBodyC() {
    // Empty out handles with a lock. This will give any stray threads a chance to exit,
    // though there should be none running in the instance by the time this gets called.
    MutexLockC lock(access);
    name2file.Empty();
  }
  
  //: Configure node with given setup.
  
  bool DataServerVFSRealDirBodyC::Configure(const ConfigFileC &config) {
    
    // Lock server while we're setting up.
    // No other threads should be running here, but better safe than sorry.
    MutexLockC lock(access);
    
    // Configure basic attributes.
    DataServerVFSNodeBodyC::Configure(config);
    
    // Setup filename 
    realDirname = config["Filename"];

    // File format
    defaultFileFormat = config["FileFormat"];
    
    return true;
  }
  
  //: Open VFS file.
  
  bool DataServerVFSRealDirBodyC::OpenVFSFile(DListC<StringC> &remainingPath,DataServerVFSRealFileC &rfile,bool forWrite) {
    StringC vfile = StringListC(remainingPath).Cat("/");
    if(vfile.IsEmpty()) {
      cerr << "DataServerVFSRealDirBodyC::OpenVFSFile, No filename remaining. VDir=" << name << "\n";
      return false;
    }
    FilenameC absFile = realDirname + "/" + vfile;

    MutexLockC lock(access);

    if(!name2file.Lookup(vfile,rfile)) {
      if (nameDeletePending.IsMember(vfile))
      {
        cerr << "DataServerVFSRealDirBodyC::OpenIPort, Refusing to open soon to be deleted file '" << absFile << "' \n";
        return false;
      }

      if(!absFile.Exists() && !forWrite) {
        cerr << "DataServerVFSRealDirBodyC::OpenIPort, Failed to open file '" << absFile << "' \n";
        return false;
      }
      
      rfile = DataServerVFSRealFileC(vfile,AbsoluteName(),absFile,canWrite);
      rfile.SetFileFormat(defaultFileFormat);
      rfile.SetCloseSignal(sigOnClose);
      rfile.SetDeleteSignal(sigOnDelete);

      name2file[vfile] = rfile;
    }

    return true;
  }

  //: Open input port.
  
  bool DataServerVFSRealDirBodyC::OpenIPort(DListC<StringC> &remainingPath,const StringC &dataType,NetISPortServerBaseC &port) {
    DataServerVFSRealFileC rfile;
    if(!OpenVFSFile(remainingPath,rfile,false))
      return false;
    DListC<StringC> emptyList;
    return rfile.OpenIPort(emptyList,dataType,port);  
  }
  
  //: Open output port.
  
  bool DataServerVFSRealDirBodyC::OpenOPort(DListC<StringC> &remainingPath,const StringC &dataType,NetOSPortServerBaseC &port) {
    // Check we can write to dir.
    if(!CanWrite())
      return false;
    
    // Setup output port.
    DataServerVFSRealFileC rfile;
    if(!OpenVFSFile(remainingPath,rfile,true))
      return false;
    DListC<StringC> emptyList;
    return rfile.OpenOPort(emptyList,dataType,port);
  }
  


  bool DataServerVFSRealDirBodyC::Delete(const DListC<StringC>& remainingPath)
  {
    ONDEBUG(cerr << "DataServerVFSRealDirBodyC::Delete '" << name << "' for '" << StringListC(remainingPath).Cat("/") << "'" << endl);
    if (!canWrite)
    {
      cerr << "DataServerVFSRealDirBodyC::OpenVFSFile attempting to delete on read-only directory '" << name << "'" << endl;
      return false;
    }

    StringC targetFilename = StringListC(remainingPath).Cat("/");
    if (targetFilename.IsEmpty())
    {
      cerr << "DataServerVFSRealDirBodyC::OpenVFSFile delete not supported for directory '" << name << "'" << endl;
      return false;
    }

    FilenameC targetFile = realDirname + "/" + targetFilename;
    DataServerVFSRealFileC targetFileNode;

    MutexLockC lock(access);
    
    if (name2file.Lookup(targetFilename, targetFileNode))
    {
      name2file.Del(targetFilename);
    }
    else
    {
      if(!targetFile.Exists())
      {
        cerr << "DataServerVFSRealDirBodyC::Delete failed to find file '" << targetFilename << "' for '" << name << "'" << endl;
        return false;
      }

      targetFileNode = DataServerVFSRealFileC(targetFilename, AbsoluteName(), targetFile, canWrite);
      targetFileNode.SetCloseSignal(sigOnClose);
      targetFileNode.SetDeleteSignal(sigOnDelete);
    }

    nameDeletePending.Insert(targetFilename);

    RavlAssert(targetFileNode.IsValid());
    return targetFileNode.Delete();
  }


  
  bool DataServerVFSRealDirBodyC::QueryNodeSpace(const StringC& remainingPath, Int64T& total, Int64T& used, Int64T& available)
  {
    StringC targetFilename =  StringListC(remainingPath).Cat("/");
    FilenameC targetFile = realDirname + "/" + targetFilename;

    if (!targetFile.Exists() || !targetFile.IsReadable())
    {
      cerr << "DataServerVFSRealDirBodyC::QueryNodeSpace target does not exist or is unreadable '" << targetFile << "'" << endl;
      return false;
    }

    if (!targetFile.IsDirectory())
    {
      if (targetFile.IsRegular())
      {
        total = -1;
        available = -1;
        used = targetFile.FileSize();

        return true;
      }

      cerr << "DataServerVFSRealDirBodyC::QueryNodeSpace cannot query size of irregular file '" << targetFile << "'" << endl;
      return false;
    }

    StringC commandLine ="df -P " + targetFile;

    ChildOSProcessC childProcess(commandLine, true);
    if (!childProcess.IsRunning() && !childProcess.ExitedOk())
    {
      cerr << "DataServerVFSRealDirBodyC::QueryNodeSpace command failed for '" << name << "'" << endl;
      return false;
    }

    StringC childOutput;
    if (childProcess.StdOut())
    {
      readline(childProcess.StdOut(), childOutput);
      if (childOutput.contains("df:"))
      {
        cerr << "DataServerVFSRealDirBodyC::QueryNodeSpace command returned error for '" << name << "' file '" << targetFile << "'" << endl;
        return false;
      }

      ONDEBUG(cerr << "DataServerVFSRealDirBodyC::QueryNodeSpace discarding command output '" << childOutput << "'" << endl);
    }

    readline(childProcess.StdOut(), childOutput);
    StringListC childOutputList(childOutput);
    if (childOutputList.Size() != 6)
    {
      cerr << "DataServerVFSRealDirBodyC::QueryNodeSpace command output size failed for '" << name << "'" << endl;
      return false;
    }

    DLIterC<StringC> listIter(childOutputList);
    listIter++; // Skip device

    total = (*listIter).Int64Value();
    listIter++;
    used = (*listIter).Int64Value();
    listIter++;
    available = (*listIter).Int64Value();

    if (childProcess.IsRunning())
    {
      if (!childProcess.Wait(g_childProcessWait))
      {
        cerr << "DataServerVFSRealDirBodyC::QueryNodeSpace waiting for process to end" << endl;
        // TODO(WM) Add a kill -9 here?
      }
    }

    return true;
  }

  
  
  bool DataServerVFSRealDirBodyC::OnDelete(DListC<StringC>& remainingPath)
  {
    ONDEBUG(cerr << "DataServerVFSRealDirBodyC::OnDelete path=" << StringListC(remainingPath).Cat("/") << endl);

    MutexLockC lock(access);
    
    StringC targetFilename = StringListC(remainingPath).Cat("/");
    nameDeletePending.Remove(targetFilename);

    return true;
  }

}
