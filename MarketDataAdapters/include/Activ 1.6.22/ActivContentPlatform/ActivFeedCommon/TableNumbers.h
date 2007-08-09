/**
 *	@file	TableNumbers.h
 *
 *	@brief	Header file for the table numbers.
 *
 *	$Log: $
 */

#if !defined(ACTIV_FEED_TABLE_NUMBERS_H)
#define ACTIV_FEED_TABLE_NUMBERS_H

#include "ActivMiddleware/Activ.h"

#include "ActivContentPlatform/ActivFeedCommon/ActivFeedDefinitions.h"


#include <vector>

namespace Activ
{

namespace Feed
{

typedef std::vector<TableNo>  TableNoList;	///<The table number list type definition.

const TableNo TABLE_NO_US_LISTING = 0;
const TableNo TABLE_NO_US_EQUITY_OPTION = 1;
const TableNo TABLE_NO_INDEX = 2;
const TableNo TABLE_NO_US_MARKET_MAKER_QUOTE = 3;
const TableNo TABLE_NO_MARKET_MAKER_QUOTE = 4;
const TableNo TABLE_NO_AMERICAS_LISTING_DEPTH = 5;
const TableNo TABLE_NO_ORDER = 6;
const TableNo TABLE_NO_OPTION = 7;
const TableNo TABLE_NO_US_FUTURE = 16;
const TableNo TABLE_NO_US_FUTURE_OPTION = 17;
const TableNo TABLE_NO_ECN_DEPTH = 19;
const TableNo TABLE_NO_MUTUAL_FUND = 21;
const TableNo TABLE_NO_MONEY_MARKET = 22;
const TableNo TABLE_NO_FUND = 23;
const TableNo TABLE_NO_FOREX = 24;
const TableNo TABLE_NO_OPTION_ROOT = 25;
const TableNo TABLE_NO_OPTION_DELIVERABLE = 26;
const TableNo TABLE_NO_FUTURE_ROOT = 27;
const TableNo TABLE_NO_FUTURE_OPTION_ROOT = 28;
const TableNo TABLE_NO_SYNTHETIC = 29;
const TableNo TABLE_NO_SECURITY = 30;
const TableNo TABLE_NO_COMPANY = 31;
const TableNo TABLE_NO_BANK_COMPANY = 32;
const TableNo TABLE_NO_INDUSTRIAL_COMPANY = 33;
const TableNo TABLE_NO_INSURANCE_COMPANY = 34;
const TableNo TABLE_NO_THRIFT_COMPANY = 35;
const TableNo TABLE_NO_SECTOR = 36;
const TableNo TABLE_NO_EXCHANGE = 37;
const TableNo TABLE_NO_SESSIONS = 38;
const TableNo TABLE_NO_STATISTICS = 39;
const TableNo TABLE_NO_ANALYTICS = 40;
const TableNo TABLE_NO_RANKINGS = 41;
const TableNo TABLE_NO_AMERICAS_FUTURE_DEPTH = 42;
const TableNo TABLE_NO_AMERICAS_OPTION_DEPTH = 43;
const TableNo TABLE_NO_HEMSCOTT = 60;
const TableNo TABLE_NO_RELATIONSHIP = 100;
const TableNo TABLE_NO_COMPANY_DOMICILE_NAVIGATION = 101;
const TableNo TABLE_NO_FUTURE_OPTION_FUTURE_OPTION_ROOT_NAVIGATION = 102;
const TableNo TABLE_NO_FUTURE_FUTURE_ROOT_NAVIGATION = 103;
const TableNo TABLE_NO_INDEX_CONSTITUENT_NAVIGATION = 104;
const TableNo TABLE_NO_LISTING_SECURITY_NAVIGATION = 105;
const TableNo TABLE_NO_OPTION_ROOT_OPTION_DELIVERABLE_NAVIGATION = 106;
const TableNo TABLE_NO_OPTION_ROOT_UNDERLYING_NAVIGATION = 107;
const TableNo TABLE_NO_SECTOR_CONSTITUENT_NAVIGATION = 108;
const TableNo TABLE_NO_SECURITY_COMPANY_NAVIGATION = 109;
const TableNo TABLE_NO_SYNTHETIC_CONSTITUENT_NAVIGATION = 110;
const TableNo TABLE_NO_LISTING_COMPANY_NAVIGATION = 111;
const TableNo TABLE_NO_ANALYTICS_NAVIGATION = 112;
const TableNo TABLE_NO_PRIMARY_LISTING_NAVIGATION = 113;
const TableNo TABLE_NO_FUTURE_FUTURE_OPTION_EXPIRATION_NAVIGATION = 114;
const TableNo TABLE_NO_FUNDAMENTAL_NAVIGATION = 115;
const TableNo TABLE_NO_CORPORATE_EVENTS = 200;
const TableNo TABLE_NO_DELIST = 201;
const TableNo TABLE_NO_DIVIDEND = 202;
const TableNo TABLE_NO_IPO = 203;
const TableNo TABLE_NO_SPLIT = 204;
const TableNo TABLE_NO_SYMBOL_CHANGE = 205;
const TableNo TABLE_NO_OPTION_SYMBOL_EVENT = 206;
const TableNo TABLE_NO_CUG = 300;
const TableNo TABLE_NO_PERMISSION = 301;
const TableNo TABLE_NO_USER = 302;
const TableNo TABLE_NO_NEWS = 400;
const TableNo TABLE_NO_NEWS_HEADLINE = 401;
const TableNo TABLE_NO_SYSTEM_MESSAGE = 402;
const TableNo TABLE_NO_TIME_SERIES_TRADE = 500;
const TableNo TABLE_NO_TIME_SERIES_INTRADAY = 501;
const TableNo TABLE_NO_TIME_SERIES_HISTORY = 502;
const TableNo TABLE_NO_COMPOSITE_EXCHANGE = 503;
const TableNo TABLE_NO_MISCELLANEOUS_ALIAS = 600;
const TableNo TABLE_NO_FUTURE_ALIAS = 601;

// Fixed table numbers.
const TableNo TABLE_NO_CONTRIBUTION_BASE = 5000;
const TableNo TABLE_NO_MAX = 8191;

} // namespace Feed

} // namespace Activ

#endif // !defined(ACTIV_FEED_TABLE_NUMBERS_H)
