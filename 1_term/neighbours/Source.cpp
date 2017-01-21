#include <cstdio>
#include <cstdlib>
#include <cmath>

void scan_points(int count);
void create_neighbours_table(int count);
void print_neighbours(int point_index, int count);

void sort_neighbours_by_point(int *neighbours, int size, const struct Point *pt);
bool closer(const int p, const int q, const Point pt);

struct Point
{
	int x, y;
};

typedef struct Point Point;
const int DEFAULT_NEAREST_COUNT = 3;

Point *points;
int **neighbours;

int main()
{
	int count;
	int point_index;
	char buffer[256];
	int neighbours_to_display;

	scanf("%d\n", &count);
	points = (Point *)malloc(count * sizeof(Point));
	scan_points(count);

	create_neighbours_table(count);
	
	while (true)
	{
		fgets(buffer, sizeof(buffer), stdin);
		int value_sscanf = sscanf(buffer, "%d %d", &point_index, &neighbours_to_display);
		
		if (point_index < 0)
		{
			printf("Bye!\n");
			return 0;
		}
		if (point_index >= count)
		{
			printf("Error, too big index. Try again\n");
			continue;
		}
		if (value_sscanf == 1)
			neighbours_to_display = DEFAULT_NEAREST_COUNT;
		if (neighbours_to_display >= count)
			neighbours_to_display = count - 1;
		print_neighbours(point_index, neighbours_to_display);
	}

	free(points);
	for (point_index = 0; point_index < count; ++point_index)
		free(neighbours[point_index]);
	free(neighbours);

	return 0;
}

void scan_points(int count) {
	int i;
	char buffer[256];

	for (i = 0; i < count; ++i)
	{
		fgets(buffer, sizeof(buffer), stdin);
		sscanf(buffer, "%d%d", &points[i].x, &points[i].y);
	}
}

void create_neighbours_table(int count) {
	int i, k;
	
	neighbours = (int **)malloc(sizeof(int *) * count);

	for (i = 0; i < count; ++i)
	{
		neighbours[i] = (int *) malloc(sizeof(int) * (count - 1));
		for (k = 0; k < i; ++k)
			neighbours[i][k] = k;
		for (k = i + 1; k <= count; ++k)
			neighbours[i][k - 1] = k;

		sort_neighbours_by_point(neighbours[i], count - 1, &points[i]);
	}
}
void sort_neighbours_by_point(int *neighbours, int size, const Point *pt)
{
	int i, k, tmp;

	for (i = 1; i < size; ++i)
	{
		tmp = neighbours[i];
		k = i;
		while (k > 0 && closer(neighbours[k], neighbours[k - 1], *pt))
		{
			neighbours[k] = neighbours[k - 1];
			--k;
		}

		neighbours[k] = tmp;
	}
}

bool closer(const int p, const int q, const Point pt)
{
	const int distance1 = (points[p].x - pt.x) * (points[p].x - pt.x) + (points[p].y - pt.y) * (points[p].y - pt.y);
	const int distance2 = (points[q].x - pt.x) * (points[q].x - pt.x) + (points[q].y - pt.y) * (points[q].y - pt.y);
	if (distance1 > distance2) {
		return false;
	}
	else if (distance1 < distance2) {
		return true;
	}
	else {
		return p < q;
	}
}

void print_neighbours(int point_index, int count) {
	int i;
	Point neighbour;
	double distance;
	Point point = points[point_index];

	printf("%d nearest points for point #%d (%d,%d):\n", count, point_index, points[point_index].x, points[point_index].y);
	for (i = 0; i < count; ++i)
	{
		neighbour = points[neighbours[point_index][i]];
		distance = sqrt((neighbour.x - point.x)*(neighbour.x - point.x) + (neighbour.y - point.y)*(neighbour.y - point.y));
		printf("#%d: (%d,%d) d=%.3lf\n", neighbours[point_index][i],
			neighbour.x, neighbour.y, distance);
	}
}