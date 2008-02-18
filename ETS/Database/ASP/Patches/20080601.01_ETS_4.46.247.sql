SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

/*PREPARATIONS FOR ERROR HANDLING*/
SET NOCOUNT ON
GO
IF EXISTS (SELECT * FROM tempdb..sysobjects WHERE id=OBJECT_ID('tempdb..#tmpErrors')) DROP TABLE #tmpErrors
GO
CREATE TABLE #tmpErrors (Error int)
GO
SET XACT_ABORT ON
GO

/*SCRIPTS MAIN SECTION*/
BEGIN TRANSACTION
GO
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE
GO
/*CHECKING of DB VERSION*/
if not exists(select * from DataInfo where dataInfoID = 1 and (keyValue = '4.46.246' or (keyValue = '4.46.247') ))
BEGIN
	select 'You can''t run this script, because you have not run script for previous version!' '4.46.247 error message:' 
	Select cast(keyValue as varchar(25)) as 'DB version', '4.46.247' as  'Version in script' from DataInfo where dataInfoID = 1
	INSERT INTO #tmpErrors (Error) SELECT -1 BEGIN TRANSACTION
END
GO

/*DATA MODIFICATION SECTION*/
/*  ExpiryOV inserting */

if NOT Exists (select * from INFORMATION_SCHEMA.COLUMNS where TABLE_NAME='CustomStrikeSkewPoint' and COLUMN_NAME='ExpiryOV')
ALTER TABLE [CustomStrikeSkewPoint]
	ADD [ExpiryOV] [datetime] NULL 

--=====================================================================================================
SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO


ALTER  PROC [dbo].[usp_AspEodUpdateMarketStructure_DefaultIVs_Execute]
		@iWithTran int = null
AS  
 -------------------------------------------------  
 set nocount on  
 -------------------------------------------------  
 declare @error int set @error = 0  
  
 declare @vcTranName varchar(32) if @iWithTran is not null set @vcTranName = replace(cast(newid() as varchar(36)), '-', '')  
 if @iWithTran is not null begin tran @vcTranName  
  
 -------------------------------------------------  
 -- default IVs  
 insert into VolaSurfaceData (contractID, isDefaultSurface, baseUnderlinePrice)  
 select c.contractID,
	1,
	isnull(cp.priceClose, 0)  
 from Contract c  
 inner join ContractPrice cp on cp.contractID = c.contractID  
 left join VolaSurfaceData vsd on vsd.contractID = c.contractID and vsd.isDefaultSurface = 1 and vsd.actionID < 3  
 where c.actionID < 3
	and c.contractTypeID in (1,2,6)
	and vsd.contractID is null
  
 if @@error != 0  
 begin  
  exec usp_AspEodMsUpdateLog_Add @vcEvent = 'Updating default IV surface: Fail to create missed IV surfaces', @iErrorCode = @@error  
  set @error = -1  
  if @iWithTran is not null rollback tran @vcTranName  
  goto finish  
 end  
  
  
 insert into CustomStrikeSkewPoint (volaSurfaceDataID, type, strike, volatility, isBasePoint, expiryDate, expiryOV)  
 select vsd.volaSurfaceDataID,  
	eod_cssp.type,
	eod_cssp.strike,
	eod_cssp.volatility,
	eod_cssp.isBasePoint,
	eod_cssp.expiryDate,
	eod_cssp.expiryOV
  
 from ETS_ASP_EOD.dbo.CustomStrikeSkewPoint eod_cssp  
  inner join ETS_ASP_EOD.dbo.VolaSurfaceData eod_vsd on eod_vsd.volaSurfaceDataID = eod_cssp.volaSurfaceDataID  
  inner join EodUnderlyingMap eod_um on eod_um.eodContractID = eod_vsd.contractID  
  inner join VolaSurfaceData vsd on vsd.contractID = eod_um.contractID  
  left join CustomStrikeSkewPoint cssp on cssp.volaSurfaceDataID = vsd.volaSurfaceDataID
	and abs(cssp.strike - eod_cssp.strike) < 0.009
	and cssp.type = eod_cssp.type
	and abs(datediff( d, cssp.expiryDate, eod_cssp.expiryDate )) < 2
	and cssp.actionID < 3
 where cssp.CustomStrikeSkewPointID is null
	and eod_cssp.actionID < 3
