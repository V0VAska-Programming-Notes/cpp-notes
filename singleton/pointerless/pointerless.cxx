#include <iostream>

#include "pointerless.h"

namespace pointerless
{

void Singleton::DoSomething() noexcept
{
	std::cout << "pointerless::DoSomething()" << std::endl;
}

} // namespace pointerless
