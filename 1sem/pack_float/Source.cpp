#include <cstdlib> 
#include <cstdio>  
#include <cstdint> 

void binprint_uint(unsigned x);
float pack_float(int sign, int exponent, unsigned significand);

int main() {
	int sign, exponent;
	unsigned significand;
	scanf("%d%d%u", &sign, &exponent, &significand);
	printf("\n%f", pack_float(sign, exponent, significand));
	scanf("%d", sign);
}

void binprint_uint(unsigned x)
{
	for (int i = 8 * sizeof(unsigned) - 1; i >= 0; i--)
	{
		printf("%d", (x&(1 << i)) >> i);
		if ((i) % 8 == 0) printf(" ");
	}
}

float pack_float(int sign, int exponent, unsigned significand) 
{
	uint32_t exponent1 = exponent, ans = 0, sign1 = sign, significand1 = significand;
	exponent1 <<= 23;
	sign1 <<= 31;
	ans |= sign1;
	ans |= significand1;
	ans |= exponent1;

	binprint_uint(ans);
	float * p = (float *)&ans;
	float ans1 = *p;
	return ans1;
}