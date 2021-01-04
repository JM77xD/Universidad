//template <class Tbase>
//ABB<Tbase>::ABB(){
//}

//template <class Tbase>
//ABB<Tbase>::ABB(const ABB<Tbase>& a):arbolb(a.arbolb){
//}

template <class Tbase>
ABB<Tbase>::ABB(const Tbase& e):arbolb(e){
}

//template <class Tbase>
//ABB<Tbase>::~ABB(){
//}

template <class Tbase>
bool ABB<Tbase>::existe(const Tbase &e) const{
  if(arbolb.empty())
    return false;
  else{
    //Empezamos a buscar por la raíz
    Nodo n = arbolb.root();
    bool encontrado = false;
    //Mientras no lo hayamos encontrado
    //ni hayamos llegado a un nodo nulo
    while(!encontrado && !n.null()){
      if(*n==e)
        encontrado = true;
      else if(e<*n)
        n = n.left();
      else
        n = n.right();
    }
    return encontrado;
  }
}

template <class Tbase>
void ABB<Tbase>::insertar(const Tbase& e){
  if (arbolb.empty())
    //Si el árbol está vacío
    arbolb = bintree<Tbase>(e);
  else{
    //Si el árbol no está vacío
    //Buscamos dónde insertar el nuevo nodo
    Nodo n = arbolb.root();
    bool posicionEncontrada = false;
    while(!posicionEncontrada){
      if (e<*n)
        if(!(n.left().null()))
          n = n.left();
        else
          posicionEncontrada = true;
      else
        if(!(n.right().null()))
          n = n.right();
        else
          posicionEncontrada = true;
    }
    //Una vez localizada la posición
    //insertamos el nodo
    //No hay que crearlo porque hay una
    //variante de insert que permite pasar
    //una etiqueta
    if (e<*n)
      arbolb.insert_left(n, e);
    else
      arbolb.insert_right(n, e);
  }
}

template <class Tbase>
void ABB<Tbase>::borrar(const Tbase &e){
  if (!arbolb.empty()){
    //Buscamos la etiqueta e en el árbol
    Nodo n = arbolb.root();
    bool encontrado = false;
    while(!encontrado && !n.null()){
      if (e == *n)
        encontrado = true;
      else if(e<*n)
        n = n.left();
      else
        n = n.right();
    }
    //Si lo hemos encontrado, lo borramos
    //Si no, no hacemos nada
    if (encontrado)
      borrar_nodo(n);
  }
}

template <class Tbase>
void ABB<Tbase>::borrar_nodo(Nodo n){
  
  if(n.left().null())
    if(n.right().null()){
      //Caso 1: n es un nodo hoja
      Nodo padre = n.parent();
      if(padre.null())
        //El árbol sólo tiene un nodo
        arbolb = bintree<Tbase>();
      else if (n == padre.left()){
        //n es un nodo hoja y es hijo izquierdo de su padre
        //Sólo tenemos que eliminarlo
        bintree<Tbase> a;
        arbolb.prune_left(padre, a);
      }
      else {
        //n es un nodo hoja y es hijo derecho de su padre
        //Sólo tenemos que eliminarlo
        bintree<Tbase> a;
        arbolb.prune_right(padre, a);
      }
    }
    else{
      //Caso 2: n sólo tiene un hijo a la derecha
      Nodo padre = n.parent();
      if (!(padre.null())){
        //Podamos el hijo para insertarlo en su lugar
        bintree<Tbase> a;
        arbolb.prune_right(n, a);
        if(n == padre.left())
          arbolb.insert_left(padre, a);
        else
          arbolb.insert_right(padre, a);
      }
      else{
        //n era la raíz y el subárbol derecho pasa
        //a ser el árbol
        bintree<Tbase> a;
        arbolb.prune_right(n, a);
        arbolb = a;
      }
    }
  
  else //arbol.izquierda(n)!=nodonulo
    if(n.right().null()){
      //Caso 3: n sólo tiene un hijo a la izquierda
      Nodo padre = n.parent();
      if(!(padre.null())){
        //Podamos el hijo para insertarlo en su lugar
        bintree <Tbase> a;
        arbolb.prune_left(n, a);
        if(n == padre.left())
          arbolb.insert_left(padre, a);
        else
          arbolb.insert_right(padre, a);
      }
      else{
        //n era la raíz y el subárbol izquierdo pasa
        //a ser el árbol
        bintree<Tbase> a;
        arbolb.prune_left(n, a);
        arbolb = a;
      }
    }
    else{
      //Caso 4: el nodo tiene dos hijos
      Nodo mhi;
      //Buscamos el mayor hijo a la izquierda
      mhi = n.left();
      while(!(mhi.right().null()))
        mhi = mhi.right();
      *n = *mhi;
      borrar_nodo(mhi);
    }
}



