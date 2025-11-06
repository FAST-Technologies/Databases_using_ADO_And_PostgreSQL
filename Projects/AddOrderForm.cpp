//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <windows.h>
#include <math.h>

#include "AddOrderForm.h"
#include "DataModule1.h"
#include <Data.Win.ADODB.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormAddOrder *FormAddOrder;
//---------------------------------------------------------------------------
__fastcall TFormAddOrder::TFormAddOrder(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormAddOrder::FormCreate(TObject *Sender)
{
    try
    {
        LoadIzdeliya();
        LoadZakazchiki();

        // Значения по умолчанию
        EditKolichestvo->Text = "1";
		EditCena->Text = "0.00";

		DateTimePickerPay->Date = Date();
		DateTimePickerShip->Date = Date();

		// По умолчанию даты отключены
		CheckBoxDatePay->Checked = false;
		CheckBoxDateShip->Checked = false;
		DateTimePickerPay->Enabled = false;
		DateTimePickerShip->Enabled = false;
	}
    catch (Exception &e)
    {
        ShowMessage("Ошибка при создании формы: " + e.Message);
    }
}

//---------------------------------------------------------------------------
// Обработчик для checkbox даты оплаты
void __fastcall TFormAddOrder::CheckBoxDatePayClick(TObject *Sender)
{
	DateTimePickerPay->Enabled = CheckBoxDatePay->Checked;
	if (CheckBoxDatePay->Checked) {
		DateTimePickerPay->Date = Date();
	}
}

//---------------------------------------------------------------------------
// Обработчик для checkbox даты отправки
void __fastcall TFormAddOrder::CheckBoxDateShipClick(TObject *Sender)
{
	DateTimePickerShip->Enabled = CheckBoxDateShip->Checked;
	if (CheckBoxDateShip->Checked) {
		DateTimePickerShip->Date = Date();
	}
}

//---------------------------------------------------------------------------
// Загрузка списка изделий
void __fastcall TFormAddOrder::LoadIzdeliya()
{
    TADOQuery *Query = new TADOQuery(this);
    try
    {
        Query->Connection = DM->ADOConnection1;
		Query->SQL->Add("SELECT n_izd, name, town FROM " + DM->SchemaName + ".j j ORDER BY n_izd");
        Query->Open();

        ComboBoxIzdeliya->Items->Clear();
        ComboBoxIzdeliya->Items->Add("-- Выберите изделие --");

        while (!Query->Eof)
        {
            String item = Query->FieldByName("n_izd")->AsString.Trim() + " - " +
                         Query->FieldByName("name")->AsString.Trim() + " (" +
                         Query->FieldByName("town")->AsString.Trim() + ")";
            ComboBoxIzdeliya->Items->Add(item);
            Query->Next();
        }

        ComboBoxIzdeliya->ItemIndex = 0;
        Query->Close();
        delete Query;
    }
    catch (Exception &e)
    {
        delete Query;
        throw Exception("Ошибка загрузки изделий: " + e.Message);
	}
}
//---------------------------------------------------------------------------
// Загрузка списка заказчиков
void __fastcall TFormAddOrder::LoadZakazchiki()
{
    TADOQuery *Query = new TADOQuery(this);
    try
    {
        Query->Connection = DM->ADOConnection1;
		Query->SQL->Add("SELECT n_cl, name, town FROM " + DM->SchemaName + ".c c ORDER BY n_cl");
        Query->Open();

        ComboBoxZakazchiki->Items->Clear();
        ComboBoxZakazchiki->Items->Add("-- Выберите заказчика --");

        while (!Query->Eof)
        {
            String item = Query->FieldByName("n_cl")->AsString.Trim() + " - " +
                         Query->FieldByName("name")->AsString.Trim() + " (" +
                         Query->FieldByName("town")->AsString.Trim() + ")";
            ComboBoxZakazchiki->Items->Add(item);
            Query->Next();
        }

        ComboBoxZakazchiki->ItemIndex = 0;
        Query->Close();
        delete Query;
    }
    catch (Exception &e)
    {
        delete Query;
        throw Exception("Ошибка загрузки заказчиков: " + e.Message);
    }
}
//---------------------------------------------------------------------------

// Отображение информации об изделии
void __fastcall TFormAddOrder::ComboBoxIzdeliyaChange(TObject *Sender)
{
	if (ComboBoxIzdeliya->ItemIndex > 0)
    {
        String selected = ComboBoxIzdeliya->Text;
		String nIzd = selected.SubString(1, selected.Pos(" - ") - 1).Trim();
        ShowIzdelieInfo(nIzd);

        // Получаем рекомендованную цену
        TADOQuery *Query = new TADOQuery(this);
        try
        {
            Query->Connection = DM->ADOConnection1;
            Query->SQL->Add(
				"SELECT cost FROM " + DM->SchemaName + ".v v "
                "WHERE n_izd = :n_izd "
                "ORDER BY date_begin DESC "
                "LIMIT 1"
            );
            Query->Parameters->ParamByName("n_izd")->Value = nIzd;
			Query->Open();

            if (!Query->IsEmpty())
            {
                EditCena->Text = Query->FieldByName("cost")->AsString;
            }

            Query->Close();
            delete Query;
        }
        catch (...)
        {
			delete Query;
		}
	}
	else
	{
		MemoInfo->Lines->Clear();
	}
}
//---------------------------------------------------------------------------

// Показать информацию об изделии (необходимые детали)
//---------------------------------------------------------------------------
void __fastcall TFormAddOrder::ShowIzdelieInfo(String nIzd)
{
    TADOQuery *Query = new TADOQuery(this);
    try
    {
        Query->Connection = DM->ADOConnection1;

        // УПРОЩЕННЫЙ запрос - сначала убедимся что он работает
        Query->SQL->Add(
            "SELECT p.n_det, p.name, q.kol "
            "FROM " + DM->SchemaName + ".q q "
            "INNER JOIN " + DM->SchemaName + ".p p ON q.n_det = p.n_det "
            "WHERE q.n_izd = :n_izd "
            "ORDER BY p.n_det ASC"
        );

        Query->Parameters->ParamByName("n_izd")->Value = nIzd;
        Query->Open();

        MemoInfo->Lines->Clear();
        MemoInfo->Lines->Add("Необходимые детали для изделия " + nIzd + ":");
        MemoInfo->Lines->Add("-------------------------------------------");

        while (!Query->Eof)
        {
            String det = Query->FieldByName("n_det")->AsString.Trim();
            String name = Query->FieldByName("name")->AsString.Trim();
            int kol = Query->FieldByName("kol")->AsInteger;

            String line = det + " (" + name + "): " + IntToStr(kol) + " шт.";
            MemoInfo->Lines->Add(line);

            Query->Next();
        }

        Query->Close();
        delete Query;
    }
    catch (Exception &e)
    {
        delete Query;
        MemoInfo->Lines->Add("Ошибка загрузки информации: " + e.Message);
    }
}
//---------------------------------------------------------------------------
// Кнопка "OK" - добавление заказа

void __fastcall TFormAddOrder::ButtonOKClick(TObject *Sender)
{
	double cost = 0.0;
	TFormatSettings fs = TFormatSettings::Create();
	fs.DecimalSeparator = '.';
	try
	{
        // Проверка заполненности полей
        if (ComboBoxIzdeliya->ItemIndex <= 0)
        {
            ShowMessage("Пожалуйста, выберите изделие!");
            ComboBoxIzdeliya->SetFocus();
            return;
        }

        if (ComboBoxZakazchiki->ItemIndex <= 0)
        {
            ShowMessage("Пожалуйста, выберите заказчика!");
            ComboBoxZakazchiki->SetFocus();
            return;
        }

        int kol = StrToIntDef(EditKolichestvo->Text, 0);
        if (kol <= 0)
        {
            ShowMessage("Количество должно быть больше нуля!");
            EditKolichestvo->SetFocus();
            return;
        }

		String priceText = EditCena->Text.Trim();

        // Проверка на пустое поле
        if (priceText == "")
        {
            ShowMessage("Поле цены не может быть пустым!");
            EditCena->SetFocus();
            return;
        }

		priceText = StringReplace(priceText, ",", ".", TReplaceFlags() << rfReplaceAll);

        // Проверяем, что строка не начинается с точки
        if (priceText == "." || priceText == ",")
        {
            ShowMessage("Некорректный формат цены!\nПример правильного формата: 123.45");
            EditCena->SetFocus();
            EditCena->SelectAll();
            return;
        }

        // Убираем лишние пробелы
        priceText = StringReplace(priceText, " ", "", TReplaceFlags() << rfReplaceAll);

        // Преобразуем в число с обработкой исключения
        try
        {
            cost = StrToFloat(priceText, fs);
        }
        catch (EConvertError &e)
        {
            ShowMessage("Некорректный формат цены!\nИспользуйте формат: 123.45\nПример: 99.99 или 150.50");
            EditCena->SetFocus();
            EditCena->SelectAll();
            return;
        }

        if (cost <= 0.0)
        {
            ShowMessage("Цена должна быть больше нуля!");
            EditCena->SetFocus();
            EditCena->SelectAll();
            return;
        }

        // Округляем до 2 знаков после запятой
        cost = std::round(cost * 100) / 100;

        if (CheckBoxDatePay->Checked && CheckBoxDateShip->Checked)
        {
            if (DateTimePickerShip->Date < DateTimePickerPay->Date) {
                if (MessageDlg("Shipping day is before payment day. Continue?", mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0) != mrYes) {
                   return;
                }
            }
        }

		String selectedIzd = ComboBoxIzdeliya->Text;
		String nIzd = selectedIzd.SubString(1, selectedIzd.Pos(" - ") - 1).Trim();

        String selectedCl = ComboBoxZakazchiki->Text;
        String nCl = selectedCl.SubString(1, selectedCl.Pos(" - ") - 1).Trim();

        Variant datePay = CheckBoxDatePay->Checked ? Variant(DateTimePickerPay->Date) : Variant();
        Variant dateShip = CheckBoxDateShip->Checked ? Variant(DateTimePickerShip->Date) : Variant();

        // Добавление заказа через модуль данных
        if (DM->AddNewOrder(nIzd, nCl, kol, cost, datePay, dateShip))
        {
            ModalResult = mrOk;
        }
    }
    catch (Exception &e)
    {
        ShowMessage("Ошибка: " + e.Message);
    }
}

//---------------------------------------------------------------------------
// Проверка допустимости символа для float
bool __fastcall TFormAddOrder::IsValidFloatChar(System::WideChar Key, String CurrentText)
{
    // Разрешаем: цифры 0-9
    if (Key >= '0' && Key <= '9')
        return true;

    // Разрешаем управляющие клавиши
    if (Key == 8 ||   // Backspace
        Key == 46 ||  // Delete
        Key == 37 ||  // Left arrow
        Key == 39 ||  // Right arrow
        Key == 35 ||  // End
        Key == 36 ||  // Home
        Key == 9)     // Tab
        return true;

    // Разрешаем точку и запятую (только одну)
    if (Key == '.' || Key == ',')
    {
        // Проверяем, что разделителя еще нет в тексте
        return (CurrentText.Pos('.') == 0) && (CurrentText.Pos(',') == 0);
    }

    return false;
}
//---------------------------------------------------------------------------

// Показ модального сообщения
void __fastcall TFormAddOrder::ShowInvalidCharMessage(System::WideChar Key)
{
    String message;

    if (Key == VK_RETURN)
    {
        message = "Недопустимый символ: Enter\nЗдесь можно ввести только число";
    }
	else if (Key == VK_SPACE)
    {
        message = "Недопустимый символ: Пробел\nЗдесь можно ввести только число";
    }
    else if (Key >= 32 && Key <= 126)
    {
        message = "Недопустимый символ: '" + String(Key) + "'\nЗдесь можно ввести только число";
    }
    else
    {
        message = "Недопустимый символ\nЗдесь можно ввести только число";
	}
    MessageDlg(message, mtWarning, TMsgDlgButtons() << mbOK, 0);
}
//---------------------------------------------------------------------------

// Обработчик KeyPress - основная валидация
void __fastcall TFormAddOrder::EditCenaKeyPress(TObject *Sender, System::WideChar &Key)
{
    TEdit *edit = dynamic_cast<TEdit*>(Sender);
    if (!edit) return;

	// Если символ недопустимый - блокируем и показываем сообщение
    if (!IsValidFloatChar(Key, edit->Text))
    {
        Key = 0;
        ShowInvalidCharMessage(Key);
    }
    else
    {
        // Автозамена запятой на точку
        if (Key == ',')
        {
            Key = '.';
		}
    }
}
//---------------------------------------------------------------------------

// Обработчик KeyDown для перехвата специальных клавиш
void __fastcall TFormAddOrder::EditCenaKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    // Блокируем пробел и Enter
    if (Key == VK_SPACE || Key == VK_RETURN)
    {
        Key = 0;
        ShowInvalidCharMessage(Key);
    }
}

//---------------------------------------------------------------------------

// Кнопка "Отмена"
void __fastcall TFormAddOrder::ButtonCancelClick(TObject *Sender)
{
    ModalResult = mrCancel;
}
//---------------------------------------------------------------------------
