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

int ponto_dentro(Item _value, int dim, Item _a, Item _b) {
  struct Point *value = _value;

  double minX, maxX, minY, maxY;
  Point a = _a;
  Point b = _b;

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

char *ponto_string(const Item _ponto) {
  struct Point *ponto = (struct Point *) _ponto;
  char *saida = calloc(8, sizeof(char));
  sprintf(saida, "(%2d,%2d)", (int) ponto->x, (int) ponto->y);
  return saida;
}

int main(int argc, const char *argv[]) {
  unsigned tam = sizeof(points) / sizeof(points[0]);

  KDTree arv = KDTree_t.create(2, equal_points, compareX, compareY);

  // Insercao dos pontos
  for (int i = 0; i < tam; i++)
    KDTree_t.insert(arv, newPoint(points[i].x, points[i].y));

  // Testes
  FILE *dotfile = fopen("graph/graph2.dot", "w");

  KDTree_t.generate_dot(arv, dotfile, ponto_string);

  fclose(dotfile);

  KDTree_t.destroy(arv, free);

  return 0;
}
