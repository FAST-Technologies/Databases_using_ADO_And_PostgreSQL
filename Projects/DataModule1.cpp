//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
#include <string>
#pragma hdrstop

#include "DataModule1.h"
#include "MainForm.h"
#include <System.DateUtils.hpp>
#include <System.SysUtils.hpp>
#include <System.IOUtils.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "Vcl.Controls.TControl"
#pragma resource "*.dfm"
TDM *DM;
//---------------------------------------------------------------------------
__fastcall TDM::TDM(TComponent* Owner)
	: TDataModule(Owner)
{
}

//---------------------------------------------------------------------------
// Получение пути к конфигурационному файлу
String __fastcall TDM::GetConfigFilePath()
{
	String exePath = ExtractFilePath(ParamStr(0));
	String configPath = exePath + "db_config.ini";

	// Проверяемм существование файла
	if (!FileExists(configPath)) {
		TIniFile *ini = new TIniFile(configPath);
		try
		{
			ini->WriteString("Database", "Host", "students.ami.nstu.ru");
			ini->WriteString("Database", "Port", "5432");
			ini->WriteString("Database", "Database", "students");
			ini->WriteString("Database", "User", "pmi-b2702");
			ini->WriteString("Database", "Password", "4ioi#ZHzE");
			ini->WriteString("Database", "Schema", "pmib2702");
			ini->WriteString("Database", "Driver", "PostgreSQL Unicode");
			ini->WriteString("Database", "Postgre_DSN", "PostgreSQL35W");
			ini->WriteString("Database", "SSL_Mode", "prefer");

			ShowMessage("Configuration file created:\n" + configPath + "\n\nPlease check the settings and restart the application.");
		}
		__finally
		{
			delete ini;
        }
	}
    return configPath;
}

//---------------------------------------------------------------------------
// Загрузка конфигурации из INI файла
bool __fastcall TDM::LoadDatabaseConfig()
{
    try
    {
        String configPath = GetConfigFilePath();

		if (!FileExists(configPath))
		{
            throw Exception("Configuration file not found: " + configPath);
        }

		TIniFile *ini = new TIniFile(configPath);
		try
		{
			FDBConfig.Host = ini->ReadString("Database", "Host", "students.ami.nstu.ru");
            FDBConfig.Port = ini->ReadString("Database", "Port", "5432");
            FDBConfig.Database = ini->ReadString("Database", "Database", "postgres");
            FDBConfig.User = ini->ReadString("Database", "User", "postgres");
            FDBConfig.Password = ini->ReadString("Database", "Password", "");
			FDBConfig.Schema = ini->ReadString("Database", "Schema", "public");
			FDBConfig.Driver = ini->ReadString("Database", "Driver", "PostgreSQL Unicode");
			FDBConfig.Postgre_DSN = ini->ReadString("Database", "Postgre_DSN", "PostgreSQL35W");
			FDBConfig.SSL_Mode = ini->ReadString("Database", "SSL_Mode", "prefer");

            FSchemaName = FDBConfig.Schema;

            // Проверка обязательных параметров
            if (FDBConfig.Host.IsEmpty() || FDBConfig.User.IsEmpty())
            {
                throw Exception("Configuration file contains empty required fields!");
            }

            return true;
        }
        __finally
        {
            delete ini;
        }
    }
    catch (Exception &e)
    {
        ShowMessage("Error loading configuration:\n" + e.Message);
		return false;
	}
}

