/**
 *	@file	FieldIds.h
 *
 *	@brief	Header file for the field ids.
 *
 *	$Log: $
 */

#if !defined(ACTIV_FEED_FIELD_IDS_H)
#define ACTIV_FEED_FIELD_IDS_H

#include "ActivMiddleware/Activ.h"

#include "ActivContentPlatform/ActivFeedCommon/External.h"
#include "ActivContentPlatform/ActivFeedCommon/ActivFeedDefinitions.h"

namespace Activ
{

namespace Feed
{

const FieldId FID_UNDEFINED = ~0;

const FieldId FID_BID = 0;
const FieldId FID_BID_SIZE = 1;
const FieldId FID_BID_CONDITION = 2;
const FieldId FID_BID_TIME = 3;
const FieldId FID_BID_EXCHANGE = 4;
const FieldId FID_ASK = 5;
const FieldId FID_ASK_SIZE = 6;
const FieldId FID_ASK_CONDITION = 7;
const FieldId FID_ASK_TIME = 8;
const FieldId FID_ASK_EXCHANGE = 9;
const FieldId FID_MARKET_MAKER_STATUS = 10;
const FieldId FID_QUOTE_DATE = 11;
const FieldId FID_TRADE = 12;
const FieldId FID_TRADE_SIZE = 13;
const FieldId FID_TRADE_CONDITION = 14;
const FieldId FID_TRADE_TIME = 15;
const FieldId FID_TRADE_DATE = 16;
const FieldId FID_TRADE_EXCHANGE = 17;
const FieldId FID_TRADE_HIGH = 18;
const FieldId FID_TRADE_HIGH_CONDITION = 19;
const FieldId FID_TRADE_HIGH_TIME = 20;
const FieldId FID_TRADE_HIGH_EXCHANGE = 21;
const FieldId FID_TRADE_LOW = 22;
const FieldId FID_TRADE_LOW_CONDITION = 23;
const FieldId FID_TRADE_LOW_TIME = 24;
const FieldId FID_TRADE_LOW_EXCHANGE = 25;
const FieldId FID_TRADE_COUNT = 26;
const FieldId FID_CURRENT = 27;
const FieldId FID_CURRENT_CONDITION = 28;
const FieldId FID_CURRENT_TIME = 29;
const FieldId FID_CURRENT_DATE = 30;
const FieldId FID_CURRENT_HIGH = 31;
const FieldId FID_CURRENT_HIGH_TIME = 32;
const FieldId FID_CURRENT_LOW = 33;
const FieldId FID_CURRENT_LOW_TIME = 34;
const FieldId FID_OPEN = 35;
const FieldId FID_OPEN_SIZE = 36;
const FieldId FID_OPEN_CONDITION = 37;
const FieldId FID_OPEN_TIME = 38;
const FieldId FID_OPEN_EXCHANGE = 39;
const FieldId FID_FIRST_TRADE = 40;
const FieldId FID_FIRST_TRADE_TIME = 41;
const FieldId FID_ORDER_PRICE = 42;
const FieldId FID_ORDER_SIZE = 43;
const FieldId FID_ORDER_TIME = 44;
const FieldId FID_ORDER_DATE = 45;
const FieldId FID_ORDER_BUY_SELL = 46;
const FieldId FID_ORDER_SEQUENCE_NUMBER = 47;
const FieldId FID_ORDER_STATE = 48;
const FieldId FID_ORDER_TYPE = 49;
const FieldId FID_CUMULATIVE_PRICE = 50;
const FieldId FID_CUMULATIVE_VALUE = 51;
const FieldId FID_CUMULATIVE_VOLUME = 52;
const FieldId FID_PRE_POST_MARKET_CUMULATIVE_VOLUME = 53;
const FieldId FID_NET_CHANGE = 54;
const FieldId FID_PERCENT_CHANGE = 55;
const FieldId FID_CLOSING_BID = 56;
const FieldId FID_CLOSING_BID_EXCHANGE = 57;
const FieldId FID_CLOSING_ASK = 58;
const FieldId FID_CLOSING_ASK_EXCHANGE = 59;
const FieldId FID_CLOSING_QUOTE_DATE = 60;
const FieldId FID_CLOSE = 61;
const FieldId FID_CLOSE_CONDITION = 62;
const FieldId FID_CLOSE_STATUS = 63;
const FieldId FID_CLOSE_TIME = 64;
const FieldId FID_CLOSE_DATE = 65;
const FieldId FID_CLOSE_EXCHANGE = 66;
const FieldId FID_CLOSE_CUMULATIVE_VOLUME = 67;
const FieldId FID_CLOSE_CUMULATIVE_VOLUME_STATUS = 68;
const FieldId FID_CLOSE_CUMULATIVE_VOLUME_DATE = 69;
const FieldId FID_CLOSE_CUMULATIVE_VALUE = 70;
const FieldId FID_CLOSE_CUMULATIVE_VALUE_STATUS = 71;
const FieldId FID_COMPOSITE_CLOSE = 72;
const FieldId FID_COMPOSITE_CLOSE_DATE = 73;
const FieldId FID_COMPOSITE_CLOSE_EXCHANGE = 74;
const FieldId FID_SETTLEMENT = 75;
const FieldId FID_SETTLEMENT_SIZE = 76;
const FieldId FID_SETTLEMENT_STATUS = 77;
const FieldId FID_SETTLEMENT_TIME = 78;
const FieldId FID_SETTLEMENT_DATE = 79;
const FieldId FID_BID1 = 80;
const FieldId FID_BID1_TIME = 81;
const FieldId FID_BID1_SIZE = 82;
const FieldId FID_BID1_COUNT = 83;
const FieldId FID_ASK1 = 84;
const FieldId FID_ASK1_TIME = 85;
const FieldId FID_ASK1_SIZE = 86;
const FieldId FID_ASK1_COUNT = 87;
const FieldId FID_BID2 = 88;
const FieldId FID_BID2_COUNT = 89;
const FieldId FID_BID2_SIZE = 90;
const FieldId FID_BID3 = 91;
const FieldId FID_ASK2 = 92;
const FieldId FID_ASK2_COUNT = 93;
const FieldId FID_ASK2_SIZE = 94;
const FieldId FID_ASK3 = 95;
const FieldId FID_BID3_SIZE = 96;
const FieldId FID_BID4 = 97;
const FieldId FID_BID3_COUNT = 98;
const FieldId FID_BID4_SIZE = 99;
const FieldId FID_ASK3_SIZE = 100;
const FieldId FID_ASK4 = 101;
const FieldId FID_ASK3_COUNT = 102;
const FieldId FID_ASK4_SIZE = 103;
const FieldId FID_BID4_COUNT = 104;
const FieldId FID_BID5_SIZE = 105;
const FieldId FID_BID5 = 106;
const FieldId FID_BID5_COUNT = 107;
const FieldId FID_ASK4_COUNT = 108;
const FieldId FID_ASK5_SIZE = 109;
const FieldId FID_ASK5 = 110;
const FieldId FID_ASK5_COUNT = 111;
const FieldId FID_PREVIOUS_TRADING_DATE = 112;
const FieldId FID_PREVIOUS_CLOSE = 113;
const FieldId FID_PREVIOUS_OPEN = 114;
const FieldId FID_PREVIOUS_TRADE_HIGH = 115;
const FieldId FID_PREVIOUS_TRADE_LOW = 116;
const FieldId FID_PREVIOUS_CURRENT_HIGH = 117;
const FieldId FID_PREVIOUS_CURRENT_LOW = 118;
const FieldId FID_PREVIOUS_NET_CHANGE = 119;
const FieldId FID_PREVIOUS_PERCENT_CHANGE = 120;
const FieldId FID_PREVIOUS_OPEN_INTEREST = 121;
const FieldId FID_PREVIOUS_OPEN_INTEREST_DATE = 122;
const FieldId FID_OPEN_RANGE_1 = 123;
const FieldId FID_OPEN_RANGE_1_CONDITION = 124;
const FieldId FID_OPEN_RANGE_2 = 125;
const FieldId FID_OPEN_RANGE_2_CONDITION = 126;
const FieldId FID_OPEN_RANGE_TIME = 127;
const FieldId FID_CLOSE_RANGE_1 = 128;
const FieldId FID_CLOSE_RANGE_1_CONDITION = 129;
const FieldId FID_CLOSE_RANGE_2 = 130;
const FieldId FID_CLOSE_RANGE_2_CONDITION = 131;
const FieldId FID_CLOSE_RANGE_TIME = 132;
const FieldId FID_LOCAL_PRICE = 133;
const FieldId FID_OPEN_INTEREST = 134;
const FieldId FID_OPEN_INTEREST_DATE = 135;
const FieldId FID_MARKET_PRICE = 136;
const FieldId FID_MARKET_PRICE_DATE = 137;
const FieldId FID_MARKET_PRICE_TIME = 138;
const FieldId FID_OFFER = 139;
const FieldId FID_OFFER_DATE = 140;
const FieldId FID_OFFER_TIME = 141;
const FieldId FID_NAV = 142;
const FieldId FID_NAV_TIME = 143;
const FieldId FID_NAV_DATE = 144;
const FieldId FID_WRAP = 145;
const FieldId FID_WRAP_TIME = 146;
const FieldId FID_WRAP_DATE = 147;
const FieldId FID_52_WEEK_HIGH = 148;
const FieldId FID_52_WEEK_HIGH_DATE = 149;
const FieldId FID_52_WEEK_LOW = 150;
const FieldId FID_52_WEEK_LOW_DATE = 151;
const FieldId FID_YEAR_HIGH = 152;
const FieldId FID_YEAR_HIGH_DATE = 153;
const FieldId FID_YEAR_LOW = 154;
const FieldId FID_YEAR_LOW_DATE = 155;
const FieldId FID_LIFETIME_HIGH = 156;
const FieldId FID_LIFETIME_HIGH_DATE = 157;
const FieldId FID_LIFETIME_LOW = 158;
const FieldId FID_LIFETIME_LOW_DATE = 159;
const FieldId FID_SESSION_1_CLOSE = 160;
const FieldId FID_SESSION_1_CLOSE_STATUS = 161;
const FieldId FID_SESSION_1_CLOSE_TIME = 162;
const FieldId FID_SESSION_1_CLOSE_CUMULATIVE_VALUE = 163;
const FieldId FID_SESSION_1_CLOSE_CUMULATIVE_VALUE_STATUS = 164;
const FieldId FID_SESSION_1_CLOSE_CUMULATIVE_VOLUME = 165;
const FieldId FID_SESSION_1_CLOSE_CUMULATIVE_VOLUME_STATUS = 166;
const FieldId FID_SESSION_1_CLOSING_ASK = 167;
const FieldId FID_SESSION_1_CLOSING_BID = 168;
const FieldId FID_SESSION_1_CURRENT_HIGH = 169;
const FieldId FID_SESSION_1_CURRENT_HIGH_TIME = 170;
const FieldId FID_SESSION_1_CURRENT_LOW = 171;
const FieldId FID_SESSION_1_CURRENT_LOW_TIME = 172;
const FieldId FID_SESSION_1_FIRST_TRADE = 173;
const FieldId FID_SESSION_1_FIRST_TRADE_TIME = 174;
const FieldId FID_SESSION_1_INDICATOR = 175;
const FieldId FID_SESSION_1_OPEN = 176;
const FieldId FID_SESSION_1_OPEN_TIME = 177;
const FieldId FID_SESSION_1_TRADE_HIGH = 178;
const FieldId FID_SESSION_1_TRADE_HIGH_TIME = 179;
const FieldId FID_SESSION_1_TRADE_LOW = 180;
const FieldId FID_SESSION_1_TRADE_LOW_TIME = 181;
const FieldId FID_SESSION_2_CLOSE = 182;
const FieldId FID_SESSION_2_CLOSE_STATUS = 183;
const FieldId FID_SESSION_2_CLOSE_TIME = 184;
const FieldId FID_SESSION_2_CLOSE_CUMULATIVE_VALUE = 185;
const FieldId FID_SESSION_2_CLOSE_CUMULATIVE_VALUE_STATUS = 186;
const FieldId FID_SESSION_2_CLOSE_CUMULATIVE_VOLUME = 187;
const FieldId FID_SESSION_2_CLOSE_CUMULATIVE_VOLUME_STATUS = 188;
const FieldId FID_SESSION_2_CLOSING_ASK = 189;
const FieldId FID_SESSION_2_CLOSING_BID = 190;
const FieldId FID_SESSION_2_CURRENT_HIGH = 191;
const FieldId FID_SESSION_2_CURRENT_HIGH_TIME = 192;
const FieldId FID_SESSION_2_CURRENT_LOW = 193;
const FieldId FID_SESSION_2_CURRENT_LOW_TIME = 194;
const FieldId FID_SESSION_2_FIRST_TRADE = 195;
const FieldId FID_SESSION_2_FIRST_TRADE_TIME = 196;
const FieldId FID_SESSION_2_INDICATOR = 197;
const FieldId FID_SESSION_2_OPEN = 198;
const FieldId FID_SESSION_2_OPEN_TIME = 199;
const FieldId FID_SESSION_2_TRADE_HIGH = 200;
const FieldId FID_SESSION_2_TRADE_HIGH_TIME = 201;
const FieldId FID_SESSION_2_TRADE_LOW = 202;
const FieldId FID_SESSION_2_TRADE_LOW_TIME = 203;
const FieldId FID_SESSION_3_CLOSE = 204;
const FieldId FID_SESSION_3_CLOSE_STATUS = 205;
const FieldId FID_SESSION_3_CLOSE_TIME = 206;
const FieldId FID_SESSION_3_CLOSE_CUMULATIVE_VALUE = 207;
const FieldId FID_SESSION_3_CLOSE_CUMULATIVE_VALUE_STATUS = 208;
const FieldId FID_SESSION_3_CLOSE_CUMULATIVE_VOLUME = 209;
const FieldId FID_SESSION_3_CLOSE_CUMULATIVE_VOLUME_STATUS = 210;
const FieldId FID_SESSION_3_CLOSING_ASK = 211;
const FieldId FID_SESSION_3_CLOSING_BID = 212;
const FieldId FID_SESSION_3_CURRENT_HIGH = 213;
const FieldId FID_SESSION_3_CURRENT_HIGH_TIME = 214;
const FieldId FID_SESSION_3_CURRENT_LOW = 215;
const FieldId FID_SESSION_3_CURRENT_LOW_TIME = 216;
const FieldId FID_SESSION_3_FIRST_TRADE = 217;
const FieldId FID_SESSION_3_FIRST_TRADE_TIME = 218;
const FieldId FID_SESSION_3_INDICATOR = 219;
const FieldId FID_SESSION_3_OPEN = 220;
const FieldId FID_SESSION_3_OPEN_TIME = 221;
const FieldId FID_SESSION_3_TRADE_HIGH = 222;
const FieldId FID_SESSION_3_TRADE_HIGH_TIME = 223;
const FieldId FID_SESSION_3_TRADE_LOW = 224;
const FieldId FID_SESSION_3_TRADE_LOW_TIME = 225;
const FieldId FID_7_DAY_YIELD = 226;
const FieldId FID_ACCRUED_INTEREST = 227;
const FieldId FID_ADDITIONAL_PAID_IN_CAPITAL = 228;
const FieldId FID_ANNUALIZED_7_DAY_YIELD = 229;
const FieldId FID_ASSETS = 230;
const FieldId FID_ATM_CALL_IMPLIED_VOLATILITY = 231;
const FieldId FID_ATM_PUT_IMPLIED_VOLATILITY = 232;
const FieldId FID_AVERAGE_MATURITY = 233;
const FieldId FID_AVERAGE_VOLUME = 234;
const FieldId FID_AVERAGE_VOLUME_100DAY = 235;
const FieldId FID_AVERAGE_VOLUME_22DAY = 236;
const FieldId FID_AVERAGE_VOLUME_250DAY = 237;
const FieldId FID_BETA = 238;
const FieldId FID_CAP_GAINS_DATE = 239;
const FieldId FID_CAP_GAINS_LONG = 240;
const FieldId FID_CAP_GAINS_OTHER = 241;
const FieldId FID_CAP_GAINS_SHORT = 242;
const FieldId FID_CAPITAL_DISTRIBUTION = 243;
const FieldId FID_CAPITAL_STOCK = 244;
const FieldId FID_CASH_FROM_FINANCING = 245;
const FieldId FID_CASH_FROM_INVESTMENTS = 246;
const FieldId FID_CASH_FROM_OPERATIONS = 247;
const FieldId FID_CASH_IN_LIEU_OF = 248;
const FieldId FID_CASH_NET_CHANGE = 249;
const FieldId FID_CASH_PER_CONTRACT = 250;
const FieldId FID_CLOSING_PRICE_MONTH = 251;
const FieldId FID_CLOSING_PRICE_QUARTER = 252;
const FieldId FID_CLOSING_PRICE_WEEK = 253;
const FieldId FID_CLOSING_PRICE_YEAR = 254;
const FieldId FID_COMMENTS = 255;
const FieldId FID_CONDITIONS = 256;
const FieldId FID_CONTRACT_MULTIPLIER = 257;
const FieldId FID_CONTRACT_TYPE = 258;
const FieldId FID_COUNTRY_CODE = 259;
const FieldId FID_CURRENCY = 260;
const FieldId FID_CURRENT_ASSETS = 261;
const FieldId FID_CURRENT_LIABILITIES = 262;
const FieldId FID_CURRENT_YIELD = 263;
const FieldId FID_DATE = 264;
const FieldId FID_DECLARE_DATE = 265;
const FieldId FID_DEPRECIATION_DEPLETION = 266;
const FieldId FID_DESCRIPTION = 267;
const FieldId FID_DISPLAY_DENOMINATOR = 268;
const FieldId FID_DIVIDEND = 269;
const FieldId FID_DIVIDEND_CURRENCY = 270;
const FieldId FID_DIVIDEND_FREQUENCY_CODE = 271;
const FieldId FID_DOWN = 272;
const FieldId FID_EMPLOYEES = 273;
const FieldId FID_ESTIMATED_CASH_AMOUNT_PER_UNIT = 274;
const FieldId FID_ESTIMATED_LONG_TERM_RETURN = 275;
const FieldId FID_EVENT_DATE = 276;
const FieldId FID_EX_DATE = 277;
const FieldId FID_EXCHANGE = 278;
const FieldId FID_EXERCISE_STYLE = 279;
const FieldId FID_EXPIRATION_DATE = 280;
const FieldId FID_EXPIRATION_TIME = 281;
const FieldId FID_FISCAL_YEAR_END = 282;
const FieldId FID_FOOTNOTES = 283;
const FieldId FID_GROSS_PROFITS = 284;
const FieldId FID_HIGHEST_SPREAD = 285;
const FieldId FID_INCOME_BEFORE_TAX = 286;
const FieldId FID_INCOME_DISTRIBUTION = 287;
const FieldId FID_INDICATED_ANNUAL_DIVIDEND = 288;
const FieldId FID_INDUSTRY_CODE = 289;
const FieldId FID_INSTITUTIONAL_SHAREHOLDERS = 290;
const FieldId FID_INTEREST_EXPENSES = 291;
const FieldId FID_INTEREST_INCOME = 292;
const FieldId FID_ISIN = 293;
const FieldId FID_ISSUER_NAME = 294;
const FieldId FID_LAST_12_MONTHS_EARNINGS = 295;
const FieldId FID_LAST_FISCAL_YEAR_EARNINGS = 296;
const FieldId FID_LAST_QUARTER_DATE = 297;
const FieldId FID_LAST_QUARTER_DATE_INCLUDED = 298;
const FieldId FID_LAST_QUARTER_EARNINGS = 299;
const FieldId FID_LAST_TRADING_DATE = 300;
const FieldId FID_LOCAL_CODE = 301;
const FieldId FID_LONG_TERM_DEBT = 302;
const FieldId FID_LONG_TERM_INVESTMENTS = 303;
const FieldId FID_LOWEST_SPREAD = 304;
const FieldId FID_MOVING_AVERAGE_100DAY = 305;
const FieldId FID_MOVING_AVERAGE_14DAY = 306;
const FieldId FID_MOVING_AVERAGE_21DAY = 307;
const FieldId FID_MOVING_AVERAGE_250DAY = 308;
const FieldId FID_MOVING_AVERAGE_50DAY = 309;
const FieldId FID_MOVING_AVERAGE_9DAY = 310;
const FieldId FID_NAME = 311;
const FieldId FID_NET_ACCRUED_DIVIDEND = 312;
const FieldId FID_NET_INCOME = 313;
const FieldId FID_NET_PROPERTY = 314;
const FieldId FID_NEXT_DIVIDEND_1 = 315;
const FieldId FID_NEXT_DIVIDEND_1_DATE = 316;
const FieldId FID_NEXT_DIVIDEND_1_STATUS = 317;
const FieldId FID_NEXT_DIVIDEND_2 = 318;
const FieldId FID_NEXT_DIVIDEND_2_DATE = 319;
const FieldId FID_NEXT_DIVIDEND_2_STATUS = 320;
const FieldId FID_NEXT_DIVIDEND_3 = 321;
const FieldId FID_NEXT_DIVIDEND_3_DATE = 322;
const FieldId FID_NEXT_DIVIDEND_3_STATUS = 323;
const FieldId FID_NEXT_DIVIDEND_4 = 324;
const FieldId FID_NEXT_DIVIDEND_4_DATE = 325;
const FieldId FID_NEXT_DIVIDEND_4_STATUS = 326;
const FieldId FID_NEXT_QUARTER_DATE = 327;
const FieldId FID_NUMBER_OF_QUARTERS_INCLUDED = 328;
const FieldId FID_OPTION_TYPE = 329;
const FieldId FID_OTHER_EXPENSES = 330;
const FieldId FID_OTHER_INCOME = 331;
const FieldId FID_PAR_VALUE_PER_UNIT = 332;
const FieldId FID_PAYMENT_DATE = 333;
const FieldId FID_PLANT_AND_EQUIPMENT = 334;
const FieldId FID_PREVIOUS_12_MONTHS_EARNINGS_PER_SHARE = 335;
const FieldId FID_PREVIOUS_7_QUARTERS_EARNINGS_PER_SHARE = 336;
const FieldId FID_PREVIOUS_CURRENT_DATE = 337;
const FieldId FID_PREVIOUS_DIVIDEND = 338;
const FieldId FID_PREVIOUS_DIVIDEND_DATE = 339;
const FieldId FID_PREVIOUS_FISCAL_YEAR_EARNINGS_PER_SHARE = 340;
const FieldId FID_PRIMARY_EXCHANGE = 341;
const FieldId FID_RATE_OF_RETURN_12MONTH = 342;
const FieldId FID_RATE_OF_RETURN_YEAR = 343;
const FieldId FID_RECORD_DATE = 344;
const FieldId FID_RETAINED_EARNINGS = 345;
const FieldId FID_RETURN_ON_CAPITAL = 346;
const FieldId FID_REVENUES_FROM_SALES = 347;
const FieldId FID_SELLING_AND_GENERAL_ADMIN_EXPENSES = 348;
const FieldId FID_SESSION_ID = 349;
const FieldId FID_SHAREHOLDERS = 350;
const FieldId FID_SHARES_AFTER = 351;
const FieldId FID_SHARES_BEFORE = 352;
const FieldId FID_SHARES_HELD_BY_INSTITUTIONS = 353;
const FieldId FID_SHARES_OUTSTANDING = 354;
const FieldId FID_SHARES_PER_CONTRACT = 355;
const FieldId FID_SIC_CODE = 356;
const FieldId FID_SPECIAL_DIVIDEND = 357;
const FieldId FID_SPECIAL_DIVIDEND_DATE = 358;
const FieldId FID_SPLIT_DATE = 359;
const FieldId FID_SPLIT_RATIO = 360;
const FieldId FID_STATE = 361;
const FieldId FID_STRIKE_PRICE = 362;
const FieldId FID_TICK_COUNT = 363;
const FieldId FID_TICK_PRICE = 364;
const FieldId FID_TICK_SIZE = 365;
const FieldId FID_TICK_TYPE = 366;
const FieldId FID_TIME = 367;
const FieldId FID_TOTAL_ASSETS = 368;
const FieldId FID_TOTAL_CASH = 369;
const FieldId FID_TOTAL_CASH_AMOUNT_PER_UNIT = 370;
const FieldId FID_UNALLOCATED = 371;
const FieldId FID_UNCHANGED = 372;
const FieldId FID_UP = 373;
const FieldId FID_VENDOR_CODE = 374;
const FieldId FID_VOLATILITY_01MONTH = 375;
const FieldId FID_VOLATILITY_02MONTH = 376;
const FieldId FID_VOLATILITY_03MONTH = 377;
const FieldId FID_VOLATILITY_04MONTH = 378;
const FieldId FID_VOLATILITY_05MONTH = 379;
const FieldId FID_VOLATILITY_06MONTH = 380;
const FieldId FID_VOLATILITY_07MONTH = 381;
const FieldId FID_VOLATILITY_08MONTH = 382;
const FieldId FID_VOLATILITY_09MONTH = 383;
const FieldId FID_VOLATILITY_10MONTH = 384;
const FieldId FID_VOLATILITY_11MONTH = 385;
const FieldId FID_VOLATILITY_12MONTH = 386;
const FieldId FID_VOLATILITY_20DAY = 387;
const FieldId FID_WEIGHT = 388;
const FieldId FID_YEAR_END_DATE = 389;
const FieldId FID_COMPANY_SYMBOL = 390;
const FieldId FID_COMPANY_TABLE_NO = 391;
const FieldId FID_CONSTITUENT_SYMBOL = 392;
const FieldId FID_CONSTITUENT_TABLE_NO = 393;
const FieldId FID_CONTEXT = 394;
const FieldId FID_CREATE_DATE = 395;
const FieldId FID_CUG_ID = 396;
const FieldId FID_DELAY_PERIOD = 397;
const FieldId FID_ENTITY_TYPE = 398;
const FieldId FID_EVENT_TYPE = 399;
const FieldId FID_FIELD_ID = 400;
const FieldId FID_FIELD_LENGTH = 401;
const FieldId FID_FIELD_ORDER = 402;
const FieldId FID_FIELD_TYPE = 403;
const FieldId FID_FUTURE_OPTION_ROOT_SYMBOL = 404;
const FieldId FID_FUTURE_OPTION_ROOT_TABLE_NO = 405;
const FieldId FID_FUTURE_ROOT_SYMBOL = 406;
const FieldId FID_FUTURE_ROOT_TABLE_NO = 407;
const FieldId FID_INDEX_NUMBER = 408;
const FieldId FID_INDEX_PROPERTIES = 409;
const FieldId FID_INDEX_SYMBOL = 410;
const FieldId FID_INDEX_TABLE_NO = 411;
const FieldId FID_INDEX_TYPE = 412;
const FieldId FID_LAST_UPDATE_DATE = 413;
const FieldId FID_LAST_UPDATE_TIME = 414;
const FieldId FID_LISTING_SYMBOL = 415;
const FieldId FID_LISTING_SYMBOL_LIST = 416;
const FieldId FID_LISTING_TABLE_NO = 417;
const FieldId FID_MESSAGE_TYPE = 418;
const FieldId FID_NAVIGATION_INDEX_NO = 419;
const FieldId FID_NAVIGATION_KEY_FIELD_ID = 420;
const FieldId FID_NAVIGATION_TABLE_NO = 421;
const FieldId FID_NEW_DESCRIPTION = 422;
const FieldId FID_NEW_ISIN = 423;
const FieldId FID_NEW_LISTING_PERMISSION_ID = 424;
const FieldId FID_NEW_LISTING_SYMBOL_LIST = 425;
const FieldId FID_NEW_SECURITY_SYMBOL = 426;
const FieldId FID_OLD_DESCRIPTION = 427;
const FieldId FID_OLD_ISIN = 428;
const FieldId FID_OLD_LISTING_PERMISSION_ID = 429;
const FieldId FID_OLD_LISTING_SYMBOL_LIST = 430;
const FieldId FID_OLD_SECURITY_SYMBOL = 431;
const FieldId FID_OPTION_DELIVERABLE_SYMBOL = 432;
const FieldId FID_OPTION_DELIVERABLE_TABLE_NO = 433;
const FieldId FID_OPTION_ROOT_SYMBOL = 434;
const FieldId FID_OPTION_ROOT_TABLE_NO = 435;
const FieldId FID_OUTPUT_KEY_FIELD_ID = 436;
const FieldId FID_OUTPUT_PERMISSION_ID_FIELD_ID = 437;
const FieldId FID_OUTPUT_TABLE_NO_FIELD_ID = 438;
const FieldId FID_PASSWORD = 439;
const FieldId FID_PERMISSION_BODY = 440;
const FieldId FID_PERMISSION_ID = 441;
const FieldId FID_PERMISSION_ID_0 = 442;
const FieldId FID_PERMISSION_ID_1 = 443;
const FieldId FID_PERMISSION_LEVEL_ID = 444;
const FieldId FID_PREVIOUS_SYMBOL = 445;
const FieldId FID_PROVIDER_NAME = 446;
const FieldId FID_RECORD_STATUS = 447;
const FieldId FID_RELATIONSHIP_ID = 448;
const FieldId FID_RESET_DATE = 449;
const FieldId FID_RESET_TIME = 450;
const FieldId FID_SECTOR_SYMBOL = 451;
const FieldId FID_SECTOR_TABLE_NO = 452;
const FieldId FID_SECURITY_SYMBOL = 453;
const FieldId FID_SECURITY_TABLE_NO = 454;
const FieldId FID_SOURCE_CONTEXT = 455;
const FieldId FID_SYMBOL = 456;
const FieldId FID_SYMBOL01 = 457;
const FieldId FID_SYMBOL02 = 458;
const FieldId FID_SYMBOL03 = 459;
const FieldId FID_SYMBOL04 = 460;
const FieldId FID_SYMBOL05 = 461;
const FieldId FID_SYMBOL06 = 462;
const FieldId FID_SYMBOL07 = 463;
const FieldId FID_SYMBOL08 = 464;
const FieldId FID_SYMBOL09 = 465;
const FieldId FID_SYMBOL10 = 466;
const FieldId FID_SYMBOL11 = 467;
const FieldId FID_SYMBOL12 = 468;
const FieldId FID_SYMBOL13 = 469;
const FieldId FID_SYMBOL14 = 470;
const FieldId FID_SYMBOL15 = 471;
const FieldId FID_SYMBOL16 = 472;
const FieldId FID_SYMBOL17 = 473;
const FieldId FID_SYMBOL18 = 474;
const FieldId FID_SYMBOL19 = 475;
const FieldId FID_SYMBOL20 = 476;
const FieldId FID_TABLE_ID = 477;
const FieldId FID_TABLE_NO = 478;
const FieldId FID_TABLE_TYPE = 479;
const FieldId FID_TABLE_VERSION = 480;
const FieldId FID_UNDERLYING_SYMBOL = 481;
const FieldId FID_UNDERLYING_TABLE_NO = 482;
const FieldId FID_UPDATE_ID = 483;
const FieldId FID_USER_BODY = 484;
const FieldId FID_USER_ID = 485;
const FieldId FID_USERNAME = 486;
const FieldId FID_LIMIT_HIGH_PRICE = 487;
const FieldId FID_LIMIT_LOW_PRICE = 488;
const FieldId FID_CURRENT_YIELD_TIME = 489;
const FieldId FID_CURRENT_YIELD_DATE = 490;
const FieldId FID_DIVIDEND_REINVEST_PRICE = 491;
const FieldId FID_CAP_GAINS_REINVEST_PRICE = 492;
const FieldId FID_DIVIDEND_REINVEST_PRICE_DATE = 493;
const FieldId FID_CAP_GAINS_REINVEST_PRICE_DATE = 494;
const FieldId FID_NAV_HIGH = 495;
const FieldId FID_NAV_HIGH_TIME = 496;
const FieldId FID_NAV_LOW = 497;
const FieldId FID_NAV_LOW_TIME = 498;
const FieldId FID_GENERAL_BUSINESS_EXPENSES_PLUS_COMMISSIONS = 499;
const FieldId FID_INTEREST_REVENUE = 500;
const FieldId FID_INVESTMENT_SECURITIES = 501;
const FieldId FID_NET_INTEREST_INCOME = 502;
const FieldId FID_NET_PROPERTY_PLANT_AND_EQUIPMENT = 503;
const FieldId FID_NON_INTEREST_EXPENSES = 504;
const FieldId FID_PAR_VALUE_OF_COMMON_STOCK = 505;
const FieldId FID_PREMIUMS_EARNED = 506;
const FieldId FID_PREMIUMS_EARNED_LESS_EXPENSES = 507;
const FieldId FID_SECURITIES = 508;
const FieldId FID_TOTAL_INTEREST_INCOME = 509;
const FieldId FID_TOTAL_INVESTED_ASSETS = 510;
const FieldId FID_TOTAL_NON_INTEREST_INCOME = 511;
const FieldId FID_TOTAL_NON_PREMIUM_INCOME = 512;
const FieldId FID_PREVIOUS_SETTLEMENT = 513;
const FieldId FID_7_DAY_YIELD_DATE = 514;
const FieldId FID_ANNUALIZED_7_DAY_YIELD_DATE = 515;
const FieldId FID_PREVIOUS_CUMULATIVE_PRICE = 516;
const FieldId FID_EX_MARKER = 517;
const FieldId FID_NEW_SYMBOL_LIST = 518;
const FieldId FID_OLD_SYMBOL_LIST = 519;
const FieldId FID_COMPOSITE_EXCHANGE = 520;
const FieldId FID_ANALYTICS_SYMBOL = 521;
const FieldId FID_ANALYTICS_TABLE_NO = 522;
const FieldId FID_STORY_DATE_TIME = 523;
const FieldId FID_HEADLINE = 524;
const FieldId FID_STORY_BODY = 525;
const FieldId FID_REPORT_DATE = 526;
const FieldId FID_INCOME_FROM_CONTINUING_OPERATIONS = 527;
const FieldId FID_ANNUAL_REVENUES_FROM_SALES = 528;
const FieldId FID_ANNUAL_GROSS_PROFITS = 529;
const FieldId FID_ANNUAL_SELLING_AND_GENERAL_ADMIN_EXPENSE = 530;
const FieldId FID_ANNUAL_DEPRECIATION_DEPLETION = 531;
const FieldId FID_ANNUAL_INTEREST_EXPENSE = 532;
const FieldId FID_ANNUAL_INCOME_BEFORE_TAX = 533;
const FieldId FID_ANNUAL_INCOME_FROM_CONTINUING_OPERATIONS = 534;
const FieldId FID_ANNUAL_NET_INCOME = 535;
const FieldId FID_ANNUAL_CURRENT_ASSETS = 536;
const FieldId FID_ANNUAL_NET_PROPERTY_PLANT_AND_EQUIPMENT = 537;
const FieldId FID_ANNUAL_TOTAL_ASSETS = 538;
const FieldId FID_ANNUAL_CURRENT_LIABILITIES = 539;
const FieldId FID_ANNUAL_TOTAL_LIABILITIES = 540;
const FieldId FID_ANNUAL_LONG_TERM_DEBT = 541;
const FieldId FID_ANNUAL_CAPITAL_STOCK = 542;
const FieldId FID_ANNUAL_ADDITIONAL_PAID_IN_CAPITAL = 543;
const FieldId FID_ANNUAL_RETAINED_EARNINGS = 544;
const FieldId FID_TOTAL_LIABILITIES = 545;
const FieldId FID_INDICATED_YIELD = 546;
const FieldId FID_PARTICIPANT = 547;
const FieldId FID_TIME_SERIES_TYPE = 548;
const FieldId FID_DATE_TIME = 549;
const FieldId FID_TIME_SERIES_SYMBOL = 550;
const FieldId FID_TIME_SERIES_TABLE_NO = 551;
const FieldId FID_SOURCE_PERMISSION_ID = 552;
const FieldId FID_NUMBER_OF_CONCURRENT_USERS = 553;
const FieldId FID_TARGET_SYMBOL = 554;
const FieldId FID_TARGET_TABLE_NO = 555;
const FieldId FID_PRICE_ADJUSTMENT = 556;
const FieldId FID_COMPOSITE_FLAG = 557;
const FieldId FID_SYMBOL_LIST = 558;
const FieldId FID_EXPIRATION_DATE_01 = 559;
const FieldId FID_EXPIRATION_DATE_02 = 560;
const FieldId FID_EXPIRATION_DATE_03 = 561;
const FieldId FID_EXPIRATION_DATE_04 = 562;
const FieldId FID_EXPIRATION_DATE_05 = 563;
const FieldId FID_EXPIRATION_DATE_06 = 564;
const FieldId FID_EXPIRATION_DATE_07 = 565;
const FieldId FID_EXPIRATION_DATE_08 = 566;
const FieldId FID_EXPIRATION_DATE_09 = 567;
const FieldId FID_EXPIRATION_DATE_10 = 568;
const FieldId FID_EXPIRATION_DATE_11 = 569;
const FieldId FID_EXPIRATION_DATE_12 = 570;
const FieldId FID_STRIKE_PRICE_01 = 571;
const FieldId FID_STRIKE_PRICE_02 = 572;
const FieldId FID_STRIKE_PRICE_03 = 573;
const FieldId FID_STRIKE_PRICE_04 = 574;
const FieldId FID_STRIKE_PRICE_05 = 575;
const FieldId FID_STRIKE_PRICE_06 = 576;
const FieldId FID_STRIKE_PRICE_07 = 577;
const FieldId FID_STRIKE_PRICE_08 = 578;
const FieldId FID_STRIKE_PRICE_09 = 579;
const FieldId FID_STRIKE_PRICE_10 = 580;
const FieldId FID_STRIKE_PRICE_11 = 581;
const FieldId FID_STRIKE_PRICE_12 = 582;
const FieldId FID_STRIKE_PRICE_13 = 583;
const FieldId FID_STRIKE_PRICE_14 = 584;
const FieldId FID_STRIKE_PRICE_15 = 585;
const FieldId FID_STRIKE_PRICE_16 = 586;
const FieldId FID_STRIKE_PRICE_17 = 587;
const FieldId FID_STRIKE_PRICE_18 = 588;
const FieldId FID_STRIKE_PRICE_19 = 589;
const FieldId FID_STRIKE_PRICE_20 = 590;
const FieldId FID_STRIKE_PRICE_21 = 591;
const FieldId FID_STRIKE_PRICE_22 = 592;
const FieldId FID_STRIKE_PRICE_23 = 593;
const FieldId FID_STRIKE_PRICE_24 = 594;
const FieldId FID_STRIKE_PRICE_25 = 595;
const FieldId FID_STRIKE_PRICE_26 = 596;
const FieldId FID_CONTRACT_SIZE = 597;
const FieldId FID_LOCAL_EXCHANGE = 598;
const FieldId FID_LOCAL_CALL_ROOT = 599;
const FieldId FID_LOCAL_PUT_ROOT = 600;
const FieldId FID_LOCAL_ROOT = 601;
const FieldId FID_MINIMUM_TICK = 602;
const FieldId FID_TRADING_DAY_START_TIME = 603;
const FieldId FID_TRADING_DAY_END_TIME = 604;
const FieldId FID_TRADING_DAYS_OF_WEEK = 605;
const FieldId FID_UNIT_OF_MEASURE = 606;
const FieldId FID_FUTURE_SYMBOL = 607;
const FieldId FID_FUTURE_TABLE_NO = 608;
const FieldId FID_FUTURE_OPTION_SYMBOL = 609;
const FieldId FID_FUTURE_OPTION_TABLE_NO = 610;
const FieldId FID_FUTURE_OPTION_EXPIRATION_SYMBOL = 611;
const FieldId FID_FUTURE_OPTION_EXPIRATION_TABLE_NO = 612;
const FieldId FID_HAS_DELIVERABLES = 613;
const FieldId FID_CATEGORY_CODE_LIST = 614;
const FieldId FID_UNIT_OF_MEASURE_CURRENCY = 615;
const FieldId FID_VOLUME_WEIGHTED_OPENING_PRICE = 616;
const FieldId FID_CONTRIBUTOR = 617;
const FieldId FID_BID6 = 618;
const FieldId FID_BID6_COUNT = 619;
const FieldId FID_BID6_SIZE = 620;
const FieldId FID_ASK6 = 621;
const FieldId FID_ASK6_COUNT = 622;
const FieldId FID_ASK6_SIZE = 623;
const FieldId FID_BID7 = 624;
const FieldId FID_BID7_COUNT = 625;
const FieldId FID_BID7_SIZE = 626;
const FieldId FID_ASK7 = 627;
const FieldId FID_ASK7_COUNT = 628;
const FieldId FID_ASK7_SIZE = 629;
const FieldId FID_BID8 = 630;
const FieldId FID_BID8_COUNT = 631;
const FieldId FID_BID8_SIZE = 632;
const FieldId FID_ASK8 = 633;
const FieldId FID_ASK8_COUNT = 634;
const FieldId FID_ASK8_SIZE = 635;
const FieldId FID_BID9 = 636;
const FieldId FID_BID9_COUNT = 637;
const FieldId FID_BID9_SIZE = 638;
const FieldId FID_ASK9 = 639;
const FieldId FID_ASK9_COUNT = 640;
const FieldId FID_ASK9_SIZE = 641;
const FieldId FID_BID10 = 642;
const FieldId FID_BID10_COUNT = 643;
const FieldId FID_BID10_SIZE = 644;
const FieldId FID_ASK10 = 645;
const FieldId FID_ASK10_COUNT = 646;
const FieldId FID_ASK10_SIZE = 647;
const FieldId FID_PE_RATIO = 648;
const FieldId FID_PERMISSION_ID_LIST = 649;
const FieldId FID_NEWS_MARKER = 650;
const FieldId FID_NEWS_COUNT = 651;
const FieldId FID_PREVIOUS_BID = 652;
const FieldId FID_PREVIOUS_ASK = 653;
const FieldId FID_PREVIOUS_QUOTE_DATE = 654;
const FieldId FID_PREVIOUS_CLOSE_DATE = 655;
const FieldId FID_PREVIOUS_SETTLEMENT_DATE = 656;
const FieldId FID_PREVIOUS_CUMULATIVE_VALUE = 657;
const FieldId FID_PREVIOUS_CUMULATIVE_VOLUME = 658;
const FieldId FID_PREVIOUS_CUMULATIVE_VOLUME_DATE = 659;
const FieldId FID_MARKET_MAKER_ID = 660;
const FieldId FID_USER_TYPE = 661;
const FieldId FID_USER_SCOPE = 662;
const FieldId FID_VOLATILITY_10DAY = 663;
const FieldId FID_VOLATILITY_30DAY = 664;
const FieldId FID_VOLATILITY_60DAY = 665;
const FieldId FID_VOLATILITY_90DAY = 666;
const FieldId FID_VOLATILITY_120DAY = 667;
const FieldId FID_VOLATILITY_150DAY = 668;
const FieldId FID_VOLATILITY_180DAY = 669;
const FieldId FID_START_DATE = 670;
const FieldId FID_UTC_OFFSET = 671;
const FieldId FID_EXCHANGE_HOLIDAY_LIST = 672;
const FieldId FID_IMBALANCE_BUY_VOLUME = 673;
const FieldId FID_IMBALANCE_SELL_VOLUME = 674;
const FieldId FID_IMBALANCE_VOLUME_TIME = 675;
const FieldId FID_HIGH_INDICATION_PRICE = 676;
const FieldId FID_LOW_INDICATION_PRICE = 677;
const FieldId FID_INDICATION_PRICE_TIME = 678;
const FieldId FID_TICK_UP = 679;
const FieldId FID_TICK_DOWN = 680;
const FieldId FID_TICK_UNCHANGED = 681;
const FieldId FID_DAY_UP = 682;
const FieldId FID_DAY_DOWN = 683;
const FieldId FID_DAY_UNCHANGED = 684;
const FieldId FID_SETTLEMENT_ALLOCATION = 685;
const FieldId FID_DST_OFFSET = 686;
const FieldId FID_SETTLEMENT_TYPE = 687;
const FieldId FID_FINANCIAL_STATUS = 688;
const FieldId FID_ORDER_COUNT = 689;
const FieldId FID_NEXT_DIVIDEND_1_DECLARE_DATE = 690;
const FieldId FID_NEXT_DIVIDEND_1_PAYMENT_DATE = 691;
const FieldId FID_NEXT_DIVIDEND_1_RECORD_DATE = 692;
const FieldId FID_TRADE_BUYER_ID = 693;
const FieldId FID_TRADE_SELLER_ID = 694;
const FieldId FID_FUNDAMENTAL_SYMBOL = 695;
const FieldId FID_FUNDAMENTAL_TABLE_NO = 696;
const FieldId FID_30_WEEK_MOVING_AVERAGE = 697;
const FieldId FID_5_DAY_MOVING_AVERAGE = 698;
const FieldId FID_5_YEAR_ANNUAL_REVENUE_GROWTH_RATE = 699;
const FieldId FID_5_YEAR_AVERAGE_PE = 700;
const FieldId FID_5_YEAR_HIGH_PRICE = 701;
const FieldId FID_5_YEAR_LOW_PRICE = 702;
const FieldId FID_ANNUAL_BASIC_NORMALIZED_NET_INCOME_PER_SHARE = 703;
const FieldId FID_ANNUAL_CASH_AND_EQUIVALENTS = 704;
const FieldId FID_ANNUAL_COMMON_PAR = 705;
const FieldId FID_ANNUAL_DIVIDENDS_PAID_PER_SHARE = 706;
const FieldId FID_ANNUAL_INTEREST_INCOME = 707;
const FieldId FID_ANNUAL_NET_CASH_FROM_FINANCING_ACTIVITIES = 708;
const FieldId FID_ANNUAL_NET_CASH_FROM_INVESTMENTS = 709;
const FieldId FID_ANNUAL_NET_CASH_FROM_OPERATIONS = 710;
const FieldId FID_ANNUAL_NET_CASH_NET_CHANGE_AND_CASH_EQUIVELENTS = 711;
const FieldId FID_ANNUAL_NET_FIXED_ASSETS = 712;
const FieldId FID_ANNUAL_NORMALIZED_CLOSE_PE_RATIO = 713;
const FieldId FID_ANNUAL_NORMALIZED_HIGH_PE_RATIO = 714;
const FieldId FID_ANNUAL_NORMALIZED_LOW_PE_RATIO = 715;
const FieldId FID_ANNUAL_NUMBER_OF_MONTHS_SINCE_LAST_REPORTING_PERIOD = 716;
const FieldId FID_ANNUAL_OTHER_INCOME = 717;
const FieldId FID_ANNUAL_OTHER_NON_CURRENT_ASSETS = 718;
const FieldId FID_ANNUAL_PREFERRED_STOCK_EQUITY = 719;
const FieldId FID_AVERAGE_DAILY_VOLUME_LAST_10_DAYS = 720;
const FieldId FID_AVERAGE_DAILY_VOLUME_LAST_52_WEEKS = 721;
const FieldId FID_BASIC_EPS_TOTAL = 722;
const FieldId FID_BASIC_NORMALIZED_NET_INCOME_PER_SHARE = 723;
const FieldId FID_CASH_AND_EQUIVALENTS = 724;
const FieldId FID_COMMON_PAR = 725;
const FieldId FID_CURRENT_MARKET_VALUE = 726;
const FieldId FID_CURRENT_PE_RATIO = 727;
const FieldId FID_DIVIDEND_YIELD_5_YEAR_AVERAGE = 728;
const FieldId FID_DIVIDENDS_PAID_PER_SHARE = 729;
const FieldId FID_DOLLAR_CHANGE_IN_12_MONTHS_EPS_VS_1_YEAR_AGO = 730;
const FieldId FID_INTERIM_ENDING_DATE = 731;
const FieldId FID_LATEST_REPORTED_SHARES_OUTSTANDING = 732;
const FieldId FID_MARKET_VALUE_AS_A_PERCENT_OF_REVENUES = 733;
const FieldId FID_NET_CASH_FROM_FINANCING_ACTIVITIES = 734;
const FieldId FID_NET_CASH_FROM_INVESTMENTS = 735;
const FieldId FID_NET_CASH_FROM_OPERATIONS = 736;
const FieldId FID_NET_CASH_NET_CHANGE_AND_CASH_EQUIVELENTS = 737;
const FieldId FID_NET_FIXED_ASSETS = 738;
const FieldId FID_NORMALIZED_CLOSE_PE_RATIO = 739;
const FieldId FID_NORMALIZED_HIGH_PE_RATIO = 740;
const FieldId FID_NORMALIZED_LOW_PE_RATIO = 741;
const FieldId FID_NUMBER_OF_MONTHS_SINCE_LAST_REPORTING_PERIOD = 742;
const FieldId FID_OTHER_NON_CURRENT_ASSETS = 743;
const FieldId FID_PREFERRED_STOCK_EQUITY = 744;
const FieldId FID_PE_RATIO_1_MONTH_AGO = 745;
const FieldId FID_PE_RATIO_52_WEEKS_AGO = 746;
const FieldId FID_QUARTERLY_INDICATOR = 747;
const FieldId FID_PRE_POST_MARKET_CUMULATIVE_VALUE = 748;
const FieldId FID_MAGAZINE = 749;
const FieldId FID_SUPPLIER = 750;

// Fixed field ids.
const FieldId FID_CONTRIBUTION_BASE = 5000;
const FieldId FID_MAX = 8191;

// ---------------------------------------------------------------------------------------------------------------------------------

/**
 *	@brief	Universal field helper class.
 */
class UniversalFieldHelper
{
public:
	/**
	 *	@brief	Default constructor.
	 */
	UniversalFieldHelper();

