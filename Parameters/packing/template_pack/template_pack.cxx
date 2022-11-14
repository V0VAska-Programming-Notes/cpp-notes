#include <iostream>

#include "template_pack.h"

namespace pack
{

void fn_handle(double param1, int param2)
{
	std::cout << param1 << " " << param2 << std::endl;
}

template<typename... Targs>
void fn(Targs... args)
{
	std::cout << "params count: " << sizeof...(args) << std::endl;
	fn_handle(args...);
}

void tprintf(const char* format) // base function
{
	std::cout << format;
}

template<typename T, typename... Targs>
void tprintf(const char* format, T value, Targs... args) // recursive variadic function
{
	for (; *format != 0; format++)
	{
		if (*format == '%')
		{
			std::cout << value;
			tprintf(format + 1, args...); // recursive call
			return;
		}
		std::cout << *format;
	}
}

} // namespace pack

void template_pack_test1() noexcept
{
	pack::fn(1.0, 5);
}

void template_pack_test2() noexcept
{
	pack::tprintf("% world% %\n", "Hello", '!', 123);
}