//---------------------------------------------------------------------------
// Создание модуля данных
void __fastcall TDM::DataModuleCreate(TObject *Sender)
{
    try
    {
        if (!LoadDatabaseConfig())
        {
            throw Exception("Failed to load database configuration!");
        }
        Sleep(50);
        ConnectToDatabase();
        CheckDatabaseStructure();
        LoadDetailsQuery();

		// 🔹 Инициализация QueryOrders
        QueryOrders->SQL->Text =
            "SELECT "
            "    r.n_real AS n_zakaza, "
            "    r.date_order AS data_zakaza, "
            "    COALESCE(NULLIF(TRIM(c.name), ''), 'Отсутствует') AS zakazchik, "
            "    COALESCE(NULLIF(TRIM(j.name), ''), 'Отсутствует') AS izdelie, "
            "    r.kol AS kol_izdeliy, "
            "    q.kol AS kol_det_na_1_izd, "
            "    (r.kol * q.kol) AS kol_det_trebuetsya, "
            "    COALESCE(nalichie.kol_nalichie, 0) AS kol_det_nalichie, "
            "    CASE "
            "        WHEN COALESCE(nalichie.kol_nalichie, 0) < (r.kol * q.kol) "
            "        THEN 'ДЕФИЦИТ' "
            "        ELSE 'OK' "
            "    END AS status "
            "FROM " + FSchemaName + ".r r "
            "INNER JOIN " + FSchemaName + ".c c ON r.n_cl = c.n_cl "
            "INNER JOIN " + FSchemaName + ".j j ON r.n_izd = j.n_izd "
            "INNER JOIN " + FSchemaName + ".q q ON r.n_izd = q.n_izd "
            "LEFT JOIN ( "
            "    SELECT "
            "        postavleno.n_det, "
            "        postavleno.n_izd, "
            "        (COALESCE(postavleno.kol_post, 0) - COALESCE(izrash.kol_izrash, 0)) AS kol_nalichie "
            "    FROM ( "
            "        SELECT n_det, n_izd, SUM(kol) AS kol_post "
            "        FROM " + FSchemaName + ".spj1 "
            "        GROUP BY n_det, n_izd "
            "    ) AS postavleno "
            "    LEFT JOIN ( "
            "        SELECT q.n_det, q.n_izd, SUM(w.kol * q.kol) AS kol_izrash "
            "        FROM " + FSchemaName + ".w w "
            "        INNER JOIN " + FSchemaName + ".q q ON w.n_izd = q.n_izd "
            "        GROUP BY q.n_det, q.n_izd "
            "    ) AS izrash ON postavleno.n_det = izrash.n_det AND postavleno.n_izd = izrash.n_izd "
            ") AS nalichie ON q.n_det = nalichie.n_det AND r.n_izd = nalichie.n_izd "
            "WHERE q.n_det = :n_det AND r.date_ship IS NULL "
            "ORDER BY r.date_order ASC;";

        QueryOrders->Parameters->ParamByName("n_det")->Value = "DUMMY";
        QueryOrders->Open();
        QueryOrders->Close();

        if (QueryDetails)
            QueryDetails->AfterScroll = QueryDetailsAfterScroll;
    }
    catch (Exception &e)
    {
        ShowMessage("Error while initialising the data module: " + e.Message);
    }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Метод для проверки существования таблиц
void __fastcall TDM::CheckDatabaseStructure()
{
    TADOQuery *CheckQuery = new TADOQuery(this);
    try
    {
        CheckQuery->Connection = ADOConnection1;

        // Проверяем существование таблиц
        CheckQuery->SQL->Clear();
        CheckQuery->SQL->Add(
            "SELECT table_name FROM information_schema.tables "
			"WHERE table_schema = 'pmib2702' AND table_name IN ('p', 'j', 'q', 'r', 's', 'c', 'v', 'w', 'e', 'spj', 'spj1')"
		);
        CheckQuery->Open();

        String tables = "";
        while (!CheckQuery->Eof)
        {
            tables = tables + CheckQuery->FieldByName("table_name")->AsString + ", ";
            CheckQuery->Next();
        }

        ShowMessage("Найдены таблицы: " + tables);
        CheckQuery->Close();
        delete CheckQuery;
    }
    catch (Exception &e)
    {
        delete CheckQuery;
        ShowMessage("Ошибка проверки структуры БД: " + e.Message);
    }
}
//---------------------------------------------------------------------------

void __fastcall TDM::ConnectToDatabase()
{
    try
    {
        if (!ADOConnection1)
            return;

		ADOConnection1->Close();

		// Format 1
		ADOConnection1->ConnectionString =
		"Provider=MSDASQL.1;"
		"DSN=" + FDBConfig.Postgre_DSN + ";"
		"Server=" + FDBConfig.Host + ";"
		"Port=" + FDBConfig.Port + ";"
		"Database=" + FDBConfig.Database + ";"
		"Uid=" + FDBConfig.User + ";"
		"Pwd=" + FDBConfig.Password + ";"
		"SSLmode=" + FDBConfig.SSL_Mode + ";";

		// Format 2
//		ADOConnection1->ConnectionString =
//			"Provider=MSDASQL.1;"
//			"Driver=" + FDBConfig.Driver + ";"
//			"Server=" + FDBConfig.Host + ";"
//			"Port=" + FDBConfig.Port + ";"
//			"Database=" + FDBConfig.Database + ";"
//			"Uid=" + FDBConfig.User + ";"
//			"Pwd=" + FDBConfig.Password + ";"
//			"SSLmode=" + FDBConfig.SSL_Mode + ";";

        ADOConnection1->LoginPrompt = false;
		ADOConnection1->Open();

        String message =
            String().sprintf(
                L"Соединение с базой данных установлено успешно!\n"
                L"Server: %s\n"
                L"Database: %s\n"
                L"Schema: %s",
                FDBConfig.Host.c_str(),
                FDBConfig.Database.c_str(),
				FSchemaName.c_str()
            );

        ShowMessage(message);
	}
    catch (Exception &e)
    {
        throw Exception("Ошибка подключения к БД: " + e.Message +
                       "\nПроверьте:\n"
                       "1. Наличие ODBC источника данных 'PostgreSQL_DSN'\n"
					   "2. Корректность логина/пароля\n"
					   "3. Доступность сервера БД");
	}
}
//---------------------------------------------------------------------------

// ЗАПРОС 1: Загрузка данных о деталях и изделиях
// ЗАПРОС 1: Загрузка данных о деталях и изделиях
void __fastcall TDM::LoadDetailsQuery()
{
	try
	{
		QueryDetails->Close();

		// SQL-запрос для получения информации о деталях и изделиях
		QueryDetails->SQL->Clear();
		QueryDetails->SQL->Add(
		"SELECT "
		"	p.n_det, "
		"	p.name AS det_name, "
		"	j.n_izd, "
		"	j.name AS izd_name, "
		"	COALESCE(nalichie.kol_nalichie, 0) AS kol_nalichie, "
		"	COALESCE(potrebnost.kol_trebuetsya, 0) AS kol_trebuetsya, "
		"	CASE "
		"		WHEN COALESCE(nalichie.kol_nalichie, 0) < COALESCE(potrebnost.kol_trebuetsya, 0) "
		"		THEN 'ДЕФИЦИТ' "
		"		ELSE 'OK' "
		"	END AS status "
		"FROM " + FSchemaName + ".p p "
		"CROSS JOIN " + FSchemaName + ".j j "
		"INNER JOIN " + FSchemaName + ".q q ON p.n_det = q.n_det AND j.n_izd = q.n_izd "
		"LEFT JOIN ( "
		"	SELECT "
		"		postavleno.n_det, "
		"		postavleno.n_izd, "
		"		(COALESCE(postavleno.kol_post, 0) - COALESCE(izrash.kol_izrash, 0)) AS kol_nalichie "
		"	FROM ( "
		"		SELECT n_det, n_izd, SUM(kol) AS kol_post "
		"		FROM " + FSchemaName + ".spj1 "
		"		GROUP BY n_det, n_izd "
		"	) AS postavleno "
		"	LEFT JOIN ( "
		"		SELECT q.n_det, q.n_izd, SUM(w.kol * q.kol) AS kol_izrash "
		"		FROM " + FSchemaName + ".w w "
		"		INNER JOIN " + FSchemaName + ".q q ON w.n_izd = q.n_izd "
		"		GROUP BY q.n_det, q.n_izd "
		"	) AS izrash ON postavleno.n_det = izrash.n_det AND postavleno.n_izd = izrash.n_izd "
		") AS nalichie ON p.n_det = nalichie.n_det AND j.n_izd = nalichie.n_izd "
		"LEFT JOIN ( "
		"	SELECT "
		"		q.n_det, "
		"		q.n_izd, "
		"		SUM(r.kol * q.kol) AS kol_trebuetsya "
		"	FROM " + FSchemaName + ".r r "
		"	INNER JOIN " + FSchemaName + ".q q ON r.n_izd = q.n_izd "
		"	WHERE r.date_ship IS NULL "
		"	GROUP BY q.n_det, q.n_izd "
		") AS potrebnost ON p.n_det = potrebnost.n_det AND j.n_izd = potrebnost.n_izd "
		"ORDER BY p.n_det, j.n_izd ASC;"
		);

		QueryDetails->Open();
		QueryDetails->First();
        while (!QueryDetails->Eof)
        {
            QueryDetails->Edit(); // Входим в режим редактирования

            // Проверяем и заменяем пустые значения
            if (QueryDetails->FieldByName("det_name")->AsString.Trim().IsEmpty()) {
				QueryDetails->FieldByName("det_name")->AsString = "Отсутствует";
            }
            if (QueryDetails->FieldByName("izd_name")->AsString.Trim().IsEmpty()) {
				QueryDetails->FieldByName("izd_name")->AsString = "Отсутствует";
			}

			QueryDetails->Post(); // Сохраняем изменения
			QueryDetails->Next();
		}
		QueryDetails->First();
	}
	catch (Exception &e)
	{
		throw Exception("Ошибка выполнения запроса 1: " + e.Message);
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

// ЗАПРОС 2: Загрузка заказов для указанной детали
void __fastcall TDM::LoadOrdersForDetail(String detailNum)
{
    try
    {
        QueryOrders->Close();
        QueryOrders->Parameters->ParamByName("n_det")->Value = detailNum;
        QueryOrders->Open();
    }
    catch (Exception &e)
    {
        throw Exception("Ошибка выполнения запроса 2: " + e.Message);
    }
}
//---------------------------------------------------------------------------

// Обработчик события прокрутки в первом запросе
void __fastcall TDM::QueryDetailsAfterScroll(TDataSet *DataSet)
{
    try
    {
        if (!QueryDetails->IsEmpty())
        {
            String detailNum = QueryDetails->FieldByName("n_det")->AsString.Trim();
            LoadOrdersForDetail(detailNum);

            // Обновляем грид
            if (FormMain)
				FormMain->RebuildGrid2();
		}
	}
	catch (Exception &e)
	{
		ShowMessage("Ошибка при обновлении списка заказов: " + e.Message);
	}
}
//---------------------------------------------------------------------------

// ЗАПРОС 3: Добавление нового заказа
bool __fastcall TDM::AddNewOrder(String nIzd, String nCl, int kol, double cost, Variant datePay, Variant dateShip){
	TADOQuery *InsertQuery = new TADOQuery(this);
    try
    {
        InsertQuery->Connection = ADOConnection1;

        // 🔹 Убираем n_real из INSERT — его сгенерирует триггер!
		InsertQuery->SQL->Text =
            "INSERT INTO " + FSchemaName + ".r (n_izd, n_cl, date_order, kol, cost, date_pay, date_ship) "
            "VALUES (:n_izd, :n_cl, :date_order, :kol, :cost, :date_pay, :date_ship)";

        InsertQuery->Parameters->ParamByName("n_izd")->Value = nIzd;
        InsertQuery->Parameters->ParamByName("n_cl")->Value = nCl;
        InsertQuery->Parameters->ParamByName("date_order")->Value = Date();
        InsertQuery->Parameters->ParamByName("kol")->Value = kol;
        InsertQuery->Parameters->ParamByName("cost")->Value = cost;
        InsertQuery->Parameters->ParamByName("date_pay")->Value = datePay.IsNull() ? Null() : datePay;
        InsertQuery->Parameters->ParamByName("date_ship")->Value = dateShip.IsNull() ? Null() : dateShip;

        InsertQuery->ExecSQL();

		String message = "Заказ " + newOrderNum + " успешно добавлен!\n" +
                       "Изделие: " + nIzd + "\n" +
                       "Заказчик: " + nCl + "\n" +
					   "Количество: " + IntToStr(kol) + "\n" +
					   "Цена: " + FloatToStrF(cost, ffFixed, 10, 2) + "\n" +
					   "Дата оплаты: " + (datePay.IsNull() ? "Не указана (NULL)" : DateToStr(datePay)) + "\n" +
					   "Дата отправки: " + (dateShip.IsNull() ? "Не указана (NULL)" : DateToStr(dateShip));

		ShowMessage(message);


        LoadDetailsQuery();
        return true;
    }
    catch (Exception &e)
	{
        String msg = e.Message;
        if (msg.Pos("violates check constraint") > 0)
        {
            ShowMessage(
                L"violates check constraint: Нарушено ограничение целостности данных!\n"
				L"Проверьте:\n"
				L"• Номер заказа должен начинаться с 'R'\n"
                L"• Дата оплаты не может быть раньше даты заказа\n"
				L"• Количество и цена должны быть > 0 " + e.Message
			);
        }
        else if (msg.Pos("duplicate key") > 0)
        {
            ShowMessage(L"Ошибка: Нарушен уникальный ключ (возможно, дубль).");
        }
        else
        {
            ShowMessage("Ошибка при добавлении заказа: " + e.Message);
        }
        return false;
    }
	delete InsertQuery;
}//---------------------------------------------------------------------------
// Получить количество деталей в наличии
int __fastcall TDM::GetAvailableDetails(String nDet, String nIzd)
{
    TADOQuery *Query = new TADOQuery(this);
    try
    {
        Query->Connection = ADOConnection1;
        Query->SQL->Add(
            "SELECT COALESCE(SUM(kol), 0) AS total "
			"FROM " + FSchemaName + ".spj1 "
            "WHERE n_det = :n_det AND n_izd = :n_izd"
        );
        Query->Parameters->ParamByName("n_det")->Value = nDet;
        Query->Parameters->ParamByName("n_izd")->Value = nIzd;
        Query->Open();

        int result = Query->FieldByName("total")->AsInteger;
        Query->Close();
        delete Query;
		return result;
    }
    catch (Exception &e)
    {
        delete Query;
        return 0;
    }
}
