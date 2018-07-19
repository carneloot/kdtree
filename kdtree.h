
#ifndef __KDTREE_H__
#define __KDTREE_H__

typedef void *KDTree;

typedef void *Item;

struct KDTree_t {
  /**
   * Funcao para criar a KDTree;
   * @param k: numero para particionar
   * resto dos parametros são as funções de comparacao do modelo
   * int compare(const void *a, const void *b)
   */
  KDTree (*create)(
    int dimensao, int (*check_equal)(const void *a, const void *b), ...);

  /**
   * Insere na arvore, usando as funcoes passadas no inicio
   */
  KDTree (*insert)(KDTree this, Item value);

  /**
   * Delete recursivamente o nó de valor 'value' da arvore 'this'
   */
  KDTree (*delete)(KDTree this, Item value);

  /**
   * Procura na arvore 'this' o nó com valor 'value'. Usa a funcao check_equal, passada ao criar a arvore
   */
  KDTree (*search)(KDTree this, Item value);

  /**
   * Retorna o valor da raiz da KDTree passada.
   */
  Item (*get)(KDTree this);

  /**
   * Retorna o node com o menor valor da dimensao 'dim'
   */
  KDTree (*find_min)(KDTree this, unsigned dim);

  /**
   * Retorna 1 caso a KDTree indicada for uma folha.
   * 0 caso nao seja.
   */
  int (*is_leaf)(KDTree this);

  /**
   * Passa por toda a arvore executando a funcao nos itens
   */
  void (*passe_simetrico)(KDTree this, void (*executar)(const Item item));

  /**
   * Pesquisa na arvore 'this' de acordo com um intervalo
   */
  KDTree (*range_search)(KDTree this, ...);

  /**
   * Destroi a arvore
   */
  void (*destroy)(KDTree this, void (*destroy_element)(Item item));
};

extern const struct KDTree_t KDTree_t;

#endif  // __KDTREE_H__
