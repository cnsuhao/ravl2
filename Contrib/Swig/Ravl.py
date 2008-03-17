# This file was created automatically by SWIG 1.3.27.
# Don't modify this file, modify the SWIG interface instead.

import _Ravl

# This file is compatible with both classic and new-style classes.
def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "this"):
        if isinstance(value, class_type):
            self.__dict__[name] = value.this
            if hasattr(value,"thisown"): self.__dict__["thisown"] = value.thisown
            del value.thisown
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    if (not static) or hasattr(self,name) or (name == "thisown"):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)

def _swig_setattr(self,class_type,name,value):
    return _swig_setattr_nondynamic(self,class_type,name,value,0)

def _swig_getattr(self,class_type,name):
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError,name

import types
try:
    _object = types.ObjectType
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0
del types


class DListRealC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DListRealC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DListRealC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DListC<RavlN::RealT > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, DListRealC, 'this', _Ravl.new_DListRealC(*args))
        _swig_setattr(self, DListRealC, 'thisown', 1)
    def Empty(*args): return _Ravl.DListRealC_Empty(*args)
    def InsFirst(*args): return _Ravl.DListRealC_InsFirst(*args)
    def InsLast(*args): return _Ravl.DListRealC_InsLast(*args)
    def PopFirst(*args): return _Ravl.DListRealC_PopFirst(*args)
    def PopLast(*args): return _Ravl.DListRealC_PopLast(*args)
    def MoveFirst(*args): return _Ravl.DListRealC_MoveFirst(*args)
    def MoveLast(*args): return _Ravl.DListRealC_MoveLast(*args)
    def First(*args): return _Ravl.DListRealC_First(*args)
    def Last(*args): return _Ravl.DListRealC_Last(*args)
    def Del(*args): return _Ravl.DListRealC_Del(*args)
    def Contains(*args): return _Ravl.DListRealC_Contains(*args)
    def Nth(*args): return _Ravl.DListRealC_Nth(*args)
    def __del__(self, destroy=_Ravl.delete_DListRealC):
        try:
            if self.thisown: destroy(self)
        except: pass


class DListRealCPtr(DListRealC):
    def __init__(self, this):
        _swig_setattr(self, DListRealC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, DListRealC, 'thisown', 0)
        self.__class__ = DListRealC
_Ravl.DListRealC_swigregister(DListRealCPtr)

class DListRealIterC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DListRealIterC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DListRealIterC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DLIterC<RavlN::RealT > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, DListRealIterC, 'this', _Ravl.new_DListRealIterC(*args))
        _swig_setattr(self, DListRealIterC, 'thisown', 1)
    def IsValid(*args): return _Ravl.DListRealIterC_IsValid(*args)
    def First(*args): return _Ravl.DListRealIterC_First(*args)
    def Last(*args): return _Ravl.DListRealIterC_Last(*args)
    def IsElm(*args): return _Ravl.DListRealIterC_IsElm(*args)
    def IsFirst(*args): return _Ravl.DListRealIterC_IsFirst(*args)
    def IsLast(*args): return _Ravl.DListRealIterC_IsLast(*args)
    def Next(*args): return _Ravl.DListRealIterC_Next(*args)
    def Prev(*args): return _Ravl.DListRealIterC_Prev(*args)
    def NextCrc(*args): return _Ravl.DListRealIterC_NextCrc(*args)
    def PrevCrc(*args): return _Ravl.DListRealIterC_PrevCrc(*args)
    def Nth(*args): return _Ravl.DListRealIterC_Nth(*args)
    def NextData(*args): return _Ravl.DListRealIterC_NextData(*args)
    def PrevData(*args): return _Ravl.DListRealIterC_PrevData(*args)
    def NextCrcData(*args): return _Ravl.DListRealIterC_NextCrcData(*args)
    def PrevCrcData(*args): return _Ravl.DListRealIterC_PrevCrcData(*args)
    def Tail(*args): return _Ravl.DListRealIterC_Tail(*args)
    def Head(*args): return _Ravl.DListRealIterC_Head(*args)
    def InclusiveTail(*args): return _Ravl.DListRealIterC_InclusiveTail(*args)
    def InclusiveHead(*args): return _Ravl.DListRealIterC_InclusiveHead(*args)
    def Data(*args): return _Ravl.DListRealIterC_Data(*args)
    def __deref__(*args): return _Ravl.DListRealIterC___deref__(*args)
    def __del__(self, destroy=_Ravl.delete_DListRealIterC):
        try:
            if self.thisown: destroy(self)
        except: pass


class DListRealIterCPtr(DListRealIterC):
    def __init__(self, this):
        _swig_setattr(self, DListRealIterC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, DListRealIterC, 'thisown', 0)
        self.__class__ = DListRealIterC
_Ravl.DListRealIterC_swigregister(DListRealIterCPtr)

class DListIntC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DListIntC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DListIntC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DListC<RavlN::IntT > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, DListIntC, 'this', _Ravl.new_DListIntC(*args))
        _swig_setattr(self, DListIntC, 'thisown', 1)
    def Empty(*args): return _Ravl.DListIntC_Empty(*args)
    def InsFirst(*args): return _Ravl.DListIntC_InsFirst(*args)
    def InsLast(*args): return _Ravl.DListIntC_InsLast(*args)
    def PopFirst(*args): return _Ravl.DListIntC_PopFirst(*args)
    def PopLast(*args): return _Ravl.DListIntC_PopLast(*args)
    def MoveFirst(*args): return _Ravl.DListIntC_MoveFirst(*args)
    def MoveLast(*args): return _Ravl.DListIntC_MoveLast(*args)
    def First(*args): return _Ravl.DListIntC_First(*args)
    def Last(*args): return _Ravl.DListIntC_Last(*args)
    def Del(*args): return _Ravl.DListIntC_Del(*args)
    def Contains(*args): return _Ravl.DListIntC_Contains(*args)
    def Nth(*args): return _Ravl.DListIntC_Nth(*args)
    def __del__(self, destroy=_Ravl.delete_DListIntC):
        try:
            if self.thisown: destroy(self)
        except: pass


class DListIntCPtr(DListIntC):
    def __init__(self, this):
        _swig_setattr(self, DListIntC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, DListIntC, 'thisown', 0)
        self.__class__ = DListIntC
_Ravl.DListIntC_swigregister(DListIntCPtr)

class DListIntIterC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DListIntIterC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DListIntIterC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DLIterC<RavlN::IntT > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, DListIntIterC, 'this', _Ravl.new_DListIntIterC(*args))
        _swig_setattr(self, DListIntIterC, 'thisown', 1)
    def IsValid(*args): return _Ravl.DListIntIterC_IsValid(*args)
    def First(*args): return _Ravl.DListIntIterC_First(*args)
    def Last(*args): return _Ravl.DListIntIterC_Last(*args)
    def IsElm(*args): return _Ravl.DListIntIterC_IsElm(*args)
    def IsFirst(*args): return _Ravl.DListIntIterC_IsFirst(*args)
    def IsLast(*args): return _Ravl.DListIntIterC_IsLast(*args)
    def Next(*args): return _Ravl.DListIntIterC_Next(*args)
    def Prev(*args): return _Ravl.DListIntIterC_Prev(*args)
    def NextCrc(*args): return _Ravl.DListIntIterC_NextCrc(*args)
    def PrevCrc(*args): return _Ravl.DListIntIterC_PrevCrc(*args)
    def Nth(*args): return _Ravl.DListIntIterC_Nth(*args)
    def NextData(*args): return _Ravl.DListIntIterC_NextData(*args)
    def PrevData(*args): return _Ravl.DListIntIterC_PrevData(*args)
    def NextCrcData(*args): return _Ravl.DListIntIterC_NextCrcData(*args)
    def PrevCrcData(*args): return _Ravl.DListIntIterC_PrevCrcData(*args)
    def Tail(*args): return _Ravl.DListIntIterC_Tail(*args)
    def Head(*args): return _Ravl.DListIntIterC_Head(*args)
    def InclusiveTail(*args): return _Ravl.DListIntIterC_InclusiveTail(*args)
    def InclusiveHead(*args): return _Ravl.DListIntIterC_InclusiveHead(*args)
    def Data(*args): return _Ravl.DListIntIterC_Data(*args)
    def __deref__(*args): return _Ravl.DListIntIterC___deref__(*args)
    def __del__(self, destroy=_Ravl.delete_DListIntIterC):
        try:
            if self.thisown: destroy(self)
        except: pass


