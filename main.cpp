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
    srand(time(0)); // Инициализация генератора случайных чисел

    DogVectorContainer dogContainer(10); // Контейнер на 10 собак

    // Заполняем контейнер случайными собаками
    int numDogs = rand() % 10 + 1; // Количество собак (от 1 до 10)
    for (int i = 0; i < numDogs; i++)
    {
        DogPtr newDog = DogFactory::CreateRandomDog();
        dogContainer.AddDog(newDog);
    }

    cout << "Create " << numDogs << " random dogs.\n";

    // Выведем список всех собак
    Iterator<DogPtr> *it = dogContainer.GetIterator();
    for (it->First(); !it->IsDone(); it->Next())
    {
        DogPtr dog = it->GetCurrent();
        cout << "Dog species: " << static_cast<int>(dog->GetSpecies())
             << ", Color: " << static_cast<int>(dog->GetColor())
             << ", Size: " << static_cast<int>(dog->GetSize())
             << ", Good? " << (dog->IsGood() ? "yes" : "no") << endl;
    }
    delete it;

    return 0;
}

/*
    // ПРОВЕРКА ДЛЯ ДЕКОРАТОРОВ
   // Создаем контейнер
    DogVectorContainer dogVector(5);

    // Добавляем собак
    DogPtr d1 = new Dachshund(ColorEnum::Brown, SizeEnum::Small);
    DogPtr d2 = new Husky(ColorEnum::Grey, SizeEnum::Big);
    DogPtr d3 = new Labrador(ColorEnum::Black, SizeEnum::Giant);
    DogPtr d4 = new Spitz(ColorEnum::White, SizeEnum::Small);
    DogPtr d5 = new Alabai(ColorEnum::Brown, SizeEnum::Giant);

    dogVector.AddDog(d1);
    dogVector.AddDog(d2);
    dogVector.AddDog(d3);
    dogVector.AddDog(d4);
    dogVector.AddDog(d5);

    // Покормим всех собак, кроме таксы
    d2->Feed();
    d3->Feed();
    d4->Feed();
    d5->Feed();

    cout << "=== All Dogs ===" << endl;
    Iterator<DogPtr> *allDogs = dogVector.GetIterator();
    for (allDogs->First(); !allDogs->IsDone(); allDogs->Next())
    {
        DogPtr dog = allDogs->GetCurrent();
        cout << "Dog species: " << static_cast<int>(dog->GetSpecies()) << " | "
             << "Color: " << static_cast<int>(dog->GetColor()) << " | "
             << "Size: " << static_cast<int>(dog->GetSize()) << " | "
             << "IsGood: " << dog->IsGood() << endl;
    }
    delete allDogs;

    cout << "\n=== Decorator: Only good boys ===" << endl;
    Iterator<DogPtr> *goodDogs = new DogGoodIteratorDecorator(dogVector.GetIterator(), true);
    for (goodDogs->First(); !goodDogs->IsDone(); goodDogs->Next())
    {
        DogPtr dog = goodDogs->GetCurrent();
        cout << "Good dog species: " << static_cast<int>(dog->GetSpecies()) << endl;
    }
    delete goodDogs;

    cout << "\n=== Decorator: Only white dogs ===" << endl;
    Iterator<DogPtr> *whiteDogs = new DogColorIteratorDecorator(dogVector.GetIterator(), ColorEnum::White);
    for (whiteDogs->First(); !whiteDogs->IsDone(); whiteDogs->Next())
    {
        DogPtr dog = whiteDogs->GetCurrent();
        cout << "White dog species: " << static_cast<int>(dog->GetSpecies()) << endl;
    }
    delete whiteDogs;

    cout << "\n=== Decorator: Only small dogs ===" << endl;
    Iterator<DogPtr> *smallDogs = new DogSizeIteratorDecorator(dogVector.GetIterator(), SizeEnum::Small);
    for (smallDogs->First(); !smallDogs->IsDone(); smallDogs->Next())
    {
        DogPtr dog = smallDogs->GetCurrent();
        cout << "Small dog species: " << static_cast<int>(dog->GetSpecies()) << endl;
    }
    delete smallDogs;

    return 0;
}*/
/*
    // ПРОВЕРКА РАБОТЫ ИТЕРАТОРОВ
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
*/


