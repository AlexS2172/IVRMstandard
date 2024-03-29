  // stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__D8E59625_3126_4753_A768_828F88B41F79__INCLUDED_)
#define AFX_STDAFX_H__D8E59625_3126_4753_A768_828F88B41F79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#pragma warning(disable:4192 4786)

#include <afxinet.h>
#include <afxdisp.h>
#include <afxwin.h>
#include <afxext.h>
#include <afxdtctl.h>
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <objbase.h>
#include <atlbase.h>
#include <atlconv.h>

#import <Oledb32.tlb> no_namespace named_guids

#define EG_DB_BACKWARD_COMPATIBLE
#include <eg_lib/egDB.h>
#include <eg_lib/EgRegistry.h>

#include <math.h>
#include <conio.h>

#include <iostream>
#include <vector>
#include <string>
#include <tchar.h>

using namespace std;
using namespace eg_reg;

struct CTrade;
typedef vector<CTrade*>             TradesArray;
typedef vector<CTrade*>::iterator   TradesArrayIter;

typedef basic_string<TCHAR, char_traits<TCHAR>, allocator<TCHAR> >	tstring;

#define SETTINGS_REGISTRY_KEY	 _T("Software\\Egar\\ETS\\CIBCTradeFeedAdapter")
#define SETTINGS_DB_SOURCE		 _T("Exchange_DB")

const int g_SymbolsCount = 206; 

const tstring g_Symbols[] = {
_T("AAPL"),
_T("ABT"),
_T("ABX"),
_T("ACS"),
_T("ADI"),
_T("ADPT"),
_T("AHG"),
_T("AIG"),
_T("AL"),
_T("ALL"),
_T("ALTR"),
_T("ALXN"),
_T("AMAT"),
_T("AMCC"),
_T("AMD"),
_T("AMGN"),
_T("AMKR"),
_T("AMR"),
_T("AMZN"),
_T("AN"),
_T("ANF"),
_T("ANN"),
_T("AWE"),
_T("AXP"),
_T("BA"),
_T("BAC"),
_T("BBH"),
_T("BBY"),
_T("BEAS"),
_T("BHI"),
_T("BMY"),
_T("BOW"),
_T("BR"),
_T("BRCM"),
_T("BUD"),
_T("C"),
_T("CAL"),
_T("CBH"),
_T("CDN"),
_T("CE"),
_T("CHTR"),
_T("CKFR"),
_T("CL"),
_T("CMCSA"),
_T("CNO"),
_T("COMS"),
_T("COST"),
_T("CPN"),
_T("CSC"),
_T("CSCO"),
_T("CSX"),
_T("CVX"),
_T("CX"),
_T("CZN"),
_T("DAL"),
_T("DD"),
_T("DE"),
_T("DIS"),
_T("DISH"),
_T("DNA"),
_T("DPH"),
_T("DST"),
_T("DT"),
_T("DTE"),
_T("DUK"),
_T("EBAY"),
_T("EDS"),
_T("EIX"),
_T("EK"),
_T("ELN"),
_T("EP"),
_T("ERICY"),
_T("ERTS"),
_T("ET"),
_T("F"),
_T("FAF"),
_T("FCX"),
_T("FD"),
_T("FDC"),
_T("FDRY"),
_T("FDS"),
_T("FE"),
_T("FLEX"),
_T("FNM"),
_T("FRE"),
_T("GE"),
_T("GENZ"),
_T("GISX"),
_T("GM"),
_T("GPS"),
_T("GSF"),
_T("GTK"),
_T("HAL"),
_T("HAS"),
_T("HD"),
_T("HDI"),
_T("HIG"),
_T("HON"),
_T("HOV"),
_T("HPQ"),
_T("IACI"),
_T("IBM"),
_T("ICOS"),
_T("INTC"),
_T("INTU"),
_T("IVX"),
_T("IWM"),
_T("JBLU"),
_T("JCP"),
_T("JNS"),
_T("JNY"),
_T("JPM"),
_T("KLAC"),
_T("KO"),
_T("KSS"),
_T("L"),
_T("LIZ"),
_T("LLTC"),
_T("LLY"),
_T("LMT"),
_T("LNCR"),
_T("LSI"),
_T("LVLT"),
_T("LYO"),
_T("MBG"),
_T("MCD"),
_T("MEDI"),
_T("MER"),
_T("MLNM"),
_T("MMC"),
_T("MMM"),
_T("MO"),
_T("MOT"),
_T("MRO"),
_T("MSFT"),
_T("MU"),
_T("MWD"),
_T("MXIM"),
_T("NEM"),
_T("NOK"),
_T("NPSP"),
_T("NSM"),
_T("NVLS"),
_T("NWL"),
_T("NXTL"),
_T("ORCL"),
_T("OXY"),
_T("PAYX"),
_T("PCG"),
_T("PCLN"),
_T("PCS"),
_T("PDG"),
_T("PFE"),
_T("PKX"),
_T("PMCS"),
_T("PTR"),
_T("PVN"),
_T("QCOM"),
_T("RJR"),
_T("RSH"),
_T("S"),
_T("SAFC"),
_T("SAP"),
_T("SBC"),
_T("SBUX"),
_T("SCH"),
_T("SEBL"),
_T("SFD"),
_T("SGP"),
_T("SGR"),
_T("SLB"),
_T("SLF"),
_T("SMH"),
_T("SO"),
_T("STM"),
_T("T"),
_T("TER"),
_T("TGT"),
_T("THC"),
_T("TJX"),
_T("TMO"),
_T("TOM"),
_T("TOY"),
_T("TSM"),
_T("TTWO"),
_T("TWR"),
_T("TWX"),
_T("TXN"),
_T("TYC"),
_T("UPL"),
_T("USM"),
_T("UTX"),
_T("VC"),
_T("VECO"),
_T("VLO"),
_T("VOD"),
_T("VRTS"),
_T("VSH"),
_T("VZ"),
_T("WFC"),
_T("WMI"),
_T("WMT"),
_T("X"),
_T("XLNX"),
_T("XMSR"),
_T("XRX")
};