class DListIntIterCPtr(DListIntIterC):
    def __init__(self, this):
        _swig_setattr(self, DListIntIterC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, DListIntIterC, 'thisown', 0)
        self.__class__ = DListIntIterC
_Ravl.DListIntIterC_swigregister(DListIntIterCPtr)

class DListUIntC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DListUIntC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DListUIntC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DListC<RavlN::UIntT > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, DListUIntC, 'this', _Ravl.new_DListUIntC(*args))
        _swig_setattr(self, DListUIntC, 'thisown', 1)
    def Empty(*args): return _Ravl.DListUIntC_Empty(*args)
    def InsFirst(*args): return _Ravl.DListUIntC_InsFirst(*args)
    def InsLast(*args): return _Ravl.DListUIntC_InsLast(*args)
    def PopFirst(*args): return _Ravl.DListUIntC_PopFirst(*args)
    def PopLast(*args): return _Ravl.DListUIntC_PopLast(*args)
    def MoveFirst(*args): return _Ravl.DListUIntC_MoveFirst(*args)
    def MoveLast(*args): return _Ravl.DListUIntC_MoveLast(*args)
    def First(*args): return _Ravl.DListUIntC_First(*args)
    def Last(*args): return _Ravl.DListUIntC_Last(*args)
    def Del(*args): return _Ravl.DListUIntC_Del(*args)
    def Contains(*args): return _Ravl.DListUIntC_Contains(*args)
    def Nth(*args): return _Ravl.DListUIntC_Nth(*args)
    def __del__(self, destroy=_Ravl.delete_DListUIntC):
        try:
            if self.thisown: destroy(self)
        except: pass


class DListUIntCPtr(DListUIntC):
    def __init__(self, this):
        _swig_setattr(self, DListUIntC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, DListUIntC, 'thisown', 0)
        self.__class__ = DListUIntC
_Ravl.DListUIntC_swigregister(DListUIntCPtr)

class DListUIntIterC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DListUIntIterC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DListUIntIterC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DLIterC<RavlN::UIntT > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, DListUIntIterC, 'this', _Ravl.new_DListUIntIterC(*args))
        _swig_setattr(self, DListUIntIterC, 'thisown', 1)
    def IsValid(*args): return _Ravl.DListUIntIterC_IsValid(*args)
    def First(*args): return _Ravl.DListUIntIterC_First(*args)
    def Last(*args): return _Ravl.DListUIntIterC_Last(*args)
    def IsElm(*args): return _Ravl.DListUIntIterC_IsElm(*args)
    def IsFirst(*args): return _Ravl.DListUIntIterC_IsFirst(*args)
    def IsLast(*args): return _Ravl.DListUIntIterC_IsLast(*args)
    def Next(*args): return _Ravl.DListUIntIterC_Next(*args)
    def Prev(*args): return _Ravl.DListUIntIterC_Prev(*args)
    def NextCrc(*args): return _Ravl.DListUIntIterC_NextCrc(*args)
    def PrevCrc(*args): return _Ravl.DListUIntIterC_PrevCrc(*args)
    def Nth(*args): return _Ravl.DListUIntIterC_Nth(*args)
    def NextData(*args): return _Ravl.DListUIntIterC_NextData(*args)
    def PrevData(*args): return _Ravl.DListUIntIterC_PrevData(*args)
    def NextCrcData(*args): return _Ravl.DListUIntIterC_NextCrcData(*args)
    def PrevCrcData(*args): return _Ravl.DListUIntIterC_PrevCrcData(*args)
    def Tail(*args): return _Ravl.DListUIntIterC_Tail(*args)
    def Head(*args): return _Ravl.DListUIntIterC_Head(*args)
    def InclusiveTail(*args): return _Ravl.DListUIntIterC_InclusiveTail(*args)
    def InclusiveHead(*args): return _Ravl.DListUIntIterC_InclusiveHead(*args)
    def Data(*args): return _Ravl.DListUIntIterC_Data(*args)
    def __deref__(*args): return _Ravl.DListUIntIterC___deref__(*args)
    def __del__(self, destroy=_Ravl.delete_DListUIntIterC):
        try:
            if self.thisown: destroy(self)
        except: pass


class DListUIntIterCPtr(DListUIntIterC):
    def __init__(self, this):
        _swig_setattr(self, DListUIntIterC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, DListUIntIterC, 'thisown', 0)
        self.__class__ = DListUIntIterC
_Ravl.DListUIntIterC_swigregister(DListUIntIterCPtr)

class DListInt64C(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DListInt64C, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DListInt64C, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DListC<RavlN::Int64T > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, DListInt64C, 'this', _Ravl.new_DListInt64C(*args))
        _swig_setattr(self, DListInt64C, 'thisown', 1)
    def Empty(*args): return _Ravl.DListInt64C_Empty(*args)
    def InsFirst(*args): return _Ravl.DListInt64C_InsFirst(*args)
    def InsLast(*args): return _Ravl.DListInt64C_InsLast(*args)
    def PopFirst(*args): return _Ravl.DListInt64C_PopFirst(*args)
    def PopLast(*args): return _Ravl.DListInt64C_PopLast(*args)
    def MoveFirst(*args): return _Ravl.DListInt64C_MoveFirst(*args)
    def MoveLast(*args): return _Ravl.DListInt64C_MoveLast(*args)
    def First(*args): return _Ravl.DListInt64C_First(*args)
    def Last(*args): return _Ravl.DListInt64C_Last(*args)
    def Del(*args): return _Ravl.DListInt64C_Del(*args)
    def Contains(*args): return _Ravl.DListInt64C_Contains(*args)
    def Nth(*args): return _Ravl.DListInt64C_Nth(*args)
    def __del__(self, destroy=_Ravl.delete_DListInt64C):
        try:
            if self.thisown: destroy(self)
        except: pass


class DListInt64CPtr(DListInt64C):
    def __init__(self, this):
        _swig_setattr(self, DListInt64C, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, DListInt64C, 'thisown', 0)
        self.__class__ = DListInt64C
_Ravl.DListInt64C_swigregister(DListInt64CPtr)

