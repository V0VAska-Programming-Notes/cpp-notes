#pragma once

namespace pointerless
{

template<typename T>
class SingletonBase
{
public:
	static T& Get() noexcept
	{
		static T _instance;
		return _instance;
	}
	~SingletonBase() = default;
	SingletonBase(const SingletonBase<T>&) = delete;
	T& operator= (const SingletonBase<T>&) = delete;
protected:
	SingletonBase() = default;
};

class Singleton : public SingletonBase<Singleton>
{
	friend SingletonBase;
public:
	void DoSomething() noexcept;
private:
	Singleton() = default;
};

} // namespace pointerless
