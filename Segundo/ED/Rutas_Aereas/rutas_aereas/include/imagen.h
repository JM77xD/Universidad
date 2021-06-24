/**
  * @file imagen.h
  * @brief Fichero con la definición e implementación de la clase Imagen
  *
  * Permite el manejo de imágenes en formato ppm y pgm
  * 
  * @see imagenES.h
  *
  */

#ifndef __IMAGEN_H
#define __IMAGEN_H
#include "imagenES.h"
#include <cassert>
#include <iostream>
#include <string>

/**
 * @enum Tipo_Pegado
 * 
 * @brief Permite distinguir entre los dos tipos de pegado en una imagen, Opaco o Bleding
 * 
 */
enum Tipo_Pegado {OPACO, BLENDING};

using namespace std;

/**
 * @struct Pixel
 * 
 * @brief Facilita el tratamiento de imágenes con una estructura tipo rgb, además de un valor para la transparencia
 * 
 */
struct Pixel {
  
  /**
   * @brief Color rojo
   * 
   */
  unsigned char r;

  /**
   * @brief Color verde
   * 
   */
  unsigned char g;

  /**
   * @brief Color azul
   * 
   */
  unsigned char b;

  /**
   * @brief Transparencia del Pixel.
   * 
   * 0->no, 255->si
   * 
   */
  unsigned char transp;

}; 


/**
 * @class Imagen
 * 
 * @brief Facilita y permite el tratamiento de imágenes en formato pgm y ppm
 * 
 * @see ImagenES.h
 * 
 */
class Imagen{
  private:

    /**
     * @brief Pixeles que conforman la Imagen
     * 
     * @see Pixel
     * 
     */
    Pixel ** data;
    /**
     * @brief Numero de filas de la Imagen
     * 
     */
    int nf;

    /**
     * @brief Numero de columnas de la Imagen
     * 
     */
    int nc;

    /**
     * @brief Borra la Imagen, liberando espacio
     * 
     */
    void Borrar();

    /**
     * @brief Copia los valores de otra Imagen
     * 
     * @param I Imagen de la que copiar los valores
     */
    void Copiar(const Imagen &I);

  public:

    /**
     * @brief Constructor por defecto
     * 
     */
    Imagen();
    
    /**
     * @brief Constructor dado el número de filas y columnas de la Imagen
     * 
     * @param f Número de filas
     * @param c Número de columnas
     */
    Imagen(int f,int c);
    
    /**
     * @brief Constructor de copia
     * 
     * @param I Imagen a copiar
     */
    Imagen(const Imagen & I);
    
    /**
     * @brief Operador de asignación
     * 
     * @param I Imagen de la que tomar los valores a asignar
     * @return Devuelve una referencia a si mismo
     */
    Imagen & operator=(const Imagen & I);
    
    ~Imagen();
    
    /**
     * @brief Operador de acceso
     * 
     * @param i Fila a la que acceder
     * @param j Columna a la que acceder
     * @return Devuelve una referencia a un objeto de la clase Pixel que se encuentra en la fila i y columna j de la Imagen
     * 
     * @see Pixel
     */
    Pixel & operator ()(int i,int j);
    
    /**
     * @brief Operador de acceso
     * 
     * @param i Fila a la que acceder
     * @param j Columna a la que acceder
     * @return Devuelve una referencia constante a un objeto de la clase Pixel que se encuentra en la fila i y columna j de la Imagen
     */
    const Pixel & operator ()(int i,int j)const;
    
    /**
     * @brief Permite escribir la Imagen actual en un archivo
     * 
     * @param nombre Nombre del archivo en el que se piensa escribir la Imagen
     */
    void EscribirImagen(const char * nombre);
    
    /**
     * @brief Permite leer la Imagen de un archivo, recortando lo que no nos interesa
     * 
     * @param nombre Nombre del archivo a leer
     * @param nombremascara Nombre del archivo que contiene la parte de nombre que no nos interesa
     */
    void LeerImagen (const char *nombre,const string &nombremascara="");

    /**
     * @brief Limpia la transparencia asociada a todos los píxeles de una Imagen
     * 
     */
    void LimpiarTransp();

    /**
     * @brief Consultor del número de filas
     * 
     * @return Devuelve el número de filas de la Imagen
     */
    int num_filas()const{return nf;}

    /**
     * @brief Consultor del número de columnas
     * 
     * @return Devuelve el número de columnas de la Imagen
     */
    int num_cols()const{return nc;}

    /**
     * @brief Superpone una Imagen sobre this
     * 
     * @param posi Fila en la que empezar a poner la Imagen
     * @param posj Columna en la que empezar a poner la Imagen
     * @param I Imagen a poner
     * @param tippegado Tipo de pegado asociado a la Imagen
     * 
     * @see Tipo_Pegado
     */
    void PutImagen(int posi,int posj, const Imagen &I,Tipo_Pegado tippegado=OPACO);

    /**
     * @brief Permite extraer una Imagen que sea parte de la Imagen this
     * 
     * @param posi Fila de inicio
     * @param posj Columna de inicio
     * @param dimi Fila final
     * @param dimj Columna final
     * @return Devuelve un nuevo objeto de la clase Imagen con los valores pertinentes
     */
    Imagen ExtraeImagen(int posi,int posj,int dimi,int dimj);

};   
   
#endif