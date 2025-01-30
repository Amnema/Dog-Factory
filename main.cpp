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
wstring PrintDogSpecies (const DogSpecies species)
{
    switch(species)
    {
        case DogSpecies::Alabai: return L"Alabai";
        case DogSpecies::Dachshund: return L"Dachshund";
        case DogSpecies::Husky: return L"Husky";
        case DogSpecies::Labrador: return L"Labrador";
        case DogSpecies::Spitz: return L"Spitz";
        default: return L"Unknown";
    }
}

wstring PrintDogColor (const ColorEnum color)
{
    switch(color)
    {
        case ColorEnum::Black: return L"Black";
        case ColorEnum::Brown: return L"Brown";
        case ColorEnum::Grey: return L"Grey";
        case ColorEnum::MultiColor: return L"MultiColor";
        case ColorEnum::White: return L"White";
        default: return L"Unknown";
    }
}

wstring PrintDogSize (const SizeEnum sizedog)
{
    switch(sizedog)
    {
        case SizeEnum::Big: return L"Big";
        case SizeEnum::Giant: return L"Giant";
        case SizeEnum::Medium: return L"Medium";
        case SizeEnum::Small: return L"Small";
        default: return L"Unknown";
    }
}
//функция для совместного использования итератора и декоратора
void PrintFilteredDogs(DogVectorContainer &dogContainer, bool goodOnly, ColorEnum colorFilter)
{
    Iterator<DogPtr> *it = dogContainer.GetIterator();

    // Декоратор для выбора только хороших собак
    if (goodOnly)
    {
        it = new DogGoodIteratorDecorator(it, true);
    }

    // Декоратор для фильтрации по цвету
    if (colorFilter != ColorEnum::MultiColor)
    {
        it = new DogColorIteratorDecorator(it, colorFilter);
    }

    cout << "Filtered dogs:\n";
    for (it->First(); !it->IsDone(); it->Next())
    {
        DogPtr dog = it->GetCurrent();
        wcout << L"Dog species: " << PrintDogSpecies(dog->GetSpecies())
             << L", Color: " << PrintDogColor(dog->GetColor())
             << L", Size: " << PrintDogSize(dog->GetSize())
             << L", Good? " << (dog->IsGood() ? L"Yes" : L"No") << endl;
    }
    delete it;
}


int main()
{
    //фабричный метод и фильтрация (совместное использование декоратора и итератора)
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
        wcout << L"Dog species: " << PrintDogSpecies(dog->GetSpecies())
             << L", Color: " << PrintDogColor(dog->GetColor())
             << L", Size: " << PrintDogSize(dog->GetSize())
             << L", Good? " << (dog->IsGood() ? L"yes" : L"no") << endl;
    }
    delete it;
    cout << "\nFilter: Only good dogs\n";
    PrintFilteredDogs(dogContainer, true, ColorEnum::MultiColor);

    cout << "\nFilter:Only wight dogs\n";
    PrintFilteredDogs(dogContainer, false, ColorEnum::White);
    return 0;
}




