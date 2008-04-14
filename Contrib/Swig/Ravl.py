# This file was created automatically by SWIG 1.3.27.
# Don't modify this file, modify the SWIG interface instead.

import _Ravl

# This file is compatible with both classic and new-style classes.

"""
Recognition and Vision Library
RAVL provides a base C++ class library together with a range of
computer vision, pattern recognition and supporting tools.
"""
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
    """Proxy of C++ DListRealC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DListRealC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DListRealC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DListC<RavlN::RealT > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """__init__(self) -> DListRealC"""
        _swig_setattr(self, DListRealC, 'this', _Ravl.new_DListRealC(*args))
        _swig_setattr(self, DListRealC, 'thisown', 1)
    def Empty(*args):
        """Empty(self)"""
        return _Ravl.DListRealC_Empty(*args)

    def InsFirst(*args):
        """InsFirst(self, dat)"""
        return _Ravl.DListRealC_InsFirst(*args)

    def InsLast(*args):
        """InsLast(self, dat)"""
        return _Ravl.DListRealC_InsLast(*args)

    def PopFirst(*args):
        """PopFirst(self) -> RealT"""
        return _Ravl.DListRealC_PopFirst(*args)

    def PopLast(*args):
        """PopLast(self) -> RealT"""
        return _Ravl.DListRealC_PopLast(*args)

    def MoveFirst(*args):
        """MoveFirst(self, lst)"""
        return _Ravl.DListRealC_MoveFirst(*args)

    def MoveLast(*args):
        """MoveLast(self, lst)"""
        return _Ravl.DListRealC_MoveLast(*args)

    def First(*args):
        """First(self) -> RealT"""
        return _Ravl.DListRealC_First(*args)

    def Last(*args):
        """Last(self) -> RealT"""
        return _Ravl.DListRealC_Last(*args)

    def Del(*args):
        """Del(self, x) -> bool"""
        return _Ravl.DListRealC_Del(*args)

    def Contains(*args):
        """Contains(self, x) -> bool"""
        return _Ravl.DListRealC_Contains(*args)

    def Nth(*args):
        """Nth(self, n) -> RealT"""
        return _Ravl.DListRealC_Nth(*args)

    def __del__(self, destroy=_Ravl.delete_DListRealC):
        """__del__(self)"""
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
    """Proxy of C++ DListRealIterC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DListRealIterC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DListRealIterC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DLIterC<RavlN::RealT > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """
        __init__(self) -> DListRealIterC
        __init__(self, lst) -> DListRealIterC
        """
        _swig_setattr(self, DListRealIterC, 'this', _Ravl.new_DListRealIterC(*args))
        _swig_setattr(self, DListRealIterC, 'thisown', 1)
    def IsValid(*args):
        """IsValid(self) -> bool"""
        return _Ravl.DListRealIterC_IsValid(*args)

    def First(*args):
        """First(self)"""
        return _Ravl.DListRealIterC_First(*args)

    def Last(*args):
        """Last(self)"""
        return _Ravl.DListRealIterC_Last(*args)

    def IsElm(*args):
        """IsElm(self) -> bool"""
        return _Ravl.DListRealIterC_IsElm(*args)

    def IsFirst(*args):
        """IsFirst(self) -> bool"""
        return _Ravl.DListRealIterC_IsFirst(*args)

    def IsLast(*args):
        """IsLast(self) -> bool"""
        return _Ravl.DListRealIterC_IsLast(*args)

    def Next(*args):
        """Next(self)"""
        return _Ravl.DListRealIterC_Next(*args)

    def Prev(*args):
        """Prev(self)"""
        return _Ravl.DListRealIterC_Prev(*args)

    def NextCrc(*args):
        """NextCrc(self)"""
        return _Ravl.DListRealIterC_NextCrc(*args)

    def PrevCrc(*args):
        """PrevCrc(self)"""
        return _Ravl.DListRealIterC_PrevCrc(*args)

    def Nth(*args):
        """Nth(self, n)"""
        return _Ravl.DListRealIterC_Nth(*args)

    def NextData(*args):
        """NextData(self) -> RealT"""
        return _Ravl.DListRealIterC_NextData(*args)

    def PrevData(*args):
        """PrevData(self) -> RealT"""
        return _Ravl.DListRealIterC_PrevData(*args)

    def NextCrcData(*args):
        """NextCrcData(self) -> RealT"""
        return _Ravl.DListRealIterC_NextCrcData(*args)

    def PrevCrcData(*args):
        """PrevCrcData(self) -> RealT"""
        return _Ravl.DListRealIterC_PrevCrcData(*args)

    def Tail(*args):
        """Tail(self) -> DListRealC"""
        return _Ravl.DListRealIterC_Tail(*args)

    def Head(*args):
        """Head(self) -> DListRealC"""
        return _Ravl.DListRealIterC_Head(*args)

    def InclusiveTail(*args):
        """InclusiveTail(self) -> DListRealC"""
        return _Ravl.DListRealIterC_InclusiveTail(*args)

    def InclusiveHead(*args):
        """InclusiveHead(self) -> DListRealC"""
        return _Ravl.DListRealIterC_InclusiveHead(*args)

    def Data(*args):
        """Data(self) -> RealT"""
        return _Ravl.DListRealIterC_Data(*args)

    def __deref__(*args):
        """__deref__(self) -> RealT"""
        return _Ravl.DListRealIterC___deref__(*args)

    def __del__(self, destroy=_Ravl.delete_DListRealIterC):
        """__del__(self)"""
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
    """Proxy of C++ DListIntC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DListIntC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DListIntC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DListC<RavlN::IntT > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """__init__(self) -> DListIntC"""
        _swig_setattr(self, DListIntC, 'this', _Ravl.new_DListIntC(*args))
        _swig_setattr(self, DListIntC, 'thisown', 1)
    def Empty(*args):
        """Empty(self)"""
        return _Ravl.DListIntC_Empty(*args)

    def InsFirst(*args):
        """InsFirst(self, dat)"""
        return _Ravl.DListIntC_InsFirst(*args)

    def InsLast(*args):
        """InsLast(self, dat)"""
        return _Ravl.DListIntC_InsLast(*args)

    def PopFirst(*args):
        """PopFirst(self) -> IntT"""
        return _Ravl.DListIntC_PopFirst(*args)

    def PopLast(*args):
        """PopLast(self) -> IntT"""
        return _Ravl.DListIntC_PopLast(*args)

    def MoveFirst(*args):
        """MoveFirst(self, lst)"""
        return _Ravl.DListIntC_MoveFirst(*args)

    def MoveLast(*args):
        """MoveLast(self, lst)"""
        return _Ravl.DListIntC_MoveLast(*args)

    def First(*args):
        """First(self) -> IntT"""
        return _Ravl.DListIntC_First(*args)

    def Last(*args):
        """Last(self) -> IntT"""
        return _Ravl.DListIntC_Last(*args)

    def Del(*args):
        """Del(self, x) -> bool"""
        return _Ravl.DListIntC_Del(*args)

    def Contains(*args):
        """Contains(self, x) -> bool"""
        return _Ravl.DListIntC_Contains(*args)

    def Nth(*args):
        """Nth(self, n) -> IntT"""
        return _Ravl.DListIntC_Nth(*args)

    def __del__(self, destroy=_Ravl.delete_DListIntC):
        """__del__(self)"""
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
    """Proxy of C++ DListIntIterC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DListIntIterC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DListIntIterC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DLIterC<RavlN::IntT > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """
        __init__(self) -> DListIntIterC
        __init__(self, lst) -> DListIntIterC
        """
        _swig_setattr(self, DListIntIterC, 'this', _Ravl.new_DListIntIterC(*args))
        _swig_setattr(self, DListIntIterC, 'thisown', 1)
    def IsValid(*args):
        """IsValid(self) -> bool"""
        return _Ravl.DListIntIterC_IsValid(*args)

    def First(*args):
        """First(self)"""
        return _Ravl.DListIntIterC_First(*args)

    def Last(*args):
        """Last(self)"""
        return _Ravl.DListIntIterC_Last(*args)

    def IsElm(*args):
        """IsElm(self) -> bool"""
        return _Ravl.DListIntIterC_IsElm(*args)

    def IsFirst(*args):
        """IsFirst(self) -> bool"""
        return _Ravl.DListIntIterC_IsFirst(*args)

    def IsLast(*args):
        """IsLast(self) -> bool"""
        return _Ravl.DListIntIterC_IsLast(*args)

    def Next(*args):
        """Next(self)"""
        return _Ravl.DListIntIterC_Next(*args)

    def Prev(*args):
        """Prev(self)"""
        return _Ravl.DListIntIterC_Prev(*args)

    def NextCrc(*args):
        """NextCrc(self)"""
        return _Ravl.DListIntIterC_NextCrc(*args)

    def PrevCrc(*args):
        """PrevCrc(self)"""
        return _Ravl.DListIntIterC_PrevCrc(*args)

    def Nth(*args):
        """Nth(self, n)"""
        return _Ravl.DListIntIterC_Nth(*args)

    def NextData(*args):
        """NextData(self) -> IntT"""
        return _Ravl.DListIntIterC_NextData(*args)

    def PrevData(*args):
        """PrevData(self) -> IntT"""
        return _Ravl.DListIntIterC_PrevData(*args)

    def NextCrcData(*args):
        """NextCrcData(self) -> IntT"""
        return _Ravl.DListIntIterC_NextCrcData(*args)

    def PrevCrcData(*args):
        """PrevCrcData(self) -> IntT"""
        return _Ravl.DListIntIterC_PrevCrcData(*args)

    def Tail(*args):
        """Tail(self) -> DListIntC"""
        return _Ravl.DListIntIterC_Tail(*args)

    def Head(*args):
        """Head(self) -> DListIntC"""
        return _Ravl.DListIntIterC_Head(*args)

    def InclusiveTail(*args):
        """InclusiveTail(self) -> DListIntC"""
        return _Ravl.DListIntIterC_InclusiveTail(*args)

    def InclusiveHead(*args):
        """InclusiveHead(self) -> DListIntC"""
        return _Ravl.DListIntIterC_InclusiveHead(*args)

    def Data(*args):
        """Data(self) -> IntT"""
        return _Ravl.DListIntIterC_Data(*args)

    def __deref__(*args):
        """__deref__(self) -> IntT"""
        return _Ravl.DListIntIterC___deref__(*args)

    def __del__(self, destroy=_Ravl.delete_DListIntIterC):
        """__del__(self)"""
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
    """Proxy of C++ DListUIntC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DListUIntC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DListUIntC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DListC<RavlN::UIntT > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """__init__(self) -> DListUIntC"""
        _swig_setattr(self, DListUIntC, 'this', _Ravl.new_DListUIntC(*args))
        _swig_setattr(self, DListUIntC, 'thisown', 1)
    def Empty(*args):
        """Empty(self)"""
        return _Ravl.DListUIntC_Empty(*args)

    def InsFirst(*args):
        """InsFirst(self, dat)"""
        return _Ravl.DListUIntC_InsFirst(*args)

    def InsLast(*args):
        """InsLast(self, dat)"""
        return _Ravl.DListUIntC_InsLast(*args)

    def PopFirst(*args):
        """PopFirst(self) -> UIntT"""
        return _Ravl.DListUIntC_PopFirst(*args)

    def PopLast(*args):
        """PopLast(self) -> UIntT"""
        return _Ravl.DListUIntC_PopLast(*args)

    def MoveFirst(*args):
        """MoveFirst(self, lst)"""
        return _Ravl.DListUIntC_MoveFirst(*args)

    def MoveLast(*args):
        """MoveLast(self, lst)"""
        return _Ravl.DListUIntC_MoveLast(*args)

    def First(*args):
        """First(self) -> UIntT"""
        return _Ravl.DListUIntC_First(*args)

    def Last(*args):
        """Last(self) -> UIntT"""
        return _Ravl.DListUIntC_Last(*args)

    def Del(*args):
        """Del(self, x) -> bool"""
        return _Ravl.DListUIntC_Del(*args)

    def Contains(*args):
        """Contains(self, x) -> bool"""
        return _Ravl.DListUIntC_Contains(*args)

    def Nth(*args):
        """Nth(self, n) -> UIntT"""
        return _Ravl.DListUIntC_Nth(*args)

    def __del__(self, destroy=_Ravl.delete_DListUIntC):
        """__del__(self)"""
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
    """Proxy of C++ DListUIntIterC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DListUIntIterC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DListUIntIterC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DLIterC<RavlN::UIntT > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """
        __init__(self) -> DListUIntIterC
        __init__(self, lst) -> DListUIntIterC
        """
        _swig_setattr(self, DListUIntIterC, 'this', _Ravl.new_DListUIntIterC(*args))
        _swig_setattr(self, DListUIntIterC, 'thisown', 1)
    def IsValid(*args):
        """IsValid(self) -> bool"""
        return _Ravl.DListUIntIterC_IsValid(*args)

    def First(*args):
        """First(self)"""
        return _Ravl.DListUIntIterC_First(*args)

    def Last(*args):
        """Last(self)"""
        return _Ravl.DListUIntIterC_Last(*args)

    def IsElm(*args):
        """IsElm(self) -> bool"""
        return _Ravl.DListUIntIterC_IsElm(*args)

    def IsFirst(*args):
        """IsFirst(self) -> bool"""
        return _Ravl.DListUIntIterC_IsFirst(*args)

    def IsLast(*args):
        """IsLast(self) -> bool"""
        return _Ravl.DListUIntIterC_IsLast(*args)

    def Next(*args):
        """Next(self)"""
        return _Ravl.DListUIntIterC_Next(*args)

    def Prev(*args):
        """Prev(self)"""
        return _Ravl.DListUIntIterC_Prev(*args)

    def NextCrc(*args):
        """NextCrc(self)"""
        return _Ravl.DListUIntIterC_NextCrc(*args)

    def PrevCrc(*args):
        """PrevCrc(self)"""
        return _Ravl.DListUIntIterC_PrevCrc(*args)

    def Nth(*args):
        """Nth(self, n)"""
        return _Ravl.DListUIntIterC_Nth(*args)

    def NextData(*args):
        """NextData(self) -> UIntT"""
        return _Ravl.DListUIntIterC_NextData(*args)

    def PrevData(*args):
        """PrevData(self) -> UIntT"""
        return _Ravl.DListUIntIterC_PrevData(*args)

    def NextCrcData(*args):
        """NextCrcData(self) -> UIntT"""
        return _Ravl.DListUIntIterC_NextCrcData(*args)

    def PrevCrcData(*args):
        """PrevCrcData(self) -> UIntT"""
        return _Ravl.DListUIntIterC_PrevCrcData(*args)

    def Tail(*args):
        """Tail(self) -> DListUIntC"""
        return _Ravl.DListUIntIterC_Tail(*args)

    def Head(*args):
        """Head(self) -> DListUIntC"""
        return _Ravl.DListUIntIterC_Head(*args)

    def InclusiveTail(*args):
        """InclusiveTail(self) -> DListUIntC"""
        return _Ravl.DListUIntIterC_InclusiveTail(*args)

    def InclusiveHead(*args):
        """InclusiveHead(self) -> DListUIntC"""
        return _Ravl.DListUIntIterC_InclusiveHead(*args)

    def Data(*args):
        """Data(self) -> UIntT"""
        return _Ravl.DListUIntIterC_Data(*args)

    def __deref__(*args):
        """__deref__(self) -> UIntT"""
        return _Ravl.DListUIntIterC___deref__(*args)

    def __del__(self, destroy=_Ravl.delete_DListUIntIterC):
        """__del__(self)"""
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
    """Proxy of C++ DListInt64C class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DListInt64C, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DListInt64C, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DListC<RavlN::Int64T > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """__init__(self) -> DListInt64C"""
        _swig_setattr(self, DListInt64C, 'this', _Ravl.new_DListInt64C(*args))
        _swig_setattr(self, DListInt64C, 'thisown', 1)
    def Empty(*args):
        """Empty(self)"""
        return _Ravl.DListInt64C_Empty(*args)

    def InsFirst(*args):
        """InsFirst(self, dat)"""
        return _Ravl.DListInt64C_InsFirst(*args)

    def InsLast(*args):
        """InsLast(self, dat)"""
        return _Ravl.DListInt64C_InsLast(*args)

    def PopFirst(*args):
        """PopFirst(self) -> Int64T"""
        return _Ravl.DListInt64C_PopFirst(*args)

    def PopLast(*args):
        """PopLast(self) -> Int64T"""
        return _Ravl.DListInt64C_PopLast(*args)

    def MoveFirst(*args):
        """MoveFirst(self, lst)"""
        return _Ravl.DListInt64C_MoveFirst(*args)

    def MoveLast(*args):
        """MoveLast(self, lst)"""
        return _Ravl.DListInt64C_MoveLast(*args)

    def First(*args):
        """First(self) -> Int64T"""
        return _Ravl.DListInt64C_First(*args)

    def Last(*args):
        """Last(self) -> Int64T"""
        return _Ravl.DListInt64C_Last(*args)

    def Del(*args):
        """Del(self, x) -> bool"""
        return _Ravl.DListInt64C_Del(*args)

    def Contains(*args):
        """Contains(self, x) -> bool"""
        return _Ravl.DListInt64C_Contains(*args)

    def Nth(*args):
        """Nth(self, n) -> Int64T"""
        return _Ravl.DListInt64C_Nth(*args)

    def __del__(self, destroy=_Ravl.delete_DListInt64C):
        """__del__(self)"""
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
    """Proxy of C++ DListInt64IterC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DListInt64IterC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DListInt64IterC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DLIterC<RavlN::Int64T > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """
        __init__(self) -> DListInt64IterC
        __init__(self, lst) -> DListInt64IterC
        """
        _swig_setattr(self, DListInt64IterC, 'this', _Ravl.new_DListInt64IterC(*args))
        _swig_setattr(self, DListInt64IterC, 'thisown', 1)
    def IsValid(*args):
        """IsValid(self) -> bool"""
        return _Ravl.DListInt64IterC_IsValid(*args)

    def First(*args):
        """First(self)"""
        return _Ravl.DListInt64IterC_First(*args)

    def Last(*args):
        """Last(self)"""
        return _Ravl.DListInt64IterC_Last(*args)

    def IsElm(*args):
        """IsElm(self) -> bool"""
        return _Ravl.DListInt64IterC_IsElm(*args)

    def IsFirst(*args):
        """IsFirst(self) -> bool"""
        return _Ravl.DListInt64IterC_IsFirst(*args)

    def IsLast(*args):
        """IsLast(self) -> bool"""
        return _Ravl.DListInt64IterC_IsLast(*args)

    def Next(*args):
        """Next(self)"""
        return _Ravl.DListInt64IterC_Next(*args)

    def Prev(*args):
        """Prev(self)"""
        return _Ravl.DListInt64IterC_Prev(*args)

    def NextCrc(*args):
        """NextCrc(self)"""
        return _Ravl.DListInt64IterC_NextCrc(*args)

    def PrevCrc(*args):
        """PrevCrc(self)"""
        return _Ravl.DListInt64IterC_PrevCrc(*args)

    def Nth(*args):
        """Nth(self, n)"""
        return _Ravl.DListInt64IterC_Nth(*args)

    def NextData(*args):
        """NextData(self) -> Int64T"""
        return _Ravl.DListInt64IterC_NextData(*args)

    def PrevData(*args):
        """PrevData(self) -> Int64T"""
        return _Ravl.DListInt64IterC_PrevData(*args)

    def NextCrcData(*args):
        """NextCrcData(self) -> Int64T"""
        return _Ravl.DListInt64IterC_NextCrcData(*args)

    def PrevCrcData(*args):
        """PrevCrcData(self) -> Int64T"""
        return _Ravl.DListInt64IterC_PrevCrcData(*args)

    def Tail(*args):
        """Tail(self) -> DListInt64C"""
        return _Ravl.DListInt64IterC_Tail(*args)

    def Head(*args):
        """Head(self) -> DListInt64C"""
        return _Ravl.DListInt64IterC_Head(*args)

    def InclusiveTail(*args):
        """InclusiveTail(self) -> DListInt64C"""
        return _Ravl.DListInt64IterC_InclusiveTail(*args)

    def InclusiveHead(*args):
        """InclusiveHead(self) -> DListInt64C"""
        return _Ravl.DListInt64IterC_InclusiveHead(*args)

    def Data(*args):
        """Data(self) -> Int64T"""
        return _Ravl.DListInt64IterC_Data(*args)

    def __deref__(*args):
        """__deref__(self) -> Int64T"""
        return _Ravl.DListInt64IterC___deref__(*args)

    def __del__(self, destroy=_Ravl.delete_DListInt64IterC):
        """__del__(self)"""
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
    """Proxy of C++ DListInt16C class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DListInt16C, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DListInt16C, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DListC<RavlN::Int16T > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """__init__(self) -> DListInt16C"""
        _swig_setattr(self, DListInt16C, 'this', _Ravl.new_DListInt16C(*args))
        _swig_setattr(self, DListInt16C, 'thisown', 1)
    def Empty(*args):
        """Empty(self)"""
        return _Ravl.DListInt16C_Empty(*args)

    def InsFirst(*args):
        """InsFirst(self, dat)"""
        return _Ravl.DListInt16C_InsFirst(*args)

    def InsLast(*args):
        """InsLast(self, dat)"""
        return _Ravl.DListInt16C_InsLast(*args)

    def PopFirst(*args):
        """PopFirst(self) -> Int16T"""
        return _Ravl.DListInt16C_PopFirst(*args)

    def PopLast(*args):
        """PopLast(self) -> Int16T"""
        return _Ravl.DListInt16C_PopLast(*args)

    def MoveFirst(*args):
        """MoveFirst(self, lst)"""
        return _Ravl.DListInt16C_MoveFirst(*args)

    def MoveLast(*args):
        """MoveLast(self, lst)"""
        return _Ravl.DListInt16C_MoveLast(*args)

    def First(*args):
        """First(self) -> Int16T"""
        return _Ravl.DListInt16C_First(*args)

    def Last(*args):
        """Last(self) -> Int16T"""
        return _Ravl.DListInt16C_Last(*args)

    def Del(*args):
        """Del(self, x) -> bool"""
        return _Ravl.DListInt16C_Del(*args)

    def Contains(*args):
        """Contains(self, x) -> bool"""
        return _Ravl.DListInt16C_Contains(*args)

    def Nth(*args):
        """Nth(self, n) -> Int16T"""
        return _Ravl.DListInt16C_Nth(*args)

    def __del__(self, destroy=_Ravl.delete_DListInt16C):
        """__del__(self)"""
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
    """Proxy of C++ DListInt16IterC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DListInt16IterC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DListInt16IterC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DLIterC<RavlN::Int16T > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """
        __init__(self) -> DListInt16IterC
        __init__(self, lst) -> DListInt16IterC
        """
        _swig_setattr(self, DListInt16IterC, 'this', _Ravl.new_DListInt16IterC(*args))
        _swig_setattr(self, DListInt16IterC, 'thisown', 1)
    def IsValid(*args):
        """IsValid(self) -> bool"""
        return _Ravl.DListInt16IterC_IsValid(*args)

    def First(*args):
        """First(self)"""
        return _Ravl.DListInt16IterC_First(*args)

    def Last(*args):
        """Last(self)"""
        return _Ravl.DListInt16IterC_Last(*args)

    def IsElm(*args):
        """IsElm(self) -> bool"""
        return _Ravl.DListInt16IterC_IsElm(*args)

    def IsFirst(*args):
        """IsFirst(self) -> bool"""
        return _Ravl.DListInt16IterC_IsFirst(*args)

    def IsLast(*args):
        """IsLast(self) -> bool"""
        return _Ravl.DListInt16IterC_IsLast(*args)

    def Next(*args):
        """Next(self)"""
        return _Ravl.DListInt16IterC_Next(*args)

    def Prev(*args):
        """Prev(self)"""
        return _Ravl.DListInt16IterC_Prev(*args)

    def NextCrc(*args):
        """NextCrc(self)"""
        return _Ravl.DListInt16IterC_NextCrc(*args)

    def PrevCrc(*args):
        """PrevCrc(self)"""
        return _Ravl.DListInt16IterC_PrevCrc(*args)

    def Nth(*args):
        """Nth(self, n)"""
        return _Ravl.DListInt16IterC_Nth(*args)

    def NextData(*args):
        """NextData(self) -> Int16T"""
        return _Ravl.DListInt16IterC_NextData(*args)

    def PrevData(*args):
        """PrevData(self) -> Int16T"""
        return _Ravl.DListInt16IterC_PrevData(*args)

    def NextCrcData(*args):
        """NextCrcData(self) -> Int16T"""
        return _Ravl.DListInt16IterC_NextCrcData(*args)

    def PrevCrcData(*args):
        """PrevCrcData(self) -> Int16T"""
        return _Ravl.DListInt16IterC_PrevCrcData(*args)

    def Tail(*args):
        """Tail(self) -> DListInt16C"""
        return _Ravl.DListInt16IterC_Tail(*args)

    def Head(*args):
        """Head(self) -> DListInt16C"""
        return _Ravl.DListInt16IterC_Head(*args)

    def InclusiveTail(*args):
        """InclusiveTail(self) -> DListInt16C"""
        return _Ravl.DListInt16IterC_InclusiveTail(*args)

    def InclusiveHead(*args):
        """InclusiveHead(self) -> DListInt16C"""
        return _Ravl.DListInt16IterC_InclusiveHead(*args)

    def Data(*args):
        """Data(self) -> Int16T"""
        return _Ravl.DListInt16IterC_Data(*args)

    def __deref__(*args):
        """__deref__(self) -> Int16T"""
        return _Ravl.DListInt16IterC___deref__(*args)

    def __del__(self, destroy=_Ravl.delete_DListInt16IterC):
        """__del__(self)"""
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
    """Proxy of C++ DListByteC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DListByteC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DListByteC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DListC<RavlN::ByteT > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """__init__(self) -> DListByteC"""
        _swig_setattr(self, DListByteC, 'this', _Ravl.new_DListByteC(*args))
        _swig_setattr(self, DListByteC, 'thisown', 1)
    def Empty(*args):
        """Empty(self)"""
        return _Ravl.DListByteC_Empty(*args)

    def InsFirst(*args):
        """InsFirst(self, dat)"""
        return _Ravl.DListByteC_InsFirst(*args)

    def InsLast(*args):
        """InsLast(self, dat)"""
        return _Ravl.DListByteC_InsLast(*args)

    def PopFirst(*args):
        """PopFirst(self) -> ByteT"""
        return _Ravl.DListByteC_PopFirst(*args)

    def PopLast(*args):
        """PopLast(self) -> ByteT"""
        return _Ravl.DListByteC_PopLast(*args)

    def MoveFirst(*args):
        """MoveFirst(self, lst)"""
        return _Ravl.DListByteC_MoveFirst(*args)

    def MoveLast(*args):
        """MoveLast(self, lst)"""
        return _Ravl.DListByteC_MoveLast(*args)

    def First(*args):
        """First(self) -> ByteT"""
        return _Ravl.DListByteC_First(*args)

    def Last(*args):
        """Last(self) -> ByteT"""
        return _Ravl.DListByteC_Last(*args)

    def Del(*args):
        """Del(self, x) -> bool"""
        return _Ravl.DListByteC_Del(*args)

    def Contains(*args):
        """Contains(self, x) -> bool"""
        return _Ravl.DListByteC_Contains(*args)

    def Nth(*args):
        """Nth(self, n) -> ByteT"""
        return _Ravl.DListByteC_Nth(*args)

    def __del__(self, destroy=_Ravl.delete_DListByteC):
        """__del__(self)"""
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
    """Proxy of C++ DListByteIterC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DListByteIterC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DListByteIterC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DLIterC<RavlN::ByteT > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """
        __init__(self) -> DListByteIterC
        __init__(self, lst) -> DListByteIterC
        """
        _swig_setattr(self, DListByteIterC, 'this', _Ravl.new_DListByteIterC(*args))
        _swig_setattr(self, DListByteIterC, 'thisown', 1)
    def IsValid(*args):
        """IsValid(self) -> bool"""
        return _Ravl.DListByteIterC_IsValid(*args)

    def First(*args):
        """First(self)"""
        return _Ravl.DListByteIterC_First(*args)

    def Last(*args):
        """Last(self)"""
        return _Ravl.DListByteIterC_Last(*args)

    def IsElm(*args):
        """IsElm(self) -> bool"""
        return _Ravl.DListByteIterC_IsElm(*args)

    def IsFirst(*args):
        """IsFirst(self) -> bool"""
        return _Ravl.DListByteIterC_IsFirst(*args)

    def IsLast(*args):
        """IsLast(self) -> bool"""
        return _Ravl.DListByteIterC_IsLast(*args)

    def Next(*args):
        """Next(self)"""
        return _Ravl.DListByteIterC_Next(*args)

    def Prev(*args):
        """Prev(self)"""
        return _Ravl.DListByteIterC_Prev(*args)

    def NextCrc(*args):
        """NextCrc(self)"""
        return _Ravl.DListByteIterC_NextCrc(*args)

    def PrevCrc(*args):
        """PrevCrc(self)"""
        return _Ravl.DListByteIterC_PrevCrc(*args)

    def Nth(*args):
        """Nth(self, n)"""
        return _Ravl.DListByteIterC_Nth(*args)

    def NextData(*args):
        """NextData(self) -> ByteT"""
        return _Ravl.DListByteIterC_NextData(*args)

    def PrevData(*args):
        """PrevData(self) -> ByteT"""
        return _Ravl.DListByteIterC_PrevData(*args)

    def NextCrcData(*args):
        """NextCrcData(self) -> ByteT"""
        return _Ravl.DListByteIterC_NextCrcData(*args)

    def PrevCrcData(*args):
        """PrevCrcData(self) -> ByteT"""
        return _Ravl.DListByteIterC_PrevCrcData(*args)

    def Tail(*args):
        """Tail(self) -> DListByteC"""
        return _Ravl.DListByteIterC_Tail(*args)

    def Head(*args):
        """Head(self) -> DListByteC"""
        return _Ravl.DListByteIterC_Head(*args)

    def InclusiveTail(*args):
        """InclusiveTail(self) -> DListByteC"""
        return _Ravl.DListByteIterC_InclusiveTail(*args)

    def InclusiveHead(*args):
        """InclusiveHead(self) -> DListByteC"""
        return _Ravl.DListByteIterC_InclusiveHead(*args)

    def Data(*args):
        """Data(self) -> ByteT"""
        return _Ravl.DListByteIterC_Data(*args)

    def __deref__(*args):
        """__deref__(self) -> ByteT"""
        return _Ravl.DListByteIterC___deref__(*args)

    def __del__(self, destroy=_Ravl.delete_DListByteIterC):
        """__del__(self)"""
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
    """Proxy of C++ Point2dC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Point2dC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Point2dC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::Point2dC instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """
        __init__(self) -> Point2dC
        __init__(self, x, y) -> Point2dC
        """
        _swig_setattr(self, Point2dC, 'this', _Ravl.new_Point2dC(*args))
        _swig_setattr(self, Point2dC, 'thisown', 1)
    def Row(*args):
        """Row(self) -> RealT"""
        return _Ravl.Point2dC_Row(*args)

    def Col(*args):
        """Col(self) -> RealT"""
        return _Ravl.Point2dC_Col(*args)

    def __del__(self, destroy=_Ravl.delete_Point2dC):
        """__del__(self)"""
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
    """Proxy of C++ DListPoint2dC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DListPoint2dC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DListPoint2dC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DListC<RavlN::Point2dC > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """__init__(self) -> DListPoint2dC"""
        _swig_setattr(self, DListPoint2dC, 'this', _Ravl.new_DListPoint2dC(*args))
        _swig_setattr(self, DListPoint2dC, 'thisown', 1)
    def Empty(*args):
        """Empty(self)"""
        return _Ravl.DListPoint2dC_Empty(*args)

    def InsFirst(*args):
        """InsFirst(self, dat)"""
        return _Ravl.DListPoint2dC_InsFirst(*args)

    def InsLast(*args):
        """InsLast(self, dat)"""
        return _Ravl.DListPoint2dC_InsLast(*args)

    def PopFirst(*args):
        """PopFirst(self) -> Point2dC"""
        return _Ravl.DListPoint2dC_PopFirst(*args)

    def PopLast(*args):
        """PopLast(self) -> Point2dC"""
        return _Ravl.DListPoint2dC_PopLast(*args)

    def MoveFirst(*args):
        """MoveFirst(self, lst)"""
        return _Ravl.DListPoint2dC_MoveFirst(*args)

    def MoveLast(*args):
        """MoveLast(self, lst)"""
        return _Ravl.DListPoint2dC_MoveLast(*args)

    def First(*args):
        """First(self) -> Point2dC"""
        return _Ravl.DListPoint2dC_First(*args)

    def Last(*args):
        """Last(self) -> Point2dC"""
        return _Ravl.DListPoint2dC_Last(*args)

    def Del(*args):
        """Del(self, x) -> bool"""
        return _Ravl.DListPoint2dC_Del(*args)

    def Contains(*args):
        """Contains(self, x) -> bool"""
        return _Ravl.DListPoint2dC_Contains(*args)

    def Nth(*args):
        """Nth(self, n) -> Point2dC"""
        return _Ravl.DListPoint2dC_Nth(*args)

    def __del__(self, destroy=_Ravl.delete_DListPoint2dC):
        """__del__(self)"""
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
    """Proxy of C++ DListPoint2dIterC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DListPoint2dIterC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DListPoint2dIterC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DLIterC<RavlN::Point2dC > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """
        __init__(self) -> DListPoint2dIterC
        __init__(self, lst) -> DListPoint2dIterC
        """
        _swig_setattr(self, DListPoint2dIterC, 'this', _Ravl.new_DListPoint2dIterC(*args))
        _swig_setattr(self, DListPoint2dIterC, 'thisown', 1)
    def IsValid(*args):
        """IsValid(self) -> bool"""
        return _Ravl.DListPoint2dIterC_IsValid(*args)

    def First(*args):
        """First(self)"""
        return _Ravl.DListPoint2dIterC_First(*args)

    def Last(*args):
        """Last(self)"""
        return _Ravl.DListPoint2dIterC_Last(*args)

    def IsElm(*args):
        """IsElm(self) -> bool"""
        return _Ravl.DListPoint2dIterC_IsElm(*args)

    def IsFirst(*args):
        """IsFirst(self) -> bool"""
        return _Ravl.DListPoint2dIterC_IsFirst(*args)

    def IsLast(*args):
        """IsLast(self) -> bool"""
        return _Ravl.DListPoint2dIterC_IsLast(*args)

    def Next(*args):
        """Next(self)"""
        return _Ravl.DListPoint2dIterC_Next(*args)

    def Prev(*args):
        """Prev(self)"""
        return _Ravl.DListPoint2dIterC_Prev(*args)

    def NextCrc(*args):
        """NextCrc(self)"""
        return _Ravl.DListPoint2dIterC_NextCrc(*args)

    def PrevCrc(*args):
        """PrevCrc(self)"""
        return _Ravl.DListPoint2dIterC_PrevCrc(*args)

    def Nth(*args):
        """Nth(self, n)"""
        return _Ravl.DListPoint2dIterC_Nth(*args)

    def NextData(*args):
        """NextData(self) -> Point2dC"""
        return _Ravl.DListPoint2dIterC_NextData(*args)

    def PrevData(*args):
        """PrevData(self) -> Point2dC"""
        return _Ravl.DListPoint2dIterC_PrevData(*args)

    def NextCrcData(*args):
        """NextCrcData(self) -> Point2dC"""
        return _Ravl.DListPoint2dIterC_NextCrcData(*args)

    def PrevCrcData(*args):
        """PrevCrcData(self) -> Point2dC"""
        return _Ravl.DListPoint2dIterC_PrevCrcData(*args)

    def Tail(*args):
        """Tail(self) -> DListPoint2dC"""
        return _Ravl.DListPoint2dIterC_Tail(*args)

    def Head(*args):
        """Head(self) -> DListPoint2dC"""
        return _Ravl.DListPoint2dIterC_Head(*args)

    def InclusiveTail(*args):
        """InclusiveTail(self) -> DListPoint2dC"""
        return _Ravl.DListPoint2dIterC_InclusiveTail(*args)

    def InclusiveHead(*args):
        """InclusiveHead(self) -> DListPoint2dC"""
        return _Ravl.DListPoint2dIterC_InclusiveHead(*args)

    def Data(*args):
        """Data(self) -> Point2dC"""
        return _Ravl.DListPoint2dIterC_Data(*args)

    def __deref__(*args):
        """__deref__(self) -> Point2dC"""
        return _Ravl.DListPoint2dIterC___deref__(*args)

    def Row(*args):
        """Row(self) -> RealT"""
        return _Ravl.DListPoint2dIterC_Row(*args)

    def Col(*args):
        """Col(self) -> RealT"""
        return _Ravl.DListPoint2dIterC_Col(*args)

    def __del__(self, destroy=_Ravl.delete_DListPoint2dIterC):
        """__del__(self)"""
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
    """Proxy of C++ IndexC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, IndexC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, IndexC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::IndexC instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """
        __init__(self) -> IndexC
        __init__(self, ??) -> IndexC
        """
        _swig_setattr(self, IndexC, 'this', _Ravl.new_IndexC(*args))
        _swig_setattr(self, IndexC, 'thisown', 1)
    def V(*args):
        """V(self) -> IntT"""
        return _Ravl.IndexC_V(*args)

    def __del__(self, destroy=_Ravl.delete_IndexC):
        """__del__(self)"""
        try:
            if self.thisown: destroy(self)
        except: pass


