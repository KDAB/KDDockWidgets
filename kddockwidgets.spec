Name:           kddockwidgets
Version:        0.99.9
Release:        1
Summary:        KDAB's Dock Widget Framework for Qt
Source0:        %{name}-%{version}.tar.gz
Source1:        %{name}-%{version}.tar.gz.asc
URL:            https://github.com/KDAB/KDDockWidgets
Group:          System/Libraries
License:        GPL-2.0-only OR GPL-3.0-only
BuildRoot:      %{_tmppath}/%{name}-%{version}-build
Vendor:         Klaralvdalens Datakonsult AB (KDAB)
Packager:       Klaralvdalens Datakonsult AB (KDAB) <info@kdab.com>

BuildRequires: cmake
%if %{defined suse_version}
BuildRequires:  libqt5-qtbase-devel libqt5-qtx11extras-devel
%endif

%if %{defined fedora}
BuildRequires:  gcc-c++ qt5-qtbase-devel qt5-qtx11extras-devel desktop-file-utils
%endif

%if %{defined rhel}
BuildRequires:  gcc-c++ qt5-qtbase-devel qt5-qtx11extras-devel desktop-file-utils
%endif

%description
KDDockWidgets is an advanced docking system for Qt which provides
many features not found in QDockWidgets, including:
 - Nesting dock widgets in a floating window and docking that group back to main window
  - Docking to any main window, not only to the parent main window
  - Docking to center of main window, or simply removing the concept of "central widget"
  - Main window supporting detachable tabs in center widget
  - Detaching arbitrary tabs from a tab bar into a dock area
  - Exposing inner helper widgets so the user can customize them or provide his own
    - Customize tab widgets
    - Customize title bars
    - Customize window frames

Authors:
--------
      Klaralvdalens Datakonsult AB (KDAB) <info@kdab.com>

%define debug_package %{nil}
%global __debug_install_post %{nil}

%package devel
Summary:        Development files for %{name}
Group:          Development/Libraries/C and C++
Requires:       %{name} = %{version}

%description devel
This package contains header files and associated tools and libraries to
develop programs using kddockwidgets.

%prep
%autosetup

%build
cmake . -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release
%__make %{?_smp_mflags}

%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig

%install
%make_install

%clean
%__rm -rf "%{buildroot}"

%files
%defattr(-,root,root)
%{_prefix}/share/doc/KDDockWidgets
%{_libdir}/libkddockwidgets.so.*
%{_libdir}/libkddockwidgets_multisplitter.so.*

%files devel
%defattr(-,root,root,-)
%{_libdir}/qt5/mkspecs/modules/*
%dir %{_includedir}/kddockwidgets
%{_includedir}/kddockwidgets/*
%dir %{_libdir}/cmake/KDDockWidgets
%{_libdir}/cmake/KDDockWidgets/*
%{_libdir}/libkddockwidgets.so
%{_libdir}/libkddockwidgets_multisplitter.so

%changelog
* Thu Aug 06 2020 Allen Winter <allen.winter@kdb.com> 0.99.9
  1.0.0 release candidate
