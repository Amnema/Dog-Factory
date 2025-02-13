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
string PrintDogSpecies (const DogSpecies species)
{
    switch(species)
    {
        case DogSpecies::Alabai: return "Alabai";
        case DogSpecies::Dachshund: return "Dachshund";
        case DogSpecies::Husky: return "Husky";
        case DogSpecies::Labrador: return "Labrador";
        case DogSpecies::Spitz: return "Spitz";
        default: return "Unknown";
    }
}

string PrintDogColor (const ColorEnum color)
{
    switch(color)
    {
        case ColorEnum::Black: return "Black";
        case ColorEnum::Brown: return "Brown";
        case ColorEnum::Grey: return "Grey";
        case ColorEnum::MultiColor: return "MultiColor";
        case ColorEnum::White: return "White";
        default: return "Unknown";
    }
}

string PrintDogSize (const SizeEnum sizedog)
{
    switch(sizedog)
    {
        case SizeEnum::Big: return "Big";
        case SizeEnum::Giant: return "Giant";
        case SizeEnum::Medium: return "Medium";
        case SizeEnum::Small: return "Small";
        default: return "Unknown";
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
        cout << "Dog species: " << PrintDogSpecies(dog->GetSpecies())
             << ", Color: " << PrintDogColor(dog->GetColor())
             << ", Size: " << PrintDogSize(dog->GetSize())
             << ", Good? " << (dog->IsGood() ? "Yes" : "No") << endl;
    }
    delete it;
}


int main()
{
        srand(static_cast<unsigned int>(time(0)));

        SQLiteContainer dogDB("dogs.db");

        // Создаём таблицу
        dogDB.ExecuteQuery("CREATE TABLE IF NOT EXISTS Dogs (Species TEXT, Color TEXT, Size TEXT);");

        // Добавляем 5 случайных собак в БД с помощью фабричного метода
        for (int i = 0; i < 5; i++) {
            DogPtr dog = DogFactory::CreateRandomDog();
            dogDB.AddDog(PrintDogSpecies(dog->GetSpecies()),
                         PrintDogColor(dog->GetColor()),
                         PrintDogSize(dog->GetSize()));
        }

        // Создаём итератор для просмотра базы данных
        SQLiteContainerIterator it(dogDB.GetDB(), "SELECT Species, Color, Size FROM Dogs;");

        // Выводим данные из БД
        for (it.First(); !it.IsDone(); it.Next()) {
            DogPtr dog = it.GetCurrent();
            cout << "Dog species: " << PrintDogSpecies(dog->GetSpecies())
                  << ", Color: " << PrintDogColor(dog->GetColor())
                  << ", Size: " << PrintDogSize(dog->GetSize()) << endl;
        }
    return 0;
}


/*
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
}*/




