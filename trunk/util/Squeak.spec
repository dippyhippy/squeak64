Name:			Squeak
Summary:		The Squeak System
Version:		[vmmajor].[vmminor]
Release:		[vmrelease]
Vendor:			Squeak.org
URL:			[vmurl]
Packager:		Ian Piumarta <ian.piumarta@inria.fr>
Source:			[vmurl]
Copyright:		Squeak License
Group:			Development/Languages
Prefix:			/usr
BuildArchitectures:	noarch
BuildRoot:		[pwd]
AutoReqProv:		no
Requires:		Squeak-vm-%{version}
Requires:		Squeak-image-[sqmajor].[sqminor]
Requires:		Squeak-sources-[sqmajor]
Provides:		%{name}-%{version}

%description
Squeak is a full-featured implementation of the Smalltalk programming
language and environment based on (and largely compatible with) the original
Smalltalk-80 system.

%prep
%build
%install
%clean
%files
