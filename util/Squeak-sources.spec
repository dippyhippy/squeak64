Name:			Squeak-sources
Summary:		Sources for the system methods in Squeak
Version:		[sqmajor]
Release:		1
Vendor:			Squeak.org
Packager:		Ian Piumarta <ian.piumarta@inria.fr>
URL:			[squrl]
Copyright:		Squeak License
Group:			Development/Languages
Prefix:			/usr
BuildArchitectures:	noarch
BuildRoot:		[pwd]
Provides:		%{name}-%{version}

%description
Squeak is a full-featured implementation of the Smalltalk programming
language and environment based on (and largely compatible with) the
original Smalltalk-80 system.  The sources for the "system" methods in
Squeak are frozen in a ".sources" file.  This package contains that
file, which can be used with any Squeak image that has major version
number [sqmajor].

You must install this package before installing Squeak-image.

%prep
%build
%install
cd [pwd]
make install-sources ROOT=[pwd] bindir=[bindir] plgdir=[plgdir] imgdir=[imgdir] docdir=[docdir] mandir=[mandir] INSTALL_ARGS="-o root -g bin"
%clean
%files
/usr
