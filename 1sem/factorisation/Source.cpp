#include <cstdio>

bool simple(int m);

int main()
{
	int n = -1, div, k, t;
	bool flag = false;
	while (true)
	{
		int check = scanf("%d", &n);
		if (!check) {
			printf("Error. Wrong argument.\n");
			break;
		}
		if (!n) return 0;
		flag = false;
		div = 2;
		printf("n = ");
		while (n != 1)
		{
			k = 0;
			if (simple(div))
			{
				if (flag) printf(" * ");
				flag = false;
				while (!(n % div))
				{
					n /= div;
					flag = true;
					if (k == 0) printf("%d^", div);
					++k;
				}
				if (flag) printf("%d", k);
			}
			++div;
		}
	}
	return 0;
}

bool simple(int m)
{
	for (int k = 2; k < m; ++k)
		if (m % k == 0)
			return false;
	return true;
}