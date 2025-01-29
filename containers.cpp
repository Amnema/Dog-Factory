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
    // FruitPtr GetByIndex(int index) const { return FruitBox[index]; }

    Iterator<DogPtr> *GetIterator()
    {
        return new DogListContainerIterator(&dogValier);
    }
};
