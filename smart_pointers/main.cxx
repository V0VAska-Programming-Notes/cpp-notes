#include <iostream>
#ifdef WIN32
#include <fcntl.h>
#include <io.h>
#endif

#include "SmartPointers.h"

using namespace smart_pointers;

int main()
{
    setlocale(LC_ALL, "");
#ifdef WIN32
    _setmode(_fileno(stdout), _O_U16TEXT);
#endif // WIN32

#if defined USE_SMART_POINTERS && (USE_SMART_POINTERS == 1)
    {
        MyClass* (*p_GetMyClass)() = getMyClass;
        MyClassPtr myClassPtr(p_GetMyClass(), std::mem_fn(&MyClass::Release));
        if (myClassPtr)
        {
            myClassPtr->Foo();
        }
    } // end of myClassPtr life-time, so MyClass::Release() will be called
#else
    smart_pointers::MyClass* p = smart_pointers::getMyClass();
    p->Foo();
    p->Release();
#endif // !USE_SMART_POINTERS

    return 0;
}