class DListInt64IterC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DListInt64IterC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DListInt64IterC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DLIterC<RavlN::Int64T > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, DListInt64IterC, 'this', _Ravl.new_DListInt64IterC(*args))
        _swig_setattr(self, DListInt64IterC, 'thisown', 1)
    def IsValid(*args): return _Ravl.DListInt64IterC_IsValid(*args)
    def First(*args): return _Ravl.DListInt64IterC_First(*args)
    def Last(*args): return _Ravl.DListInt64IterC_Last(*args)
    def IsElm(*args): return _Ravl.DListInt64IterC_IsElm(*args)
    def IsFirst(*args): return _Ravl.DListInt64IterC_IsFirst(*args)
    def IsLast(*args): return _Ravl.DListInt64IterC_IsLast(*args)
    def Next(*args): return _Ravl.DListInt64IterC_Next(*args)
    def Prev(*args): return _Ravl.DListInt64IterC_Prev(*args)
    def NextCrc(*args): return _Ravl.DListInt64IterC_NextCrc(*args)
    def PrevCrc(*args): return _Ravl.DListInt64IterC_PrevCrc(*args)
    def Nth(*args): return _Ravl.DListInt64IterC_Nth(*args)
    def NextData(*args): return _Ravl.DListInt64IterC_NextData(*args)
    def PrevData(*args): return _Ravl.DListInt64IterC_PrevData(*args)
    def NextCrcData(*args): return _Ravl.DListInt64IterC_NextCrcData(*args)
    def PrevCrcData(*args): return _Ravl.DListInt64IterC_PrevCrcData(*args)
    def Tail(*args): return _Ravl.DListInt64IterC_Tail(*args)
    def Head(*args): return _Ravl.DListInt64IterC_Head(*args)
    def InclusiveTail(*args): return _Ravl.DListInt64IterC_InclusiveTail(*args)
    def InclusiveHead(*args): return _Ravl.DListInt64IterC_InclusiveHead(*args)
    def Data(*args): return _Ravl.DListInt64IterC_Data(*args)
    def __deref__(*args): return _Ravl.DListInt64IterC___deref__(*args)
    def __del__(self, destroy=_Ravl.delete_DListInt64IterC):
        try:
            if self.thisown: destroy(self)
        except: pass


class DListInt64IterCPtr(DListInt64IterC):
    def __init__(self, this):
        _swig_setattr(self, DListInt64IterC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, DListInt64IterC, 'thisown', 0)
        self.__class__ = DListInt64IterC
_Ravl.DListInt64IterC_swigregister(DListInt64IterCPtr)

class DListInt16C(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DListInt16C, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DListInt16C, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DListC<RavlN::Int16T > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, DListInt16C, 'this', _Ravl.new_DListInt16C(*args))
        _swig_setattr(self, DListInt16C, 'thisown', 1)
    def Empty(*args): return _Ravl.DListInt16C_Empty(*args)
    def InsFirst(*args): return _Ravl.DListInt16C_InsFirst(*args)
    def InsLast(*args): return _Ravl.DListInt16C_InsLast(*args)
    def PopFirst(*args): return _Ravl.DListInt16C_PopFirst(*args)
    def PopLast(*args): return _Ravl.DListInt16C_PopLast(*args)
    def MoveFirst(*args): return _Ravl.DListInt16C_MoveFirst(*args)
    def MoveLast(*args): return _Ravl.DListInt16C_MoveLast(*args)
    def First(*args): return _Ravl.DListInt16C_First(*args)
    def Last(*args): return _Ravl.DListInt16C_Last(*args)
    def Del(*args): return _Ravl.DListInt16C_Del(*args)
    def Contains(*args): return _Ravl.DListInt16C_Contains(*args)
    def Nth(*args): return _Ravl.DListInt16C_Nth(*args)
    def __del__(self, destroy=_Ravl.delete_DListInt16C):
        try:
            if self.thisown: destroy(self)
        except: pass


class DListInt16CPtr(DListInt16C):
    def __init__(self, this):
        _swig_setattr(self, DListInt16C, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, DListInt16C, 'thisown', 0)
        self.__class__ = DListInt16C
_Ravl.DListInt16C_swigregister(DListInt16CPtr)

class DListInt16IterC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DListInt16IterC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DListInt16IterC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DLIterC<RavlN::Int16T > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, DListInt16IterC, 'this', _Ravl.new_DListInt16IterC(*args))
        _swig_setattr(self, DListInt16IterC, 'thisown', 1)
    def IsValid(*args): return _Ravl.DListInt16IterC_IsValid(*args)
    def First(*args): return _Ravl.DListInt16IterC_First(*args)
    def Last(*args): return _Ravl.DListInt16IterC_Last(*args)
    def IsElm(*args): return _Ravl.DListInt16IterC_IsElm(*args)
    def IsFirst(*args): return _Ravl.DListInt16IterC_IsFirst(*args)
    def IsLast(*args): return _Ravl.DListInt16IterC_IsLast(*args)
    def Next(*args): return _Ravl.DListInt16IterC_Next(*args)
    def Prev(*args): return _Ravl.DListInt16IterC_Prev(*args)
    def NextCrc(*args): return _Ravl.DListInt16IterC_NextCrc(*args)
    def PrevCrc(*args): return _Ravl.DListInt16IterC_PrevCrc(*args)
    def Nth(*args): return _Ravl.DListInt16IterC_Nth(*args)
    def NextData(*args): return _Ravl.DListInt16IterC_NextData(*args)
    def PrevData(*args): return _Ravl.DListInt16IterC_PrevData(*args)
    def NextCrcData(*args): return _Ravl.DListInt16IterC_NextCrcData(*args)
    def PrevCrcData(*args): return _Ravl.DListInt16IterC_PrevCrcData(*args)
    def Tail(*args): return _Ravl.DListInt16IterC_Tail(*args)
    def Head(*args): return _Ravl.DListInt16IterC_Head(*args)
    def InclusiveTail(*args): return _Ravl.DListInt16IterC_InclusiveTail(*args)
    def InclusiveHead(*args): return _Ravl.DListInt16IterC_InclusiveHead(*args)
    def Data(*args): return _Ravl.DListInt16IterC_Data(*args)
    def __deref__(*args): return _Ravl.DListInt16IterC___deref__(*args)
    def __del__(self, destroy=_Ravl.delete_DListInt16IterC):
        try:
            if self.thisown: destroy(self)
        except: pass


class DListInt16IterCPtr(DListInt16IterC):
    def __init__(self, this):
        _swig_setattr(self, DListInt16IterC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, DListInt16IterC, 'thisown', 0)
        self.__class__ = DListInt16IterC
_Ravl.DListInt16IterC_swigregister(DListInt16IterCPtr)

class DListByteC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DListByteC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DListByteC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DListC<RavlN::ByteT > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, DListByteC, 'this', _Ravl.new_DListByteC(*args))
        _swig_setattr(self, DListByteC, 'thisown', 1)
    def Empty(*args): return _Ravl.DListByteC_Empty(*args)
    def InsFirst(*args): return _Ravl.DListByteC_InsFirst(*args)
    def InsLast(*args): return _Ravl.DListByteC_InsLast(*args)
    def PopFirst(*args): return _Ravl.DListByteC_PopFirst(*args)
    def PopLast(*args): return _Ravl.DListByteC_PopLast(*args)
    def MoveFirst(*args): return _Ravl.DListByteC_MoveFirst(*args)
    def MoveLast(*args): return _Ravl.DListByteC_MoveLast(*args)
    def First(*args): return _Ravl.DListByteC_First(*args)
    def Last(*args): return _Ravl.DListByteC_Last(*args)
    def Del(*args): return _Ravl.DListByteC_Del(*args)
    def Contains(*args): return _Ravl.DListByteC_Contains(*args)
    def Nth(*args): return _Ravl.DListByteC_Nth(*args)
    def __del__(self, destroy=_Ravl.delete_DListByteC):
        try:
            if self.thisown: destroy(self)
        except: pass


class DListByteCPtr(DListByteC):
    def __init__(self, this):
        _swig_setattr(self, DListByteC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, DListByteC, 'thisown', 0)
        self.__class__ = DListByteC
_Ravl.DListByteC_swigregister(DListByteCPtr)

