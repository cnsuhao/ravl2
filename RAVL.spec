Summary: RAVL, Recognition And Vision Library
Name: RAVL
Version: 0.6
Release: 11
Source0: %{name}-%{version}.tar.bz2
License: LGPL
Group: Development/Libraries
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
LD_LIBRARY_PATH=$RPM_BUILD_ROOT/usr/lib/RAVL/$ARC/shared\:$LD_LIBRARY_PATH
echo "Root $LD_LIBRARY_PATH $ARC"
./install /usr rpm $RPM_BUILD_ROOT/usr
%files
%defattr(-,root,root)

/usr/bin
/usr/lib/RAVL/*/bin
/usr/lib/RAVL/*/shared
/usr/share/RAVL/Fonts
/usr/share/RAVL/AutoPort
/usr/share/RAVL/CodeManager
/usr/share/RAVL/CxxDoc

################### Documentation package #########################

%package -n RAVL-doc
Summary:    HTML documentation for the RAVL libraries.
Group:      Development/Libraries
#Requires:   %{nam} = %{PACKAGE_VERSION}
%description -n RAVL-doc
Documentation for the RAVL libraries.

%files -n RAVL-doc
%doc /usr/share/doc/RAVL

################### Development package #########################

%package -n RAVL-devel
Summary:    Development package for creating RAVL applications.
Group:      Development/Libraries
%description -n RAVL-devel

Development libraries and tools for RAVL.

%files -n RAVL-devel

/usr/lib/RAVL/libdep
/usr/lib/RAVL/*/check
/usr/include
/usr/share/RAVL/QMake

################### Debug package #########################

%package -n RAVL-debug

Summary:    Debug libraries for RAVL.
Group:      Development/Libraries

%description -n RAVL-debug

Debugging libraries and tools for RAVL.

%files -n RAVL-debug

/usr/lib/RAVL/*/debug
