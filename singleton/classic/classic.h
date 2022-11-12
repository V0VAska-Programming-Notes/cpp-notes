#pragma once

#include <atomic>
#include <mutex>

namespace classic
{

template<typename T>
class SingletonBase
{
private:
	static std::atomic<T*> _instance;
	static std::mutex instatiation_mutex;
public:
	static T* instance() noexcept
	{
		T* tmp = _instance.load(std::memory_order_consume);
		if (!tmp)
		{
			std::lock_guard<std::mutex> guard(instatiation_mutex);
			tmp = _instance.load(std::memory_order_consume);
			if (!tmp)
			{
				tmp = new T;
				_instance.store(tmp, std::memory_order_release);
			}
		}
		return tmp;
	}
    SingletonBase(const SingletonBase<T>&) = delete;
    T& operator= (const SingletonBase<T>&) = delete;
protected:
    SingletonBase() = default;
};

template<typename T>
std::mutex SingletonBase<T>::instatiation_mutex;

template<typename T>
std::atomic<T*> SingletonBase<T>::_instance{nullptr};

class Singleton : public SingletonBase<Singleton>
{
    friend SingletonBase;
public:
    void DoSomething() noexcept;
private:
    Singleton() = default;
};

} // namespace classic
