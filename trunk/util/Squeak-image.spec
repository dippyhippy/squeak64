Name:			Squeak-image
Summary:		The .image and .changes files needed to run Squeak.
Version:		[sqmajor].[sqminor]
Release:		[squpdate]
Requires:		Squeak-sources = [sqmajor]
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
language and environment based on (and largely compatible with) the original
Smalltalk-80 system.  The persistent state of the Squeak environment is saved
in a pair of ".image" and ".changes" files.  This package contains version
[sqversion] of these files for use with version [vmversion] of Squeak.

You must install this package before installing Squeak-vm-[vmversion].  You will
need to install the package Squeak-sources-[vmmajor] before installing this one.

%prep
%build
%install
cd [pwd]
make install-image ROOT=[pwd] bindir=[bindir] plgdir=[plgdir] imgdir=[imgdir] docdir=[docdir] mandir=[mandir] INSTALL_ARGS="-o root -g bin"
%clean
%files
/usr
