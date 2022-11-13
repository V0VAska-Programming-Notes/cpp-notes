#pragma once

#if defined USE_SMART_POINTERS && USE_SMART_POINTERS == 1
#include <memory>
#include <functional>
#endif // USE_SMART_POINTERS

namespace smart_pointers
{

class MyClass
{
public:
	MyClass() = default;
	~MyClass();
	void Foo() const noexcept;
	void Release() noexcept;
};

MyClass* getMyClass() noexcept;
//void smart_pointers_func();

#if defined USE_SMART_POINTERS && USE_SMART_POINTERS == 1
typedef std::shared_ptr<MyClass> MyClassPtr;
#endif // USE_SMART_POINTERS

} // namespace smart_pointers
