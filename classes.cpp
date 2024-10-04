#include <iostream>

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
    bool BoyIsGood = false;
    SizeEnum Size;
    ColorEnum Color;
    DogSpecies Species;
public:
    bool IsGood() {return BoyIsGood;}
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
