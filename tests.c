#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dac/closest.h"
#include "kdtree.h"
#include "lista.h"

#define min(a, b) ((a < b) ? (a) : (b))
#define max(a, b) ((a > b) ? (a) : (b))
#define mod(a) ((a < 0) ? (-a) : (a))
#define sqr(a) ((a) * (a))

#define TREE 0
#define ARRAY 1

#define TIPO TREE
// #define TIPO ARRAY

struct Point {
  double x, y;
};

typedef struct Point *Point;

#include "pontos.h"

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
  unsigned tam = sizeof(points) / sizeof(points[0]);

#if TIPO == TREE
  KDTree arv = KDTree_t.create(2, equal_points, compareX, compareY);

  // Insercao dos pontos
  for (int i = 0; i < tam; i++)
    KDTree_t.insert(arv, newPoint(points[i].x, points[i].y));

  // Testes
  Pair pair = KDTree_t.closest_pair(arv, distance_squared);

  printf("===== ARVORE =====\n");
  printf("Pontos mais proximos:\n");
  printf("Distancia: %.2f\n", sqrt(pair.distance));
  printar_ponto(pair.point1, 0);
  printar_ponto(pair.point2, 0);

  KDTree_t.destroy(arv, free);

#endif
#if TIPO == ARRAY

  Point vector[tam];

  for (int i = 0; i < tam; i++)
    vector[i] = newPoint(points[i].x, points[i].y);

  ClosestPair pair;

  pair = find_closest((void **) vector, tam);

  printf("===== DIVIDE AND CONQUER =====\n");
  printf("Pontos mais proximos:\n");
  printf("Distancia: %.2f\n", pair.dist);
  printar_ponto(pair.point1, 0);
  printar_ponto(pair.point2, 0);

#endif

  return 0;
}
