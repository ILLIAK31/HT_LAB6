// ALGO2 IS1 224B LAB06
// ILLIA KARMAZIN
// ki53819@zut.edu.pl
#include <iostream>
#include <string>
#include <list>

template <class T>
class Obj
{
public:
	Obj();
	~Obj();
	std::string key;
	T value;
	Obj* prev{ nullptr };
	Obj* next{ nullptr };
};

template <class T>
Obj<T>::~Obj(){}

template <class T>
class TH
{
public:
	TH()=default;
	~TH();
	int size{ 0 }, Max_Size{ 1 } , Expansion{ 2 };
	Obj<int>** objs = new Obj<int>*[Max_Size];
	int HashFunc(std::string key);
	void Add(std::string key, T value);
};

template <class T>
TH<T>::~TH() {}

template<class T>
int TH<T>::HashFunc(std::string key)
{
	int index = 0;
	for (int i = 0; i < key.length(); ++i)
	{
		index += (int(key[i]) * pow(31, key.length() - i + 1));
	}
	index %= this->Max_Size;
	index = abs(index);
	return index;
}

template<class T>
void TH<T>::Add(std::string key, T value)
{
	int index = HashFunc(key);
	if (objs[index] == nullptr)
	{
		//
	}
	else
	{
		//
	}
}

int main()
{
	TH<int>* th = new TH<int>();
	//
	return 0;
}