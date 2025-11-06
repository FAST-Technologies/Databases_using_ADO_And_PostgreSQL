//---------------------------------------------------------------------------

#ifndef AddOrderFormH
#define AddOrderFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCTrls.hpp>
//---------------------------------------------------------------------------
class TFormAddOrder : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
    TLabel *Label7;
    TComboBox *ComboBoxIzdeliya;
    TComboBox *ComboBoxZakazchiki;
    TEdit *EditKolichestvo;
    TEdit *EditCena;
    TButton *ButtonOK;
	TButton *ButtonCancel;
	TMemo *MemoInfo;

	TCheckBox *CheckBoxDatePay;
	TDateTimePicker *DateTimePickerPay;
	TCheckBox *CheckBoxDateShip;
	TDateTimePicker *DateTimePickerShip;

    void __fastcall FormCreate(TObject *Sender);
    void __fastcall ButtonOKClick(TObject *Sender);
    void __fastcall ButtonCancelClick(TObject *Sender);
	void __fastcall ComboBoxIzdeliyaChange(TObject *Sender);
	void __fastcall CheckBoxDatePayClick(TObject *Sender);
	void __fastcall CheckBoxDateShipClick(TObject *Sender);
	void __fastcall EditCenaKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EditCenaKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private:	// User declarations
    void __fastcall LoadIzdeliya();
	void __fastcall LoadZakazchiki();
	void __fastcall ShowIzdelieInfo(String nIzd);
    bool __fastcall IsValidFloatChar(System::WideChar Key, String CurrentText);
    void __fastcall ShowInvalidCharMessage(System::WideChar Key);

public:		// User declarations
    __fastcall TFormAddOrder(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormAddOrder *FormAddOrder;
//---------------------------------------------------------------------------
#endif