class DListByteIterC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DListByteIterC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DListByteIterC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DLIterC<RavlN::ByteT > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, DListByteIterC, 'this', _Ravl.new_DListByteIterC(*args))
        _swig_setattr(self, DListByteIterC, 'thisown', 1)
    def IsValid(*args): return _Ravl.DListByteIterC_IsValid(*args)
    def First(*args): return _Ravl.DListByteIterC_First(*args)
    def Last(*args): return _Ravl.DListByteIterC_Last(*args)
    def IsElm(*args): return _Ravl.DListByteIterC_IsElm(*args)
    def IsFirst(*args): return _Ravl.DListByteIterC_IsFirst(*args)
    def IsLast(*args): return _Ravl.DListByteIterC_IsLast(*args)
    def Next(*args): return _Ravl.DListByteIterC_Next(*args)
    def Prev(*args): return _Ravl.DListByteIterC_Prev(*args)
    def NextCrc(*args): return _Ravl.DListByteIterC_NextCrc(*args)
    def PrevCrc(*args): return _Ravl.DListByteIterC_PrevCrc(*args)
    def Nth(*args): return _Ravl.DListByteIterC_Nth(*args)
    def NextData(*args): return _Ravl.DListByteIterC_NextData(*args)
    def PrevData(*args): return _Ravl.DListByteIterC_PrevData(*args)
    def NextCrcData(*args): return _Ravl.DListByteIterC_NextCrcData(*args)
    def PrevCrcData(*args): return _Ravl.DListByteIterC_PrevCrcData(*args)
    def Tail(*args): return _Ravl.DListByteIterC_Tail(*args)
    def Head(*args): return _Ravl.DListByteIterC_Head(*args)
    def InclusiveTail(*args): return _Ravl.DListByteIterC_InclusiveTail(*args)
    def InclusiveHead(*args): return _Ravl.DListByteIterC_InclusiveHead(*args)
    def Data(*args): return _Ravl.DListByteIterC_Data(*args)
    def __deref__(*args): return _Ravl.DListByteIterC___deref__(*args)
    def __del__(self, destroy=_Ravl.delete_DListByteIterC):
        try:
            if self.thisown: destroy(self)
        except: pass


class DListByteIterCPtr(DListByteIterC):
    def __init__(self, this):
        _swig_setattr(self, DListByteIterC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, DListByteIterC, 'thisown', 0)
        self.__class__ = DListByteIterC
_Ravl.DListByteIterC_swigregister(DListByteIterCPtr)

class Point2dC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Point2dC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Point2dC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::Point2dC instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, Point2dC, 'this', _Ravl.new_Point2dC(*args))
        _swig_setattr(self, Point2dC, 'thisown', 1)
    def Row(*args): return _Ravl.Point2dC_Row(*args)
    def Col(*args): return _Ravl.Point2dC_Col(*args)
    def __del__(self, destroy=_Ravl.delete_Point2dC):
        try:
            if self.thisown: destroy(self)
        except: pass


class Point2dCPtr(Point2dC):
    def __init__(self, this):
        _swig_setattr(self, Point2dC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, Point2dC, 'thisown', 0)
        self.__class__ = Point2dC
_Ravl.Point2dC_swigregister(Point2dCPtr)

class DListPoint2dC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DListPoint2dC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DListPoint2dC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DListC<RavlN::Point2dC > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, DListPoint2dC, 'this', _Ravl.new_DListPoint2dC(*args))
        _swig_setattr(self, DListPoint2dC, 'thisown', 1)
    def Empty(*args): return _Ravl.DListPoint2dC_Empty(*args)
    def InsFirst(*args): return _Ravl.DListPoint2dC_InsFirst(*args)
    def InsLast(*args): return _Ravl.DListPoint2dC_InsLast(*args)
    def PopFirst(*args): return _Ravl.DListPoint2dC_PopFirst(*args)
    def PopLast(*args): return _Ravl.DListPoint2dC_PopLast(*args)
    def MoveFirst(*args): return _Ravl.DListPoint2dC_MoveFirst(*args)
    def MoveLast(*args): return _Ravl.DListPoint2dC_MoveLast(*args)
    def First(*args): return _Ravl.DListPoint2dC_First(*args)
    def Last(*args): return _Ravl.DListPoint2dC_Last(*args)
    def Del(*args): return _Ravl.DListPoint2dC_Del(*args)
    def Contains(*args): return _Ravl.DListPoint2dC_Contains(*args)
    def Nth(*args): return _Ravl.DListPoint2dC_Nth(*args)
    def __del__(self, destroy=_Ravl.delete_DListPoint2dC):
        try:
            if self.thisown: destroy(self)
        except: pass


class DListPoint2dCPtr(DListPoint2dC):
    def __init__(self, this):
        _swig_setattr(self, DListPoint2dC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, DListPoint2dC, 'thisown', 0)
        self.__class__ = DListPoint2dC
_Ravl.DListPoint2dC_swigregister(DListPoint2dCPtr)

class DListPoint2dIterC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DListPoint2dIterC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DListPoint2dIterC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DLIterC<RavlN::Point2dC > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, DListPoint2dIterC, 'this', _Ravl.new_DListPoint2dIterC(*args))
        _swig_setattr(self, DListPoint2dIterC, 'thisown', 1)
    def IsValid(*args): return _Ravl.DListPoint2dIterC_IsValid(*args)
    def First(*args): return _Ravl.DListPoint2dIterC_First(*args)
    def Last(*args): return _Ravl.DListPoint2dIterC_Last(*args)
    def IsElm(*args): return _Ravl.DListPoint2dIterC_IsElm(*args)
    def IsFirst(*args): return _Ravl.DListPoint2dIterC_IsFirst(*args)
    def IsLast(*args): return _Ravl.DListPoint2dIterC_IsLast(*args)
    def Next(*args): return _Ravl.DListPoint2dIterC_Next(*args)
    def Prev(*args): return _Ravl.DListPoint2dIterC_Prev(*args)
    def NextCrc(*args): return _Ravl.DListPoint2dIterC_NextCrc(*args)
    def PrevCrc(*args): return _Ravl.DListPoint2dIterC_PrevCrc(*args)
    def Nth(*args): return _Ravl.DListPoint2dIterC_Nth(*args)
    def NextData(*args): return _Ravl.DListPoint2dIterC_NextData(*args)
    def PrevData(*args): return _Ravl.DListPoint2dIterC_PrevData(*args)
    def NextCrcData(*args): return _Ravl.DListPoint2dIterC_NextCrcData(*args)
    def PrevCrcData(*args): return _Ravl.DListPoint2dIterC_PrevCrcData(*args)
    def Tail(*args): return _Ravl.DListPoint2dIterC_Tail(*args)
    def Head(*args): return _Ravl.DListPoint2dIterC_Head(*args)
    def InclusiveTail(*args): return _Ravl.DListPoint2dIterC_InclusiveTail(*args)
    def InclusiveHead(*args): return _Ravl.DListPoint2dIterC_InclusiveHead(*args)
    def Data(*args): return _Ravl.DListPoint2dIterC_Data(*args)
    def __deref__(*args): return _Ravl.DListPoint2dIterC___deref__(*args)
    def Row(*args): return _Ravl.DListPoint2dIterC_Row(*args)
    def Col(*args): return _Ravl.DListPoint2dIterC_Col(*args)
    def __del__(self, destroy=_Ravl.delete_DListPoint2dIterC):
        try:
            if self.thisown: destroy(self)
        except: pass


class DListPoint2dIterCPtr(DListPoint2dIterC):
    def __init__(self, this):
        _swig_setattr(self, DListPoint2dIterC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, DListPoint2dIterC, 'thisown', 0)
        self.__class__ = DListPoint2dIterC
_Ravl.DListPoint2dIterC_swigregister(DListPoint2dIterCPtr)

