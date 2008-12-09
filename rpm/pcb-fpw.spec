Summary: 	Yet another footprint generator for pcb.
Name: 		pcb-fpw
Version: 	0.0.9
Release: 	1%{?dist}
License:	GPLv2
Group: 		Applications/Engineering
Url:		http://www.xs4all.nl/~ljh4timm/downloads
Packager:	Bert Timmerman <bert.timmerman@xs4all.nl>
Source:		%{name}-%{version}.tar.gz 	
Buildroot: 	/var/tmp/%{name}-%{version}

%description
The pcb-fpw FootPrintWizard is what the name says it will be:
a footprint wizard (a.k.a. footprint generator).
pcb-fpw is not a footprint editor, therefor one can NOT load an existing 
footprint file into pcb-fpw, make some changes and save it back to file, and 
subsequent load the edited footprint file into pcb.
The main, interactive, modus of operating the software is probably with the 
GUI application "pcb-gfpw".
The "other" modus of non-interactive (batch) operation is from the Command Line 
Interface.
This assumes for an existing footprintwizard file (or series of files when 
batch processing).

%prep
%setup

%build
./autogen.sh
make

%install
# the rest has to be installed by hand ...
install -c -m 755 src/pcb-gfpw $RPM_BUILD_ROOT/usr/bin
install -c -m 755 src/fpw $RPM_BUILD_ROOT/usr/bin
install -d $RPM_BUILD_ROOT/usr/share/doc/%{name}
install -c -m 644 AUTHORS $RPM_BUILD_ROOT/usr/share/doc/%{name}-%{version}
install -c -m 644 ChangeLog $RPM_BUILD_ROOT/usr/share/doc/%{name}-%{version}
install -c -m 644 COPYING $RPM_BUILD_ROOT/usr/share/doc/%{name}-%{version}
install -c -m 644 HACKING $RPM_BUILD_ROOT/usr/share/doc/%{name}-%{version}
install -c -m 644 INSTALL $RPM_BUILD_ROOT/usr/share/doc/%{name}-%{version}
install -c -m 644 ISSUES $RPM_BUILD_ROOT/usr/share/doc/%{name}-%{version}
install -c -m 644 NEWS $RPM_BUILD_ROOT/usr/share/doc/%{name}-%{version}
install -c -m 644 README $RPM_BUILD_ROOT/usr/share/doc/%{name}-%{version}

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
/usr/bin/pcb-gfpw
/usr/bin/fpw
%doc AUTHORS
%doc ChangeLog
%doc COPYING
%doc HACKING
%doc INSTALL
%doc ISSUES
%doc NEWS
%doc README

%changelog
* Mon Sep 17 2008 L.J.H. Timmerman <bert.timmerman@xs4all.nl>
  Built on Fedora Core 5
  Initial spec file.

# End Of File
