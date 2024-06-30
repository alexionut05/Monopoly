#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <memory>
#include <mutex>

template <typename T>
class Singleton {
public:
	template <typename... Args>
	static T& GetInstance(Args&&... args)
	{
		std::call_once
			( initInstanceFlag
			, &Singleton::InitSingleton<Args...>
			, std::forward<Args>(args)...
			);
		return *instance;
	}

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

protected:
	Singleton() = default;
	virtual ~Singleton() = default;

private:
	template <typename... Args>
	static void InitSingleton(Args&&... args)
	{
		instance.reset(new T(std::forward<Args>(args)...));
	}

	static std::unique_ptr<T> instance;
	static std::once_flag initInstanceFlag;
};

template <typename T>
std::unique_ptr<T> Singleton<T>::instance = nullptr;

template <typename T>
std::once_flag Singleton<T>::initInstanceFlag;

#endif // "SINGLETON_HPP"