//////////////////////////////
// ITERADORES
//////////////////////////////

//template <class Tbase>
//ABB<Tbase>::iterator::iterator():elnodo(0){
//}

template <class Tbase>
ABB<Tbase>::iterator::iterator(Nodo n):iterador(n){
}

//template <class Tbase>
//ABB<Tbase>::iterator::iterator(const ABB<Tbase>::iterator& it):elnodo(it.elnodo){
//}

template <class Tbase>
bool ABB<Tbase>::iterator::operator==(const ABB<Tbase>::iterator &it)const{
  return this->iterador == it.iterador;
}

template <class Tbase>
bool ABB<Tbase>::iterator::operator!=(const ABB<Tbase>::iterator &it)const{
  return this->iterador != it.iterador;
}

//template <class Tbase>
//typename ABB<Tbase>::iterator&
//ABB<Tbase>::iterator::operator=(const ABB::iterator &it){
//  this->iterador = it.iterador;
//  return *this;
//}

template <class Tbase>
Tbase& ABB<Tbase>::iterator::operator*(){
  return *iterador;
}

template <class Tbase>
typename ABB<Tbase>::iterator& ABB<Tbase>::iterator::operator++(){
  ++iterador;
  return *this;
}

template <class Tbase>
typename ABB<Tbase>::iterator ABB<Tbase>::begin(){
  ABB<Tbase>::iterator it;
  it.iterador = arbolb.begin_inorder();
  return it;
}

template <class Tbase>
typename ABB<Tbase>::iterator ABB<Tbase>::end(){
  ABB<Tbase>::iterator it;
  it.iterador = arbolb.end_inorder();
  return it;
}

////////////////////////////////
//
//template <class Tbase>
//ABB<Tbase>::const_iterator::const_iterator():elnodo(0){
//}

template <class Tbase>
ABB<Tbase>::const_iterator::const_iterator(typename ABB<Tbase>::Nodo n):iterador(n){
}

//
//template <class Tbase>
//ABB<Tbase>::const_iterator::const_iterator(const ABB<Tbase>::const_iterator& it):elnodo(it.elnodo){
//}

template <class Tbase>
bool ABB<Tbase>::const_iterator::operator!=(const ABB<Tbase>::const_iterator &it)const{
  return this->iterador != it.iterador;
}

template <class Tbase>
bool ABB<Tbase>::const_iterator::operator==(const ABB<Tbase>::const_iterator &it)const{
  return this->iterador == it.iterador;
}

//template <class Tbase>
//typename ABB<Tbase>::const_iterator&
//ABB<Tbase>::const_iterator::operator=(const ABB::const_iterator &it){
//  this->iterador = it.iterador;
//  return *this;
//}

template <class Tbase>
const Tbase& ABB<Tbase>::const_iterator::operator*()const{
  return *iterador;
}

template <class Tbase>
typename ABB<Tbase>::const_iterator& ABB<Tbase>::const_iterator::operator++(){
  ++iterador;
  return *this;
}


template <class Tbase>
typename ABB<Tbase>::const_iterator ABB<Tbase>::begin()const{
  ABB<Tbase>::const_iterator it;
  it.iterador = arbolb.begin_inorder();
  return it;
}

template <class Tbase>
typename ABB<Tbase>::const_iterator ABB<Tbase>::end()const{
  ABB<Tbase>::const_iterator it;
  it.iterador = arbolb.end_inorder();
  return it;
}


