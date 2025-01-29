#include <iostream>
#include "containers.cpp"
using namespace std;
//роспись функций входящих в контейнер типа вектор
DogVectorContainer::DogVectorContainer(int maxSize)
{
    DogValier = new DogPtr[maxSize];

    for(int i = 0; i < maxSize; i++)
    {
        DogValier[i] = NULL;
    }

    DogCount = 0;
    MaxSize = maxSize;
}

DogVectorContainer::~DogVectorContainer()
{
    for(int i = 0; i < MaxSize; i++)
    {
        if(DogValier[i] != NULL)
        {
            delete DogValier[i];
            DogValier[i] = NULL;
        }
    }

    delete [] DogValier;
}

void DogVectorContainer::AddDog(DogPtr newDog)
{
    DogValier[DogCount] = newDog;
    DogCount++;
}

/*wstring PrintFruitType(const FruitType type)
{
    switch(type)
    {
        case FruitType::Apple: return L"яблоко";
        case FruitType::Kiwi: return L"киви";
        case FruitType::Orange: return L"апельсин";
        default: return L"неизвестный фрукт";
    }
}

wstring PrintFruitColor(const ColorEnum color)
{
    switch(color)
    {
        case ColorEnum::Green: return L"зеленый";
        case ColorEnum::Red: return L"красный";
        case ColorEnum::Orange: return L"ораанжевый";
        default: return L"неизвестный";
    }
}*/

int main()
{
    // Создаем контейнеры
    DogVectorContainer dogVector(5);
    DogListContainer dogList;

    // Добавляем собак
    DogPtr d1 = new Dachshund(ColorEnum::Brown, SizeEnum::Small);
    DogPtr d2 = new Husky(ColorEnum::Grey, SizeEnum::Big);
    DogPtr d3 = new Labrador(ColorEnum::Black, SizeEnum::Giant);

    dogVector.AddDog(d1);
    dogVector.AddDog(d2);
    dogVector.AddDog(d3);

    dogList.AddDog(d1);
    dogList.AddDog(d2);
    dogList.AddDog(d3);

    // Тест итератора для вектора
    Iterator<DogPtr> *vectorIterator = dogVector.GetIterator();
    cout << "=== DogVectorContainer ===\n";
    for (vectorIterator->First(); !vectorIterator->IsDone(); vectorIterator->Next())
    {
        DogPtr current = vectorIterator->GetCurrent();
        current->Pet();
        current->Feed();
        current->Pet();
    }
    delete vectorIterator;  // Удаляем итератор

    // Тест итератора для списка
    Iterator<DogPtr> *listIterator = dogList.GetIterator();
    cout << "\n=== DogListContainer ===\n";
    for (listIterator->First(); !listIterator->IsDone(); listIterator->Next())
    {
        DogPtr current = listIterator->GetCurrent();
        current->Pet();
        current->Feed();
        current->Pet();
    }
    delete listIterator;  // Удаляем итератор

    return 0;
}

