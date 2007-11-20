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
if not exists(select * from DataInfo where dataInfoID = 1 and (keyValue = '3.46.235'  or (keyValue = '3.46.236') ))
	BEGIN
		select 'You can''t run this script, because you have not run script for previous version!' '3.46.236 error message:' 
		Select cast(keyValue as varchar(25)) as 'DB version', '3.46.236' as  'Version in script' from DataInfo where dataInfoID = 1
		INSERT INTO #tmpErrors (Error) SELECT -1 BEGIN TRANSACTION
	END
GO
---------------------------------------------------------------------------------------------------------------------------
--now when custom stream loaded for index - div type automaticly state to CustomStream
ALTER     procedure dbo.usp_BO_DividentsImport

  @vXMLData ntext  
As  

  DECLARE @idoc int  
  EXEC sp_xml_preparedocument @idoc OUTPUT, @vXMLData  

  select V_XML.Symbol As SymbolsNotExist  
           from ( SELECT * FROM       OPENXML (@idoc, '/Dividents/Divs',1)   
   WITH (Symbol[varchar](255) )      
               ) V_XML  
   where V_XML.Symbol COLLATE SQL_Latin1_General_CP1_CI_AS not in ( select symbol from contract where ContractTypeID in (1, 2) and actionID < 3 )  


  begin Tran
     update Stock 
     Set  
	  divDateCustom = Upd.DivDate,
	  isDivCustom = 2
     from
     (
        select Cn.contractid As CnId , V_XML.DivDate As DivDate , V_XML.DivAmt As DivAmt
             from ( SELECT * FROM       OPENXML (@idoc, '/Dividents/Divs',1)   
        WITH (Symbol[varchar](255) , DivDate[Datetime] , DivAmt[float] )      
               ) V_XML  
        join Contract Cn on ( Cn.Symbol = V_XML.Symbol COLLATE SQL_Latin1_General_CP1_CI_AS  and Cn.contractTypeID in (1,2,4) and Cn.actionID<3  ) 
     ) Upd 
     where Upd.CnId = Stockid
    
     if @@Error <> 0
     begin
        rollback
	Return -1
     end

     update [Index]
     Set  
	  isDivCustom = 2
     from
     (
        select Cn.contractid As CnId
             from ( SELECT * FROM       OPENXML (@idoc, '/Dividents/Divs',1)   
        WITH (Symbol[varchar](255) , DivDate[Datetime] , DivAmt[float] )      
               ) V_XML  
        join Contract Cn on ( Cn.Symbol = V_XML.Symbol COLLATE SQL_Latin1_General_CP1_CI_AS  and Cn.contractTypeID in (1,2,4) and Cn.actionID<3  ) 
     ) Upd 
     where Upd.CnId = Indexid
    
     if @@Error <> 0
     begin
        rollback
	Return -1
     end

   delete CustomDividend   
    where Stockid  in 
	(  select Cn.contractid As StockID 
             from ( SELECT * FROM       OPENXML (@idoc, '/Dividents/Divs',1)   
           WITH (Symbol[varchar](255) , DivDate[Datetime] , DivAmt[float] )      
               ) V_XML  
          join Contract Cn on ( Cn.Symbol = V_XML.Symbol COLLATE SQL_Latin1_General_CP1_CI_AS  and Cn.contractTypeID in (1,2,4) and Cn.actionID<3  ) 
	) 

   insert into dbo.CustomDividend
     ( [StockID], [DivAmnt], [DivYtes] )
--     Values
     (
        select Cn.contractid As StockID , V_XML.DivAmt As DivAmnt , V_XML.DivDate As DivYtes
             from ( SELECT * FROM       OPENXML (@idoc, '/Dividents/Divs',1)   
        WITH (Symbol[varchar](255) , DivDate[Datetime] , DivAmt[float] )      
               ) V_XML  
        join Contract Cn on ( Cn.Symbol = V_XML.Symbol COLLATE SQL_Latin1_General_CP1_CI_AS  and Cn.contractTypeID in (1,2,4) and Cn.actionID<3  ) 
      )
    
     if @@Error <> 0
     begin
        rollback
	Return -1
     end

  commit
  EXEC sp_xml_removedocument @idoc   
  Return 0

GO
---------------------------------------------------------------------------------------------------------------------------
GO
if not exists(select * from DataInfo where DataInfoID = 1 and keyValue = '3.46.236')
	begin
		update DataInfo set keyValue = '3.46.236' where dataInfoID = 1
	end
GO

/* RESULTS ANALYTHING */
IF @@ERROR <> 0 AND @@TRANCOUNT > 0  ROLLBACK TRANSACTION
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
	select 'DB VERSION WAS CHANGED TO 3.46.236' '3.46.236 update message:' 
	select 'The database update succeeded'

	COMMIT TRANSACTION
END
	ELSE select 'The database update failed'
GO
DROP TABLE #tmpErrors
GO


SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO




