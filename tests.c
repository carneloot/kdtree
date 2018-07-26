#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kdtree.h"
#include "lista.h"

#define min(a, b) ((a < b) ? (a) : (b))
#define max(a, b) ((a > b) ? (a) : (b))
#define mod(a) ((a < 0) ? (-a) : (a))
#define sqr(a) ((a) * (a))

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
  return floor(a->x - b->x);
}

int compareY(const void *_a, const void *_b) {
  struct Point *a = (struct Point *) _a;
  struct Point *b = (struct Point *) _b;
  return floor(a->y - b->y);
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

double distance_squared(const Item _a, const Item _b, int dim) {
  struct Point *a = (struct Point *) _a;
  struct Point *b = (struct Point *) _b;

  double result = -1;

  switch (dim) {
    case -1: result = (sqr(a->x - b->x) + sqr(a->y - b->y)); break;
    case 0: result = sqr(a->x - b->x); break;
    case 1: result = sqr(a->y - b->y); break;
  }

  return result;
}

double distance(const Item a, const Item b, int dim) {
  return sqrt(distance_squared(a, b, dim));
}

void printar_ponto(const Item _p, unsigned prof) {
  struct Point *p = (struct Point *) _p;
  char tabs[prof + 1];
  for (int i = 0; i < prof; i++)
    tabs[i] = '\t';
  tabs[prof] = 0;
  printf("%s%c (%2.2f, %2.2f)\n", tabs, (prof % 2) ? 'y' : 'x', p->x, p->y);
}

int main(int argc, const char *argv[]) {
  KDTree arv = KDTree_t.create(2, equal_points, compareX, compareY);

  // Insercao dos pontos
  KDTree_t.insert(arv, newPoint(5, 8));
  KDTree_t.insert(arv, newPoint(6, 4));
  KDTree_t.insert(arv, newPoint(7, 6));
  KDTree_t.insert(arv, newPoint(9, 1));
  KDTree_t.insert(arv, newPoint(4, 5));
  KDTree_t.insert(arv, newPoint(3, 2));
  KDTree_t.insert(arv, newPoint(1, 1));
  KDTree_t.insert(arv, newPoint(9, 4));
  KDTree_t.insert(arv, newPoint(2, 4));
  KDTree_t.insert(arv, newPoint(2, 7));
  KDTree_t.insert(arv, newPoint(8, 2));
  KDTree_t.insert(arv, newPoint(6, 2));
  KDTree_t.insert(arv, newPoint(1, 6));
  KDTree_t.insert(arv, newPoint(8, 4));
  KDTree_t.insert(arv, newPoint(6, 3));
  KDTree_t.insert(arv, newPoint(7, 5));
  KDTree_t.insert(arv, newPoint(7, 3));
  KDTree_t.insert(arv, newPoint(2, 2));
  KDTree_t.insert(arv, newPoint(6, 8));
  KDTree_t.insert(arv, newPoint(5, 6));
  KDTree_t.insert(arv, newPoint(4, 3));
  KDTree_t.insert(arv, newPoint(9, 8));

  // Testes
  printf("Todos os pontos:\n");
  KDTree_t.passe_simetrico(arv, printar_ponto);

  // Nearest neighbor
  Point a = newPoint(strtod(argv[1], NULL), strtod(argv[2], NULL));

  printf("Ponto pesquisado: ");
  printar_ponto(a, 0);

  Pair prox = KDTree_t.nearest_neighbor(arv, a, distance_squared);

  printf("Ponto encontrado: ");
  printar_ponto(prox.point1, 0);
  printf("Distancia: %.2f\n", prox.distance);

  free(a);

  // Range Search
  /* Point A = newPoint(1.5, 1.5);
  Point B = newPoint(5, 5);

  Lista range = KDTree_t.range_search(arv, ponto_dentro, A, B);
  Posic it    = Lista_t.get_first(range);
  while (it) {
    printar_ponto(Lista_t.get(range, it), 0);
    it = Lista_t.get_next(range, it);
  }

  Lista_t.destruir(range, NULL);
  free(A);
  free(B); */

  KDTree_t.destroy(arv, free);

  return 0;
}
