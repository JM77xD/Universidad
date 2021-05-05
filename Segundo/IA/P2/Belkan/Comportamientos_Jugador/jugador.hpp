#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"

#include <list>
#include <vector>

struct estado {
  int fila;
  int columna;
  int orientacion;

  inline bool operator==(const estado &otro) const {
    return (this->columna == otro.columna && this->fila == otro.fila && this->orientacion == otro.orientacion);
  }

  inline bool operator==(const estado &otro) {
    return (this->columna == otro.columna && this->fila == otro.fila && this->orientacion == otro.orientacion);
  }

  inline bool operator!=(const estado &otro) const {
    return !(*this == otro);
  }

  inline bool operator!=(const estado &otro) {
    return !(*this == otro);
  }
};

class ComportamientoJugador : public Comportamiento {
  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size) {
      hayPlan = false;
    }

    ComportamientoJugador(std::vector< std::vector< unsigned char> > mapaR) : Comportamiento(mapaR) {
      hayPlan = false;
    }
    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    void VisualizaPlan(const estado &st, const list<Action> &plan);
    ComportamientoJugador * clone(){return new ComportamientoJugador(*this);}
    struct nodoAnch {
	    estado st;
	    Action accion;
    };

    struct nodoCost {
	    estado st;
      bool bikini;
      bool zapatillas;

      int costo;

      inline bool operator == (const nodoCost &otro) const {
        return st == otro.st && bikini == otro.bikini && zapatillas == otro.zapatillas;
      }

      inline bool operator != (const nodoCost &otro) const {
        return !(*this == otro);
      }

      
      inline bool operator<(const nodoCost &otro) const {
        return this->costo > otro.costo;
      }
      

    };


  private:
    // Declarar Variables de Estado
    estado actual;
    list<estado> objetivos;
    list<Action> plan;
    bool hayPlan;

    // Métodos privados de la clase
    bool pathFinding(int level, const estado &origen, const list<estado> &destino, list<Action> &plan);
    bool pathFinding_Profundidad(const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_Anchura(const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_Costo(const estado &origen, const estado &destino, list<Action> &plan);

    bool esDestino(const estado &est, const estado &dest);
    bool esOrigen(const estado & est, const estado &orig);
    vector<nodoAnch> siguientes(const estado &origen);
    vector<pair<nodoCost, Action>> siguientesCosto(const nodoCost &origen);

    void PintaPlan(list<Action> plan);
    bool HayObstaculoDelante(estado &st);

    friend struct ComparaEstadosAnch;

};

#endif
