#ifndef FIX44_COLLATERALINQUIRYACK_H
#define FIX44_COLLATERALINQUIRYACK_H

#include "Message.h"

namespace FIX44
{

  class CollateralInquiryAck : public Message
  {
  public:
    CollateralInquiryAck() : Message(MsgType()) {}
    CollateralInquiryAck(const FIX::Message& m) : Message(m) {}
    CollateralInquiryAck(const Message& m) : Message(m) {}
    CollateralInquiryAck(const CollateralInquiryAck& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("BG"); }

    CollateralInquiryAck(
      const FIX::CollInquiryID& aCollInquiryID,
      const FIX::CollInquiryStatus& aCollInquiryStatus )
    : Message(MsgType())
    {
      set(aCollInquiryID);
      set(aCollInquiryStatus);
    }

    FIELD_SET(*this, FIX::CollInquiryID);
    FIELD_SET(*this, FIX::CollInquiryStatus);
    FIELD_SET(*this, FIX::CollInquiryResult);
    FIELD_SET(*this, FIX::TotNumReports);
    FIELD_SET(*this, FIX::NoPartyIDs);
    class NoPartyIDs: public FIX::Group
    {
    public:
    NoPartyIDs() : FIX::Group(453,448,FIX::message_order(448,447,452,802,0)) {}
      FIELD_SET(*this, FIX::PartyID);
      FIELD_SET(*this, FIX::PartyIDSource);
      FIELD_SET(*this, FIX::PartyRole);
      FIELD_SET(*this, FIX::NoPartySubIDs);
      class NoPartySubIDs: public FIX::Group
      {
      public:
      NoPartySubIDs() : FIX::Group(802,523,FIX::message_order(523,803,0)) {}
        FIELD_SET(*this, FIX::PartySubID);
        FIELD_SET(*this, FIX::PartySubIDType);
      };
    };
    FIELD_SET(*this, FIX::Account);
    FIELD_SET(*this, FIX::AccountType);
    FIELD_SET(*this, FIX::ClOrdID);
    FIELD_SET(*this, FIX::OrderID);
    FIELD_SET(*this, FIX::SecondaryOrderID);
    FIELD_SET(*this, FIX::SecondaryClOrdID);
    FIELD_SET(*this, FIX::Symbol);
    FIELD_SET(*this, FIX::SymbolSfx);
    FIELD_SET(*this, FIX::SecurityID);
    FIELD_SET(*this, FIX::SecurityIDSource);
    FIELD_SET(*this, FIX::Product);
    FIELD_SET(*this, FIX::CFICode);
    FIELD_SET(*this, FIX::SecurityType);
    FIELD_SET(*this, FIX::SecuritySubType);
    FIELD_SET(*this, FIX::MaturityMonthYear);
    FIELD_SET(*this, FIX::MaturityDate);
    FIELD_SET(*this, FIX::CouponPaymentDate);
    FIELD_SET(*this, FIX::IssueDate);
    FIELD_SET(*this, FIX::RepoCollateralSecurityType);
    FIELD_SET(*this, FIX::RepurchaseTerm);
    FIELD_SET(*this, FIX::RepurchaseRate);
    FIELD_SET(*this, FIX::Factor);
    FIELD_SET(*this, FIX::CreditRating);
    FIELD_SET(*this, FIX::InstrRegistry);
    FIELD_SET(*this, FIX::CountryOfIssue);
    FIELD_SET(*this, FIX::StateOrProvinceOfIssue);
    FIELD_SET(*this, FIX::LocaleOfIssue);
    FIELD_SET(*this, FIX::RedemptionDate);
    FIELD_SET(*this, FIX::StrikePrice);
    FIELD_SET(*this, FIX::StrikeCurrency);
    FIELD_SET(*this, FIX::OptAttribute);
    FIELD_SET(*this, FIX::ContractMultiplier);
    FIELD_SET(*this, FIX::CouponRate);
    FIELD_SET(*this, FIX::SecurityExchange);
    FIELD_SET(*this, FIX::Issuer);
    FIELD_SET(*this, FIX::EncodedIssuerLen);
    FIELD_SET(*this, FIX::EncodedIssuer);
    FIELD_SET(*this, FIX::SecurityDesc);
    FIELD_SET(*this, FIX::EncodedSecurityDescLen);
    FIELD_SET(*this, FIX::EncodedSecurityDesc);
    FIELD_SET(*this, FIX::Pool);
    FIELD_SET(*this, FIX::ContractSettlMonth);
    FIELD_SET(*this, FIX::CPProgram);
    FIELD_SET(*this, FIX::CPRegType);
    FIELD_SET(*this, FIX::DatedDate);
    FIELD_SET(*this, FIX::InterestAccrualDate);
    FIELD_SET(*this, FIX::NoSecurityAltID);
    class NoSecurityAltID: public FIX::Group
    {
    public:
    NoSecurityAltID() : FIX::Group(454,455,FIX::message_order(455,456,0)) {}
      FIELD_SET(*this, FIX::SecurityAltID);
      FIELD_SET(*this, FIX::SecurityAltIDSource);
    };
    FIELD_SET(*this, FIX::NoEvents);
    class NoEvents: public FIX::Group
    {
    public:
    NoEvents() : FIX::Group(864,865,FIX::message_order(865,866,867,868,0)) {}
      FIELD_SET(*this, FIX::EventType);
      FIELD_SET(*this, FIX::EventDate);
      FIELD_SET(*this, FIX::EventPx);
      FIELD_SET(*this, FIX::EventText);
    };
    FIELD_SET(*this, FIX::AgreementDesc);
    FIELD_SET(*this, FIX::AgreementID);
    FIELD_SET(*this, FIX::AgreementDate);
    FIELD_SET(*this, FIX::AgreementCurrency);
    FIELD_SET(*this, FIX::TerminationType);
    FIELD_SET(*this, FIX::StartDate);
    FIELD_SET(*this, FIX::EndDate);
    FIELD_SET(*this, FIX::DeliveryType);
    FIELD_SET(*this, FIX::MarginRatio);
    FIELD_SET(*this, FIX::SettlDate);
    FIELD_SET(*this, FIX::Quantity);
    FIELD_SET(*this, FIX::QtyType);
    FIELD_SET(*this, FIX::Currency);
    FIELD_SET(*this, FIX::NoLegs);
    FIELD_SET(*this, FIX::LegSymbol);
    FIELD_SET(*this, FIX::LegSymbolSfx);
    FIELD_SET(*this, FIX::LegSecurityID);
    FIELD_SET(*this, FIX::LegSecurityIDSource);
    FIELD_SET(*this, FIX::LegProduct);
    FIELD_SET(*this, FIX::LegCFICode);
    FIELD_SET(*this, FIX::LegSecurityType);
    FIELD_SET(*this, FIX::LegSecuritySubType);
    FIELD_SET(*this, FIX::LegMaturityMonthYear);
    FIELD_SET(*this, FIX::LegMaturityDate);
    FIELD_SET(*this, FIX::LegCouponPaymentDate);
    FIELD_SET(*this, FIX::LegIssueDate);
    FIELD_SET(*this, FIX::LegRepoCollateralSecurityType);
    FIELD_SET(*this, FIX::LegRepurchaseTerm);
    FIELD_SET(*this, FIX::LegRepurchaseRate);
    FIELD_SET(*this, FIX::LegFactor);
    FIELD_SET(*this, FIX::LegCreditRating);
    FIELD_SET(*this, FIX::LegInstrRegistry);
    FIELD_SET(*this, FIX::LegCountryOfIssue);
    FIELD_SET(*this, FIX::LegStateOrProvinceOfIssue);
    FIELD_SET(*this, FIX::LegLocaleOfIssue);
    FIELD_SET(*this, FIX::LegRedemptionDate);
    FIELD_SET(*this, FIX::LegStrikePrice);
    FIELD_SET(*this, FIX::LegStrikeCurrency);
    FIELD_SET(*this, FIX::LegOptAttribute);
    FIELD_SET(*this, FIX::LegContractMultiplier);
    FIELD_SET(*this, FIX::LegCouponRate);
    FIELD_SET(*this, FIX::LegSecurityExchange);
    FIELD_SET(*this, FIX::LegIssuer);
    FIELD_SET(*this, FIX::EncodedLegIssuerLen);
    FIELD_SET(*this, FIX::EncodedLegIssuer);
    FIELD_SET(*this, FIX::LegSecurityDesc);
    FIELD_SET(*this, FIX::EncodedLegSecurityDescLen);
    FIELD_SET(*this, FIX::EncodedLegSecurityDesc);
    FIELD_SET(*this, FIX::LegRatioQty);
    FIELD_SET(*this, FIX::LegSide);
    FIELD_SET(*this, FIX::LegCurrency);
    FIELD_SET(*this, FIX::LegPool);
    FIELD_SET(*this, FIX::LegDatedDate);
    FIELD_SET(*this, FIX::LegContractSettlMonth);
    FIELD_SET(*this, FIX::LegInterestAccrualDate);
    FIELD_SET(*this, FIX::NoLegSecurityAltID);
    class NoLegSecurityAltID: public FIX::Group
    {
    public:
    NoLegSecurityAltID() : FIX::Group(604,605,FIX::message_order(605,606,0)) {}
      FIELD_SET(*this, FIX::LegSecurityAltID);
      FIELD_SET(*this, FIX::LegSecurityAltIDSource);
    };
    FIELD_SET(*this, FIX::TradingSessionID);
    FIELD_SET(*this, FIX::TradingSessionSubID);
    FIELD_SET(*this, FIX::SettlSessID);
    FIELD_SET(*this, FIX::SettlSessSubID);
    FIELD_SET(*this, FIX::ClearingBusinessDate);
    FIELD_SET(*this, FIX::ResponseTransportType);
    FIELD_SET(*this, FIX::ResponseDestination);
    FIELD_SET(*this, FIX::Text);
    FIELD_SET(*this, FIX::EncodedTextLen);
    FIELD_SET(*this, FIX::EncodedText);
    FIELD_SET(*this, FIX::NoCollInquiryQualifier);
    class NoCollInquiryQualifier: public FIX::Group
    {
    public:
    NoCollInquiryQualifier() : FIX::Group(938,896,FIX::message_order(896,0)) {}
      FIELD_SET(*this, FIX::CollInquiryQualifier);
    };
    FIELD_SET(*this, FIX::NoExecs);
    class NoExecs: public FIX::Group
    {
    public:
    NoExecs() : FIX::Group(124,17,FIX::message_order(17,0)) {}
      FIELD_SET(*this, FIX::ExecID);
    };
    FIELD_SET(*this, FIX::NoTrades);
    class NoTrades: public FIX::Group
    {
    public:
    NoTrades() : FIX::Group(897,571,FIX::message_order(571,818,0)) {}
      FIELD_SET(*this, FIX::TradeReportID);
      FIELD_SET(*this, FIX::SecondaryTradeReportID);
    };
    FIELD_SET(*this, FIX::NoUnderlyings);
    class NoUnderlyings: public FIX::Group
    {
    public:
    NoUnderlyings() : FIX::Group(711,311,FIX::message_order(311,312,309,305,457,462,463,310,763,313,542,241,242,243,244,245,246,256,595,592,593,594,247,316,941,317,436,435,308,306,362,363,307,364,365,877,878,318,879,810,882,883,884,885,886,0)) {}
      FIELD_SET(*this, FIX::UnderlyingSymbol);
      FIELD_SET(*this, FIX::UnderlyingSymbolSfx);
      FIELD_SET(*this, FIX::UnderlyingSecurityID);
      FIELD_SET(*this, FIX::UnderlyingSecurityIDSource);
      FIELD_SET(*this, FIX::UnderlyingProduct);
      FIELD_SET(*this, FIX::UnderlyingCFICode);
      FIELD_SET(*this, FIX::UnderlyingSecurityType);
      FIELD_SET(*this, FIX::UnderlyingSecuritySubType);
      FIELD_SET(*this, FIX::UnderlyingMaturityMonthYear);
      FIELD_SET(*this, FIX::UnderlyingMaturityDate);
      FIELD_SET(*this, FIX::UnderlyingCouponPaymentDate);
      FIELD_SET(*this, FIX::UnderlyingIssueDate);
      FIELD_SET(*this, FIX::UnderlyingRepoCollateralSecurityType);
      FIELD_SET(*this, FIX::UnderlyingRepurchaseTerm);
      FIELD_SET(*this, FIX::UnderlyingRepurchaseRate);
      FIELD_SET(*this, FIX::UnderlyingFactor);
      FIELD_SET(*this, FIX::UnderlyingCreditRating);
      FIELD_SET(*this, FIX::UnderlyingInstrRegistry);
      FIELD_SET(*this, FIX::UnderlyingCountryOfIssue);
      FIELD_SET(*this, FIX::UnderlyingStateOrProvinceOfIssue);
      FIELD_SET(*this, FIX::UnderlyingLocaleOfIssue);
      FIELD_SET(*this, FIX::UnderlyingRedemptionDate);
      FIELD_SET(*this, FIX::UnderlyingStrikePrice);
      FIELD_SET(*this, FIX::UnderlyingStrikeCurrency);
      FIELD_SET(*this, FIX::UnderlyingOptAttribute);
      FIELD_SET(*this, FIX::UnderlyingContractMultiplier);
      FIELD_SET(*this, FIX::UnderlyingCouponRate);
      FIELD_SET(*this, FIX::UnderlyingSecurityExchange);
      FIELD_SET(*this, FIX::UnderlyingIssuer);
      FIELD_SET(*this, FIX::EncodedUnderlyingIssuerLen);
      FIELD_SET(*this, FIX::EncodedUnderlyingIssuer);
      FIELD_SET(*this, FIX::UnderlyingSecurityDesc);
      FIELD_SET(*this, FIX::EncodedUnderlyingSecurityDescLen);
      FIELD_SET(*this, FIX::EncodedUnderlyingSecurityDesc);
      FIELD_SET(*this, FIX::UnderlyingCPProgram);
      FIELD_SET(*this, FIX::UnderlyingCPRegType);
      FIELD_SET(*this, FIX::UnderlyingCurrency);
      FIELD_SET(*this, FIX::UnderlyingQty);
      FIELD_SET(*this, FIX::UnderlyingPx);
      FIELD_SET(*this, FIX::UnderlyingDirtyPrice);
      FIELD_SET(*this, FIX::UnderlyingEndPrice);
      FIELD_SET(*this, FIX::UnderlyingStartValue);
      FIELD_SET(*this, FIX::UnderlyingCurrentValue);
      FIELD_SET(*this, FIX::UnderlyingEndValue);
      FIELD_SET(*this, FIX::NoUnderlyingSecurityAltID);
      class NoUnderlyingSecurityAltID: public FIX::Group
      {
      public:
      NoUnderlyingSecurityAltID() : FIX::Group(457,458,FIX::message_order(458,459,0)) {}
        FIELD_SET(*this, FIX::UnderlyingSecurityAltID);
        FIELD_SET(*this, FIX::UnderlyingSecurityAltIDSource);
      };
    };
  };

}

#endif
