#include <stdarg.h>
#include <stdlib.h>

#include "kdtree.h"

typedef int (*func_compare)(const void *a, const void *b);

struct KDTree {
  Item value;
  struct KDTree *left, *right;

  int dim;
  func_compare check_equal;
  func_compare *funcs;
};

// ===== HELPERS =====

// ===== FUNCOES =====

static KDTree __create_aux_kdtree(
  int dim, func_compare check_equal, func_compare *funcs) {
  struct KDTree *this = calloc(1, sizeof(struct KDTree));

  this->dim   = dim;
  this->value = NULL;
  this->left  = NULL;
  this->right = NULL;

  this->check_equal = check_equal;

  this->funcs = funcs;

  return this;
}

static KDTree __create_kdtree(int dim, func_compare check_equal, ...) {
  func_compare *funcs = calloc(dim, sizeof(func_compare));

  va_list list;
  va_start(list, check_equal);

  for (int i = 0; i < dim; i++)
    funcs[i] = va_arg(list, func_compare);

  va_end(list);

  return (KDTree) __create_aux_kdtree(dim, check_equal, funcs);
}

static KDTree __insert_rec_kdtree(KDTree _this, Item value, int k_atual) {
  struct KDTree *this = (struct KDTree *) _this;

  if (this->value == NULL) {
    this->value = value;
    return _this;
  }

  // Se o ponto for o mesmo, nao insere
  if (this->check_equal(value, this->value))
    return _this;

  int indice_func = k_atual % this->dim;

  if (this->funcs[indice_func](value, this->value) < 0) {
    if (!this->left)
      this->left =
        __create_aux_kdtree(this->dim, this->check_equal, this->funcs);

    return __insert_rec_kdtree(this->left, value, k_atual + 1);
  } else {
    if (!this->right)
      this->right =
        __create_aux_kdtree(this->dim, this->check_equal, this->funcs);

    return __insert_rec_kdtree(this->right, value, k_atual + 1);
  }

  return NULL;
}

static KDTree __insert_kdtree(KDTree this, Item value) {
  return __insert_rec_kdtree(this, value, 0);
}

static KDTree __search_rec_kdtree(KDTree _this, Item value, int prof) {
  struct KDTree *this = (struct KDTree *) _this;

  if (!this)
    return NULL;

  if (this->check_equal(this->value, value))
    return this;

  int indice_func = prof % this->dim;

  if (this->funcs[indice_func](value, this->value) < 0)
    return __search_rec_kdtree(this->left, value, prof + 1);
  else
    return __search_rec_kdtree(this->right, value, prof + 1);

  return NULL;
}

static KDTree __search_kdtree(KDTree this, Item value) {
  return __search_rec_kdtree(this, value, 0);
}

static Item __get_kdtree(KDTree _this) {
  struct KDTree *this = (struct KDTree *) _this;
  return this->value;
}

static int __is_leaf_kdtree(KDTree _this) {
  struct KDTree *this = (struct KDTree *) _this;
  return !(this->left || this->right);
}

static void __passe_simetrico_kdtree(
  KDTree _this, void (*executar)(const Item item)) {
  struct KDTree *this = (struct KDTree *) _this;

  if (this->left)
    __passe_simetrico_kdtree(this->left, executar);

  executar(this->value);

  if (this->right)
    __passe_simetrico_kdtree(this->right, executar);
}

static void __destroy_rec_kdtree(KDTree _this, void (*destroy)(Item item)) {
  struct KDTree *this = (struct KDTree *) _this;

  if (this->left)
    __destroy_rec_kdtree(this->left, destroy);

  if (this->right)
    __destroy_rec_kdtree(this->right, destroy);

  if (destroy && this->value)
    destroy(this->value);

  free(this);
}

static void __destroy_kdtree(KDTree _this, void (*destroy)(Item item)) {
  struct KDTree *this = (struct KDTree *) _this;

  free(this->funcs);

  __destroy_rec_kdtree(this, destroy);
}

const struct KDTree_t KDTree_t = {  //
  .create          = &__create_kdtree,
  .insert          = &__insert_kdtree,
  .search          = &__search_kdtree,
  .get             = &__get_kdtree,
  .is_leaf         = &__is_leaf_kdtree,
  .passe_simetrico = &__passe_simetrico_kdtree,
  .destroy         = &__destroy_kdtree};