class IndexC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, IndexC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, IndexC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::IndexC instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, IndexC, 'this', _Ravl.new_IndexC(*args))
        _swig_setattr(self, IndexC, 'thisown', 1)
    def V(*args): return _Ravl.IndexC_V(*args)
    def __del__(self, destroy=_Ravl.delete_IndexC):
        try:
            if self.thisown: destroy(self)
        except: pass


class IndexCPtr(IndexC):
    def __init__(self, this):
        _swig_setattr(self, IndexC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, IndexC, 'thisown', 0)
        self.__class__ = IndexC
_Ravl.IndexC_swigregister(IndexCPtr)

ToList = _Ravl.ToList

class Index2dC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Index2dC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Index2dC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::Index2dC instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, Index2dC, 'this', _Ravl.new_Index2dC(*args))
        _swig_setattr(self, Index2dC, 'thisown', 1)
    def Row(*args): return _Ravl.Index2dC_Row(*args)
    def Col(*args): return _Ravl.Index2dC_Col(*args)
    def __del__(self, destroy=_Ravl.delete_Index2dC):
        try:
            if self.thisown: destroy(self)
        except: pass


class Index2dCPtr(Index2dC):
    def __init__(self, this):
        _swig_setattr(self, Index2dC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, Index2dC, 'thisown', 0)
        self.__class__ = Index2dC
_Ravl.Index2dC_swigregister(Index2dCPtr)

class IndexRange2dC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, IndexRange2dC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, IndexRange2dC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::IndexRange2dC instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, IndexRange2dC, 'this', _Ravl.new_IndexRange2dC(*args))
        _swig_setattr(self, IndexRange2dC, 'thisown', 1)
    def Rows(*args): return _Ravl.IndexRange2dC_Rows(*args)
    def Cols(*args): return _Ravl.IndexRange2dC_Cols(*args)
    def Area(*args): return _Ravl.IndexRange2dC_Area(*args)
    def Contains(*args): return _Ravl.IndexRange2dC_Contains(*args)
    def Expand(*args): return _Ravl.IndexRange2dC_Expand(*args)
    def ClipBy(*args): return _Ravl.IndexRange2dC_ClipBy(*args)
    def __del__(self, destroy=_Ravl.delete_IndexRange2dC):
        try:
            if self.thisown: destroy(self)
        except: pass


class IndexRange2dCPtr(IndexRange2dC):
    def __init__(self, this):
        _swig_setattr(self, IndexRange2dC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, IndexRange2dC, 'thisown', 0)
        self.__class__ = IndexRange2dC
_Ravl.IndexRange2dC_swigregister(IndexRange2dCPtr)

class Array2dByteC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Array2dByteC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Array2dByteC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::Array2dC<RavlN::ByteT > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, Array2dByteC, 'this', _Ravl.new_Array2dByteC(*args))
        _swig_setattr(self, Array2dByteC, 'thisown', 1)
    def Frame(*args): return _Ravl.Array2dByteC_Frame(*args)
    def Fill(*args): return _Ravl.Array2dByteC_Fill(*args)
    def Stride(*args): return _Ravl.Array2dByteC_Stride(*args)
    def Access(*args): return _Ravl.Array2dByteC_Access(*args)
    def __del__(self, destroy=_Ravl.delete_Array2dByteC):
        try:
            if self.thisown: destroy(self)
        except: pass


class Array2dByteCPtr(Array2dByteC):
    def __init__(self, this):
        _swig_setattr(self, Array2dByteC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, Array2dByteC, 'thisown', 0)
        self.__class__ = Array2dByteC
_Ravl.Array2dByteC_swigregister(Array2dByteCPtr)

class Array2dRealC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Array2dRealC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Array2dRealC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::Array2dC<RavlN::RealT > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, Array2dRealC, 'this', _Ravl.new_Array2dRealC(*args))
        _swig_setattr(self, Array2dRealC, 'thisown', 1)
    def Frame(*args): return _Ravl.Array2dRealC_Frame(*args)
    def Fill(*args): return _Ravl.Array2dRealC_Fill(*args)
    def Stride(*args): return _Ravl.Array2dRealC_Stride(*args)
    def Access(*args): return _Ravl.Array2dRealC_Access(*args)
    def __del__(self, destroy=_Ravl.delete_Array2dRealC):
        try:
            if self.thisown: destroy(self)
        except: pass


class Array2dRealCPtr(Array2dRealC):
    def __init__(self, this):
        _swig_setattr(self, Array2dRealC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, Array2dRealC, 'thisown', 0)
        self.__class__ = Array2dRealC
_Ravl.Array2dRealC_swigregister(Array2dRealCPtr)

class StringC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, StringC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, StringC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::StringC instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, StringC, 'this', _Ravl.new_StringC(*args))
        _swig_setattr(self, StringC, 'thisown', 1)
    def IsEmpty(*args): return _Ravl.StringC_IsEmpty(*args)
    def chars(*args): return _Ravl.StringC_chars(*args)
    def Size(*args): return _Ravl.StringC_Size(*args)
    def __str__(*args): return _Ravl.StringC___str__(*args)
    def __del__(self, destroy=_Ravl.delete_StringC):
        try:
            if self.thisown: destroy(self)
        except: pass


class StringCPtr(StringC):
    def __init__(self, this):
        _swig_setattr(self, StringC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, StringC, 'thisown', 0)
        self.__class__ = StringC
_Ravl.StringC_swigregister(StringCPtr)

class RealRangeC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, RealRangeC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, RealRangeC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::RealRangeC instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, RealRangeC, 'this', _Ravl.new_RealRangeC(*args))
        _swig_setattr(self, RealRangeC, 'thisown', 1)
    def Size(*args): return _Ravl.RealRangeC_Size(*args)
    def Range(*args): return _Ravl.RealRangeC_Range(*args)
    def Min(*args): return _Ravl.RealRangeC_Min(*args)
    def Max(*args): return _Ravl.RealRangeC_Max(*args)
    def Center(*args): return _Ravl.RealRangeC_Center(*args)
    def CenterD(*args): return _Ravl.RealRangeC_CenterD(*args)
    def Percentage(*args): return _Ravl.RealRangeC_Percentage(*args)
    def IsEmpty(*args): return _Ravl.RealRangeC_IsEmpty(*args)
    def IsValid(*args): return _Ravl.RealRangeC_IsValid(*args)
    def Contains(*args): return _Ravl.RealRangeC_Contains(*args)
    def __eq__(*args): return _Ravl.RealRangeC___eq__(*args)
    def __ne__(*args): return _Ravl.RealRangeC___ne__(*args)
    def In(*args): return _Ravl.RealRangeC_In(*args)
    def IsOverlapping(*args): return _Ravl.RealRangeC_IsOverlapping(*args)
    def SetOrigin(*args): return _Ravl.RealRangeC_SetOrigin(*args)
    def __iadd__(*args): return _Ravl.RealRangeC___iadd__(*args)
    def __isub__(*args): return _Ravl.RealRangeC___isub__(*args)
    def __add__(*args): return _Ravl.RealRangeC___add__(*args)
    def __sub__(*args): return _Ravl.RealRangeC___sub__(*args)
    def ClipBy(*args): return _Ravl.RealRangeC_ClipBy(*args)
    def Clip(*args): return _Ravl.RealRangeC_Clip(*args)
    def FirstHalf(*args): return _Ravl.RealRangeC_FirstHalf(*args)
    def FirstHalfD(*args): return _Ravl.RealRangeC_FirstHalfD(*args)
    def Enlarge(*args): return _Ravl.RealRangeC_Enlarge(*args)
    def Expand(*args): return _Ravl.RealRangeC_Expand(*args)
    def Shrink(*args): return _Ravl.RealRangeC_Shrink(*args)
    def ShrinkHigh(*args): return _Ravl.RealRangeC_ShrinkHigh(*args)
    def Swap(*args): return _Ravl.RealRangeC_Swap(*args)
    def Involve(*args): return _Ravl.RealRangeC_Involve(*args)
    def __del__(self, destroy=_Ravl.delete_RealRangeC):
        try:
            if self.thisown: destroy(self)
        except: pass


