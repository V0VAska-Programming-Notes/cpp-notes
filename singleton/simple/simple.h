#pragma once

namespace simple
{

template<typename T>
class SingletonBase
{
public:
	static T* Get() noexcept
	{
		if (!_instance)
		{
			_instance = new T;
		}
		return _instance;
	}

	SingletonBase(const SingletonBase<T>&) = delete;
	T& operator= (const SingletonBase<T>&) = delete;
protected:
	SingletonBase() = default;
private:
	static T* _instance;
};

template<typename T>
T* SingletonBase<T>::_instance = nullptr;

class Singleton: public SingletonBase<Singleton>
{
	friend SingletonBase;
public:
	void SomethingToDo() noexcept;
private:
	Singleton() = default;
};

} // namespace simple
