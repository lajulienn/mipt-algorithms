#include <cstdio>
#include <cstdlib>
#include <cstring>

const int MAX_LEN = 100;
const int START_CAPACITY = 100;

struct WordInfo
{
	char word[MAX_LEN + 1];
	int count;
};

typedef struct WordInfo WordInfo;
void sort_words(struct WordInfo **pwords, int size);
bool greater(const WordInfo *A, const WordInfo *B);
WordInfo *words;


int main()
{
	FILE *text = fopen("D:\\text.txt", "r");
	if (text == NULL)
	{
		printf("Error: file was not opened\n");
		return 0;
	}
	char buf[MAX_LEN + 1];
	int capacity = START_CAPACITY;
	int size_words = 0;
	int all_size = 0;
	words = (WordInfo *)malloc(sizeof(WordInfo) * capacity);
	if (words == NULL)
	{
		printf("Error: not enough memory\n");
		return 0;
	}
	while (!(feof(text)))
	{
		if (fscanf(text, "%s", buf) >= 0)
		{
			int i = 0;
			while (i < size_words && strcmp(buf, words[i].word) != 0)
				++i;
			if (i < size_words)
			{
				words[i].count += 1;
				all_size += 1;
			}
			else
				if (size_words < capacity)
				{
					strcpy(words[size_words].word, buf);
					words[size_words].count = 1;
					size_words += 1;
					all_size += 1;
				}
				else
				{
					words = (struct WordInfo *)realloc(words, 2 * capacity * sizeof(struct WordInfo));
					if (words == NULL)
					{
						printf("Error! No memory!");
						return -1;
					}
					capacity *= 2;
					strcpy(words[size_words].word, buf);
					words[size_words].count = 1;
					size_words += 1;
					all_size += 1;
				}
		}
	}
	struct WordInfo **pwords = (struct WordInfo **)malloc(size_words*sizeof(WordInfo*));
	for (int t = 0; t < size_words; ++t)
		pwords[t] = words + t;
	sort_words(pwords, size_words);
	printf("%d\n", all_size);
	for (int j = 0; j < size_words; ++j)
		printf("%s	%d	%.2f%%\n", pwords[j]->word, pwords[j]->count, ((float)pwords[j]->count / all_size) * 100);
	free(pwords);
	free(words);
	fclose(text);
	return 0;
}

/*void sort_WordInfo(WordInfo **pWordInfo, int size)
{
	WordInfo *tmp;
	int i, k;
	for (i = 1; i < size; ++i)
	{
		tmp = pWordInfo[i];
		k = i;
		while (k > 0)
		{
			if (greater(tmp, pWordInfo[k - 1]))
			{
				pWordInfo[k] = pWordInfo[k - 1];
				--k;
			}
			else
			{
				break;
			}
		}
		*(pWordInfo)[k] = tmp;
	}
} */
void sort_words(struct WordInfo **pwords, int size)
{
	struct WordInfo *tmp;
	for (int i = 1; i < size; ++i)
	{
		int key = pwords[i]->count;
		int j = i - 1;
		while (j >= 0 && pwords[j]->count < key)
		{
			tmp = pwords[j + 1];
			pwords[j + 1] = pwords[j];
			pwords[j] = tmp;
			--j;
		}
		while (j >= 0 && pwords[j]->count == key && (strcmp(pwords[j + 1]->word, pwords[j]->word) < 0))
		{
			tmp = pwords[j + 1];
			pwords[j + 1] = pwords[j];
			pwords[j] = tmp;
			--j;
		}
	}
}
bool greater(const WordInfo *A, const WordInfo *B)
{
	if (A->count > B->count)
		return true;
	else if (A->count == B->count)
	{
		return strcmp(A->word, B->word) >= 0;
	}
	else return false;
}