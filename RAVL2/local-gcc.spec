Summary: gcc-2.95.3 built to /usr/local
Name: local-gcc
Version: 2.95.3
Release: 1
Source0: %{name}-%{version}.tar.bz2
License: LGPL
Group: Development/Libraries
#BuildRoot: %{_builddir}/%{name}-root
%description
A version of gcc built to /usr/local to avoid conflicting with
the system compiler.

%prep
%setup -q
%build
./configure --prefix=/usr/local/gcc-2.95.3 
make LANGUAGES="c c++"
%clean
#rm -rf $RPM_BUILD_ROOT
%install
# DESTDIR=$RPM_BUILD_ROOT
make LANGUAGES="c c++" install
%files
%defattr(-,root,root)
/usr/local/gcc-2.95.3/bin
/usr/local/gcc-2.95.3/lib
/usr/local/gcc-2.95.3/include
/usr/local/gcc-2.95.3/i686-pc-linux-gnu
