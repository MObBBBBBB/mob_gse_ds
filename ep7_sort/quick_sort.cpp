#include<iostream>
using namespace std;

void QuickSort(int a[], int low, int high)
{
	if (low >= high) return;
	int l = low - 1, h = high + 1;
	int pivot = a[(l+h)/2];
	while (l < h)
	{
		do l++; while (pivot > a[l]);
		do h--; while (pivot < a[h]);
		if (l < h)
		{
			int t = a[l];
			a[l] = a[h];
			a[h] = t;
		}
	}
	QuickSort(a, low, h); QuickSort(a, h + 1, high);
}

int main()
{

	return 0;
}
