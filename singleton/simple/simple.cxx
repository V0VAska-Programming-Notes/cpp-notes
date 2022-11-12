#include <iostream>

#include "simple.h"

namespace simple
{

void Singleton::SomethingToDo() noexcept
{
	std::cout << "simple::SomethingToDo()" << std::endl;
}

} // namespace simple