class IndexCPtr(IndexC):
    def __init__(self, this):
        _swig_setattr(self, IndexC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, IndexC, 'thisown', 0)
        self.__class__ = IndexC
_Ravl.IndexC_swigregister(IndexCPtr)

def ToList(*args):
    """
    ToList(list) -> PyObject
    ToList(list) -> PyObject
    ToList(list) -> PyObject
    ToList(list) -> PyObject
    ToList(list) -> PyObject
    ToList(list) -> PyObject
    ToList(list) -> PyObject
    """
    return _Ravl.ToList(*args)

class Index2dC(_object):
    """Proxy of C++ Index2dC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Index2dC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Index2dC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::Index2dC instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """
        __init__(self) -> Index2dC
        __init__(self, x, y) -> Index2dC
        __init__(self, x, y) -> Index2dC
        """
        _swig_setattr(self, Index2dC, 'this', _Ravl.new_Index2dC(*args))
        _swig_setattr(self, Index2dC, 'thisown', 1)
    def Row(*args):
        """Row(self) -> IndexC"""
        return _Ravl.Index2dC_Row(*args)

    def Col(*args):
        """Col(self) -> IndexC"""
        return _Ravl.Index2dC_Col(*args)

    def __del__(self, destroy=_Ravl.delete_Index2dC):
        """__del__(self)"""
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
    """Proxy of C++ IndexRange2dC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, IndexRange2dC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, IndexRange2dC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::IndexRange2dC instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """__init__(self) -> IndexRange2dC"""
        _swig_setattr(self, IndexRange2dC, 'this', _Ravl.new_IndexRange2dC(*args))
        _swig_setattr(self, IndexRange2dC, 'thisown', 1)
    def Rows(*args):
        """Rows(self) -> IntT"""
        return _Ravl.IndexRange2dC_Rows(*args)

    def Cols(*args):
        """Cols(self) -> IntT"""
        return _Ravl.IndexRange2dC_Cols(*args)

    def Area(*args):
        """Area(self) -> SizeT"""
        return _Ravl.IndexRange2dC_Area(*args)

    def Contains(*args):
        """Contains(self, index) -> bool"""
        return _Ravl.IndexRange2dC_Contains(*args)

    def Expand(*args):
        """Expand(self, n) -> IndexRange2dC"""
        return _Ravl.IndexRange2dC_Expand(*args)

    def ClipBy(*args):
        """ClipBy(self, range)"""
        return _Ravl.IndexRange2dC_ClipBy(*args)

    def __del__(self, destroy=_Ravl.delete_IndexRange2dC):
        """__del__(self)"""
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
    """Proxy of C++ Array2dByteC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Array2dByteC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Array2dByteC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::Array2dC<RavlN::ByteT > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """
        __init__(self) -> Array2dByteC
        __init__(self, rows, cols) -> Array2dByteC
        __init__(self, range) -> Array2dByteC
        """
        _swig_setattr(self, Array2dByteC, 'this', _Ravl.new_Array2dByteC(*args))
        _swig_setattr(self, Array2dByteC, 'thisown', 1)
    def Frame(*args):
        """Frame(self) -> IndexRange2dC"""
        return _Ravl.Array2dByteC_Frame(*args)

    def Fill(*args):
        """Fill(self, value)"""
        return _Ravl.Array2dByteC_Fill(*args)

    def Stride(*args):
        """Stride(self) -> IntT"""
        return _Ravl.Array2dByteC_Stride(*args)

    def Access(*args):
        """
        Access(self, index) -> ByteT
        Access(self, r, c) -> ByteT
        Access(self, r, c) -> ByteT
        """
        return _Ravl.Array2dByteC_Access(*args)

    def __del__(self, destroy=_Ravl.delete_Array2dByteC):
        """__del__(self)"""
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
    """Proxy of C++ Array2dRealC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Array2dRealC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Array2dRealC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::Array2dC<RavlN::RealT > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """
        __init__(self) -> Array2dRealC
        __init__(self, rows, cols) -> Array2dRealC
        __init__(self, range) -> Array2dRealC
        """
        _swig_setattr(self, Array2dRealC, 'this', _Ravl.new_Array2dRealC(*args))
        _swig_setattr(self, Array2dRealC, 'thisown', 1)
    def Frame(*args):
        """Frame(self) -> IndexRange2dC"""
        return _Ravl.Array2dRealC_Frame(*args)

    def Fill(*args):
        """Fill(self, value)"""
        return _Ravl.Array2dRealC_Fill(*args)

    def Stride(*args):
        """Stride(self) -> IntT"""
        return _Ravl.Array2dRealC_Stride(*args)

    def Access(*args):
        """
        Access(self, index) -> RealT
        Access(self, r, c) -> RealT
        Access(self, r, c) -> RealT
        """
        return _Ravl.Array2dRealC_Access(*args)

    def __del__(self, destroy=_Ravl.delete_Array2dRealC):
        """__del__(self)"""
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
    """Proxy of C++ StringC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, StringC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, StringC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::StringC instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """
        __init__(self) -> StringC
        __init__(self, ??) -> StringC
        """
        _swig_setattr(self, StringC, 'this', _Ravl.new_StringC(*args))
        _swig_setattr(self, StringC, 'thisown', 1)
    def IsEmpty(*args):
        """IsEmpty(self) -> bool"""
        return _Ravl.StringC_IsEmpty(*args)

    def chars(*args):
        """chars(self) -> char"""
        return _Ravl.StringC_chars(*args)

    def Size(*args):
        """Size(self) -> SizeT"""
        return _Ravl.StringC_Size(*args)

    def __str__(*args):
        """__str__(self) -> char"""
        return _Ravl.StringC___str__(*args)

    def __del__(self, destroy=_Ravl.delete_StringC):
        """__del__(self)"""
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
    """Proxy of C++ RealRangeC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, RealRangeC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, RealRangeC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::RealRangeC instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """
        __init__(self, size=0) -> RealRangeC
        __init__(self) -> RealRangeC
        __init__(self, minReal, maxReal) -> RealRangeC
        """
        _swig_setattr(self, RealRangeC, 'this', _Ravl.new_RealRangeC(*args))
        _swig_setattr(self, RealRangeC, 'thisown', 1)
    def Size(*args):
        """Size(self) -> RealT"""
        return _Ravl.RealRangeC_Size(*args)

    def Range(*args):
        """Range(self) -> RealRangeC"""
        return _Ravl.RealRangeC_Range(*args)

    def Min(*args):
        """
        Min(self) -> RealT
        Min(self) -> RealT
        """
        return _Ravl.RealRangeC_Min(*args)

    def Max(*args):
        """
        Max(self) -> RealT
        Max(self) -> RealT
        """
        return _Ravl.RealRangeC_Max(*args)

    def Center(*args):
        """Center(self) -> RealT"""
        return _Ravl.RealRangeC_Center(*args)

    def CenterD(*args):
        """CenterD(self) -> RealT"""
        return _Ravl.RealRangeC_CenterD(*args)

    def Percentage(*args):
        """Percentage(self, p) -> RealT"""
        return _Ravl.RealRangeC_Percentage(*args)

    def IsEmpty(*args):
        """IsEmpty(self) -> bool"""
        return _Ravl.RealRangeC_IsEmpty(*args)

    def IsValid(*args):
        """IsValid(self) -> bool"""
        return _Ravl.RealRangeC_IsValid(*args)

    def Contains(*args):
        """
        Contains(self, i) -> bool
        Contains(self, range) -> bool
        """
        return _Ravl.RealRangeC_Contains(*args)

    def __eq__(*args):
        """__eq__(self, range) -> bool"""
        return _Ravl.RealRangeC___eq__(*args)

    def __ne__(*args):
        """__ne__(self, range) -> bool"""
        return _Ravl.RealRangeC___ne__(*args)

    def In(*args):
        """In(self, range) -> bool"""
        return _Ravl.RealRangeC_In(*args)

    def IsOverlapping(*args):
        """IsOverlapping(self, r) -> bool"""
        return _Ravl.RealRangeC_IsOverlapping(*args)

    def SetOrigin(*args):
        """SetOrigin(self, position) -> RealRangeC"""
        return _Ravl.RealRangeC_SetOrigin(*args)

    def __iadd__(*args):
        """__iadd__(self, i) -> RealRangeC"""
        return _Ravl.RealRangeC___iadd__(*args)

    def __isub__(*args):
        """__isub__(self, i) -> RealRangeC"""
        return _Ravl.RealRangeC___isub__(*args)

    def __add__(*args):
        """__add__(self, i) -> RealRangeC"""
        return _Ravl.RealRangeC___add__(*args)

    def __sub__(*args):
        """__sub__(self, i) -> RealRangeC"""
        return _Ravl.RealRangeC___sub__(*args)

    def ClipBy(*args):
        """ClipBy(self, r) -> RealRangeC"""
        return _Ravl.RealRangeC_ClipBy(*args)

    def Clip(*args):
        """Clip(self, r) -> RealT"""
        return _Ravl.RealRangeC_Clip(*args)

    def FirstHalf(*args):
        """FirstHalf(self) -> RealRangeC"""
        return _Ravl.RealRangeC_FirstHalf(*args)

    def FirstHalfD(*args):
        """FirstHalfD(self) -> RealRangeC"""
        return _Ravl.RealRangeC_FirstHalfD(*args)

    def Enlarge(*args):
        """Enlarge(self, f) -> RealRangeC"""
        return _Ravl.RealRangeC_Enlarge(*args)

    def Expand(*args):
        """Expand(self, n) -> RealRangeC"""
        return _Ravl.RealRangeC_Expand(*args)

    def Shrink(*args):
        """Shrink(self, n) -> RealRangeC"""
        return _Ravl.RealRangeC_Shrink(*args)

    def ShrinkHigh(*args):
        """ShrinkHigh(self, n) -> RealRangeC"""
        return _Ravl.RealRangeC_ShrinkHigh(*args)

    def Swap(*args):
        """Swap(self, r) -> RealRangeC"""
        return _Ravl.RealRangeC_Swap(*args)

    def Involve(*args):
        """
        Involve(self, i) -> RealRangeC
        Involve(self, subRange) -> RealRangeC
        """
        return _Ravl.RealRangeC_Involve(*args)

    def __del__(self, destroy=_Ravl.delete_RealRangeC):
        """__del__(self)"""
        try:
            if self.thisown: destroy(self)
        except: pass


