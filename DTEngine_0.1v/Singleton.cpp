#include "pch.h"
#include "Singleton.h"


template <typename T>
Singleton<T>::Singleton()
{
}

template <typename T>
Singleton<T>::~Singleton()
{
}


template <typename T>
T& Singleton<T>::GetInstance()
{
	static T instance;
	return instance;
}