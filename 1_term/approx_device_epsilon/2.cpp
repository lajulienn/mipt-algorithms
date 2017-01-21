#include <cstdio>

float machine_epsilon_float();
double machine_epsilon_double();

int main()
{
	printf("%e\n%e\n", machine_epsilon_float, machine_epsilon_double);
	return 0;
}

float machine_epsilon_float()
{
	float eps = 1.0;
	while (1.0f + eps != 1.0f)
		eps /= 2;
	return eps;
}

double machine_epsilon_double()
{
	double eps = 1.0;
	while (1.0 + eps != 1.0)
		eps /= 2;
	return eps;
}