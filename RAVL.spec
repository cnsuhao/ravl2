Summary: RAVL, Recognition And Vision Library
Name: RAVL
Version: 0.6
Release: 9
Source0: %{name}-%{version}.tar.bz2
License: LGPL
Group: Development/Libraries
BuildRoot: %{_builddir}/%{name}-root
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
./install /usr rpm $RPM_BUILD_ROOT/usr
%files
%defattr(-,root,root)
/usr/bin
/usr/lib
/usr/include
%doc /usr/share/doc/RAVL
#%doc /usr/share/man
#%doc /usr/README