class RealRangeCPtr(RealRangeC):
    def __init__(self, this):
        _swig_setattr(self, RealRangeC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, RealRangeC, 'thisown', 0)
        self.__class__ = RealRangeC
_Ravl.RealRangeC_swigregister(RealRangeCPtr)

def PrintIOFormats(*args):
    """
    PrintIOFormats(os=std::cout)
    PrintIOFormats()
    """
    return _Ravl.PrintIOFormats(*args)

def PrintIOConversions(*args):
    """
    PrintIOConversions(os=std::cout)
    PrintIOConversions()
    """
    return _Ravl.PrintIOConversions(*args)

def PrintIOClassTypes(*args):
    """
    PrintIOClassTypes(os=std::cout)
    PrintIOClassTypes()
    """
    return _Ravl.PrintIOClassTypes(*args)

class RealRange2dC(_object):
    """Proxy of C++ RealRange2dC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, RealRange2dC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, RealRange2dC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::RealRange2dC instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """
        __init__(self) -> RealRange2dC
        __init__(self, rowNumber, colNumber) -> RealRange2dC
        __init__(self, rowRange, colRange) -> RealRange2dC
        __init__(self, range) -> RealRange2dC
        __init__(self, minRow, maxRow, minCol, maxCol) -> RealRange2dC
        """
        _swig_setattr(self, RealRange2dC, 'this', _Ravl.new_RealRange2dC(*args))
        _swig_setattr(self, RealRange2dC, 'thisown', 1)
    def TRow(*args):
        """
        TRow(self) -> RealT
        TRow(self) -> RealT
        """
        return _Ravl.RealRange2dC_TRow(*args)

    def LCol(*args):
        """
        LCol(self) -> RealT
        LCol(self) -> RealT
        """
        return _Ravl.RealRange2dC_LCol(*args)

    def BRow(*args):
        """
        BRow(self) -> RealT
        BRow(self) -> RealT
        """
        return _Ravl.RealRange2dC_BRow(*args)

    def RCol(*args):
        """
        RCol(self) -> RealT
        RCol(self) -> RealT
        """
        return _Ravl.RealRange2dC_RCol(*args)

    def Rows(*args):
        """Rows(self) -> RealT"""
        return _Ravl.RealRange2dC_Rows(*args)

    def Cols(*args):
        """Cols(self) -> RealT"""
        return _Ravl.RealRange2dC_Cols(*args)

    def Area(*args):
        """Area(self) -> RealT"""
        return _Ravl.RealRange2dC_Area(*args)

    def Dilate(*args):
        """Dilate(self) -> RealRange2dC"""
        return _Ravl.RealRange2dC_Dilate(*args)

    def Erode(*args):
        """Erode(self) -> RealRange2dC"""
        return _Ravl.RealRange2dC_Erode(*args)

    def Expand(*args):
        """Expand(self, n) -> RealRange2dC"""
        return _Ravl.RealRange2dC_Expand(*args)

    def Shrink(*args):
        """Shrink(self, n) -> RealRange2dC"""
        return _Ravl.RealRange2dC_Shrink(*args)

    def ClipBy(*args):
        """ClipBy(self, r) -> RealRange2dC"""
        return _Ravl.RealRange2dC_ClipBy(*args)

    def Contains(*args):
        """Contains(self, oth) -> bool"""
        return _Ravl.RealRange2dC_Contains(*args)

    def RowRange(*args):
        """RowRange(self) -> RealRangeC"""
        return _Ravl.RealRange2dC_RowRange(*args)

    def ColRange(*args):
        """ColRange(self) -> RealRangeC"""
        return _Ravl.RealRange2dC_ColRange(*args)

    def Range1(*args):
        """Range1(self) -> RealRangeC"""
        return _Ravl.RealRange2dC_Range1(*args)

    def Range2(*args):
        """Range2(self) -> RealRangeC"""
        return _Ravl.RealRange2dC_Range2(*args)

    def Involve(*args):
        """Involve(self, subrectangle)"""
        return _Ravl.RealRange2dC_Involve(*args)

    def IsValid(*args):
        """IsValid(self) -> bool"""
        return _Ravl.RealRange2dC_IsValid(*args)

    def __eq__(*args):
        """__eq__(self, oth) -> bool"""
        return _Ravl.RealRange2dC___eq__(*args)

    def __ne__(*args):
        """__ne__(self, oth) -> bool"""
        return _Ravl.RealRange2dC___ne__(*args)

    def IsOverlapping(*args):
        """IsOverlapping(self, r) -> bool"""
        return _Ravl.RealRange2dC_IsOverlapping(*args)

    def __del__(self, destroy=_Ravl.delete_RealRange2dC):
        """__del__(self)"""
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
    """Proxy of C++ PointSet2dC class"""
    __swig_setmethods__ = {}
    for _s in [DListPoint2dC]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, PointSet2dC, name, value)
    __swig_getmethods__ = {}
    for _s in [DListPoint2dC]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, PointSet2dC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::PointSet2dC instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """__init__(self) -> PointSet2dC"""
        _swig_setattr(self, PointSet2dC, 'this', _Ravl.new_PointSet2dC(*args))
        _swig_setattr(self, PointSet2dC, 'thisown', 1)
    def Centroid(*args):
        """Centroid(self) -> Point2dC"""
        return _Ravl.PointSet2dC_Centroid(*args)

    def BoundingRectangle(*args):
        """BoundingRectangle(self) -> RealRange2dC"""
        return _Ravl.PointSet2dC_BoundingRectangle(*args)

    def __del__(self, destroy=_Ravl.delete_PointSet2dC):
        """__del__(self)"""
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
    """Proxy of C++ Polygon2dC class"""
    __swig_setmethods__ = {}
    for _s in [PointSet2dC]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, Polygon2dC, name, value)
    __swig_getmethods__ = {}
    for _s in [PointSet2dC]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, Polygon2dC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::Polygon2dC instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """__init__(self) -> Polygon2dC"""
        _swig_setattr(self, Polygon2dC, 'this', _Ravl.new_Polygon2dC(*args))
        _swig_setattr(self, Polygon2dC, 'thisown', 1)
    def InsLast(*args):
        """InsLast(self, point)"""
        return _Ravl.Polygon2dC_InsLast(*args)

    def Size(*args):
        """Size(self) -> SizeT"""
        return _Ravl.Polygon2dC_Size(*args)

    def __del__(self, destroy=_Ravl.delete_Polygon2dC):
        """__del__(self)"""
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
    """Proxy of C++ ByteRGBArray2dC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, ByteRGBArray2dC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, ByteRGBArray2dC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::Array2dC<RavlImageN::ByteRGBValueC > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """
        __init__(self) -> ByteRGBArray2dC
        __init__(self, rows, cols) -> ByteRGBArray2dC
        __init__(self, range) -> ByteRGBArray2dC
        """
        _swig_setattr(self, ByteRGBArray2dC, 'this', _Ravl.new_ByteRGBArray2dC(*args))
        _swig_setattr(self, ByteRGBArray2dC, 'thisown', 1)
    def Frame(*args):
        """Frame(self) -> IndexRange2dC"""
        return _Ravl.ByteRGBArray2dC_Frame(*args)

    def Fill(*args):
        """Fill(self, value)"""
        return _Ravl.ByteRGBArray2dC_Fill(*args)

    def Stride(*args):
        """Stride(self) -> IntT"""
        return _Ravl.ByteRGBArray2dC_Stride(*args)

    def Access(*args):
        """
        Access(self, index) -> ByteRGBValueC
        Access(self, r, c) -> ByteRGBValueC
        Access(self, r, c) -> ByteRGBValueC
        """
        return _Ravl.ByteRGBArray2dC_Access(*args)

    def __del__(self, destroy=_Ravl.delete_ByteRGBArray2dC):
        """__del__(self)"""
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
    """Proxy of C++ RealRGBArray2dC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, RealRGBArray2dC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, RealRGBArray2dC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::Array2dC<RavlImageN::RealRGBValueC > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """
        __init__(self) -> RealRGBArray2dC
        __init__(self, rows, cols) -> RealRGBArray2dC
        __init__(self, range) -> RealRGBArray2dC
        """
        _swig_setattr(self, RealRGBArray2dC, 'this', _Ravl.new_RealRGBArray2dC(*args))
        _swig_setattr(self, RealRGBArray2dC, 'thisown', 1)
    def Frame(*args):
        """Frame(self) -> IndexRange2dC"""
        return _Ravl.RealRGBArray2dC_Frame(*args)

    def Fill(*args):
        """Fill(self, value)"""
        return _Ravl.RealRGBArray2dC_Fill(*args)

    def Stride(*args):
        """Stride(self) -> IntT"""
        return _Ravl.RealRGBArray2dC_Stride(*args)

    def Access(*args):
        """
        Access(self, index) -> RealRGBValueC
        Access(self, r, c) -> RealRGBValueC
        Access(self, r, c) -> RealRGBValueC
        """
        return _Ravl.RealRGBArray2dC_Access(*args)

    def __del__(self, destroy=_Ravl.delete_RealRGBArray2dC):
        """__del__(self)"""
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
    """Proxy of C++ RealRGBValueC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, RealRGBValueC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, RealRGBValueC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlImageN::RealRGBValueC instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """__init__(self, r, g, b) -> RealRGBValueC"""
        _swig_setattr(self, RealRGBValueC, 'this', _Ravl.new_RealRGBValueC(*args))
        _swig_setattr(self, RealRGBValueC, 'thisown', 1)
    def Red(*args):
        """Red(self) -> RealT"""
        return _Ravl.RealRGBValueC_Red(*args)

    def Green(*args):
        """Green(self) -> RealT"""
        return _Ravl.RealRGBValueC_Green(*args)

    def Blue(*args):
        """Blue(self) -> RealT"""
        return _Ravl.RealRGBValueC_Blue(*args)

    def __del__(self, destroy=_Ravl.delete_RealRGBValueC):
        """__del__(self)"""
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
    """Proxy of C++ ByteRGBValueC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, ByteRGBValueC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, ByteRGBValueC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlImageN::ByteRGBValueC instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """__init__(self, r, g, b) -> ByteRGBValueC"""
        _swig_setattr(self, ByteRGBValueC, 'this', _Ravl.new_ByteRGBValueC(*args))
        _swig_setattr(self, ByteRGBValueC, 'thisown', 1)
    def Red(*args):
        """Red(self) -> IntT"""
        return _Ravl.ByteRGBValueC_Red(*args)

    def Green(*args):
        """Green(self) -> IntT"""
        return _Ravl.ByteRGBValueC_Green(*args)

    def Blue(*args):
        """Blue(self) -> IntT"""
        return _Ravl.ByteRGBValueC_Blue(*args)

    def __del__(self, destroy=_Ravl.delete_ByteRGBValueC):
        """__del__(self)"""
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
    """Proxy of C++ ImageByteRGBValueC class"""
    __swig_setmethods__ = {}
    for _s in [ByteRGBArray2dC]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, ImageByteRGBValueC, name, value)
    __swig_getmethods__ = {}
    for _s in [ByteRGBArray2dC]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, ImageByteRGBValueC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlImageN::ImageC<RavlImageN::ByteRGBValueC > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """
        __init__(self) -> ImageByteRGBValueC
        __init__(self, rows, cols) -> ImageByteRGBValueC
        __init__(self, range) -> ImageByteRGBValueC
        __init__(self, img, range) -> ImageByteRGBValueC
        """
        _swig_setattr(self, ImageByteRGBValueC, 'this', _Ravl.new_ImageByteRGBValueC(*args))
        _swig_setattr(self, ImageByteRGBValueC, 'thisown', 1)
    def Rows(*args):
        """Rows(self) -> SizeT"""
        return _Ravl.ImageByteRGBValueC_Rows(*args)

    def Cols(*args):
        """Cols(self) -> SizeT"""
        return _Ravl.ImageByteRGBValueC_Cols(*args)

    def __del__(self, destroy=_Ravl.delete_ImageByteRGBValueC):
        """__del__(self)"""
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
    """Proxy of C++ ByteRGBImageC class"""
    __swig_setmethods__ = {}
    for _s in [ByteRGBArray2dC]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, ByteRGBImageC, name, value)
    __swig_getmethods__ = {}
    for _s in [ByteRGBArray2dC]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, ByteRGBImageC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlImageN::ImageC<RavlImageN::ByteRGBValueC > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """
        __init__(self) -> ByteRGBImageC
        __init__(self, rows, cols) -> ByteRGBImageC
        __init__(self, range) -> ByteRGBImageC
        __init__(self, img, range) -> ByteRGBImageC
        """
        _swig_setattr(self, ByteRGBImageC, 'this', _Ravl.new_ByteRGBImageC(*args))
        _swig_setattr(self, ByteRGBImageC, 'thisown', 1)
    def Rows(*args):
        """Rows(self) -> SizeT"""
        return _Ravl.ByteRGBImageC_Rows(*args)

    def Cols(*args):
        """Cols(self) -> SizeT"""
        return _Ravl.ByteRGBImageC_Cols(*args)

    def __del__(self, destroy=_Ravl.delete_ByteRGBImageC):
        """__del__(self)"""
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
    """Proxy of C++ ImageByteC class"""
    __swig_setmethods__ = {}
    for _s in [Array2dByteC]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, ImageByteC, name, value)
    __swig_getmethods__ = {}
    for _s in [Array2dByteC]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, ImageByteC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlImageN::ImageC<RavlN::ByteT > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """
        __init__(self) -> ImageByteC
        __init__(self, rows, cols) -> ImageByteC
        __init__(self, range) -> ImageByteC
        __init__(self, img, range) -> ImageByteC
        """
        _swig_setattr(self, ImageByteC, 'this', _Ravl.new_ImageByteC(*args))
        _swig_setattr(self, ImageByteC, 'thisown', 1)
    def Rows(*args):
        """Rows(self) -> SizeT"""
        return _Ravl.ImageByteC_Rows(*args)

    def Cols(*args):
        """Cols(self) -> SizeT"""
        return _Ravl.ImageByteC_Cols(*args)

    def __del__(self, destroy=_Ravl.delete_ImageByteC):
        """__del__(self)"""
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
    """Proxy of C++ FontC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, FontC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, FontC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlImageN::FontC instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """__init__(self) -> FontC"""
        _swig_setattr(self, FontC, 'this', _Ravl.new_FontC(*args))
        _swig_setattr(self, FontC, 'thisown', 1)
    def IsValid(*args):
        """IsValid(self) -> bool"""
        return _Ravl.FontC_IsValid(*args)

    def Center(*args):
        """Center(self, text) -> Index2dC"""
        return _Ravl.FontC_Center(*args)

    def Size(*args):
        """Size(self, text) -> Index2dC"""
        return _Ravl.FontC_Size(*args)

    def Count(*args):
        """Count(self) -> UIntT"""
        return _Ravl.FontC_Count(*args)

    def __del__(self, destroy=_Ravl.delete_FontC):
        """__del__(self)"""
        try:
            if self.thisown: destroy(self)
        except: pass


