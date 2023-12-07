#include<iostream>
using namespace std;

int Binary_Search(int a[], int key)
{
    int low = 0, high = sizeof(a) / sizeof(int) - 1, mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (a[mid] == key) return mid;
        if (a[mid] < key) low = mid - 1;
        else high = mid + 1;
    }
    return -1;
}


int main()
{

	return 0;
}