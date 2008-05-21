// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html



%include "Ravl/Swig/Types.i"

%{
#ifdef SWIGPERL
#undef Copy
#endif

#include "Ravl/String.hh"

#ifdef SWIGPERL
#define Copy(s,d,n,t)   (MEM_WRAP_CHECK_(n,t) (void)memcpy((char*)(d),(const char*)(s), (n) * sizeof(t)))
#endif
%}

namespace RavlN
{

  class StringC
  {
  public:
    StringC();
    StringC(const char *);

    bool IsEmpty() const;

    const char *chars() const;

    SizeT Size() const;

#ifdef SWIGPYTHON

    %extend
    {
      const char *__str__()
      {
        return self->chars();
      }
    }

    %typemap(out) StringC
    {
      $result = PyString_FromStringAndSize($1.chars(), $1.Size());
    }
    
#endif




#ifdef SWIGPERL

    //%typemap(out) StringC
    //{
    //  $result = newSVpv($1.chars(), $1.Size());
    //}

    %typemap(in) StringC
    {
      $1 = RavlN::StringC(SvPV($input, SvLEN($input)));
    }
    
#endif

  };



#ifdef SWIGJAVA

////////////////////////////////////////////////////////////////////////////////////////////////
// These are some conversions that should work between RavlN::StringC and the Java String class.
// I have pretty much copied and modified whats in std_string.i
////////////////////////////////////////////////////////////////////////////////////////////////

/////////////
// StringC
/////////////
%typemap(jni) StringC "jstring"
%typemap(jtype) StringC "String"
%typemap(jstype) StringC "String"
%typemap(javadirectorin) StringC "$jniinput"
%typemap(javadirectorout) StringC "$javacall"

%typemap(in) StringC 
%{ if(!$input) {
     SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null StringC");
     return $null;
    } 
    const char *$1_pstr = (const char *)jenv->GetStringUTFChars($input, 0); 
    if (!$1_pstr) return $null;
    $1 =  RavlN::StringC($1_pstr);
    jenv->ReleaseStringUTFChars($input, $1_pstr); %}

%typemap(directorout) StringC 
%{ if(!$input) {
     SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null StringC");
     return $null;
   } 
   const char *$1_pstr = (const char *)jenv->GetStringUTFChars($input, 0); 
   if (!$1_pstr) return $null;
   $result =  RavlN::StringC($1_pstr);
   jenv->ReleaseStringUTFChars($input, $1_pstr); %}

%typemap(directorin,descriptor="Ljava/lang/String;") StringC 
%{ $input = jenv->NewStringUTF($1.chars()); %}

%typemap(out) StringC 
%{ $result = jenv->NewStringUTF($1.chars()); %}

%typemap(javain) StringC "$javainput"

%typemap(javaout) StringC {
    return $jnicall;
  }

%typemap(typecheck) StringC = char *;

%typemap(throws) StringC
%{ SWIG_JavaThrowException(jenv, SWIG_JavaRuntimeException, $1.chars());
   return $null; %}


/////////////
// StringC &
/////////////

%typemap(jni) StringC & "jstring"
%typemap(jtype) StringC & "String"
%typemap(jstype) StringC & "String"
%typemap(javadirectorin) StringC & "$jniinput"
%typemap(javadirectorout) StringC & "$javacall"

%typemap(in) StringC &
%{ if(!$input) {
     SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null StringC");
     return $null;
   }
   const char *$1_pstr = (const char *)jenv->GetStringUTFChars($input, 0); 
   if (!$1_pstr) return $null;
   RavlN::StringC $1_str($1_pstr);
   $1 = &$1_str;
   jenv->ReleaseStringUTFChars($input, $1_pstr); %}

%typemap(directorout,warning=SWIGWARN_TYPEMAP_THREAD_UNSAFE_MSG) StringC &
%{ if(!$input) {
     SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null StringC");
     return $null;
   }
   const char *$1_pstr = (const char *)jenv->GetStringUTFChars($input, 0); 
   if (!$1_pstr) return $null;
   /* possible thread/reentrant code problem */
   static RavlN::StringC $1_str;
   $1_str = $1_pstr;
   $result = &$1_str;
   jenv->ReleaseStringUTFChars($input, $1_pstr); %}

%typemap(directorin,descriptor="Ljava/lang/String;") StringC &
%{ $input = jenv->NewStringUTF($1.chars()); %}

%typemap(out) const StringC & 
%{ $result = jenv->NewStringUTF($1->chars()); %}

%typemap(javain) StringC & "$javainput"

%typemap(javaout) StringC & {
    return $jnicall;
  }

%typemap(typecheck) StringC & = char *;

%typemap(throws) StringC &
%{ SWIG_JavaThrowException(jenv, SWIG_JavaRuntimeException, $1.chars());
   return $null; %}


//////////////////
// const StringC &
//////////////////

%typemap(jni) const StringC & "jstring"
%typemap(jtype) const StringC & "String"
%typemap(jstype) const StringC & "String"
%typemap(javadirectorin) const StringC & "$jniinput"
%typemap(javadirectorout) const StringC & "$javacall"

%typemap(in) const StringC &
%{ if(!$input) {
     SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null StringC");
     return $null;
   }
   const char *$1_pstr = (const char *)jenv->GetStringUTFChars($input, 0); 
   if (!$1_pstr) return $null;
   RavlN::StringC $1_str($1_pstr);
   $1 = &$1_str;
   jenv->ReleaseStringUTFChars($input, $1_pstr); %}

%typemap(directorout,warning=SWIGWARN_TYPEMAP_THREAD_UNSAFE_MSG) const StringC &
%{ if(!$input) {
     SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null StringC");
     return $null;
   }
   const char *$1_pstr = (const char *)jenv->GetStringUTFChars($input, 0); 
   if (!$1_pstr) return $null;
   /* possible thread/reentrant code problem */
   static RavlN::StringC $1_str;
   $1_str = $1_pstr;
   $result = &$1_str;
   jenv->ReleaseStringUTFChars($input, $1_pstr); %}

%typemap(directorin,descriptor="Ljava/lang/String;") const StringC &
%{ $input = jenv->NewStringUTF($1.chars()); %}

%typemap(out) const StringC & 
%{ $result = jenv->NewStringUTF($1->chars()); %}

%typemap(javain) const StringC & "$javainput"

%typemap(javaout) const StringC & {
    return $jnicall;
  }

%typemap(typecheck) const StringC & = char *;

%typemap(throws) const StringC &
%{ SWIG_JavaThrowException(jenv, SWIG_JavaRuntimeException, $1.chars());
   return $null; %}

#endif

}


