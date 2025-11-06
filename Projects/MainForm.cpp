#include <vcl.h>
#pragma hdrstop
#include <windows.h>
#include "MainForm.h"
#include "DataModule1.h"
#include "AddOrderForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------

__fastcall TFormMain::TFormMain(TComponent* Owner)
    : TForm(Owner)
{
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::FormCreate(TObject *Sender)
{
    try
    {
		Sleep(100);

        if (!DM)
        {
            ShowMessage(L"Error: Data module is not initialised!");
            return;
        }

        if (!DM->ADOConnection1->Connected)
        {
            ShowMessage(L"Error: No connection to database!");
            return;
        }

        DM->LoadDetailsQuery();

        // Инициализируем оба грида
        SetupGridColumns();

        DBGrid1->PopupMenu = PopupMenu1;
        DBGrid2->PopupMenu = PopupMenu1;

        StatusBar1->SimpleText = L"Ready. Records number: " +
            IntToStr(DM->QueryDetails->RecordCount);
    }
    catch (Exception &e)
    {
        ShowMessage(L"Error while creating form: " + e.Message);
    }
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::SetupGridColumns()
{
    // --- Grid 1 ---
    DBGrid1->DataSource = nullptr;
    DBGrid1->Columns->Clear();
    DBGrid1->DataSource = DM->DataSourceDetails;
    Application->ProcessMessages();

    if (DBGrid1->Columns->Count > 0)
    {
		DBGrid1->Columns->Items[0]->Title->Caption = L"Detail number";
		DBGrid1->Columns->Items[0]->Width = 100;
		DBGrid1->Columns->Items[1]->Title->Caption = L"Detail Name";
		DBGrid1->Columns->Items[1]->Width = 150;
		DBGrid1->Columns->Items[2]->Title->Caption = L"Product Number";
		DBGrid1->Columns->Items[2]->Width = 100;
		DBGrid1->Columns->Items[3]->Title->Caption = L"Product Name";
		DBGrid1->Columns->Items[3]->Width = 150;
		DBGrid1->Columns->Items[4]->Title->Caption = L"In stock";
		DBGrid1->Columns->Items[4]->Width = 90;
		DBGrid1->Columns->Items[5]->Title->Caption = L"Needed";
		DBGrid1->Columns->Items[5]->Width = 90;
		DBGrid1->Columns->Items[6]->Title->Caption = L"Status";
		DBGrid1->Columns->Items[6]->Width = 80;
    }

    // --- Grid 2 (инициализация пустой структуры) ---
    SetupGridColumns2();
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::SetupGridColumns2()
{
    DBGrid2->DataSource = nullptr;
    DBGrid2->Columns->Clear();

    // Гарантируем, что QueryOrders имеет структуру
    bool wasActive = DM->QueryOrders->Active;
    if (!wasActive)
    {
        DM->QueryOrders->Close();
        DM->QueryOrders->Parameters->ParamByName("n_det")->Value = "NONEXISTENT";
        DM->QueryOrders->Open();
    }

    DBGrid2->DataSource = DM->DataSourceOrders;
    Application->ProcessMessages();

    if (!wasActive)
    {
        DM->QueryOrders->Close();
    }

    // Настройка заголовков
    if (DBGrid2->Columns->Count > 0)
    {
		DBGrid2->Columns->Items[0]->Title->Caption = L"№ order";
		DBGrid2->Columns->Items[0]->Width = 80;
		DBGrid2->Columns->Items[1]->Title->Caption = L"Date of order";
		DBGrid2->Columns->Items[1]->Width = 100;
		DBGrid2->Columns->Items[2]->Title->Caption = L"Customer";
		DBGrid2->Columns->Items[2]->Width = 120;
		DBGrid2->Columns->Items[3]->Title->Caption = L"Product";
		DBGrid2->Columns->Items[3]->Width = 120;
		DBGrid2->Columns->Items[4]->Title->Caption = L"Products number";
		DBGrid2->Columns->Items[4]->Width = 100;
		DBGrid2->Columns->Items[5]->Title->Caption = L"Details per 1 prod.";
		DBGrid2->Columns->Items[5]->Width = 120;
		DBGrid2->Columns->Items[6]->Title->Caption = L"Details needed";
		DBGrid2->Columns->Items[6]->Width = 120;
		DBGrid2->Columns->Items[7]->Title->Caption = L"Details in stock";
		DBGrid2->Columns->Items[7]->Width = 120;
		DBGrid2->Columns->Items[8]->Title->Caption = L"Status";
		DBGrid2->Columns->Items[8]->Width = 80;
    }
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::RebuildGrid2()
{
    DBGrid2->Visible = false;
    try
    {
        SetupGridColumns2();
    }
    __finally
    {
        DBGrid2->Visible = true;
    }
}

// Выделение строк цветом в первом гриде
void __fastcall TFormMain::DBGrid1DrawColumnCell(TObject *Sender,
    const TRect &Rect, int DataCol, TColumn *Column, TGridDrawState State)
{
    try
    {
        if (!DM->QueryDetails->IsEmpty())
        {
            int nalichie = DM->QueryDetails->FieldByName("kol_nalichie")->AsInteger;
            int trebuetsya = DM->QueryDetails->FieldByName("kol_trebuetsya")->AsInteger;

            // Если деталей не хватает - выделяем красным
            if (nalichie < trebuetsya)
            {
                if (!State.Contains(gdSelected))
                {
                    DBGrid1->Canvas->Brush->Color = clRed;
                    DBGrid1->Canvas->Font->Color = clWhite;
                    DBGrid1->Canvas->Font->Style = TFontStyles() << fsBold;
                }
            }

            DBGrid1->DefaultDrawColumnCell(Rect, DataCol, Column, State);
        }
    }
    catch (Exception &e)
    {
        // Игнорируем ошибки отрисовки
    }
}
//---------------------------------------------------------------------------

// Выделение строк цветом во втором гридее
void __fastcall TFormMain::DBGrid2DrawColumnCell(TObject *Sender,
    const TRect &Rect, int DataCol, TColumn *Column, TGridDrawState State)
{
    try
    {
        if (!DM->QueryOrders->IsEmpty())
        {
            String status = DM->QueryOrders->FieldByName("status")->AsString;

            // Если статус "ДЕФИЦИТ" - выделяем желтым
            if (status == "ДЕФИЦИТ")
            {
                if (!State.Contains(gdSelected))
                {
                    DBGrid2->Canvas->Brush->Color = clYellow;
                    DBGrid2->Canvas->Font->Color = clBlack;
                }
            }

            DBGrid2->DefaultDrawColumnCell(Rect, DataCol, Column, State);
        }
    }
    catch (Exception &e)
    {
        // Игнорируем ошибки отрисовки
    }
}
//---------------------------------------------------------------------------

// Кнопка "Добавить заказ"
void __fastcall TFormMain::ButtonAddOrderClick(TObject *Sender)
{
    TFormAddOrder *Form = new TFormAddOrder(this);
    try
    {
        Form->ShowModal();
    }
    __finally
    {
        delete Form;
    }
}
//---------------------------------------------------------------------------

// Кнопка "Обновить"
void __fastcall TFormMain::ButtonRefreshClick(TObject *Sender)
{
    try
    {
        DM->LoadDetailsQuery();
		StatusBar1->SimpleText = L"Data was updated. Records: " +
            IntToStr(DM->QueryDetails->RecordCount);
    }
    catch (Exception &e)
	{
		ShowMessage(L"Error while updating: " + e.Message);
    }
}
//---------------------------------------------------------------------------

// Контекстное меню - Добавить заказ
void __fastcall TFormMain::MenuAddOrderClick(TObject *Sender)
{
    ButtonAddOrderClick(Sender);
}
//---------------------------------------------------------------------------

// Контекстное меню - Обновить
void __fastcall TFormMain::MenuRefreshClick(TObject *Sender)
{
    ButtonRefreshClick(Sender);
}
//---------------------------------------------------------------------------