class FontCPtr(FontC):
    def __init__(self, this):
        _swig_setattr(self, FontC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, FontC, 'thisown', 0)
        self.__class__ = FontC
_Ravl.FontC_swigregister(FontCPtr)

def Save(*args):
    """
    Save(??, ??) -> bool
    Save(??, ??) -> bool
    Save(??, ??) -> bool
    Save(??, ??) -> bool
    """
    return _Ravl.Save(*args)

def Load(*args):
    """
    Load(??, ??) -> bool
    Load(??, ??) -> bool
    Load(??, ??) -> bool
    Load(??, ??) -> bool
    """
    return _Ravl.Load(*args)

def DrawPolygon(*args):
    """
    DrawPolygon(??, ??, poly, fill=False)
    DrawPolygon(??, ??, poly)
    DrawPolygon(??, ??, poly, fill=False)
    DrawPolygon(??, ??, poly)
    """
    return _Ravl.DrawPolygon(*args)


def DefaultFont(*args):
    """DefaultFont() -> FontC"""
    return _Ravl.DefaultFont(*args)
class Affine2dC(_object):
    """Proxy of C++ Affine2dC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Affine2dC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Affine2dC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::Affine2dC instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """__init__(self) -> Affine2dC"""
        _swig_setattr(self, Affine2dC, 'this', _Ravl.new_Affine2dC(*args))
        _swig_setattr(self, Affine2dC, 'thisown', 1)
    def __del__(self, destroy=_Ravl.delete_Affine2dC):
        """__del__(self)"""
        try:
            if self.thisown: destroy(self)
        except: pass


class Affine2dCPtr(Affine2dC):
    def __init__(self, this):
        _swig_setattr(self, Affine2dC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, Affine2dC, 'thisown', 0)
        self.__class__ = Affine2dC
_Ravl.Affine2dC_swigregister(Affine2dCPtr)

def DrawText(*args):
    """
    DrawText(font, value, offset, text, image)
    DrawText(font, value, offset, text, image)
    """
    return _Ravl.DrawText(*args)

def DrawTextCenter(*args):
    """
    DrawTextCenter(font, value, offset, text, image)
    DrawTextCenter(font, value, offset, text, image)
    """
    return _Ravl.DrawTextCenter(*args)

class DateC(_object):
    """Proxy of C++ DateC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DateC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DateC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::DateC instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def NowUTC(*args):
        """NowUTC() -> DateC"""
        return _Ravl.DateC_NowUTC(*args)

    if _newclass:NowUTC = staticmethod(NowUTC)
    __swig_getmethods__["NowUTC"] = lambda x: NowUTC
    def NowLocal(*args):
        """NowLocal() -> DateC"""
        return _Ravl.DateC_NowLocal(*args)

    if _newclass:NowLocal = staticmethod(NowLocal)
    __swig_getmethods__["NowLocal"] = lambda x: NowLocal
    def NowVirtual(*args):
        """NowVirtual() -> DateC"""
        return _Ravl.DateC_NowVirtual(*args)

    if _newclass:NowVirtual = staticmethod(NowVirtual)
    __swig_getmethods__["NowVirtual"] = lambda x: NowVirtual
    def TimeZoneOffset(*args):
        """TimeZoneOffset() -> DateC"""
        return _Ravl.DateC_TimeZoneOffset(*args)

    if _newclass:TimeZoneOffset = staticmethod(TimeZoneOffset)
    __swig_getmethods__["TimeZoneOffset"] = lambda x: TimeZoneOffset
    def __init__(self, *args):
        """
        __init__(self) -> DateC
        __init__(self, setval, useVirt=False) -> DateC
        __init__(self, setval) -> DateC
        __init__(self, val) -> DateC
        __init__(self, year, month, day, hour=0, min=0, sec=0, usec=0, useLocalTimeZone=False) -> DateC
        __init__(self, year, month, day, hour=0, min=0, sec=0, usec=0) -> DateC
        __init__(self, year, month, day, hour=0, min=0, sec=0) -> DateC
        __init__(self, year, month, day, hour=0, min=0) -> DateC
        __init__(self, year, month, day, hour=0) -> DateC
        __init__(self, year, month, day) -> DateC
        __init__(self, xsec, xusec) -> DateC
        __init__(self, val) -> DateC
        __init__(self, str) -> DateC
        """
        _swig_setattr(self, DateC, 'this', _Ravl.new_DateC(*args))
        _swig_setattr(self, DateC, 'thisown', 1)
    def IsLeapYear(*args):
        """IsLeapYear(year) -> bool"""
        return _Ravl.DateC_IsLeapYear(*args)

    if _newclass:IsLeapYear = staticmethod(IsLeapYear)
    __swig_getmethods__["IsLeapYear"] = lambda x: IsLeapYear
    def YearToDaysSince1970(*args):
        """YearToDaysSince1970(year) -> int"""
        return _Ravl.DateC_YearToDaysSince1970(*args)

    if _newclass:YearToDaysSince1970 = staticmethod(YearToDaysSince1970)
    __swig_getmethods__["YearToDaysSince1970"] = lambda x: YearToDaysSince1970
    def IsValid(*args):
        """IsValid(self) -> bool"""
        return _Ravl.DateC_IsValid(*args)

    def IsZero(*args):
        """IsZero(self) -> bool"""
        return _Ravl.DateC_IsZero(*args)

    def SetInvalid(*args):
        """SetInvalid(self)"""
        return _Ravl.DateC_SetInvalid(*args)

    def SetToNow(*args):
        """
        SetToNow(self, useVirt=False)
        SetToNow(self)
        """
        return _Ravl.DateC_SetToNow(*args)

    def MaxUSeconds(*args):
        """MaxUSeconds(self) -> long"""
        return _Ravl.DateC_MaxUSeconds(*args)

    def Resolution(*args):
        """Resolution(self) -> long"""
        return _Ravl.DateC_Resolution(*args)

    def NormalisePos(*args):
        """NormalisePos(self)"""
        return _Ravl.DateC_NormalisePos(*args)

    def NormaliseNeg(*args):
        """NormaliseNeg(self)"""
        return _Ravl.DateC_NormaliseNeg(*args)

    def __eq__(*args):
        """__eq__(self, oth) -> bool"""
        return _Ravl.DateC___eq__(*args)

    def __ne__(*args):
        """__ne__(self, oth) -> bool"""
        return _Ravl.DateC___ne__(*args)

    def __gt__(*args):
        """__gt__(self, oth) -> bool"""
        return _Ravl.DateC___gt__(*args)

    def __lt__(*args):
        """__lt__(self, oth) -> bool"""
        return _Ravl.DateC___lt__(*args)

    def __ge__(*args):
        """__ge__(self, oth) -> bool"""
        return _Ravl.DateC___ge__(*args)

    def __le__(*args):
        """__le__(self, oth) -> bool"""
        return _Ravl.DateC___le__(*args)

    def __add__(*args):
        """__add__(self, oth) -> DateC"""
        return _Ravl.DateC___add__(*args)

    def __sub__(*args):
        """__sub__(self, oth) -> DateC"""
        return _Ravl.DateC___sub__(*args)

    def __isub__(*args):
        """
        __isub__(self, val) -> DateC
        __isub__(self, val) -> DateC
        """
        return _Ravl.DateC___isub__(*args)

    def __iadd__(*args):
        """
        __iadd__(self, val) -> DateC
        __iadd__(self, val) -> DateC
        """
        return _Ravl.DateC___iadd__(*args)

    def Text(*args):
        """Text(self) -> StringC"""
        return _Ravl.DateC_Text(*args)

    def ODBC(*args):
        """
        ODBC(self, convertUTCToLocal=False) -> StringC
        ODBC(self) -> StringC
        """
        return _Ravl.DateC_ODBC(*args)

    def SetODBC(*args):
        """SetODBC(self, odbcStr) -> bool"""
        return _Ravl.DateC_SetODBC(*args)

    def CTime(*args):
        """
        CTime(self, convertUTCToLocal=False) -> StringC
        CTime(self) -> StringC
        """
        return _Ravl.DateC_CTime(*args)

    def CTimeShort(*args):
        """
        CTimeShort(self, convertUTCToLocal=False) -> StringC
        CTimeShort(self) -> StringC
        """
        return _Ravl.DateC_CTimeShort(*args)

    def USeconds(*args):
        """USeconds(self) -> long"""
        return _Ravl.DateC_USeconds(*args)

    def TotalSeconds(*args):
        """TotalSeconds(self) -> long"""
        return _Ravl.DateC_TotalSeconds(*args)

    def Double(*args):
        """Double(self) -> double"""
        return _Ravl.DateC_Double(*args)

    def Seconds(*args):
        """
        Seconds(self, convertUTCToLocal=False) -> IntT
        Seconds(self) -> IntT
        """
        return _Ravl.DateC_Seconds(*args)

    def Minute(*args):
        """
        Minute(self, convertUTCToLocal=False) -> IntT
        Minute(self) -> IntT
        """
        return _Ravl.DateC_Minute(*args)

    def Hour(*args):
        """
        Hour(self, convertUTCToLocal=False) -> IntT
        Hour(self) -> IntT
        """
        return _Ravl.DateC_Hour(*args)

    def Month(*args):
        """
        Month(self, convertUTCToLocal=False) -> IntT
        Month(self) -> IntT
        """
        return _Ravl.DateC_Month(*args)

    def Year(*args):
        """
        Year(self, convertUTCToLocal=False) -> IntT
        Year(self) -> IntT
        """
        return _Ravl.DateC_Year(*args)

    def DayInMonth(*args):
        """
        DayInMonth(self, convertUTCToLocal=False) -> IntT
        DayInMonth(self) -> IntT
        """
        return _Ravl.DateC_DayInMonth(*args)

    def DayInYear(*args):
        """
        DayInYear(self, convertUTCToLocal=False) -> IntT
        DayInYear(self) -> IntT
        """
        return _Ravl.DateC_DayInYear(*args)

    def DayInWeek(*args):
        """
        DayInWeek(self, convertUTCToLocal=False) -> IntT
        DayInWeek(self) -> IntT
        """
        return _Ravl.DateC_DayInWeek(*args)

    def TextDayInWeek(*args):
        """
        TextDayInWeek(self, convertUTCToLocal=False) -> StringC
        TextDayInWeek(self) -> StringC
        """
        return _Ravl.DateC_TextDayInWeek(*args)

    def DaylightSaving(*args):
        """DaylightSaving(self) -> bool"""
        return _Ravl.DateC_DaylightSaving(*args)

    def Wait(*args):
        """Wait(self) -> bool"""
        return _Ravl.DateC_Wait(*args)

    def __del__(self, destroy=_Ravl.delete_DateC):
        """__del__(self)"""
        try:
            if self.thisown: destroy(self)
        except: pass


