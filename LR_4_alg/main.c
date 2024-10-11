#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include "string.h"


struct Node {
	int data;
	struct Node* left;
	struct Node* right;
};

struct Node* root;

struct Node* CreateTree(struct Node* root, struct Node* r, int data)
{
	if (r == NULL)
	{
		r = (struct Node*)malloc(sizeof(struct Node));
		if (r == NULL)
		{
			printf("Ошибка выделения памяти");
			exit(0);
		}

		r->left = NULL;
		r->right = NULL;
		r->data = data;
		if (root == NULL) return r;

		if (data > root->data)	root->left = r;
		else root->right = r;
		return r;
	}

	if (data > r->data)
		CreateTree(r, r->left, data);
	else
		CreateTree(r, r->right, data);

	return root;
}

struct Node* find(struct Node* root, int data) {

	if (root->data == data)return root;
	if (root->data > data && root->right != NULL) find(root->right, data);
	else if (root->left != NULL) find(root->left, data);
	else return NULL;

}

int count(struct Node* root, int data, int cnt) {

	if (root->data == data) cnt++;

	if (root->data >= data && root->right != NULL)cnt = count(root->right, data, cnt);
	else if (root->left != NULL)cnt = count(root->left, data, cnt);
	else return cnt;

}

void print_tree(struct Node* r, int l)
{

	if (r == NULL)
	{
		return;
	}

	print_tree(r->right, l + 1);
	for (int i = 0; i < l; i++)
	{
		printf(" ");
	}

	printf("%d\n", r->data);
	print_tree(r->left, l + 1);
}

int main()
{
	setlocale(LC_ALL, "Rus");
	int D, start = 1, c = 0;

	root = NULL;
	printf("-1 - окончание построения дерева\n");
	while (start)
	{
		printf("Введите число: ");
		scanf_s("%d", &D);
		if (D == -1)
		{
			printf("Построение дерева окончено\n\n");
			start = 0;
		}
		else
			root = CreateTree(root, root, D);

	}

	print_tree(root, 0);
	int a = 0;
	printf("\nВведите искомое число: ");
	scanf_s("%d", &a);

	struct Node* r = find(root, a);
	if (r) printf("Искомое число: %d\n", r->data);
	else printf("Not found");

	int b = 0;
	printf("\nВведите число для подсчета его вхождений: ");
	scanf_s("%d", &b);
	int cnt;
	cnt = count(root, b, 0);
	printf("Счетчик: %d", cnt);

	scanf_s("%d", &D);
	return 0;
}

