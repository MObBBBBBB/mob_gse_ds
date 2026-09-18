#include<iostream>
using namespace std;
typedef int status;

void swap(status* a, int x, int y) {
	int t = a[x];
	a[x] = a[y];
	a[y] = t;
}

void Heapify(status* tree, int len, int i) {
	if (i >= len) return;

	int child1 = 2 * i + 1;
	int child2 = 2 * i + 2;
	int max = i;

	if (child1 < len && tree[child1] > tree[max]){
		max = child1;
	}
	if (child2 < len && tree[child2] > tree[max]){
		max = child2;
	}
	if (i != max) {
		swap(tree, max, i);
		Heapify(tree, len, max);
	}
}

void Build_Heap(status* tree, int len) {
	for (int i = len / 2 - 1; i >= 0; i--)
	{
		Heapify(tree, len, i);
	}
}

void HeapSort(status* tree, int len) {
	Build_Heap(tree, len);
	for (int i = len - 1; i >= 0; i--)
	{
		swap(tree, i, 0);
		Heapify(tree, i, 0);
	}
}

int main() {
	status tree[] = { 23,6,4,8,49,616,479,64,4 };
	HeapSort(tree, sizeof(tree) / sizeof(status));
	for (int i = 0; i < sizeof(tree) / sizeof(status); i++)
	{
		cout << tree[i] << " ";
	}
	cout << endl;
	return 0;
}