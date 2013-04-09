Summary:	FootPrintWizard for pcb.
Name:	pcb-fpw
Version:	0.0.11
Release:	1%{?dist}
License:	GPLv2
Group:	Applications/Engineering
URL:	http://www.xs4all.nl/~ljh4timm/pcb-fpw/pcb-fpw.html
Packager:	Bert Timmerman <bert.timmerman@xs4all.nl>
Source:		%{name}-%{version}.tar.gz 	
Buildroot:	/var/tmp/%{name}

%description
The pcb-fpw FootPrintWizard is what the name says it will be:
a footprint wizard (a.k.a. footprint generator).
pcb-fpw is not a footprint editor, therefor one can NOT load an existing 
footprint file into pcb-fpw, make some changes and save it back to file, and 
subsequent load the edited footprint file into pcb.
The main, interactive, modus of operating the software is probably with the 
GUI application "pcb-gfpw".
The "other" modus of non-interactive (batch) operation is from the Command Line 
Interface "fpw", this assumes the use of an existing footprintwizard file
(or series of files when batch processing).

%prep
%setup -n %{name}

%build
./autogen.sh
make

%install
# we can't assume we have permission for "make install"
# so *everything* has to be installed by hand ...

# binaries
install -d $RPM_BUILD_ROOT/usr/local/bin
install -c -m 755 src/pcb-gfpw $RPM_BUILD_ROOT/usr/local/bin
install -c -m 755 src/fpw $RPM_BUILD_ROOT/usr/local/bin
# data
install -d $RPM_BUILD_ROOT/usr/local/share/%{name}/data
install -c -m 644 data/README $RPM_BUILD_ROOT/usr/local/share/%{name}/data/
install -c -m 644 data/fpw_data.csv $RPM_BUILD_ROOT/usr/local/share/%{name}/data/
install -c -m 644 data/fpw_data.sql $RPM_BUILD_ROOT/usr/local/share/%{name}/data/
install -c -m 644 data/user_data.csv $RPM_BUILD_ROOT/usr/local/share/%{name}/data/
install -c -m 644 data/user_data.sql $RPM_BUILD_ROOT/usr/local/share/%{name}/data/
# pixmaps
install -d $RPM_BUILD_ROOT/usr/local/share/%{name}/pixmaps
install -c -m 644 pixmaps/*.xpm $RPM_BUILD_ROOT/usr/local/share/%{name}/pixmaps/
# man page
install -d $RPM_BUILD_ROOT/usr/local/share/man/man1
install -c -m 644 doc/fpw.1 $RPM_BUILD_ROOT/usr/local/share/man/man1/
# docs
# - user manual docs
install -d $RPM_BUILD_ROOT/usr/local/doc/%{name}-%{version}
install -c -m 644 doc/user-manual.html $RPM_BUILD_ROOT/usr/local/doc/%{name}-%{version}/
install -c -m 644 doc/pin_pad_1_locations.html $RPM_BUILD_ROOT/usr/local/doc/%{name}-%{version}/
install -c -m 644 doc/footprint_licensing.html $RPM_BUILD_ROOT/usr/local/doc/%{name}-%{version}/
install -c -m 644 doc/footprint_naming_convention.html $RPM_BUILD_ROOT/usr/local/doc/%{name}-%{version}/
# - user manual images
install -d $RPM_BUILD_ROOT/usr/local/doc/%{name}-%{version}/images
install -c -m 644 doc/images/about_dialog.png $RPM_BUILD_ROOT/usr/local/doc/%{name}-%{version}/images/
install -c -m 644 doc/images/credits_dialog.png $RPM_BUILD_ROOT/usr/local/doc/%{name}-%{version}/images/
install -c -m 644 doc/images/footprint_tab.png $RPM_BUILD_ROOT/usr/local/doc/%{name}-%{version}/images/
install -c -m 644 doc/images/heel_and_toe_goals_tab.png $RPM_BUILD_ROOT/usr/local/doc/%{name}-%{version}/images/
install -c -m 644 doc/images/license_dialog.png $RPM_BUILD_ROOT/usr/local/doc/%{name}-%{version}/images/
install -c -m 644 doc/images/pins_pads_tab.png $RPM_BUILD_ROOT/usr/local/doc/%{name}-%{version}/images/
install -c -m 644 doc/images/select_exception_dialog.png $RPM_BUILD_ROOT/usr/local/doc/%{name}-%{version}/images/
install -c -m 644 doc/images/silkscreen_tab.png $RPM_BUILD_ROOT/usr/local/doc/%{name}-%{version}/images/
install -c -m 644 doc/images/thermal_pad_tab.png $RPM_BUILD_ROOT/usr/local/doc/%{name}-%{version}/images/
# - release docs
install -c -m 644 AUTHORS $RPM_BUILD_ROOT/usr/local/doc/%{name}-%{version}/
install -c -m 644 ChangeLog $RPM_BUILD_ROOT/usr/local/doc/%{name}-%{version}/
install -c -m 644 COPYING $RPM_BUILD_ROOT/usr/local/doc/%{name}-%{version}/
install -c -m 644 HACKING $RPM_BUILD_ROOT/usr/local/doc/%{name}-%{version}/
install -c -m 644 INSTALL $RPM_BUILD_ROOT/usr/local/doc/%{name}-%{version}/
install -c -m 644 ISSUES $RPM_BUILD_ROOT/usr/local/doc/%{name}-%{version}/
install -c -m 644 LICENSE $RPM_BUILD_ROOT/usr/local/doc/%{name}-%{version}/
install -c -m 644 NEWS $RPM_BUILD_ROOT/usr/local/doc/%{name}-%{version}/
install -c -m 644 README $RPM_BUILD_ROOT/usr/local/doc/%{name}-%{version}/

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
# docs
%docdir /usr/local/doc/%{name}-%{version}
%doc /usr/local/doc/%{name}-%{version}/
%doc /usr/local/share/%{name}/data/README
# binaries
/usr/local/bin/pcb-gfpw
/usr/local/bin/fpw
# data
/usr/local/share/%{name}/data/
# pixmaps
/usr/local/share/%{name}/pixmaps/
# man pages
%doc /usr/local/share/man/man1/

%changelog
* Thu Mar 10 2011 Bert Timmerman <bert.timmerman@xs4all.nl>
  Updated for Fedora Core 13 / pcb-fpw-0.0.11.

* Sun Jan 16 2011 Bert Timmerman <bert.timmerman@xs4all.nl>
  Updated for Fedora Core 13 / pcb-fpw-0.0.10.

* Mon Sep 17 2008 Bert Timmerman <bert.timmerman@xs4all.nl>
  Built on Fedora Core 5.
  Initial spec file.

# End Of File
