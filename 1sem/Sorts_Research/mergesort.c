#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>


int CompareChar(void* a, void* b);
int CompareInt(void* a, void* b);
int CompareFloat(void* a, void* b);
int CompareDouble(void* a, void* b);
void* PositionInArray(void* a, int i, int sizeoftype);
void SwapVoid(void *base, int a, int b, int sizeoftype);
void merge(void* a, int l, int m, int r, int sizeoftype, int(*compare)(void* a, void* b), int* buf);
void AssignValue(void* a, void* b, int i, int j, int sizeoftype);
void MergeSort(void* a, int l, int r, int sizeoftype, int(*compare)(void* a, void* b), int* buf);
void GetMassInt(int n,int *a);
void GetMassFloat(int n,float *a);
void GetMassDouble(int n,double *a);
void PrintMassFloat( float* a, int n);
void PrintMassInt( int* a, int n);
void PrintMassChar( char* a, int n);
void PrintMassDouble( double* a, int n);
void GetMassChar(int n,char *a);
int check(void* a, int n, int sizeoftype, int(*compare)(void* a, void* b));


int main()
{
    int type;
    printf("chose among types of data you want to sort: 1 - int, 2 - float, 3 - double, 4 - char: ");
    scanf("%d", &type);
    printf("enter the count of elements: ");
    int n;
    scanf("%d", &n);
	int* buf = (int*)malloc(sizeof(int)*(n+1));
    switch (type)
    {
        case 1:
        {
            int* a = (int*)malloc(n * sizeof(int));
			GetMassInt(n, a);
            MergeSort(a, 0, n-1, sizeof(int), CompareInt, buf);
			/*PrintMassInt(a, n);*/
            if (check(a, n, sizeof(int), CompareInt))
                printf("true");
            else
                printf("false");
            printf("\n");
            free(a);
            break;
        }
        case 2:
	    {
            float* a = (float*)malloc(n * sizeof(float));
            GetMassFloat(n, a);
            MergeSort(a, 0, n-1, sizeof(float), CompareFloat, buf);
            /*PrintMassFloat(a, n);*/
			 if (check(a, n, sizeof(float), CompareFloat))
                printf("true");
            else
                printf("false");
            printf("\n");
            free(a);
	        break;
	    }
        case 3:
	    {
            double* a = (double*)malloc(n * sizeof(double));
            GetMassDouble(n, a);
            MergeSort(a, 0, n-1, sizeof(double), CompareDouble, buf);
            /*PrintMassDouble(a, n);*/
			 if (check(a, n, sizeof(double), CompareDouble))
                printf("true");
            else
                printf("false");
            printf("\n");
            free(a);
            break;
	    }
        case 4:
	    {
            char* a = (char*)malloc(n * sizeof(char));
            GetMassChar(n, a);
            MergeSort(a, 0, n-1, sizeof(char), CompareChar, buf);
            /*PrintMassChar(a, n);*/
			 if (check(a, n, sizeof(char), CompareChar))
                printf("true");
            else
                printf("false");
            printf("\n");
            free(a);
            break;
	    }
        default: printf("your choice is wrong!");
        }
    free(buf);
	return 0;
}


void GetMassInt(int n,int *a)
{
    int i;
    srand(time(NULL));
    for (i = 0; i < n; i++)
    a[i] = rand();
}


void GetMassFloat(int n,float *a)
{
	srand(time(NULL));
    int i;
    for (i = 0; i < n; i++)
    a[i] = (float)(rand() / 24345.3453);
}


void GetMassDouble(int n, double *a)
{
	srand(time(NULL));
    int i;
    for (i = 0; i < n; i++)
    a[i] = (double)(rand() / 67896777.4532);
}


void PrintMassFloat( float* a, int n)
{
	int i;
	for(i = 0; i < n; i++)
		printf("%g ", a[i]);
}


void PrintMassInt( int* a, int n)
{
	int i;
	for(i = 0; i < n; i++)
		printf("%d ", a[i]);
}


void PrintMassChar( char* a, int n)
{
	int i;
	for(i = 0; i < n; i++)
		printf("%c ", a[i]);
}


void PrintMassDouble( double* a, int n)
{
	int i;
	for(i = 0; i < n; i++)
		printf("%lf ", a[i]);
}


void GetMassChar(int n,char *a)
{
	srand(time(NULL));
    int i;
    for (i = 0; i < n; i++)
    a[i] = (char)(rand() % 255);
}


void merge(void* a, int l, int m, int r, int sizeoftype, int(*compare)(void* a, void*b), int* buf)
{
	int i, j, k;
	for ( i = m + 1; i > l; --i)
		AssignValue(buf, a, i - 1, i - 1, sizeoftype);
	for (j = m; j < r; ++j)
		AssignValue(buf, a, r + m - j, j + 1, sizeoftype);
	for ( k = l; k <= r; ++k)
	{
		if (compare(PositionInArray(buf, i, sizeoftype), PositionInArray(buf, j, sizeoftype)) > 0)
		{
			AssignValue(a, buf, k, j, sizeoftype);
			--j;
		}
		else
		{
			AssignValue(a, buf, k, i, sizeoftype);
			++i;
		}
	}
	for (i = 0; i <= r - l; ++i)
		buf[i] = 0;
}


void MergeSort(void* a, int l, int r, int sizeoftype, int(*compare)(void* a, void* b), int* buf)
{
    if (l >= r)
		return;
	int m = (l+r)/ 2;
	MergeSort(a, l, m, sizeoftype, compare, buf);
	MergeSort(a, m+1, r, sizeoftype, compare, buf);
	merge(a, l, m, r, sizeoftype, compare, buf);
}


void AssignValue(void* a, void* b, int i, int j, int sizeoftype)
{
	memcpy((void*)((char*)a + i * sizeoftype), (void*)((char*)b + j * sizeoftype), sizeoftype);
}


void* PositionInArray(void* a, int i, int sizeoftype)
{
	return (char*)a + i*sizeoftype;
}


int CompareChar(void* a, void* b)
{
 if (*((char*)a) - *((char*)b) > 0) return 1;
 if (*((char*)a) - * (( char *)b) < 0) return -1;
 return 0;
}


int CompareInt(void* a, void* b)
{
  return *((int*)a) - *((int*)b);
}


int CompareFloat(void* a, void* b)
{
   if ((*((float*)a) - *((float*)b)) > 0)
      return 1;
   else if ((*((float*)a) - *((float*)b)) < 0)
	       return -1;
   return 0;
}


int CompareDouble(void* a, void* b)
{
   if ((*((double*)a) - *((double*)b)) > 0)
	   return 1;
   else if ((*((double*)a) - *((double*)b)) < 0)
	        return -1;
   return 0;
}


int check(void* a, int n, int sizeoftype, int(*compare)(void* a, void* b))
{
    int i;
    for (i = 0; i < n - 1; i++)
        if (compare(PositionInArray(a, i, sizeoftype), PositionInArray(a, i + 1, sizeoftype)) > 0)
            return 0;
    return 1;
}


void SwapVoid(void *base, int a, int b, int sizeoftype)
{
	void* buf = malloc(sizeoftype);
	memcpy(buf, (char*)base + b * sizeoftype, sizeoftype);
	memcpy((char*)base + b * sizeoftype, (char*)base + a * sizeoftype, sizeoftype);
	memcpy((char*)base + a * sizeoftype, buf, sizeoftype);
	free(buf);
}

