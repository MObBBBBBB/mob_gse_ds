#include<iostream>
#define MAXSIZE 257
using namespace std;

typedef struct
{
	char ch[MAXSIZE];
	int length;
} SqString;

SqString SubString(SqString s, int pos, int len);
int StrCompare(SqString s, SqString t);
int index(SqString s, SqString t); // 暴力


int main()
{


	return 0;
}


SqString SubString(SqString s, int pos, int len)
{
	SqString t = {"", 0};
	if (pos < 1 || pos + len - 1 > s.length) return t;
	for (int i = pos, j = 0; i < pos + len; i++, j++) t.ch[j] = s.ch[i];
	t.length = len;
	return t;
}

int StrCompare(SqString s, SqString t)
{
	for (int i = 1; i <= s.length && i <= t.length; i++)
	{
		if (s.ch[i] != t.ch[i]) return s.ch[i] - t.ch[i];
	}
	return s.length - t.length;
}

int index(SqString s, SqString t) // 暴力
{
	int i, n = s.length, m = t.length;
	SqString sub;
	while (i <= n-m+1)
	{
		sub = SubString(s, i, m);
		if (StrCompare(sub, t) != 0) i++;
		else return i;
	}
	return -1;
}