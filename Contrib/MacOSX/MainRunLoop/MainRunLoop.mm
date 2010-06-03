
#import <Foundation/Foundation.h>

#include "Ravl/EntryPnt.hh"
#include "Ravl/Threads/Mutex.hh"
#include "Ravl/Threads/Thread.hh"
#include <map>

#define DPDEBUG 0
#if DPDEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

@interface MacOSXStartMain : NSObject {
  RavlN::FuncMainCallT mMainFunc;
  int mArgc;
  char **mArgv;
}

- (int)callMain;

- (void)setmMainFunc:(RavlN::FuncMainCallT) funcPtr;
- (void)setmArgc:(int)argc;
- (void)setmArgv:(char **)argv;

@end

@implementation MacOSXStartMain
- (int)callMain {
  return mMainFunc(mArgc,mArgv);
}
// setArgv:(char **)newArgv
- (void) setmMainFunc:(RavlN::FuncMainCallT)aFuncPtr 
{
  mMainFunc = aFuncPtr;
}

- (void) setmArgc:(int)argc
{
  mArgc = argc;
}

- (void) setmArgv:(char **)argv
{
  mArgv = argv;
}

@end

namespace RavlN {

  static NSAutoreleasePool *AutoReleasepoolAccess() {
    static MutexC access;
    MutexLockC lock(access);
    static std::map<ThreadID,NSAutoreleasePool *> thePool;
    std::map<ThreadID,NSAutoreleasePool *>::iterator at = thePool.find(ThisThreadID());
    NSAutoreleasePool *ret;
    if(at != thePool.end()) {
      ret = at->second; 
    } else {
      ret = [[NSAutoreleasePool alloc] init];
      thePool[ThisThreadID()] = ret;
    }
    return ret;
  }
  
  //! Make sure release pool is initialised for the current thread.
  bool AutoReleasepoolInit() {
    AutoReleasepoolAccess();
    return true;
  }

  //! Call release for the current pool
  bool AutoReleasepoolRelase() {
    [AutoReleasepoolAccess() release];
    return true;
  }

  
  
  static int g_returnCode = 0;
  static volatile bool g_timeToExit = false;
  
  bool NewMainThread(int argc, char* argv[],int (*func)(int argc, char* argv[])) {
    NSAutoreleasePool *pool = AutoReleasepoolAccess();
    g_returnCode = func(argc,argv);
    g_timeToExit = true;
    [pool release];
    return true;
  }
  
  int MacOSXMainCallManager(int argc, char* argv[],int (*func)(int argc, char* argv[])) {
    NSAutoreleasePool *pool = AutoReleasepoolAccess();
      
    MacOSXStartMain *theThreadStarter = [[MacOSXStartMain alloc] init];
    [theThreadStarter setmMainFunc: func];
    [theThreadStarter setmArgc: argc];
    [theThreadStarter setmArgv: argv];
         
    [NSThread detachNewThreadSelector:@selector(callMain) toTarget:(id) theThreadStarter withObject:nil ];

    ONDEBUG(std::cerr << "Starting MacOSX main loop \n");
    // FIXME:- Must be a way of signalling the run loop to exit??
    while(!g_timeToExit) {
      ONDEBUG(std::cerr << "Loop. \n");
      [[NSRunLoop currentRunLoop] runUntilDate:[NSDate dateWithTimeIntervalSinceNow: 1]];
    }
    ONDEBUG(std::cerr << "Completed MacOSX main loop \n");
    
    [pool release];
    return g_returnCode;
  }

  bool g_linkMacOSXRunLoop =  RegisterMainCallManager(&MacOSXMainCallManager);
  bool DoLinkMacOSXMainRunLoop()
  { return g_linkMacOSXRunLoop; }
}
