#include <iostream>

#include "classic.h"

namespace classic
{
    void Singleton::DoSomething() noexcept
    {
        std::cout << "classic::DoSomething()" << std::endl;
    }
} // namespace classic
