#include <iostream>
using namespace std;
template<typename T>
class Data
{
public:
	virtual int GetSize() const = 0;
	virtual void Push(const T& element) = 0; //int -> T<template>
	virtual T Pop() = 0; //int -> T<template>
	virtual T Peek() = 0; //int -> T<template>
};
template<typename T>
ostream& operator<<(ostream& str, Data<T> *mass)
{
	Data<T> *t = mass;
	int k = t->GetSize();
	for (int i = 0; i < k; ++i)
	{
		str << t->Pop() << " ";
	}
	str << "\n";
	return str;
}
template<typename T>
ostream& operator<<(ostream& str, Data<T>& mass)
{
	Data<T> &t = mass;
	int k = t.GetSize();
	for (int i = 0; i < k; ++i)
	{
		str << t.Pop() << " ";
	}
	str << "\n";
	return str;
}
template<typename T>
void testUkazatel(Data<T>* ukaz)
{
	ukaz->Push("Lexa");
	ukaz->Push("tor");
	ukaz->Push("Log");
	cout << ukaz;
}
template<typename T>
void testSsilka(Data<T>& ukaz)
{
	ukaz.Push("Petya");
	ukaz.Push("Bor");
	ukaz.Push("Sarra");
	cout << ukaz;
}
template<typename T>
struct comp
{
	T Data;
	comp* next;
	comp* prev;
};
template <typename T>
class Stack : public Data<T>
{
public:
	Stack()
	{
		x = NULL;
		x = new comp<T>();
		x->next = NULL;
		x->prev = NULL;
	}
	Stack(const Stack& other)
	{
		int i = 0;
		comp<T>* d = other.x;
		while (d->next)
		{
			++i;
			d = d->next;//после того как вывели передвигаем b на следующий элемент(ячейку)
		}
		for (int b = 0; b <= i; ++b)
		{
			Push(d->Data);
			d = d->prev;
		}
	}
	Stack(Stack&& other)
	{
		x = other.x;
		other.x = NULL;
	}
	~Stack()
	{
		comp<T>* q = x;
		while (x->next)
		{
			q = x->next;
			delete x;
			x = q;
		}
		x = nullptr;
	}

	Stack& operator=(const Stack& other)
	{
		int i = 0;
		if (this == &other)
		{
			return *this;
		}
		while (x)
		{
			Pop();
		}
		comp<T>* d = other.x;
		while (d->next)
		{
			++i;
			d = d->next;//после того как вывели передвигаем b на следующий элемент(ячейку)
		}
		for (int b = 0; b <= i; ++b)
		{
			Push(d->Data);
			d = d->prev;
		}
	}

	Stack& operator=(Stack&& other)
	{
		int i = 0;
		if (this == &other)
		{
			return *this;
		}
		while (x)
		{
			Pop();
		}
		comp<T>* d = other.x;
		while (d->next)
		{
			++i;
			d = d->next;//после того как вывели передвигаем b на следующий элемент(ячейку)
		}
		for (int b = 0; b <= i; ++b)
		{
			Push(d->Data);
			d = d->prev;
		}
		while (other.x)
		{
			other.Pop();
		}
	}

	template<typename T>
	friend ostream& operator<<(ostream& stream, const Stack<T>* stack);
	comp<T>* x;
	T Pop()
	{
		T ret;
		--count;
		comp<T>* q = x;
		ret = x->Data;
		q = x->next;
		delete x;
		x = q;
		q->prev = NULL;
		return ret;
	}
	void check()
	{
		if (x->next == nullptr)
		{
			cout << "Empty Stack" << endl;
		}
	}
	T Peek()
	{
		T ret = x->Data;
		return ret;
	}
	int GetSize() const
	{
		return count;
	}
	void Push(const T& D)
	{
		comp<T>** c = &x;
		comp<T>* q; //Создаем новый указатель q типа структуры comp. По сути это и есть наш новый элемент
		q = new comp<T>(); //выделяем память для нового элемента
		comp<T>* pr = *c;
		++count;
		q->Data = D; //Записываем необходимое число  в Data элемента
		if (*c == NULL)
		{
			*c = q; //вершиной стека будет новый элемент
		}
		else //если стек не пустой
		{
			q->next = *c; //Проводим связь от нового элемента, к вершине. Тоесть кладем книжку на вершину стопки.
			pr->prev = q;
			*c = q; //Обозначаем, что вершиной теперь является новый элемент
		}
	}
private:

	int count = 0;
};
template<typename T>
ostream& operator<<(ostream& str, const Stack<T>* stack)
{
	comp<T>* q = stack->x;
	while (q)
	{
		str << q->Data << endl;
		q = q->next;
	}
	return str;
}



//Новая структура
template<typename T>
class Mass : public Data<T>
{
public:
	Mass(int count);
	Mass(const Mass& other);
	Mass(Mass&& other);
	Mass& operator=(const Mass& other);
	~Mass();
	int GetSize() const;
	void Push(const T &element);
	T Pop();
	bool Check();
	T Peek();
	template<typename T> friend ostream& operator<<(ostream& str, Mass<T>& mass);
private:
	int i = 0;
	T* arr;
	int count;
};

template<typename T>
ostream& operator<<(ostream& str, Mass<T>& mass)
{
	if (mass.Check())
	{
		for (int i = 0; i < mass.i; i++)
		{
			str << mass.arr[i] << " ";
		}
	}
	else
	{
		str << "Empty";
	}
	return str;
}

template<typename T>
Mass<T>::Mass(int count)
	: count(count)
{
	arr = new T[count];
}
template<typename T>
Mass<T>::~Mass()
{
	delete[] arr;
}
template<typename T>
Mass<T>::Mass(const Mass& other)
{
	arr = new T[other.count];
	count = other.count;
	for (int i = 0; i < count; ++i)
	{
		arr[i] = other.arr[i];
	}
}

template<typename T>
Mass<T>& Mass<T>::operator=(const Mass<T>& other)
{
	if (this == &other)
	{
		return *this;
	}
	delete[] arr;
	arr = new T[other.count];
	count = other.count;
	for (int i = 0; i < count; ++i)
	{
		arr[i] = other.arr[i];
	}
}
template<typename T>
int Mass<T>::GetSize() const
{
	return i;
}
template<typename T>
void Mass<T>::Push(const T& element)
{
	if (i < count)
	{
		arr[i] = element;
		i++;
	}
	else
	{
		std::cout << "Overflow" << "\n";
	}
}
template<typename T>
bool Mass<T>::Check()
{
	if (i == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
template<typename T>
T Mass<T>::Pop()
{
	if (Check())
	{
		--i;
		return arr[i];
	}
	else
	{
		std::cout << "Empty" << "\n";
		return arr[0];
	}
}
template<typename T>
Mass<T>::Mass(Mass<T>&& other)
{
	arr = other.arr;
	count = other.count;
	other.arr = nullptr;
}
template<typename T>
T Mass<T>::Peek()
{
	if (Check())
	{
		return arr[i - 1];
	}
	else
	{
		std::cout << "Empty. Exiting with code ";
		return 0;
	}
}