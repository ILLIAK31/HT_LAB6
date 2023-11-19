// ALGO2 IS1 224B LAB06
// ILLIA KARMAZIN
// ki53819@zut.edu.pl
#include <iostream>
#include <string>
#include <list>

class Obj
{
public:
	Obj()=default;
	Obj(std::string Key, int Value);
	~Obj();
	std::string key;
	int value;
	Obj* prev{ nullptr };
	Obj* next{ nullptr };
};


Obj::Obj(std::string Key, int Value):key(Key),value(Value){}

Obj::~Obj(){}

template <class T>
class TH
{
public:
	TH()=default;
	~TH();
	int size{ 0 }, Max_Size{ 1 } , Expansion{ 2 };
	Obj** objs = new Obj*[Max_Size];
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
		index += (key[i] * pow(31, key.length() - i + 1));
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
		Obj* obj = new Obj(key, value);
		objs[index] = obj;
		obj = nullptr;
		delete obj;
	}
	else
	{
		Obj* obj = new Obj(key, value);
		int i = 0;
		for (;objs[i]->next != nullptr;++i){}
		objs[i]->next = obj;
		objs[i]->next->prev = objs[i];
		obj = nullptr;
		delete obj;
	}
}

int main()
{
	TH<int>* th = new TH<int>();
	th->Add("Manish", 16);
	return 0;
}