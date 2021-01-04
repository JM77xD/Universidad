#ifndef ABB_hpp
#define ABB_hpp
#include "bintree.h"

template <class Tbase>
class ABB{
private:
  typedef typename bintree<Tbase>::node Nodo;
  //Representación
  bintree <Tbase> arbolb;
public:
  ABB() = default;
  ABB(const ABB<Tbase>& a) = default;
  ABB(const Tbase& e);
  ~ABB() = default;
  bool existe(const Tbase& e) const;
  void insertar(const Tbase& e);
  void borrar(const Tbase& e);
private:
  void borrar_nodo(Nodo n);
  
  /**
   Clase iterator para recorrer el árbol en Inorden
   */
public:
  class iterator{
  private:
    typename bintree<Tbase>::inorder_iterator iterador;
    iterator(Nodo n);
    friend class ABB<Tbase>;
  public:
    iterator() = default;
    iterator(const iterator & it) = default;
    ~iterator() = default;
    bool operator!=(const iterator & it) const;
    bool operator==(const iterator & it) const;
    iterator & operator=(const iterator & it) = default;
    Tbase & operator*();
    iterator & operator++();
  };

  iterator begin();
  iterator end();

  class const_iterator{
  private:
    typename bintree<Tbase>::const_inorder_iterator iterador;
    const_iterator(Nodo n);
    friend class ABB<Tbase>;
  public:
    const_iterator() = default;
    const_iterator(const const_iterator & i) = default;
    ~const_iterator() = default;
    bool operator!=(const const_iterator & i) const;
    bool operator==(const const_iterator & i) const;
    const_iterator & operator=(const const_iterator & i) = default;
    const Tbase & operator*() const;
    const_iterator & operator++();
  };

  const_iterator begin() const;
  const_iterator end() const;

};


#include "ABB.cpp"

#endif /* ABB_hpp */
