#include <iostream>

#include "simple.h"
#include "pointerless.h"
#include "classic.h"

int main()
{
    simple::Singleton* obj = simple::Singleton::Get();
    obj->SomethingToDo();
    //simple::Singleton a;
    //simple::Singleton b = *obj;
    //simple::Singleton c = std::move(*obj);
    //simple::Singleton* obj1 = new simple::Singleton;
    //simple::Singleton* obj2;
    //*obj2 = *obj;
    //*obj2 = std::move(*obj);

    pointerless::Singleton::Get().DoSomething();

    classic::Singleton* classicObj = classic::Singleton::instance();
    classicObj->DoSomething();

    return 0;
}
