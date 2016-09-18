#include <cstdio>
#include <ctime>

int main()
{
	time_t timer;
	time(&timer);
	//printf()
	/*const struct tm *tp;
	time(tp);*/
	printf("%d\n", timer);
	return 0;
}