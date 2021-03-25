/*
Вариант: 21
Процедура: Удаление всех повторов
Вид дерева: Дерево поиска 
Обход дерева: Обратный

В программе необходимо реализовать:
1. Структуру, необходимую для создания бинарного дерева.
2. Функцию, выполняющую процедуру, соответствующую заданию для
обработки построенного дерева.
3. Сохранение результатов выполнения процедуры в файл с учётом обхода,
соответствующего варианту

1. Числа в исходном файле записаны в одну строку, через одиночный пробел.
2. Результат работы программы записываются также в одну строку, через
одиночный пробел.
3. Дерево поиска и сбалансированное дерево — это разные деревья. Определение
сбалансированного дерева не содержит информации об упорядочивании
элементов на основе их значений. Дерево поиска ничего не говорит об особой
структуре дерева.
4. В любой непонятной ситуации ссылаться сначала «влево». Пример:
- для дерева поиска. В случае, если число больше корневого элемента –
«вправо», иначе (меньше или равно) – «влево»,
- для сбалансированного дерева – сначала добавлять элемент «влево».
*/

#include <iostream>
#include <fstream>

using namespace std;

struct node
{
	double value;
	node* left;
	node* right;
};

void insert(node*& root, double x)
{
	if (!root)
	{
		root = new node;
		root->right = NULL;
		root->left = NULL;
		root->value = x;
	}
	else
	{
		if (x > root->value)
		{
			if (root->right)
			{
				insert(root->right, x);
			}
			else
			{
				root->right = new node;
				root->right->left = NULL;
				root->right->right = NULL;
				root->right->value = x;
			}
		}
		else
		{
			if (root->left)
			{
				insert(root->left, x);
			}
			else
			{
				root->left = new node;
				root->left->left = NULL;
				root->left->right = NULL;
				root->left->value = x;
			}
		}
	}
}

void inputTreeFromFile(node*& root)
{
	double temp;
	ifstream fin("input.txt");
	if (!fin.is_open()) throw("I tried to find the file, but you decided not to create it ;(");
	while(!fin.eof())
	{
		fin >> temp;
		insert(root, temp);
	}
	fin.close();
}

void deleteRepeat(node*& root)
{
	if(root)
	{
		if (root->left)
		{
			if (root->value == root->left->value)
			{
				node* temp = root->left;
				root->left = root->left->left;
				delete temp;
			}
			deleteRepeat(root);
		}
		if (root->right)
		{
			deleteRepeat(root->right);
		}
	}
}

void printTree(node*& root)
{
	if (root)
	{
		if (root->left) printTree(root->left);
		if (root->right) printTree(root->right);
		cout << root->value << " ";
	}
}

int main()
{
	node* root = NULL;
	inputTreeFromFile(root);
	//printTree(root);
	deleteRepeat(root);
	printTree(root);
	return 0;
}