Name:		Squeak-vm
Summary:	The Squeak virual machine
Version:	[vmmajor].[vmminor]
Release:	[vmrelease]
Vendor:		Squeak.org
URL:		[vmurl]
Packager:	Ian Piumarta <ian.piumarta@inria.fr>
Source:		[vmurl]/unix/release/Squeak-[vmmajor].[vmminor]-[vmrelease].src.tar.gz
Copyright:	Squeak License
Group:		Development/Languages
Prefix:		/usr
BuildRoot:	[pwd]
AutoReqProv:	no
Requires:	libc.so.6
Requires:	libm.so.6
Requires:	libdl.so.2
Requires:	libutil.so.1
Requires:	libnsl.so.1
Requires:	/lib/ld-linux.so.2
Provides:	%{name}-%{version}

%description
Squeak is a full-featured implementation of the Smalltalk programming
language and environment based on (and largely compatible with) the original
Smalltalk-80 system.

This package contains just the Squeak virtual machine.  You will have
to install it before you install the package Squeak.

%prep
%build
%install
cd [pwd]
make install ROOT=[pwd] bindir=[bindir] plgdir=[plgdir] imgdir=[imgdir] docdir=[docdir] mandir=[mandir] INSTALL_ARGS="-o root -g bin"
%clean
%files
/usr