OPTION (MAXDOP 1)
  
 if @@error != 0  
 begin  
  exec usp_AspEodMsUpdateLog_Add @vcEvent = 'Updating default IV surface: Fail to add new IV points', @iErrorCode = @@error  
  set @error = -1  
  if @iWithTran is not null rollback tran @vcTranName  
  goto finish  
 end  
  
 update CustomStrikeSkewPoint
 set type = eod_cssp.type,
     strike = eod_cssp.strike,
     volatility = eod_cssp.volatility,
     isBasePoint = eod_cssp.isBasePoint,
     expiryDate = eod_cssp.expiryDate,
     expiryOV = eod_cssp.expiryOV
 from ETS_ASP_EOD.dbo.CustomStrikeSkewPoint eod_cssp  
  inner join ETS_ASP_EOD.dbo.VolaSurfaceData eod_vsd on eod_vsd.volaSurfaceDataID = eod_cssp.volaSurfaceDataID  
  inner join EodUnderlyingMap eod_um on eod_um.eodContractID = eod_vsd.contractID  
  inner join VolaSurfaceData vsd on vsd.contractID = eod_um.contractID  
  inner join CustomStrikeSkewPoint cssp on cssp.volaSurfaceDataID = vsd.volaSurfaceDataID  
	and abs(cssp.strike - eod_cssp.strike) < 0.009  
	and cssp.type = eod_cssp.type  
	and abs(datediff( d, cssp.expiryDate, eod_cssp.expiryDate )) < 2   
	and cssp.actionID < 3  
 where eod_cssp.actionID < 3
	and eod_cssp.volatility > -100.0 --IV's mark 'not calculated'  
	and (vsd.IsManualVol is NULL OR vsd.IsManualVol != 1)  
  
  
 if @@error != 0  
 begin  
  exec usp_AspEodMsUpdateLog_Add @vcEvent = 'Updating default IV surface: Fail to update IV points', @iErrorCode = @@error  
  set @error = -1  
  if @iWithTran is not null rollback tran @vcTranName  
  goto finish  
 end  
  
 create table #CustStrikeskewpoint (customstrikeskewpoint int)  
 insert into #CustStrikeskewpoint (customstrikeskewpoint) --values   
 select csp.customStrikeSkewPointID from contract c   
  inner join VolaSurfaceData vsd on vsd.contractID= c.ContractID  
  inner join customstrikeskewpoint csp on vsd.volaSurfaceDataID = csp.volaSurfaceDataID   
 where   
   (not exists(select top 1 1 from optionRoot orr where orr.underlyingID = c.ContractID and orr.ActionId < 3) and 
    not exists(select top 1 1 from futureRoot orr where orr.underlyingID = c.ContractID) )
   and c.ActionId < 3
   and  c.contractTypeId in (1,2,6)  
  group by csp.customStrikeSkewPointID  


 delete from customstrikeskewpoint where customStrikeSkewPointID in (  
	select customstrikeskewpoint from #CustStrikeskewpoint  
 )  
