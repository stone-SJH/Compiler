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
	int a[10];
	int n = 10;
	a[0] = 1;
	a[1] = 2;
	a[2] = 0;
	a[3] = 10;
	a[4] = 22;
	a[5] = 1;
	a[6] = 3;
	a[7] = 12;
	a[8] = 4;
	a[9] = 3;
	quicksort(a, n);
	return 0;
}
