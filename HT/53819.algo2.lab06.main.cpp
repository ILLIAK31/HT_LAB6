// ALGO2 IS1 224B LAB06
// ILLIA KARMAZIN
// ki53819@zut.edu.pl
#include <iostream>
#include <string>
#include <vector>

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
	void Print();
	void Rehash();
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
		Rehash();
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
	if (this->size == 0)
		return nullptr;
	for (int index = 0; index < this->Max_Size; ++index)
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
	for (int index = 0; index < this->Max_Size; ++index)
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
	for (int i = 0; i < this->Max_Size; ++i)
	{
		if (this->objs[i] == nullptr)
		{
			continue;
		}
		else
		{
			Obj<T>* obj2 = objs[i];
			while (obj2 != nullptr)
			{
				if (obj2->next != nullptr)
				{
					obj2 = obj2->next;
					this->Delete(obj2->prev->key);
				}
				else
				{
					this->Delete(obj2->key);
					break;
				}
			}
			obj2 = nullptr;
			delete obj2;
		}
	}
	this->size = 0;
	this->Max_Size = 1;
	this->objs = nullptr;
}

template<class T>
void TH<T>::Print()
{
	std::cout << "\t| Hash Table |\n";
	std::cout << "\t| Size : " << this->size << " |\n";
	std::cout << "\t| Max size : " << this->Max_Size << " |\n";
	for (int i = 0; i < this->Max_Size; ++i)
	{
		if (this->size == 0)
			break;
		if (this->objs[i] == nullptr)
		{
			continue;
		}
		else
		{
			Obj<T>* obj2 = objs[i];
			while (obj2 != nullptr)
			{
				int index = HashFunc(obj2->key);
				std::cout << i << " | " << obj2->key << " -> " << obj2->value << " | ";
				if (obj2->next == nullptr)
					break;
				obj2 = obj2->next;
			}
			std::cout << std::endl;
			obj2 = nullptr;
			delete obj2;
		}
	}
	std::cout << "\t| Min size : 1 |\n" << "\t| Max size : " << this->Max_Size << " |\n";
}

template<class T>
void TH<T>::Rehash()
{
	std::vector<Obj<T>*> links;
	for (int i = 0; i < Max_Size; ++i)
	{
		if (this->size == 0)
			break;
		if (objs[i] == nullptr)
		{
			continue;
		}
		else
		{
			Obj<T>* obj2 = objs[i];
			while (obj2 != nullptr)
			{
				links.push_back(obj2);
				if (obj2->next == nullptr)
					break;
				else
					obj2 = obj2->next;
			}
		}
	}
	this->Max_Size *= this->Expansion;
	this->objs = new Obj<T>*[Max_Size];
	for (int i = 0; i < Max_Size; ++i)
	{
		objs[i] = nullptr;
	}
	for (int l = 0; l < links.size(); ++l)
	{
		Obj<T>* OBJ = links[l];
		OBJ->prev = OBJ->next = nullptr;
		std::string key = OBJ->key;
		T value = OBJ->value;
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
		OBJ = nullptr;
		delete OBJ;
	}
}

std::string RK()
{
	std::vector<char> L =
	{
	'a', 'b', 'c', 'd', 'e',
	'f','g', 'h', 'i', 'j',
	'k','l', 'm', 'n', 'o',
	'p','q', 'r', 's', 't',
	'u','v', 'w', 'x', 'y',
	'z','A', 'B', 'C', 'D',
	'E','F', 'G', 'H','I',
	'J','K', 'L', 'M', 'N',
	'O','P', 'Q', 'R', 'S',
	'T','U', 'V', 'W', 'X',
	'Y', 'Z'
	};
	std::string KEY = "";
	for (int index = 0; index < 6; ++index)
	{
		KEY += L[rand() % 52];
	}
	return KEY;
}

int main()
{
	TH<int>* th = new TH<int>();
	int hit{ 0 };
	double avr{ 0 };
	clock_t timer1, timer2, timer3, timer4;
	timer1 = clock();
	for (int index = 0; index < 1000; ++index)
	{
		std::string key = RK();
		timer3 = clock();
		th->Add(key, index);
		timer4 = clock();
		avr += (timer4 - timer3) / (double)CLOCKS_PER_SEC;
		key = "";
	}
	timer2 = clock();
	th->Print();
	avr /= 1000;
	avr *= 1000;
	std::cout << "| Full time : " << (timer2-timer1)/(double)CLOCKS_PER_SEC << " s | Average time : " << avr << " ms |\n";
	avr = 0;
	timer1 = clock();
	for (int index = 0; index < 1000; ++index)
	{
		std::string key = RK();
		timer3 = clock();
		Obj<int>* OBJ = th->Search(key);
		timer4 = clock();
		if (OBJ != nullptr)
			++hit;
		avr += (timer4 - timer3) / (double)CLOCKS_PER_SEC;
	}
	timer2 = clock();
	avr /= 1000;
	avr *= 1000;
	std::cout << "| Full time : " << (timer2 - timer1) / (double)CLOCKS_PER_SEC << " s | Average time : " << avr << " ms | Hits : " << hit << " |\n";
	th->Clear();
	delete th;
	return 0;
}