#include <cstdio>
#include <cstdlib>
#include <cstring>

const int MAX_NAME_LEN = 15;
typedef struct Student Student;
void sort_students(const struct Student **pstudents, int size);
bool greater(const Student *A, const Student *B);

struct Student
{
	char name[MAX_NAME_LEN + 1];
	int score;
};

int main()
{
	int n;
	scanf("%d", &n);
	struct Student **a = (Student **)malloc(n * sizeof(Student *));
	for (int i = 0; i < n; ++i)
	{
		a[i] = (Student *)malloc(sizeof(Student));
		scanf("%s%d", a[i]->name, &a[i]->score);
	}
	sort_students((const Student **)a, n);
	printf("\nSorted students:\n\n");
	for (int i = 0; i < n; ++i)
	{
		printf("%s %d\n", a[i]->name, a[i]->score);
		free(a[i]);
	}
	free(a);
	return 0;
}

void sort_students(const Student **pstudents, int size)
{
	const Student *tmp;
	int i, k;
	for (i = 1; i < size; ++i)
	{
		tmp = pstudents[i];
		k = i;
		while (k > 0)
		{
			if (greater(pstudents[k - 1], tmp))
			{
				pstudents[k] = pstudents[k - 1];
				--k;
			}
			else
			{
				break;
			}
		}
		pstudents[k] = tmp;
	}
}

bool greater(const Student *A, const Student *B)
{
	if (A->score > B->score)
		return true;
	else if (A->score == B->score)
	{
		if (strcmp(A->name, B->name) >= 0)
			return true;
		else return false;
	}
	else return false;
}