
%define version 0.6

Summary: RAVL, Recognition And Vision Library
Name: RAVL
Version: %{version}
Release: 12
Source0: %{name}-SRC-%{version}.tar.bz2
License: LGPL
Group: Applications/Engineering
BuildRoot: %{_builddir}/%{name}-root
Requires: gtk+ >= 1.2.5
%description
General C++ Library, with modules for Computer Vision, Pattern Recognition and much more. 
%prep
%setup -q
%build
%clean
rm -rf $RPM_BUILD_ROOT
%install
rm -rf $RPM_BUILD_ROOT
DEFAULTTMP=$RPM_BUILD_ROOT
ARC=`QMake/config.arc`
LD_LIBRARY_PATH=$RPM_BUILD_ROOT/usr/lib/RAVL/$ARC/shared\:$LD_LIBRARY_PATH
./install /usr rpm $RPM_BUILD_ROOT/usr
if test -f  $RPM_BUILD_ROOT/usr/.dir ; then
  rm $RPM_BUILD_ROOT/usr/.dir ;
fi
if test -f $RPM_BUILD_ROOT/usr/lib/.dir ; then
  rm $RPM_BUILD_ROOT/usr/lib/.dir 
fi
if test -f $RPM_BUILD_ROOT/usr/bin/.dir ; then
  rm $RPM_BUILD_ROOT/usr/bin/.dir 
fi
if test -f $RPM_BUILD_ROOT/usr/include/.dir ; then
  rm $RPM_BUILD_ROOT/usr/include/.dir
fi
ln -s -f $RPM_BUILD_ROOT/usr/lib/RAVL/$ARC/shared/* $RPM_BUILD_ROOT/usr/lib
%files
%defattr(-,root,root)

/usr/bin
/usr/lib/RAVL/*/bin
/usr/lib/RAVL/*/shared
/usr/share/RAVL/Fonts
/usr/share/RAVL/AutoPort
/usr/share/RAVL/CodeManager
/usr/share/RAVL/CxxDoc
/usr/share/RAVL/config.arc

################### Documentation package #########################

%package -n RAVL-doc
Summary:    HTML documentation for the RAVL libraries.
Group:      Development/Libraries
%description -n RAVL-doc
Documentation for the RAVL libraries.

%files -n RAVL-doc
%doc /usr/share/doc/RAVL

################### Development package #########################

%package -n RAVL-devel
Summary:    Development package for creating RAVL applications.
Group:      Development/Libraries
Requires:  RAVL = %{version}
%description -n RAVL-devel

Development libraries and tools for RAVL.

%files -n RAVL-devel

/usr/lib/RAVL/libdep
/usr/lib/RAVL/*/check
/usr/include
/usr/share/RAVL/QMake

################### Debug package #########################

%package -n RAVL-debug

Summary:    Static debug libraries for RAVL.
Group:      Development/Libraries
Requires:  RAVL-devel = %{version}

%description -n RAVL-debug

Debugging libraries and tools for RAVL.

%files -n RAVL-debug

/usr/lib/RAVL/*/debug

################### Opt package #########################

%package -n RAVL-opt

Summary:    Static optimised libraries for RAVL.
Group:      Development/Libraries
Requires:  RAVL-devel = %{version}

%description -n RAVL-opt

Static optimised libraries for RAVL.

%files -n RAVL-opt

/usr/lib/RAVL/*/opt