	/**
	 *	@brief	Constructor.
	 *
	 *	@param	pName the name of the field.
	 *	@param	pDescription a description of the field.
	 *	@param	type the type of the field.
	 */
	UniversalFieldHelper(const char * const pName, const char * const pDescription, const FieldType type, const size_t maxLength);

	const std::string			m_name;				///< The name of the field.
	const std::string			m_description;		///< A description of the field.
	const Activ::FieldType		m_type;				///< The type of the field.
	const size_t				m_maxLength;		///< The maximum length.
};

// ---------------------------------------------------------------------------------------------------------------------------------

/**
 *	@brief	Get the universal field helper.
 *
 *	@param	fieldId the field id.
 *
 *	@return	the universal field helper.
 */
ACTIV_FEED_COMMON_API const UniversalFieldHelper &GetUniversalFieldHelper(const FieldId fieldId);

/**
 *	@brief	Get the universal field name.
 *
 *	@param	fieldId the field id.
 *
 *	@return	the name of the field.
 */
ACTIV_FEED_COMMON_API std::string GetUniversalFieldName(const FieldId fieldId);

/**
 *	@brief	Get the universal field description.
 *
 *	@param	fieldId the field id.
 *
 *	@return	the description of the field.
 */
ACTIV_FEED_COMMON_API std::string GetUniversalFieldDescription(const FieldId fieldId);

/**
 *	@brief	Get the universal field type.
 *
 *	@param	fieldId the field id.
 *
 *	@return	the type of the field.
 */
ACTIV_FEED_COMMON_API FieldType GetUniversalFieldType(const FieldId fieldId);

/**
 *	@brief	Get the universal field maximum length.
 *
 *	@param	fieldId the field id.
 *
 *	@return	the maximum length of the field.
 */
ACTIV_FEED_COMMON_API size_t GetUniversalFieldMaxLength(const FieldId fieldId);

} // namespace Feed

} // namespace Activ

#endif // !defined(ACTIV_FEED_FIELD_IDS_H)
