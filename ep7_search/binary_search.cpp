#include<iostream>
using namespace std;

int Binary_Search(int a[], int key, int len)
{
    int low = 0, high = len-1, mid;
    while (low <= high)
    {
		mid = (low + high) / 2;
		if (a[mid] == key) return mid;
		else if (a[mid] > key) high = mid - 1;
		else low = mid + 1;
	}
	return -1;
}


int main()
{

	return 0;
}