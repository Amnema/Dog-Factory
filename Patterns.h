#ifndef PatternsH
#define PatternsH

// пишем шаблон итератора

template<class Type>
class Iterator
{
protected:
    Iterator() {}

public:
    virtual ~Iterator() {} // диструктор
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() const = 0;
    virtual Type GetCurrent() const = 0;
};
/*
//декоратор
template<class Type>
class IteratorDecorator : public Iterator<Type>
{
protected:
    Iterator<Type> *It;

public:
    IteratorDecorator(Iterator<Type> *it)
    {
        It = it;
    }

    virtual ~IteratorDecorator() { delete It; } // диструктор
    void First() { It->First(); }
    void Next() { It->Next(); }
    bool IsDone() const { return It->IsDone(); }
    Type GetCurrent() const { return It->GetCurrent(); }

};
*/
#endif // PatternsH
