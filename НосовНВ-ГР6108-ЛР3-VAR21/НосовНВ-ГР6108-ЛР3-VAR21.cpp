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

struct node  // Структура узла дерева
{
	double value;   // Значение узла
	node* left;     // Указатель на левого
	node* right;    // Указатель на правого
};

void insert(node*& root, double x)  // Обычная вставка элемента в бинарное дерево поиска (с повторами)
{
	if (!root)  // Если корня нет
	{
		root = new node;   // Создаём новый элемент
		root->right = NULL;
		root->left = NULL;
		root->value = x;
	}
	else
	{
		if (x > root->value)  // Элемент нужно вставить справа от текущего узла
		{
			if (root->right)  // Если указатель на правый существует
			{
				insert(root->right, x);  
			}
			else
			{
				root->right = new node;  // Если указатель на правый элемент пуст, то инициализируем его новым элементом
				root->right->left = NULL;
				root->right->right = NULL;
				root->right->value = x;
			}
		}
		else  // Элемент нужно вставить слева от текущего узла
		{
			if (root->left) // Если указатель на левый существует
			{
				insert(root->left, x);
			}
			else
			{
				root->left = new node;  //  Если указатель на левый элемент пуст, то инициализируем его новым элементом
				root->left->left = NULL;
				root->left->right = NULL;
				root->left->value = x;
			}
		}
	}
}

void insert2(node*& root, double x)  // Вставка только элементов, не имеющик повторы (с повторами ничего не делается)
{
	if (!root)  // Если корня нет
	{
		root = new node;   // Создаём новый элемент
		root->right = NULL;
		root->left = NULL;
		root->value = x;
	}
	else
	{
		if (x > root->value)  // Элемент нужно вставить справа от текущего узла
		{
			if (root->right)  // Если указатель на правый существует
			{
				insert2(root->right, x);
			}
			else
			{
				root->right = new node;  // Если указатель на правый элемент пуст, то инициализируем его новым элементом
				root->right->left = NULL;
				root->right->right = NULL;
				root->right->value = x;
			}
		}
		if (x < root->value) // Элемент нужно вставить слева от текущего узла
		{
			if (root->left) // Если указатель на левый существует
			{
				insert2(root->left, x);
			}
			else
			{
				root->left = new node;  //  Если указатель на левый элемент пуст, то инициализируем его новым элементом
				root->left->left = NULL;
				root->left->right = NULL;
				root->left->value = x;
			}
		}
	}
}

void inputTreeFromFile(node*& root) // Процедура получения дерева из файла
{
	double temp;
	ifstream fin("input.txt");  // Открываем файл
	if (!fin.is_open()) throw("I tried to find the file, but you decided not to create it ;("); // Если файл не открылся
	while(!fin.eof())  // Пока не конец файла
	{
		fin >> temp;  // Считываем элемент
		insert(root, temp);  // Вставляем его
	}
	fin.close();  // Закрываем файл
}

void copy(node*& root, node*& newRoot)  // Функция каждый элемент из дерева с корнем root вставляет (без повторов) в дерево с корнем newRoot
{
	if (root)  
	{
		insert2(newRoot, root->value);
		if (root->left) copy(root->left, newRoot);
		if (root->right) copy(root->right, newRoot);
	}

}

void deleteTree(node*& root)  // Удаление дерева
{
	if (root)
	{
		if (root->left) deleteTree(root->left);
		if (root->right) deleteTree(root->right);
		delete root;
	}
}

void deleteRepeat(node*& root)  // Процедура, удаляющая все повторы из дерева с корнем root
{
	node* newTree = NULL;  // Создаём указатель на новое дерево
	node* temp = root;  
	copy(root, newTree); // Переносим элементы из старого дерева в новое без копий
	root = newTree;  
	deleteTree(temp); // Удаляем старое дерево
}

void saveTreeToFile(ofstream& fout, node*& root)  // Сохранение дерева в файл обратным обходом
{
	if (root)
	{
		if (root->left) saveTreeToFile(fout, root->left);
		if (root->right) saveTreeToFile(fout, root->right);
		fout << root->value << " ";
	}
}

int main()
{
	node* root = NULL;
	inputTreeFromFile(root);
	deleteRepeat(root);
	ofstream fout("output.txt");
	saveTreeToFile(fout, root);
	deleteTree(root);
	fout.close();
	return 0;
}