/*  
 ----------------------------------------------------------------------------------  
 delete from customstrikeskewpoint where customStrikeSkewPointID in (  
 --update customstrikeskewpoint set ActionId = 3 where customStrikeSkewPointID in (   
  select csp.customStrikeSkewPointID from contract c   
   inner join VolaSurfaceData vsd on vsd.contractID = c.ContractID  
   inner join customstrikeskewpoint csp on vsd.volaSurfaceDataID = csp.volaSurfaceDataID   
  where   
   not exists(select top 1 1 from optionRoot orr where orr.ActionId < 3 and orr.underlyingID = c.ContractID)
   and c.ActionId < 3
   and  c.contractTypeId in (1,2,6)
  group by csp.customStrikeSkewPointID
 )  
*/  
 delete from customstrikeskewpoint where customStrikeSkewPointID in (  
 --update customstrikeskewpoint set ActionId = 3 where customStrikeSkewPointID in (   
  select csp.customStrikeSkewPointID from contract c   
   inner join VolaSurfaceData vsd on vsd.contractID= c.ContractID  
   inner join customstrikeskewpoint csp on vsd.volaSurfaceDataID = csp.volaSurfaceDataID and  datediff(d,csp.actionDate, getDate()) >0  
  where   
   exists(select top 1 1 from optionRoot orr where orr.ActionId<3 and orr.underlyingID =c.ContractID)  
   and c.ActionId <3  
   and  c.contractTypeId in (1,2,6)  
   and c.ContractID  not in (    
    select  tt.contractID from (  
     select t.contractID, t.symbol, max(t.maxDate) as md from (  
      select  c.contractID, c.symbol, csp.actionDate as maxDate from contract c   
       inner join VolaSurfaceData vsd on vsd.contractID= c.ContractID  
       inner join customstrikeskewpoint csp on vsd.volaSurfaceDataID = csp.volaSurfaceDataID --and csp.expiryID> 66  
      where   
       (exists(select top 1 1 from optionRoot orr where orr.underlyingID = c.ContractID and orr.ActionId < 3) or
        exists(select top 1 1 from futureRoot orr where orr.underlyingID = c.ContractID)  
       )  
       and c.ActionId < 3
       and  c.contractTypeId in (1,2,6)
      group by  c.ContractID, c.symbol, csp.actionDate) T
     group by t.contractID, t.symbol  
    ) TT where datediff(d,TT.md, getDate())<>0)  
    group by csp.customStrikeSkewPointID  
  )  
  
  
 if @iWithTran is not null commit tran @vcTranName  
   
finish:  
 return @error  
  
  

GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO


--================================================================================================
SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO

ALTER PROC dbo.usp_CustomStrikeSkewPoint_Get 
            @iCustomStrikeSkewPointID INT = NULL, 
            @iVolaSurfaceDataID INT = NULL,
            @iType INT = NULL,
            @dtExpDate DATETIME = NULL
AS
            ------------------------------------------------
            SET NOCOUNT ON
            ------------------------------------------------
            DECLARE @error INT     SET @error = -1
 
            -- Sharky: faster request for special parameters' set
            IF @dtExpDate IS NULL AND @iCustomStrikeSkewPointID IS NULL
                        AND @iVolaSurfaceDataID IS NOT NULL AND @iType IS NOT NULL
            BEGIN
                        SELECT 
                                   CSSP.customStrikeSkewPointID AS iCustomStrikeSkewPointID,
                                   CSSP.volaSurfaceDataID AS iVolaSurfaceDataID,
                                   CSSP.strike AS fStrike, 
                                   CSSP.type AS iType,
                                   CSSP.volatility AS fVolatility,
                                   CSSP.ExpiryOV AS dtExpDate,
                                   CSSP.isBasePoint AS iIsBasePoint
                        FROM CustomStrikeSkewPoint CSSP WITH(INDEX = IX_CustomStrikeSkewPoint_volaSurfaceDataID_type_actionID, NOLOCK)
                        WHERE CSSP.volaSurfaceDataID = @iVolaSurfaceDataID
                                   AND CSSP.type = @iType
                                   AND CSSP.actionID < 3
            END
            ELSE
            BEGIN
                        SELECT 
                                   CSSP.customStrikeSkewPointID AS iCustomStrikeSkewPointID,
                                   CSSP.volaSurfaceDataID AS iVolaSurfaceDataID,
                                   CSSP.strike AS fStrike, 
                                   CSSP.type AS iType,
                                   CSSP.volatility AS fVolatility,
                                   CSSP.expiryOV AS dtExpDate,
                                   CSSP.isBasePoint AS iIsBasePoint 
                        FROM CustomStrikeSkewPoint CSSP WITH(INDEX = IX_CustomStrikeSkewPoint_volaSurfaceDataID_type_actionID, NOLOCK)
                        WHERE customStrikeSkewPointID = ISNULL(@iCustomStrikeSkewPointID, customStrikeSkewPointID) AND
                                   CSSP.volaSurfaceDataID = ISNULL(@iVolaSurfaceDataID, CSSP.volaSurfaceDataID) AND
                                   type = ISNULL(@iType, type) AND
                                   CSSP.expiryOV = ISNULL(@dtExpDate, CSSP.expiryOV)
				   AND CSSP.actionID < 3
            END

            SET @error = @@ERROR
            RETURN(@error)




GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

--=============================================================================================
--change version of DB
--=============================================================================================
if not exists(select * from DataInfo where DataInfoID = 1 and keyValue = '4.46.247')
	begin
		update DataInfo set keyValue = '4.46.247' where dataInfoID = 1
	end
GO
/* RESULTS ANALYTHING */
IF @@ERROR <> 0 ROLLBACK TRANSACTION
GO
IF @@TRANCOUNT = 0 BEGIN INSERT INTO #tmpErrors (Error) SELECT 1 BEGIN TRANSACTION END
GO
IF EXISTS (SELECT * FROM #tmpErrors)
BEGIN
	ROLLBACK TRANSACTION
	--SELECT * FROM #tmpErrors
END
GO
IF @@TRANCOUNT > 0 
BEGIN
	select 'DB VERSION WAS CHANGED TO 4.46.247' '4.46.247 update message:' 
	select 'The database update succeeded'

	COMMIT TRANSACTION
END
	ELSE select 'The database update failed'
GO
DROP TABLE #tmpErrors
GO
