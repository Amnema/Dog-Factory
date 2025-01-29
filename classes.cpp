#include <iostream>
#include "Patterns.h"
#include <cstdlib> // для rand()
#include <ctime>   // для srand()
using namespace std;
enum class SizeEnum:int
{
    Small,
    Medium,
    Big,
    Giant
};
enum class ColorEnum:int
{
    Black,
    Brown,
    Grey,
    White,
    MultiColor= -1,

};
enum class DogSpecies:int
{
    Dachshund,
    Spitz,
    Husky,
    Labrador,
    Alabai
};
class Dog
{
protected:
    bool BoyIsGood;
    SizeEnum Size;
    ColorEnum Color;
    DogSpecies Species;
public:
    Dog()
    {
        // 80% шанс, что собака добрая, 20% - злая
        BoyIsGood = (rand() % 10 < 8);
    }

    bool IsGood() { return BoyIsGood; }
    void SetGood(bool value) { BoyIsGood = value; }

    virtual SizeEnum GetSize() {return Size;}
    virtual DogSpecies GetSpecies() {return Species;}
    virtual ColorEnum GetColor() {return Color;}
    virtual void Pet()=0;
    virtual void Feed()=0;
};
typedef Dog *DogPtr;

class Dachshund:public Dog
{
public:
    Dachshund(ColorEnum color, SizeEnum sizeDog){Color=color; Size=sizeDog;}
    DogSpecies GetSpecies() {return DogSpecies::Dachshund;}
    void Pet() {if(IsGood()){cout<<"Dachshund is happy!!!\n";} else {cout<<"Dachshund is angry...\n";}}
    void Feed() {cout<<"Dachshund ate all food :D\n"; BoyIsGood = true;}
};
class Spitz:public Dog
{
public:
    Spitz(ColorEnum color, SizeEnum sizeDog){Color=color; Size=sizeDog;}
    DogSpecies GetSpecies() {return DogSpecies::Spitz;}
    void Pet() {if(IsGood()){cout<<"Spitz is happy!!!\n";} else {cout<<"Spitz is angry...\n";}}
    void Feed() {cout<<"Spitz ate all food :D\n"; BoyIsGood = true;}
};
class Husky:public Dog
{
public:
    Husky(ColorEnum color, SizeEnum sizeDog){Color=color; Size=sizeDog;}
    DogSpecies GetSpecies() {return DogSpecies::Husky;}
    void Pet() {if(IsGood()){cout<<"Husky is happy!!!\n";} else {cout<<"Husky is angry...\n";}}
    void Feed() {cout<<"Husky ate all food :D\n"; BoyIsGood = true;}
};
class Labrador:public Dog
{
public:
    Labrador(ColorEnum color, SizeEnum sizeDog){Color=color; Size=sizeDog;}
    DogSpecies GetSpecies() {return DogSpecies::Labrador;}
    void Pet() {if(IsGood()){cout<<"Labrador is happy!!!\n";} else {cout<<"Labrador is angry...\n";}}
    void Feed() {cout<<"Labrador ate all food :D\n"; BoyIsGood = true;}
};
class Alabai:public Dog
{
public:
    Alabai(ColorEnum color, SizeEnum sizeDog){Color=color; Size=sizeDog;}
    DogSpecies GetSpecies() {return DogSpecies::Alabai;}
    void Pet() {if(IsGood()){cout<<"Alabai is happy!!!\n";} else {cout<<"Alabai is angry...\n";}}
    void Feed() {cout<<"Alabai ate all food :D\n"; BoyIsGood = true;}
};

//Создание фабрики для реализации фабричного метода
class DogFactory
{
public:
    static DogPtr CreateRandomDog()
    {
        // Генерируем случайные параметры
        DogSpecies species = static_cast<DogSpecies>(rand() % 5);
        ColorEnum color = static_cast<ColorEnum>(rand() % 4);
        SizeEnum size = static_cast<SizeEnum>(rand() % 4);

        // Создаем случайную собаку
        switch (species)
        {
            case DogSpecies::Dachshund: return new Dachshund(color, size);
            case DogSpecies::Spitz: return new Spitz(color, size);
            case DogSpecies::Husky: return new Husky(color, size);
            case DogSpecies::Labrador: return new Labrador(color, size);
            case DogSpecies::Alabai: return new Alabai(color, size);
            default: return nullptr;
        }
    }
};

