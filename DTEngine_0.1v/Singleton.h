#pragma once

template <typename T>
class Singleton
{
private:
	Singleton();
	virtual ~Singleton();

public:
	static T& GetInstance() {
		static T instance;
		return instance;
	}
};

