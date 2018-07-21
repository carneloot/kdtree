#include <stdio.h>
#include <stdlib.h>

#include "kdtree.h"

#define min(a, b) ((a < b) ? (a) : (b));
#define max(a, b) ((a > b) ? (a) : (b));

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

int ponto_dentro(Item _value, int dim, Item rect[]) {
  struct Point *value = _value;

  double minX, maxX, minY, maxY;
  struct Point *a, *b;
  a = rect[0];
  b = rect[1];

  minX = min(a->x, b->x);
  maxX = max(a->x, b->x);

  minY = min(a->y, b->y);
  maxY = max(a->y, b->y);

  switch (dim) {
    // Checa se o ponto esta dentro do retangulo
    case -1:
      return !(
        value->x < minX || value->x > maxX ||  //
        value->y < minY || value->y > maxY);

    // Checa o valor de X
    case 0:
      if (value->x < minX)
        return -1;
      else if (value->x > maxX)
        return 1;
      return 0;

    // Checa o valor de Y
    case 1:
      if (value->y < minY)
        return -1;
      else if (value->y > maxY)
        return 1;
      return 0;
  };

  return 0;
}

void printar_ponto(const Item _p) {
  struct Point *p = (struct Point *) _p;
  printf("(%2.0f, %2.0f)\n", p->x, p->y);
}

int main() {
  KDTree arv = KDTree_t.create(2, equal_points, compareX, compareY);

  KDTree_t.insert(arv, newPoint(5, 8));
  KDTree_t.insert(arv, newPoint(7, 6));
  KDTree_t.insert(arv, newPoint(3, 2));
  KDTree_t.insert(arv, newPoint(4, 5));
  KDTree_t.insert(arv, newPoint(9, 1));
  KDTree_t.insert(arv, newPoint(2, 7));
  KDTree_t.insert(arv, newPoint(6, 4));
  KDTree_t.insert(arv, newPoint(1, 1));

  Point a = newPoint(3, 9);
  Point b = newPoint(8, 5);

  KDTree range = KDTree_t.range_search(arv, ponto_dentro, a, b);

  KDTree_t.passe_simetrico(range, printar_ponto);

  KDTree_t.destroy(arv, free);
  KDTree_t.destroy(range, NULL);
  free(a);
  free(b);

  return 0;
}
