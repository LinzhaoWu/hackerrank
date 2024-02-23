#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct triangle
{
	int a;
	int b;
	int c;
};

typedef struct triangle triangle;
double get_area(triangle* tr)
{
    const int p = (tr->a + tr->b + tr->c) / 2;
    return sqrt((double)p * (p - tr->a) * (p - tr->b) * (p - tr->c));
}

void sort_by_area(triangle* tr, int n) 
{
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (get_area(tr + i) > get_area(tr + j)) {
                triangle tmp = *(tr + j);
                *(tr + j) = *(tr + i);
                *(tr + i) = tmp;
            }
        }
    }
}

int main()
{
	int n;
	scanf("%d", &n);
	triangle *tr = (triangle *)malloc(n * sizeof(triangle));
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &tr[i].a, &tr[i].b, &tr[i].c);
	}
	sort_by_area(tr, n);
	for (int i = 0; i < n; i++) {
		printf("%d %d %d\n", tr[i].a, tr[i].b, tr[i].c);
	}
	return 0;
}