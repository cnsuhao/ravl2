
%define version 0.7

Summary: RAVL, Recognition And Vision Library
Name: RAVL
Version: %{version}
Release: 1
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
#rm -rf $RPM_BUILD_ROOT
%install
#rm -rf $RPM_BUILD_ROOT
DEFAULTTMP=$RPM_BUILD_ROOT
ARC=`QMake/config.arc`
LD_LIBRARY_PATH=$RPM_BUILD_ROOT/usr/local/lib/RAVL/$ARC/shared\:$LD_LIBRARY_PATH
./install /usr/local rpm $RPM_BUILD_ROOT/usr/local
if test -f  $RPM_BUILD_ROOT/usr/local/.dir ; then
  rm $RPM_BUILD_ROOT/usr/local/.dir ;
fi
if test -f $RPM_BUILD_ROOT/usr/local/lib/.dir ; then
  rm $RPM_BUILD_ROOT/usr/local/lib/local/.dir 
fi
if test -f $RPM_BUILD_ROOT/usr/local/bin/.dir ; then
  rm $RPM_BUILD_ROOT/usr/local/bin/.dir 
fi
if test -f $RPM_BUILD_ROOT/usr/local/include/.dir ; then
  rm $RPM_BUILD_ROOT/usr/local/include/.dir
fi
ln -s -f $RPM_BUILD_ROOT/usr/local/lib/RAVL/$ARC/shared/* $RPM_BUILD_ROOT/usr/local/lib
%files
%defattr(-,root,root)

/usr/local/bin
/usr/local/lib/RAVL/*/bin
/usr/local/lib/RAVL/*/shared
/usr/local/share/RAVL/Fonts
/usr/local/share/RAVL/AutoPort
/usr/local/share/RAVL/CodeManager
/usr/local/share/RAVL/CxxDoc
/usr/local/share/RAVL/config.arc

%doc README lgpl.license gpl.license
################### Documentation package #########################

%package -n RAVL-doc
Summary:    HTML documentation for the RAVL libraries.
Group:      Development/Libraries
%description -n RAVL-doc
Documentation for the RAVL libraries.

%files -n RAVL-doc
%defattr(-,root,root)
%doc /usr/local/share/doc/RAVL

################### Development package #########################

%package -n RAVL-devel
Summary:    Development package for creating RAVL applications.
Group:      Development/Libraries
Requires:  RAVL = %{version}
Requires: local-gcc = 2.95.3
%description -n RAVL-devel

Development libraries and tools for RAVL.

%files -n RAVL-devel
%defattr(-,root,root)

/usr/local/lib/RAVL/libdep
/usr/local/lib/RAVL/*/check
/usr/local/lib/RAVL/*/obj
/usr/local/include
/usr/local/share/RAVL/QMake

################### Debug package #########################

%package -n RAVL-debug

Summary:    Static debug libraries for RAVL.
Group:      Development/Libraries
Requires:  RAVL-devel = %{version}

%description -n RAVL-debug

Debugging libraries and tools for RAVL.

%files -n RAVL-debug
%defattr(-,root,root)

/usr/local/lib/RAVL/*/debug

################### Opt package #########################

%package -n RAVL-opt

Summary:    Static optimised libraries for RAVL.
Group:      Development/Libraries
Requires:  RAVL-devel = %{version}

%description -n RAVL-opt

Static optimised libraries for RAVL.

%files -n RAVL-opt
%defattr(-,root,root)

/usr/local/lib/RAVL/*/opt
