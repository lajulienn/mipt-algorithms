#include <cstdio>
#include <cstdlib>
#include <cmath>

float dist(float x1, float y1, float x2, float y2);

int main()
{
	int n, i, k;
	float max = 0, tmp = 0;
	scanf("%d", &n);
	float * x = (float *) malloc(n * sizeof(float));
	if (!x)
	{
		printf("Error, no memory\n");
		free(x);
		return 0;
	}
	float * y = (float *) malloc(n * sizeof(float));
	if (!y)
	{
		printf("Error, no memory\n");
		free(y);
		return 0;
	}
	for (i = 0; i < n; ++i)
	{
		scanf("%f%f", &x[i], &y[i]);
	}

	for (i = 0; i < n; ++i)
	{
		for (k = i + 1; k < n; ++k)
		{
			if ((tmp = dist(x[i], y[i], x[k], y[k])) > max)
				max = tmp;
		}
	}
	printf("%f\n", max);

	free(x);
	free(y);
	return 0;
}

float dist(float x1, float y1, float x2, float y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}