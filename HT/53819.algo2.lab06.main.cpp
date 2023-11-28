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
	Obj()=default;
	Obj(std::string Key, int Value);
	~Obj();
	std::string key;
	T value;
	Obj* prev{ nullptr };
	Obj* next{ nullptr };
};

template<class T>
Obj<T>::Obj(std::string Key, int Value) : key(Key),value(Value){}

template <class T>
Obj<T>::~Obj(){}

template <class T>
class TH
{
public:
	TH();
	~TH();
	int size{ 0 }, Max_Size{ 1 } , Expansion{ 2 };
	Obj<T>** objs = new Obj<T>*[Max_Size];
	int HashFunc(std::string key);
	void Add(std::string key, T value);
	Obj<T>* Search(std::string key);
	bool Delete(std::string key);
	void Clear();
};

template<class T>
TH<T>::TH()
{
	for (int i = 0; i < Max_Size; ++i)
	{
		objs[i] = nullptr;
	}
}

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
	if (this->size + 1 > this->Max_Size)
	{
		this->Max_Size *= this->Expansion;
		Obj<T>** copy_objs = this->objs;
		this->objs = nullptr;
		this->objs = new Obj<T>*[Max_Size];
		for (int i = 0; i < Max_Size; ++i)
		{
			objs[i] = nullptr;
		}
		for (int i = 0; i < this->size; ++i)
		{
			this->objs[i] = copy_objs[i];
		}
	}
	int index = HashFunc(key);
	if (objs[index] == nullptr)
	{
		Obj<T>* obj = new Obj<T>(key, value);
		objs[index] = obj;
		obj = nullptr;
		delete obj;
	}
	else
	{
		Obj<T>* obj = new Obj<T>(key, value);
		Obj<T>* obj2 = objs[index];
		bool flag = false;
		while (obj2->next != nullptr)
		{
			if (obj2->key == obj->key)
			{
				obj2->value = obj->value;
				flag = true;
				break;
			}
			obj2 = obj2->next;
		}
		if (!flag)
		{
			obj2->next = obj;
			obj->prev = obj2;
		}
		obj = nullptr;
		delete obj;
		obj2 = nullptr;
		delete obj2;
	}
	++this->size;
}

template<class T>
Obj<T>* TH<T>::Search(std::string key)
{
	for (int index = 0; index <= this->size; ++index)
	{
		if (this->objs[index] == nullptr)
		{
			continue;
		}
		else
		{
			Obj<T>* obj2 = objs[index];
			while (obj2 != nullptr)
			{
				if (obj2->key == key)
				{
					return obj2;
				}
				obj2 = obj2->next;
			}
		}
	}
	return nullptr;
}

template<class T>
bool TH<T>::Delete(std::string key)
{
	for (int index = 0; index <= this->size; ++index)
	{
		if (this->objs[index] == nullptr)
		{
			continue;
		}
		else
		{
			Obj<T>* obj2 = objs[index];
			while (obj2 != nullptr)
			{
				if (obj2->key == key)
				{
					if (obj2->prev != nullptr && obj2->next != nullptr)
					{
						obj2->prev->next = obj2->next;
						obj2->next->prev = obj2->prev;
					}
					else if (obj2->prev == nullptr && obj2->next != nullptr)
					{
						this->objs[index] = obj2->next;
						obj2->next->prev = nullptr;
					}
					else if(obj2->prev != nullptr && obj2->next == nullptr)
					{
						obj2->prev->next = nullptr;
					}
					else if (obj2->prev == nullptr && obj2->next == nullptr)
					{
						this->objs[index] = nullptr;
					}
					delete obj2;
					obj2 = nullptr;
					return true;
				}
				obj2 = obj2->next;
			}
		}
	}
	return false;
}

template<class T>
void TH<T>::Clear()
{
	//
}

int main()
{
	TH<int>* th = new TH<int>();
	th->Add("Manish", 16);
	th->Add("Vartika", 14);
	th->Add("ITT", 5);
	th->Add("elite_Programmer", 4);
	th->Add("pluto14", 14);
	th->Add("GeeksForGeeks", 11);
	//
	// Clear
	//
	return 0;
}