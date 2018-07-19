#include <stdio.h>
#include <stdlib.h>

#include "kdtree.h"

struct Point {
  double x, y;
};

typedef struct Point *Point;

Point newPoint(double x, double y) {
  struct Point *this = calloc(1, sizeof(struct Point));

  this->x = x;
  this->y = y;

  return this;
}

int compareX(const void *_a, const void *_b) {
  struct Point *a = (struct Point *) _a;
  struct Point *b = (struct Point *) _b;
  return (int) (a->x - b->x);
}

int compareY(const void *_a, const void *_b) {
  struct Point *a = (struct Point *) _a;
  struct Point *b = (struct Point *) _b;
  return (int) (a->y - b->y);
}

int equal_points(const void *_a, const void *_b) {
  struct Point *a = (struct Point *) _a;
  struct Point *b = (struct Point *) _b;
  return (a->y == b->y && a->x == b->x);
}

void printar_ponto(const Item _p) {
  struct Point *p = (struct Point *) _p;
  printf("(%2.0f, %2.0f)\n", p->x, p->y);
}

int main() {
  KDTree arv = KDTree_t.create(2, equal_points, compareX, compareY);

  KDTree_t.insert(arv, newPoint(6, 12));
  KDTree_t.insert(arv, newPoint(3, 6));
  KDTree_t.insert(arv, newPoint(17, 15));
  KDTree_t.insert(arv, newPoint(13, 15));
  KDTree_t.insert(arv, newPoint(9, 1));
  KDTree_t.insert(arv, newPoint(2, 7));
  KDTree_t.insert(arv, newPoint(3, 15));
  KDTree_t.insert(arv, newPoint(22, 17));
  KDTree_t.insert(arv, newPoint(10, 17));
  KDTree_t.insert(arv, newPoint(12, 15));
  KDTree_t.insert(arv, newPoint(5, 7));
  KDTree_t.insert(arv, newPoint(10, 19));

  KDTree_t.passe_simetrico(arv, printar_ponto);

  // Delecao
  Point a = newPoint(10, 19);
  KDTree_t.delete(arv, a);

  printf("========\n");
  KDTree_t.passe_simetrico(arv, printar_ponto);

  KDTree_t.destroy(arv, free);

  free(a);

  return 0;
}
