#pragma once

#include <iostream>

namespace simple
{
	template<typename T>
	void do_smth(T&&);

	template<typename T>
	auto do_smth_ret(T&& fn) -> decltype(fn());

	void some_void() noexcept;

	int some_int() noexcept;
} // namespace simple

void simple_demo() noexcept;