class RealRangeCPtr(RealRangeC):
    def __init__(self, this):
        _swig_setattr(self, RealRangeC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, RealRangeC, 'thisown', 0)
        self.__class__ = RealRangeC
_Ravl.RealRangeC_swigregister(RealRangeCPtr)

PrintIOFormats = _Ravl.PrintIOFormats

PrintIOConversions = _Ravl.PrintIOConversions

PrintIOClassTypes = _Ravl.PrintIOClassTypes

class RealRange2dC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, RealRange2dC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, RealRange2dC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::RealRange2dC instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, RealRange2dC, 'this', _Ravl.new_RealRange2dC(*args))
        _swig_setattr(self, RealRange2dC, 'thisown', 1)
    def TRow(*args): return _Ravl.RealRange2dC_TRow(*args)
    def LCol(*args): return _Ravl.RealRange2dC_LCol(*args)
    def BRow(*args): return _Ravl.RealRange2dC_BRow(*args)
    def RCol(*args): return _Ravl.RealRange2dC_RCol(*args)
    def Rows(*args): return _Ravl.RealRange2dC_Rows(*args)
    def Cols(*args): return _Ravl.RealRange2dC_Cols(*args)
    def Area(*args): return _Ravl.RealRange2dC_Area(*args)
    def Dilate(*args): return _Ravl.RealRange2dC_Dilate(*args)
    def Erode(*args): return _Ravl.RealRange2dC_Erode(*args)
    def Expand(*args): return _Ravl.RealRange2dC_Expand(*args)
    def Shrink(*args): return _Ravl.RealRange2dC_Shrink(*args)
    def ClipBy(*args): return _Ravl.RealRange2dC_ClipBy(*args)
    def Contains(*args): return _Ravl.RealRange2dC_Contains(*args)
    def RowRange(*args): return _Ravl.RealRange2dC_RowRange(*args)
    def ColRange(*args): return _Ravl.RealRange2dC_ColRange(*args)
    def Range1(*args): return _Ravl.RealRange2dC_Range1(*args)
    def Range2(*args): return _Ravl.RealRange2dC_Range2(*args)
    def Involve(*args): return _Ravl.RealRange2dC_Involve(*args)
    def IsValid(*args): return _Ravl.RealRange2dC_IsValid(*args)
    def __eq__(*args): return _Ravl.RealRange2dC___eq__(*args)
    def __ne__(*args): return _Ravl.RealRange2dC___ne__(*args)
    def IsOverlapping(*args): return _Ravl.RealRange2dC_IsOverlapping(*args)
    def __del__(self, destroy=_Ravl.delete_RealRange2dC):
        try:
            if self.thisown: destroy(self)
        except: pass


class RealRange2dCPtr(RealRange2dC):
    def __init__(self, this):
        _swig_setattr(self, RealRange2dC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, RealRange2dC, 'thisown', 0)
        self.__class__ = RealRange2dC
_Ravl.RealRange2dC_swigregister(RealRange2dCPtr)

class PointSet2dC(DListPoint2dC):
    __swig_setmethods__ = {}
    for _s in [DListPoint2dC]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, PointSet2dC, name, value)
    __swig_getmethods__ = {}
    for _s in [DListPoint2dC]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, PointSet2dC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::PointSet2dC instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, PointSet2dC, 'this', _Ravl.new_PointSet2dC(*args))
        _swig_setattr(self, PointSet2dC, 'thisown', 1)
    def Centroid(*args): return _Ravl.PointSet2dC_Centroid(*args)
    def BoundingRectangle(*args): return _Ravl.PointSet2dC_BoundingRectangle(*args)
    def __del__(self, destroy=_Ravl.delete_PointSet2dC):
        try:
            if self.thisown: destroy(self)
        except: pass


class PointSet2dCPtr(PointSet2dC):
    def __init__(self, this):
        _swig_setattr(self, PointSet2dC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, PointSet2dC, 'thisown', 0)
        self.__class__ = PointSet2dC
_Ravl.PointSet2dC_swigregister(PointSet2dCPtr)

class Polygon2dC(PointSet2dC):
    __swig_setmethods__ = {}
    for _s in [PointSet2dC]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, Polygon2dC, name, value)
    __swig_getmethods__ = {}
    for _s in [PointSet2dC]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, Polygon2dC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::Polygon2dC instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, Polygon2dC, 'this', _Ravl.new_Polygon2dC(*args))
        _swig_setattr(self, Polygon2dC, 'thisown', 1)
    def InsLast(*args): return _Ravl.Polygon2dC_InsLast(*args)
    def Size(*args): return _Ravl.Polygon2dC_Size(*args)
    def __del__(self, destroy=_Ravl.delete_Polygon2dC):
        try:
            if self.thisown: destroy(self)
        except: pass


class Polygon2dCPtr(Polygon2dC):
    def __init__(self, this):
        _swig_setattr(self, Polygon2dC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, Polygon2dC, 'thisown', 0)
        self.__class__ = Polygon2dC
_Ravl.Polygon2dC_swigregister(Polygon2dCPtr)

class ByteRGBArray2dC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, ByteRGBArray2dC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, ByteRGBArray2dC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::Array2dC<RavlImageN::ByteRGBValueC > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, ByteRGBArray2dC, 'this', _Ravl.new_ByteRGBArray2dC(*args))
        _swig_setattr(self, ByteRGBArray2dC, 'thisown', 1)
    def Frame(*args): return _Ravl.ByteRGBArray2dC_Frame(*args)
    def Fill(*args): return _Ravl.ByteRGBArray2dC_Fill(*args)
    def Stride(*args): return _Ravl.ByteRGBArray2dC_Stride(*args)
    def Access(*args): return _Ravl.ByteRGBArray2dC_Access(*args)
    def __del__(self, destroy=_Ravl.delete_ByteRGBArray2dC):
        try:
            if self.thisown: destroy(self)
        except: pass


class ByteRGBArray2dCPtr(ByteRGBArray2dC):
    def __init__(self, this):
        _swig_setattr(self, ByteRGBArray2dC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, ByteRGBArray2dC, 'thisown', 0)
        self.__class__ = ByteRGBArray2dC
_Ravl.ByteRGBArray2dC_swigregister(ByteRGBArray2dCPtr)

class RealRGBArray2dC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, RealRGBArray2dC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, RealRGBArray2dC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::Array2dC<RavlImageN::RealRGBValueC > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, RealRGBArray2dC, 'this', _Ravl.new_RealRGBArray2dC(*args))
        _swig_setattr(self, RealRGBArray2dC, 'thisown', 1)
    def Frame(*args): return _Ravl.RealRGBArray2dC_Frame(*args)
    def Fill(*args): return _Ravl.RealRGBArray2dC_Fill(*args)
    def Stride(*args): return _Ravl.RealRGBArray2dC_Stride(*args)
    def Access(*args): return _Ravl.RealRGBArray2dC_Access(*args)
    def __del__(self, destroy=_Ravl.delete_RealRGBArray2dC):
        try:
            if self.thisown: destroy(self)
        except: pass


class RealRGBArray2dCPtr(RealRGBArray2dC):
    def __init__(self, this):
        _swig_setattr(self, RealRGBArray2dC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, RealRGBArray2dC, 'thisown', 0)
        self.__class__ = RealRGBArray2dC
_Ravl.RealRGBArray2dC_swigregister(RealRGBArray2dCPtr)

