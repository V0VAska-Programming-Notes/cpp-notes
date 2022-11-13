#include <iostream>

#include "SmartPointers.h"

namespace smart_pointers
{

MyClass::~MyClass()
{
	std::wcout << L"Oops, I thought: life has just begun." << std::endl;
}

void MyClass::Foo() const noexcept
{
	std::wcout << L"Просто Фу()." << std::endl;
}

void MyClass::Release() noexcept
{
	delete this;
}

MyClass* getMyClass() noexcept
{
	return new MyClass;
}

} // namespace smart_pointers
