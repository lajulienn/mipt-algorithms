#include <cstdlib>
#include <cstdio>
#include <cmath>

int n;
typedef double(*Func) (double);

int bisection_solve(double a, double b, Func f, double eps, int max_it, double *x);
double sqr(double x);
double trig(double x);

int main()
{
	while (1)
	{
		double x, a, b, eps;
		int max_it;
		scanf("%lf%lf%lf%d", &a, &b, &eps, &max_it);
		//printf("%lf\t%d\n", a, max_it);
		printf("%d\n", bisection_solve(a, b, sqr, eps, max_it, &x));
		printf("%lf\n", x);
		printf("delta=%lf\n", x*x - 2);
	}
}

int bisection_solve(double a, double b, Func f, double eps, int max_it, double *x)
{
	//printf("%lf\t%lf\n", a, f(a));
	if (f(a)*f(b) > 0)
		return -1;
	double m = (a + b) / 2.0;
	int i = 1;
	while (i <= max_it)
	{
		if (abs(f(m)) < eps)
		{
			*x = m; return i;
		}

		if (f(m)*f(a) > 0)
			a = m;
		else if (f(m)*f(b) > 0)
			b = m;
		++i;
		m = (a + b) / 2.0;
	}
	return -2;
}


double sqr(double x)
{
	return x*x - 2;
}

double trig(double x)
{
	return sin(x) - 0.5;
}