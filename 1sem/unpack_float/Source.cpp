#include <cstdlib> 
#include <cstdio> 
#include <cstdint> 

void binprint_uint(unsigned x);
void unpack_float(float f, int *sign, int *exponent, unsigned *significand);

int main() {
	float f;
	int sign = 0;
	int exponent = 0;
	unsigned significand = 0;
	scanf("%f", &f);
	unpack_float(f, &sign, &exponent, &significand);
	printf("%d %d %u \n", sign, exponent, significand);
}

void binprint_uint(unsigned x)
{
	for (int i = 8 * sizeof(unsigned) - 1; i >= 0; i--)
	{
		printf("%d", (x & (1 << i)) >> i);
		if ((i) % 8 == 0) printf(" ");
	}
}

void unpack_float(float f, int *sign, int *exponent, unsigned *significand) 
{
	uint32_t *p = (uint32_t *)&f;
	uint32_t f1 = *p;
	uint32_t sign1 = 1, exponent1 = 1, significand1 = 1;

	sign1 <<= 31;
	sign1 &= f1;
	sign1 >>= 31;
	for (int i = 1; i < 8; i++) 
	{
		exponent1 |= 1 << i;
	}
	exponent1 <<= 23;
	exponent1 &= f1;
	exponent1 >>= 23;
	for (int i = 1; i < 23; i++)
	{
		significand1 |= 1 << i;
	}
	significand1 &= f1;
	*sign = sign1;
	*exponent = exponent1;
	*significand = significand1;

	binprint_uint(f1);
}