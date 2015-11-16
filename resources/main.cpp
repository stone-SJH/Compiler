#include "time.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
using namespace std;
void _quicksort(int* a, int iLo, int iHi){
	int Lo = iLo;
	int Hi = iHi;
	int Mid = a[(Lo + Hi) / 2];
	while (Lo < Hi){
		while (a[Lo] < Mid) Lo++;
		while (a[Hi] > Mid) Hi--;
		if (Lo <= Hi){
			int temp = a[Lo];
			a[Lo] = a[Hi];
			a[Hi] = temp;
			Lo++;
			Hi--;
		}
	}
	if (Hi > iLo) _quicksort(a, iLo, Hi);
	if (Lo < iHi) _quicksort(a, Lo, iHi);
}
void quicksort(int* a, int length){
	_quicksort(a, 0, length - 1);
}
int main()
{
	srand(time(NULL));
	int a[10];
	int n = 10;
	for (int i = 0; i < n; ++i)
		a[i] = rand() % n;
	for (int i = 0; i < n; ++i)
		cout << a[i] << " ";
	cout << endl;
	quicksort(a, n);
	for (int i = 0; i < n; ++i)
		cout << a[i] << " ";
	cout << endl;
	return 0;
}