class DateCPtr(DateC):
    def __init__(self, this):
        _swig_setattr(self, DateC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, DateC, 'thisown', 0)
        self.__class__ = DateC
_Ravl.DateC_swigregister(DateCPtr)

def DateC_NowUTC(*args):
    """DateC_NowUTC() -> DateC"""
    return _Ravl.DateC_NowUTC(*args)

def DateC_NowLocal(*args):
    """DateC_NowLocal() -> DateC"""
    return _Ravl.DateC_NowLocal(*args)

def DateC_NowVirtual(*args):
    """DateC_NowVirtual() -> DateC"""
    return _Ravl.DateC_NowVirtual(*args)

def DateC_TimeZoneOffset(*args):
    """DateC_TimeZoneOffset() -> DateC"""
    return _Ravl.DateC_TimeZoneOffset(*args)

def DateC_IsLeapYear(*args):
    """DateC_IsLeapYear(year) -> bool"""
    return _Ravl.DateC_IsLeapYear(*args)

def DateC_YearToDaysSince1970(*args):
    """DateC_YearToDaysSince1970(year) -> int"""
    return _Ravl.DateC_YearToDaysSince1970(*args)

class HashInt64Int64C(_object):
    """Proxy of C++ HashInt64Int64C class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, HashInt64Int64C, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, HashInt64Int64C, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::HashC<RavlN::Int64T,RavlN::Int64T > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """
        __init__(self, nBins=23) -> HashInt64Int64C
        __init__(self) -> HashInt64Int64C
        """
        _swig_setattr(self, HashInt64Int64C, 'this', _Ravl.new_HashInt64Int64C(*args))
        _swig_setattr(self, HashInt64Int64C, 'thisown', 1)
    def Lookup(*args):
        """Lookup(self, key, OUTPUT) -> bool"""
        return _Ravl.HashInt64Int64C_Lookup(*args)

    def Update(*args):
        """
        Update(self, key, data) -> bool
        Update(self, key) -> Int64T
        """
        return _Ravl.HashInt64Int64C_Update(*args)

    def Insert(*args):
        """Insert(self, key, data) -> bool"""
        return _Ravl.HashInt64Int64C_Insert(*args)

    def Access(*args):
        """
        Access(self, key, def=RavlN::Int64T()) -> Int64T
        Access(self, key) -> Int64T
        """
        return _Ravl.HashInt64Int64C_Access(*args)

    def AccessCopy(*args):
        """
        AccessCopy(self, key, def=RavlN::Int64T()) -> Int64T
        AccessCopy(self, key) -> Int64T
        """
        return _Ravl.HashInt64Int64C_AccessCopy(*args)

    def Del(*args):
        """
        Del(self, key, allowResize=True) -> bool
        Del(self, key) -> bool
        """
        return _Ravl.HashInt64Int64C_Del(*args)

    def Get(*args):
        """
        Get(self, key, allowResize=True) -> Int64T
        Get(self, key) -> Int64T
        """
        return _Ravl.HashInt64Int64C_Get(*args)

    def IsElm(*args):
        """IsElm(self, key) -> bool"""
        return _Ravl.HashInt64Int64C_IsElm(*args)

    def Empty(*args):
        """Empty(self)"""
        return _Ravl.HashInt64Int64C_Empty(*args)

    def Bins(*args):
        """Bins(self) -> UIntT"""
        return _Ravl.HashInt64Int64C_Bins(*args)

    def Resize(*args):
        """Resize(self, newSize)"""
        return _Ravl.HashInt64Int64C_Resize(*args)

    def __del__(self, destroy=_Ravl.delete_HashInt64Int64C):
        """__del__(self)"""
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
    """Proxy of C++ HashInt64Int64IterC class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, HashInt64Int64IterC, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, HashInt64Int64IterC, name)
    def __repr__(self):
        return "<%s.%s; proxy of C++ RavlN::HashIterC<RavlN::Int64T,RavlN::Int64T > instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args):
        """
        __init__(self) -> HashInt64Int64IterC
        __init__(self, nTab) -> HashInt64Int64IterC
        __init__(self, oth) -> HashInt64Int64IterC
        """
        _swig_setattr(self, HashInt64Int64IterC, 'this', _Ravl.new_HashInt64Int64IterC(*args))
        _swig_setattr(self, HashInt64Int64IterC, 'thisown', 1)
    def First(*args):
        """First(self) -> bool"""
        return _Ravl.HashInt64Int64IterC_First(*args)

    def Next(*args):
        """Next(self) -> bool"""
        return _Ravl.HashInt64Int64IterC_Next(*args)

    def IsElm(*args):
        """IsElm(self) -> bool"""
        return _Ravl.HashInt64Int64IterC_IsElm(*args)

    def Key(*args):
        """Key(self) -> Int64T"""
        return _Ravl.HashInt64Int64IterC_Key(*args)

    def Data(*args):
        """
        Data(self) -> Int64T
        Data(self) -> Int64T
        """
        return _Ravl.HashInt64Int64IterC_Data(*args)

    def Del(*args):
        """Del(self) -> bool"""
        return _Ravl.HashInt64Int64IterC_Del(*args)

    def __del__(self, destroy=_Ravl.delete_HashInt64Int64IterC):
        """__del__(self)"""
        try:
            if self.thisown: destroy(self)
        except: pass


class HashInt64Int64IterCPtr(HashInt64Int64IterC):
    def __init__(self, this):
        _swig_setattr(self, HashInt64Int64IterC, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, HashInt64Int64IterC, 'thisown', 0)
        self.__class__ = HashInt64Int64IterC
_Ravl.HashInt64Int64IterC_swigregister(HashInt64Int64IterCPtr)



