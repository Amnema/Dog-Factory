#include "classes.cpp"
#include "sqlite3.h"
#include <stdexcept>
#include <vector>
#include <list>

using namespace std;

//итератор для контейнера типа вектор
class DogVectorContainerIterator : public Iterator<DogPtr>
{
private:
    const DogPtr *DogValier;
    int Pos; // отслеживает положение итератора
    int Count; // общее кол-во собак

public:
    DogVectorContainerIterator(const DogPtr *dogValier, int count)
    {
        DogValier = dogValier;
        Count = count;
        Pos = 0;
    }

    void First() { Pos = 0; }
    void Next() { Pos++; }
    bool IsDone() const { return Pos >= Count; }
    DogPtr GetCurrent() const { return DogValier[Pos]; }
};

//контейнер типа вектор
class DogVectorContainer
{
private:
    DogPtr *DogValier; // указатель на указатель
    int DogCount;
    int MaxSize;

public:
    DogVectorContainer(int maxSize);
    virtual ~DogVectorContainer();
    void AddDog(DogPtr newDog);
    int GetCount() const { return DogCount; }
    DogPtr GetByIndex(int index) const { return DogValier[index]; }

    Iterator<DogPtr> *GetIterator()
    {
        return new DogVectorContainerIterator(DogValier, DogCount);
    }
};

//декораторы для итератора векторного контейнера

class DogGoodIteratorDecorator : public IteratorDecorator<DogPtr>
{
private:
    bool TargetGood;

public:
    DogGoodIteratorDecorator(Iterator<DogPtr> *it, bool targetGood)
    : IteratorDecorator(it)
    {
        TargetGood = targetGood;
    }

    void First()
    {
        It->First();
        while(!It->IsDone() &&
              It->GetCurrent()->IsGood() != TargetGood)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();

        } while(!It->IsDone() &&
                It->GetCurrent()->IsGood() != TargetGood);
    }
};

class DogColorIteratorDecorator : public IteratorDecorator<DogPtr>
{
private:
    ColorEnum TargetColor;

public:
    DogColorIteratorDecorator(Iterator<DogPtr> *it, ColorEnum targetColor)
    : IteratorDecorator(it)
    {
        TargetColor = targetColor;
    }

    void First()
    {
        It->First();
        while(!It->IsDone() &&
              It->GetCurrent()->GetColor() != TargetColor)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();

        } while(!It->IsDone() &&
                It->GetCurrent()->GetColor() != TargetColor);
    }
};

class DogSizeIteratorDecorator : public IteratorDecorator<DogPtr>
{
private:
    SizeEnum TargetSize;

public:
    DogSizeIteratorDecorator(Iterator<DogPtr> *it, SizeEnum targetSize)
    : IteratorDecorator(it)
    {
        TargetSize = targetSize;
    }

    void First()
    {
        It->First();
        while(!It->IsDone() &&
              It->GetCurrent()->GetSize() != TargetSize)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();

        } while(!It->IsDone() &&
                It->GetCurrent()->GetSize() != TargetSize);
    }
};


//итератор для контейнера типа лист
class DogListContainerIterator : public Iterator<DogPtr>
{
private:
    const list<DogPtr> *DogValier;
    list<DogPtr>::const_iterator it;

public:
    DogListContainerIterator(const list<DogPtr> *dogValier)
    {
        DogValier = dogValier;
        it = DogValier->begin();
    }

    void First() { it = DogValier->begin(); }
    void Next() { it++; }
    bool IsDone()  const { it ==DogValier->end(); }
    DogPtr GetCurrent() const { return *it; }
};

//контейнер типа лист
class DogListContainer
{
private:
    vector<DogPtr> DogValier;
    list<DogPtr> dogValier;

public:
    void AddDog(DogPtr newDog) { dogValier.push_back(newDog); }
    int GetCount() const { return DogValier.size(); }

    Iterator<DogPtr> *GetIterator()
    {
        return new DogListContainerIterator(&dogValier);
    }
};

//итератор для контейнера с дб
class SQLiteContainerIterator : public Iterator<DogPtr> {
private:
    sqlite3_stmt *stmt; // Указатель на подготовленный SQL-запрос
    sqlite3 *db;        // Указатель на базу данных
    bool done;          // Флаг завершения итерации

public:
    SQLiteContainerIterator(sqlite3 *db, const string &query)
        : db(db), stmt(nullptr), done(false)
    {
        // Подготавливаем SQL-запрос
        if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw runtime_error("Failed to prepare SQLite statement");
        }
        First(); // Устанавливаем итератор на первую строку
    }

    ~SQLiteContainerIterator() {
        if (stmt) {
            sqlite3_finalize(stmt);
        }
    }

    void First() override {
        sqlite3_reset(stmt); // Сбрасываем запрос
        done = (sqlite3_step(stmt) != SQLITE_ROW); // Переходим к первой строке
    }

    void Next() override {
        done = (sqlite3_step(stmt) != SQLITE_ROW); // Переходим к следующей строке
    }

    bool IsDone() const override {
        return done; // Проверяем, достигнут ли конец результата
    }

    DogPtr GetCurrent() const override {
        if (done) {
            throw out_of_range("No more rows to fetch");
        }

        // Считываем данные из текущей строки
        string species = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
        string color = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        string size = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));

        // Создаём объект Dog через фабрику
        DogPtr dog = DogFactory::CreateDogFromData(species, color, size);
        return dog;
    }
};


//Контейнер SQLite
class SQLiteContainer {
private:
    sqlite3 *db;
    string dbPath;

public:
    // Конструктор
    SQLiteContainer(const string &path) : dbPath(path) {
        // Открываем базу данных
        if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
            throw runtime_error("Failed to open SQLite database");
        }
    }

    // Деструктор
    ~SQLiteContainer() {
        if (db) {
            sqlite3_close(db); // Закрываем базу данных
        }
    }

    // Метод для выполнения SQL-запросов
    void ExecuteQuery(const string &query) {
        char *errMsg = nullptr;
        if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
            string error = errMsg;
            sqlite3_free(errMsg);
            throw runtime_error("SQLite query failed: " + error);
        }
    }

    // Метод для добавления записей
    void AddDog(const string &species, const string &color, const string &size) {
        string query = "INSERT INTO Dogs (Species, Color, Size) VALUES ('" + species + "', '" + color + "', '" + size + "');";
        ExecuteQuery(query);
    }

    Iterator<DogPtr> *GetIterator()
    {
        return new SQLiteContainerIterator(db, "SELECT Species, Color, Size FROM Dogs;");
    }

    sqlite3 *GetDB() { return db; }
};

