#include <iostream>
using namespace std;
class Data
{
	virtual int GetSize() const = 0;
	virtual void Push(const int& element) = 0; //int -> T<template>
	virtual int Pop() = 0; //int -> T<template>
	virtual int Peek() = 0; //int -> T<template>
};
struct comp
{
	int Data;
	comp* next;
	comp* prev;
};

class Stack : public Data
{
public:
Stack()
{
	x = NULL;
	x = new comp();
	x->next = NULL;
	x->prev = NULL;
}
Stack(const Stack& other)
{
	int i = 0;
	comp* d = other.x;
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
	comp* q = x;
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
	comp* d = other.x;
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
	comp* d = other.x;
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
friend ostream& operator<<(ostream& stream, const Stack* instance);
comp* x;
int Pop() override
{
	int ret;
	comp* q = x;
	ret = x->Data;
	q = x->next;
	delete x;
	x = q;
	q->prev = NULL;
}
void check() 
{
	if (x->next == nullptr)
	{
		cout << "Empty Stack" << endl;
	}
}
int Peek() override
{
	int ret;
	ret = x->Data;
	return ret;
}
void Push(const int &D) override
{
	comp** c = &x;
	comp* q; //Создаем новый указатель q типа структуры comp. По сути это и есть наш новый элемент
	q = new comp(); //выделяем память для нового элемента
	comp* pr = *c;

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

	int count = 9;
};
ostream& operator<<(ostream& str, const Stack* stack)
{
	comp* q = stack->x;
	while (q)
	{
		str << q->Data << endl;
		q = q->next;
	}
	return str;
}


//Новая структура
class Mass : public Data
{
public:
	Mass(int count);
	Mass(const Mass& other);
	Mass(Mass&& other);
	Mass& operator=(const Mass& other);
	~Mass();
	int GetSize() const;
	void Push(const int &element);
	int Pop();
	bool Check();
	int Peek();
	friend ostream& operator<<(ostream& str, Mass& mass);
private:
	int i = 0;
	int* arr;
	int count;
};
ostream& operator<<(ostream& str, Mass& mass)
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


Mass::Mass(int count)
	: count(count)
{
	arr = new int[count];
}
Mass::~Mass()
{
	delete[] arr;
}
Mass::Mass(const Mass& other)
{
	arr = new int[other.count];
	count = other.count;
	for (int i = 0; i < count; ++i)
	{
		arr[i] = other.arr[i];
	}
}

Mass& Mass::operator=(const Mass& other)
{
	if (this == &other)
	{
		return *this;
	}
	delete[] arr;
	arr = new int[other.count];
	count = other.count;
	for (int i = 0; i < count; ++i)
	{
		arr[i] = other.arr[i];
	}
}
int Mass::GetSize() const
{
	return count;
}
void Mass::Push(const int& element)
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
bool Mass::Check()
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
int Mass::Pop()
{
	if (Check())
	{
		--i;
		return arr[i + 1];
	}
	else
	{
		std::cout << "Empty" << "\n";
		return 0;
	}
}
Mass::Mass(Mass&& other)
{
	arr = other.arr;
	count = other.count;
	other.arr = nullptr;
}
int Mass::Peek()
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
