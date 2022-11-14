#include <iostream>

#include "simple.h"

namespace simple
{

template<typename T>
void do_smth(T&& fn)
{
	fn();
}

template<typename T>
auto do_smth_ret(T&& fn) -> decltype(fn())
{
	return fn();
}

void some_void() noexcept
{
	std::cout << "void some_void()" << std::endl;
}

int some_int() noexcept
{
	std::cout << "int some_int()" << std::endl;
	return 10;
}

} // namespace simple

void simple_demo() noexcept
{
	auto some_lambda = [=]()
	{
		std::cout << "auto some_lambda()" << std::endl;
		return 10.5;
	};

	simple::do_smth(simple::some_void);
	simple::do_smth(simple::some_int);
	simple::do_smth(some_lambda);
	std::cout << "-------------------------" << std::endl;
	auto val_int = simple::do_smth_ret(simple::some_int);
	std::printf("returned %i\n\n", val_int);
	
	auto val_double = simple::do_smth_ret(some_lambda);
	std::printf("returned %f\n\n", val_double);
}
