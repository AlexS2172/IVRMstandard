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
if not exists(select * from DataInfo where dataInfoID = 1 and (keyValue = '3.46.173'  or (keyValue = '3.46.174') ))
	BEGIN
		select 'You can''t run this script, because you have not run script for previous version!' '3.46.174 error message:' 
		Select cast(keyValue as varchar(25)) as 'DB version', '3.46.174' as  'Version in script' from DataInfo where dataInfoID = 1
		INSERT INTO #tmpErrors (Error) SELECT -1 BEGIN TRANSACTION
	END
GO
SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO
/*DATA MODIFICATION SECTION*/
GO

-- Created by Victoria Prischepova Egar T  
-- 2005 - 12 - 23  

ALTER   PROC dbo.usp_RegUserAction_Save
	@LogOnOutTime datetime,
	@LogOnOut smallint,
	@DBLogin varchar(50),
	@ServerPath varchar(50),
	@CompanyName varchar(50)  
As  

    set @LogOnOutTime = GetDate()
    exec ETS_BACKOFFICE.dbo.RegUserAction @LogOnOutTime, @LogOnOut, @DBLogin, @ServerPath, @CompanyName
GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO


GO
--=============================================================================================
--change version of DB
--=============================================================================================
if not exists(select * from DataInfo where DataInfoID = 1 and keyValue = '3.46.174')
	begin
		update DataInfo set keyValue = '3.46.174' where dataInfoID = 1
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
	select 'DB VERSION WAS CHANGED TO 3.46.174' '3.46.174 update message:' 
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