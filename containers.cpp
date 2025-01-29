#include "classes.cpp"
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
    // FruitPtr GetByIndex(int index) const { return FruitBox[index]; }

    Iterator<DogPtr> *GetIterator()
    {
        return new DogListContainerIterator(&dogValier);
    }
};
