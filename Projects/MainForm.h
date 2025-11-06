//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ComCtrls.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *Panel3;
	TDBGrid *DBGrid1;
	TDBGrid *DBGrid2;
	TLabel *Label1;
	TLabel *Label2;
	TButton *ButtonAddOrder;
	TButton *ButtonRefresh;
	TStatusBar *StatusBar1;
	TPopupMenu *PopupMenu1;
	TMenuItem *MenuAddOrder;
	TMenuItem *N1;
	TMenuItem *MenuRefresh;
	TDataSource *DataSourceDetails;
	TDataSource *DataSourceOrders;

	void __fastcall FormCreate(TObject *Sender);
    void __fastcall DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, TGridDrawState State);
    void __fastcall DBGrid2DrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, TGridDrawState State);
    void __fastcall ButtonAddOrderClick(TObject *Sender);
    void __fastcall ButtonRefreshClick(TObject *Sender);
    void __fastcall MenuAddOrderClick(TObject *Sender);
	void __fastcall MenuRefreshClick(TObject *Sender);
    void __fastcall SetupGridColumns2();

private:	// User declarations
	void __fastcall SetupGridColumns();

public:		// User declarations
	__fastcall TFormMain(TComponent* Owner);
    void __fastcall RebuildGrid2();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
