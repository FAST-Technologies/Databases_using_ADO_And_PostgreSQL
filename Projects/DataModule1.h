//---------------------------------------------------------------------------

#ifndef DataModule1H
#define DataModule1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <System.IniFiles.hpp>
//---------------------------------------------------------------------------
class TDM : public TDataModule
{
__published:	// IDE-managed Components
	TADOConnection *ADOConnection1;
	TADOQuery *QueryDetails;
	TADOQuery *QueryOrders;
	TDataSource *DataSourceDetails;
	TDataSource *DataSourceOrders;

    void __fastcall DataModuleCreate(TObject *Sender);
    void __fastcall QueryDetailsAfterScroll(TDataSet *DataSet);

private:	// User declarations
	String FSchemaName;

    struct TDatabaseConfig {
	   String Host;
	   String Port;
	   String Database;
	   String User;
	   String Password;
	   String Schema;
	   String Driver;
	   String Postgre_DSN;
       String SSL_Mode;
	} FDBConfig;

	bool __fastcall LoadDatabaseConfig();
    String __fastcall GetConfigFilePath();

public:		// User declarations
	__fastcall TDM(TComponent* Owner);

    void __fastcall ConnectToDatabase();
	void __fastcall LoadDetailsQuery();
    void __fastcall CheckDatabaseStructure();
	void __fastcall LoadOrdersForDetail(String detailNum);
    bool __fastcall AddNewOrder(String nIzd, String nCl, int kol, double cost, Variant datePay, Variant dayShip);
	int __fastcall GetAvailableDetails(String nDet, String nIzd);

    __property String SchemaName = {read=FSchemaName};
};
//---------------------------------------------------------------------------
extern PACKAGE TDM *DM;
//---------------------------------------------------------------------------
#endif
