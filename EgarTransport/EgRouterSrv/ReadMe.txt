========================================================================
    ACTIVE TEMPLATE LIBRARY : EgRouterSrv Project Overview
========================================================================

AppWizard has created this EgRouterSrv project for you to use as the starting point for
writing your Service (EXE).

This file contains a summary of what you will find in each of the files that
make up your project.

EgRouterSrv.vcproj
    This is the main project file for VC++ projects generated using an Application Wizard. 
    It contains information about the version of Visual C++ that generated the file, and 
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

EgRouterSrv.idl
    This file contains the IDL definitions of the type library, the interfaces
    and co-classes defined in your project.
    This file will be processed by the MIDL compiler to generate:
        C++ interface definitions and GUID declarations (EgRouterSrv.h)
        GUID definitions                                (EgRouterSrv_i.c)
        A type library                                  (EgRouterSrv.tlb)
        Marshaling code                                 (EgRouterSrv_p.c and dlldata.c)

EgRouterSrv.h
    This file contains the C++ interface definitions and GUID declarations of the
    items defined in EgRouterSrv.idl. It will be regenerated by MIDL during compilation.
EgRouterSrv.cpp
    This file contains the object map and the implementation of WinMain, ServiceMain, and
    the service management functions.
EgRouterSrv.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.


/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named EgRouterSrv.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file that defines resource IDs.

/////////////////////////////////////////////////////////////////////////////
Proxy/stub DLL project and module definition file:

EgRouterSrvps.vcproj
    This file is the project file for building a proxy/stub DLL if necessary.
	The IDL file in the main project must contain at least one interface and you must 
	first compile the IDL file before building the proxy/stub DLL.	This process generates
	dlldata.c, EgRouterSrv_i.c and EgRouterSrv_p.c which are required
	to build the proxy/stub DLL.

EgRouterSrvps.def
    This module definition file provides the linker with information about the exports
    required by the proxy/stub.
/////////////////////////////////////////////////////////////////////////////