const int g_HedgeGroupsCount = 200; 

const tstring g_HedgeGroups[] = {
_T("AAPL"),
_T("ABT"),
_T("ABX"),
_T("ACS"),
_T("ADI"),
_T("ADPT"),
_T("AHG"),
_T("AIG"),
_T("AL"),
_T("ALL"),
_T("ALXN"),
_T("AMAT"),
_T("AMCC"),
_T("AMD"),
_T("AMGN"),
_T("AMKR"),
_T("AMR"),
_T("AMZN"),
_T("AN"),
_T("ANF"),
_T("ANN"),
_T("AWE"),
_T("AXP"),
_T("BA"),
_T("BAC"),
_T("BBH"),
_T("BBY"),
_T("BEAS"),
_T("BHI"),
_T("BMY"),
_T("BOW"),
_T("BR"),
_T("BRCM"),
_T("BUD"),
_T("C"),
_T("CAL"),
_T("CBH"),
_T("CDN"),
_T("CE"),
_T("CHTR"),
_T("CKFR"),
_T("CL"),
_T("CMCSA"),
_T("CNO"),
_T("COMS"),
_T("COST"),
_T("CPN"),
_T("CSC"),
_T("CSCO"),
_T("CSX"),
_T("CVX"),
_T("CX"),
_T("CZN"),
_T("DAL"),
_T("DD"),
_T("DE"),
_T("DIS"),
_T("DISH"),
_T("DNA"),
_T("DPH"),
_T("DST"),
_T("DT"),
_T("DTE"),
_T("DUKRC"),
_T("EBAY"),
_T("EDS"),
_T("EIX"),
_T("EK"),
_T("ELN"),
_T("EP"),
_T("ERICY"),
_T("ERTS"),
_T("ET"),
_T("F"),
_T("FAF"),
_T("FCX"),
_T("FD"),
_T("FDC"),
_T("FDRY"),
_T("FDS"),
_T("FE"),
_T("FLEX"),
_T("FNM"),
_T("FRE"),
_T("GE"),
_T("GENZ"),
_T("GISX"),
_T("GM"),
_T("GPS"),
_T("GSF"),
_T("GTK"),
_T("HAL"),
_T("HAS"),
_T("HD"),
_T("HDI"),
_T("HIG"),
_T("HON"),
_T("HOV"),
_T("HPQ"),
_T("IACI"),
_T("IBM"),
_T("ICOS"),
_T("INTC"),
_T("INTU"),
_T("IVX"),
_T("IWM"),
_T("JBLU"),
_T("JCP"),
_T("JNS"),
_T("JNY"),
_T("JPM"),
_T("KO"),
_T("KSS"),
_T("L"),
_T("LIZ"),
_T("LLTC"),
_T("LLY"),
_T("LMT"),
_T("LNCR"),
_T("LSI"),
_T("LVLT"),
_T("LYO"),
_T("MBG"),
_T("MCD"),
_T("MEDI"),
_T("MER"),
_T("MLNM"),
_T("MMC"),
_T("MMM"),
_T("MO"),
_T("MOT"),
_T("MRO"),
_T("MSFT"),
_T("MU"),
_T("MWD"),
_T("MXIM"),
_T("NEM"),
_T("NOK"),
_T("NPSP"),
_T("NVLS"),
_T("NWL"),
_T("NXTL"),
_T("ORCL"),
_T("OXY"),
_T("PAYX"),
_T("PCG"),
_T("PCLN"),
_T("PCS"),
_T("PDG"),
_T("PFE"),
_T("PKX"),
_T("PMCS"),
_T("PTR"),
_T("PVN"),
_T("QCOM"),
_T("RJR"),
_T("RSH"),
_T("S"),
_T("SAFC"),
_T("SAP"),
_T("SBC"),
_T("SBUX"),
_T("SCH"),
_T("SEBL"),
_T("SFD"),
_T("SGP"),
_T("SGR"),
_T("SLB"),
_T("SLF"),
_T("SMH"),
_T("SO"),
_T("SOXSPX"),
_T("T"),
_T("TGT"),
_T("THC"),
_T("TJX"),
_T("TMO"),
_T("TOM"),
_T("TOY"),
_T("TTWO"),
_T("TWR"),
_T("TWX"),
_T("TXN"),
_T("TYC"),
_T("UPL"),
_T("USM"),
_T("UTX"),
_T("VC"),
_T("VECO"),
_T("VLO"),
_T("VOD"),
_T("VRTS"),
_T("VSH"),
_T("VZ"),
_T("WFC"),
_T("WMI"),
_T("WMT"),
_T("X"),
_T("XMSR"),
_T("XRX")
};

const int g_AcctIDsCount = 7; 

const tstring g_AcctIDs[] = {
    _T("us8101"), 
    _T("us8102"),
    _T("us8103"),
    _T("us8104"),
    _T("us8105"),
    _T("us8106"),
    _T("us8109")
};


// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__D8E59625_3126_4753_A768_828F88B41F79__INCLUDED_)