class RealRGBValueC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, RealRGBValueC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, RealRGBValueC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlImageN::RealRGBValueC instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, RealRGBValueC, 'this', _Ravl.new_RealRGBValueC(*args))
        _swig_setattr(self, RealRGBValueC, 'thisown', 1)
    def Red(*args): return _Ravl.RealRGBValueC_Red(*args)
    def Green(*args): return _Ravl.RealRGBValueC_Green(*args)
    def Blue(*args): return _Ravl.RealRGBValueC_Blue(*args)
    def __del__(self, destroy=_Ravl.delete_RealRGBValueC):
        try:
            if self.thisown: destroy(self)
        except: pass


class RealRGBValueCPtr(RealRGBValueC):
    def __init__(self, this):
        _swig_setattr(self, RealRGBValueC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, RealRGBValueC, 'thisown', 0)
        self.__class__ = RealRGBValueC
_Ravl.RealRGBValueC_swigregister(RealRGBValueCPtr)

class ByteRGBValueC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, ByteRGBValueC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, ByteRGBValueC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlImageN::ByteRGBValueC instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, ByteRGBValueC, 'this', _Ravl.new_ByteRGBValueC(*args))
        _swig_setattr(self, ByteRGBValueC, 'thisown', 1)
    def Red(*args): return _Ravl.ByteRGBValueC_Red(*args)
    def Green(*args): return _Ravl.ByteRGBValueC_Green(*args)
    def Blue(*args): return _Ravl.ByteRGBValueC_Blue(*args)
    def __del__(self, destroy=_Ravl.delete_ByteRGBValueC):
        try:
            if self.thisown: destroy(self)
        except: pass


class ByteRGBValueCPtr(ByteRGBValueC):
    def __init__(self, this):
        _swig_setattr(self, ByteRGBValueC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, ByteRGBValueC, 'thisown', 0)
        self.__class__ = ByteRGBValueC
_Ravl.ByteRGBValueC_swigregister(ByteRGBValueCPtr)

class ImageByteRGBValueC(ByteRGBArray2dC):
    __swig_setmethods__ = {}
    for _s in [ByteRGBArray2dC]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, ImageByteRGBValueC, name, value)
    __swig_getmethods__ = {}
    for _s in [ByteRGBArray2dC]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, ImageByteRGBValueC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlImageN::ImageC<RavlImageN::ByteRGBValueC > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, ImageByteRGBValueC, 'this', _Ravl.new_ImageByteRGBValueC(*args))
        _swig_setattr(self, ImageByteRGBValueC, 'thisown', 1)
    def Rows(*args): return _Ravl.ImageByteRGBValueC_Rows(*args)
    def Cols(*args): return _Ravl.ImageByteRGBValueC_Cols(*args)
    def __del__(self, destroy=_Ravl.delete_ImageByteRGBValueC):
        try:
            if self.thisown: destroy(self)
        except: pass


class ImageByteRGBValueCPtr(ImageByteRGBValueC):
    def __init__(self, this):
        _swig_setattr(self, ImageByteRGBValueC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, ImageByteRGBValueC, 'thisown', 0)
        self.__class__ = ImageByteRGBValueC
_Ravl.ImageByteRGBValueC_swigregister(ImageByteRGBValueCPtr)

class ByteRGBImageC(ByteRGBArray2dC):
    __swig_setmethods__ = {}
    for _s in [ByteRGBArray2dC]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, ByteRGBImageC, name, value)
    __swig_getmethods__ = {}
    for _s in [ByteRGBArray2dC]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, ByteRGBImageC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlImageN::ImageC<RavlImageN::ByteRGBValueC > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, ByteRGBImageC, 'this', _Ravl.new_ByteRGBImageC(*args))
        _swig_setattr(self, ByteRGBImageC, 'thisown', 1)
    def Rows(*args): return _Ravl.ByteRGBImageC_Rows(*args)
    def Cols(*args): return _Ravl.ByteRGBImageC_Cols(*args)
    def __del__(self, destroy=_Ravl.delete_ByteRGBImageC):
        try:
            if self.thisown: destroy(self)
        except: pass


class ByteRGBImageCPtr(ByteRGBImageC):
    def __init__(self, this):
        _swig_setattr(self, ByteRGBImageC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, ByteRGBImageC, 'thisown', 0)
        self.__class__ = ByteRGBImageC
_Ravl.ByteRGBImageC_swigregister(ByteRGBImageCPtr)

class ImageByteC(Array2dByteC):
    __swig_setmethods__ = {}
    for _s in [Array2dByteC]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, ImageByteC, name, value)
    __swig_getmethods__ = {}
    for _s in [Array2dByteC]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, ImageByteC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlImageN::ImageC<RavlN::ByteT > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, ImageByteC, 'this', _Ravl.new_ImageByteC(*args))
        _swig_setattr(self, ImageByteC, 'thisown', 1)
    def Rows(*args): return _Ravl.ImageByteC_Rows(*args)
    def Cols(*args): return _Ravl.ImageByteC_Cols(*args)
    def __del__(self, destroy=_Ravl.delete_ImageByteC):
        try:
            if self.thisown: destroy(self)
        except: pass


class ImageByteCPtr(ImageByteC):
    def __init__(self, this):
        _swig_setattr(self, ImageByteC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, ImageByteC, 'thisown', 0)
        self.__class__ = ImageByteC
_Ravl.ImageByteC_swigregister(ImageByteCPtr)

class FontC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, FontC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, FontC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlImageN::FontC instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, FontC, 'this', _Ravl.new_FontC(*args))
        _swig_setattr(self, FontC, 'thisown', 1)
    def IsValid(*args): return _Ravl.FontC_IsValid(*args)
    def Center(*args): return _Ravl.FontC_Center(*args)
    def Size(*args): return _Ravl.FontC_Size(*args)
    def Count(*args): return _Ravl.FontC_Count(*args)
    def __del__(self, destroy=_Ravl.delete_FontC):
        try:
            if self.thisown: destroy(self)
        except: pass


class FontCPtr(FontC):
    def __init__(self, this):
        _swig_setattr(self, FontC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, FontC, 'thisown', 0)
        self.__class__ = FontC
_Ravl.FontC_swigregister(FontCPtr)

Save = _Ravl.Save

Load = _Ravl.Load

DrawPolygon = _Ravl.DrawPolygon


DefaultFont = _Ravl.DefaultFont
class Affine2dC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Affine2dC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Affine2dC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::Affine2dC instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, Affine2dC, 'this', _Ravl.new_Affine2dC(*args))
        _swig_setattr(self, Affine2dC, 'thisown', 1)
    def __del__(self, destroy=_Ravl.delete_Affine2dC):
        try:
            if self.thisown: destroy(self)
        except: pass


class Affine2dCPtr(Affine2dC):
    def __init__(self, this):
        _swig_setattr(self, Affine2dC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, Affine2dC, 'thisown', 0)
        self.__class__ = Affine2dC
_Ravl.Affine2dC_swigregister(Affine2dCPtr)

DrawText = _Ravl.DrawText

DrawTextCenter = _Ravl.DrawTextCenter

