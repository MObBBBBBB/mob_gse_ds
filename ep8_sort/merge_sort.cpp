#include<iostream>
using namespace std;
const int N = 1e5;

int tmp[N];

void MergeSort(int a[], int low, int high)
{
	if (low >= high) return;
	int mid = (low + high) / 2;
	MergeSort(a, low, mid);
	MergeSort(a, mid + 1, high);

	// merge
	int k = 0, l = low, h = mid + 1;
	while (l <= mid && h <= high)
	{
		if (a[l] <= a[h]) tmp[k++] = a[l++];
		else tmp[k++] = a[h++];
	}
	while (l <= mid) tmp[k++] = a[l++];
	while (h <= high) tmp[k++] = a[h++];
	for (l = low, h = 0; l <= high; l++, h++) a[l] = tmp[h];
}


int main()
{

	return 0;
}