class DateC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DateC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DateC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DateC instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    __swig_getmethods__["NowUTC"] = lambda x: _Ravl.DateC_NowUTC
    if _newclass:NowUTC = staticmethod(_Ravl.DateC_NowUTC)
    __swig_getmethods__["NowLocal"] = lambda x: _Ravl.DateC_NowLocal
    if _newclass:NowLocal = staticmethod(_Ravl.DateC_NowLocal)
    __swig_getmethods__["NowVirtual"] = lambda x: _Ravl.DateC_NowVirtual
    if _newclass:NowVirtual = staticmethod(_Ravl.DateC_NowVirtual)
    __swig_getmethods__["TimeZoneOffset"] = lambda x: _Ravl.DateC_TimeZoneOffset
    if _newclass:TimeZoneOffset = staticmethod(_Ravl.DateC_TimeZoneOffset)
    def __init__(self, *args):
        _swig_setattr(self, DateC, 'this', _Ravl.new_DateC(*args))
        _swig_setattr(self, DateC, 'thisown', 1)
    __swig_getmethods__["IsLeapYear"] = lambda x: _Ravl.DateC_IsLeapYear
    if _newclass:IsLeapYear = staticmethod(_Ravl.DateC_IsLeapYear)
    __swig_getmethods__["YearToDaysSince1970"] = lambda x: _Ravl.DateC_YearToDaysSince1970
    if _newclass:YearToDaysSince1970 = staticmethod(_Ravl.DateC_YearToDaysSince1970)
    def IsValid(*args): return _Ravl.DateC_IsValid(*args)
    def IsZero(*args): return _Ravl.DateC_IsZero(*args)
    def SetInvalid(*args): return _Ravl.DateC_SetInvalid(*args)
    def SetToNow(*args): return _Ravl.DateC_SetToNow(*args)
    def MaxUSeconds(*args): return _Ravl.DateC_MaxUSeconds(*args)
    def Resolution(*args): return _Ravl.DateC_Resolution(*args)
    def NormalisePos(*args): return _Ravl.DateC_NormalisePos(*args)
    def NormaliseNeg(*args): return _Ravl.DateC_NormaliseNeg(*args)
    def __eq__(*args): return _Ravl.DateC___eq__(*args)
    def __ne__(*args): return _Ravl.DateC___ne__(*args)
    def __gt__(*args): return _Ravl.DateC___gt__(*args)
    def __lt__(*args): return _Ravl.DateC___lt__(*args)
    def __ge__(*args): return _Ravl.DateC___ge__(*args)
    def __le__(*args): return _Ravl.DateC___le__(*args)
    def __add__(*args): return _Ravl.DateC___add__(*args)
    def __sub__(*args): return _Ravl.DateC___sub__(*args)
    def __isub__(*args): return _Ravl.DateC___isub__(*args)
    def __iadd__(*args): return _Ravl.DateC___iadd__(*args)
    def Text(*args): return _Ravl.DateC_Text(*args)
    def ODBC(*args): return _Ravl.DateC_ODBC(*args)
    def SetODBC(*args): return _Ravl.DateC_SetODBC(*args)
    def CTime(*args): return _Ravl.DateC_CTime(*args)
    def CTimeShort(*args): return _Ravl.DateC_CTimeShort(*args)
    def USeconds(*args): return _Ravl.DateC_USeconds(*args)
    def TotalSeconds(*args): return _Ravl.DateC_TotalSeconds(*args)
    def Double(*args): return _Ravl.DateC_Double(*args)
    def Seconds(*args): return _Ravl.DateC_Seconds(*args)
    def Minute(*args): return _Ravl.DateC_Minute(*args)
    def Hour(*args): return _Ravl.DateC_Hour(*args)
    def Month(*args): return _Ravl.DateC_Month(*args)
    def Year(*args): return _Ravl.DateC_Year(*args)
    def DayInMonth(*args): return _Ravl.DateC_DayInMonth(*args)
    def DayInYear(*args): return _Ravl.DateC_DayInYear(*args)
    def DayInWeek(*args): return _Ravl.DateC_DayInWeek(*args)
    def TextDayInWeek(*args): return _Ravl.DateC_TextDayInWeek(*args)
    def DaylightSaving(*args): return _Ravl.DateC_DaylightSaving(*args)
    def Wait(*args): return _Ravl.DateC_Wait(*args)
    def __del__(self, destroy=_Ravl.delete_DateC):
        try:
            if self.thisown: destroy(self)
        except: pass


class DateCPtr(DateC):
    def __init__(self, this):
        _swig_setattr(self, DateC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, DateC, 'thisown', 0)
        self.__class__ = DateC
_Ravl.DateC_swigregister(DateCPtr)

DateC_NowUTC = _Ravl.DateC_NowUTC

DateC_NowLocal = _Ravl.DateC_NowLocal

DateC_NowVirtual = _Ravl.DateC_NowVirtual

DateC_TimeZoneOffset = _Ravl.DateC_TimeZoneOffset

DateC_IsLeapYear = _Ravl.DateC_IsLeapYear

DateC_YearToDaysSince1970 = _Ravl.DateC_YearToDaysSince1970

class HashInt64Int64C(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, HashInt64Int64C, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, HashInt64Int64C, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::HashC<RavlN::Int64T,RavlN::Int64T > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, HashInt64Int64C, 'this', _Ravl.new_HashInt64Int64C(*args))
        _swig_setattr(self, HashInt64Int64C, 'thisown', 1)
    def Lookup(*args): return _Ravl.HashInt64Int64C_Lookup(*args)
    def Update(*args): return _Ravl.HashInt64Int64C_Update(*args)
    def Insert(*args): return _Ravl.HashInt64Int64C_Insert(*args)
    def Access(*args): return _Ravl.HashInt64Int64C_Access(*args)
    def AccessCopy(*args): return _Ravl.HashInt64Int64C_AccessCopy(*args)
    def Del(*args): return _Ravl.HashInt64Int64C_Del(*args)
    def Get(*args): return _Ravl.HashInt64Int64C_Get(*args)
    def IsElm(*args): return _Ravl.HashInt64Int64C_IsElm(*args)
    def Empty(*args): return _Ravl.HashInt64Int64C_Empty(*args)
    def Bins(*args): return _Ravl.HashInt64Int64C_Bins(*args)
    def Resize(*args): return _Ravl.HashInt64Int64C_Resize(*args)
    def __del__(self, destroy=_Ravl.delete_HashInt64Int64C):
        try:
            if self.thisown: destroy(self)
        except: pass


class HashInt64Int64CPtr(HashInt64Int64C):
    def __init__(self, this):
        _swig_setattr(self, HashInt64Int64C, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, HashInt64Int64C, 'thisown', 0)
        self.__class__ = HashInt64Int64C
_Ravl.HashInt64Int64C_swigregister(HashInt64Int64CPtr)

class HashInt64Int64IterC(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, HashInt64Int64IterC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, HashInt64Int64IterC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::HashIterC<RavlN::Int64T,RavlN::Int64T > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        _swig_setattr(self, HashInt64Int64IterC, 'this', _Ravl.new_HashInt64Int64IterC(*args))
        _swig_setattr(self, HashInt64Int64IterC, 'thisown', 1)
    def First(*args): return _Ravl.HashInt64Int64IterC_First(*args)
    def Next(*args): return _Ravl.HashInt64Int64IterC_Next(*args)
    def IsElm(*args): return _Ravl.HashInt64Int64IterC_IsElm(*args)
    def Key(*args): return _Ravl.HashInt64Int64IterC_Key(*args)
    def Data(*args): return _Ravl.HashInt64Int64IterC_Data(*args)
    def Del(*args): return _Ravl.HashInt64Int64IterC_Del(*args)
    def __del__(self, destroy=_Ravl.delete_HashInt64Int64IterC):
        try:
            if self.thisown: destroy(self)
        except: pass


class HashInt64Int64IterCPtr(HashInt64Int64IterC):
    def __init__(self, this):
        _swig_setattr(self, HashInt64Int64IterC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, HashInt64Int64IterC, 'thisown', 0)
        self.__class__ = HashInt64Int64IterC
_Ravl.HashInt64Int64IterC_swigregister(HashInt64Int64IterCPtr)



