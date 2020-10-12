/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

import java.util.ArrayList;

/**
 *
 * @author jmramirez
 */
public class Tablero {
    private int numCasillaCarcel;
    private ArrayList<Casilla> casillas;
    private int porSalida;
    private boolean tieneJuez;
    
    public Tablero(int carcel) {        //Constructor al que se le pasa por parámetros la casilla carcel
        if (carcel >= 1) {      //if para comprobar la validez de la casilla carcel
            numCasillaCarcel = carcel;
        } else {
            numCasillaCarcel = 1;
        }
        casillas = new ArrayList<>();
        Casilla salida = new Casilla("Salida", TipoCasilla.DESCANSO);
        casillas.add(salida);
        porSalida = 0;
        tieneJuez = false;
    }
    
    private boolean correcto(){     //Comprueba la validez del tablero
        if (casillas.size() > numCasillaCarcel && tieneJuez) {
            return true;
        } else {
            return false;
        }
    }
    
    private boolean correcto(int numCasilla){       //Comprueba la validez de una casilla
        return correcto() && casillas.size() > numCasilla;
    }
    
    int getCarcel() {       //Consultor del numCasillaCarcel
        return numCasillaCarcel;
    }
    
    int getPorSalida() {    //Devuelve el valor de porSalida
        if (porSalida > 0 ) {
            int valor = porSalida;
            porSalida--;
            return valor;
        } else {
            return porSalida;
        }
    }
    
    void añadeCasilla(Casilla casilla) {        //Añade una casilla al tablero
        if (casillas.size() == numCasillaCarcel) {
            Casilla carcel = new Casilla("Cárcel",TipoCasilla.DESCANSO);
            casillas.add(carcel);
        }
        casillas.add(casilla);
        if (casillas.size() == numCasillaCarcel) {
            Casilla carcel = new Casilla("Cárcel", TipoCasilla.DESCANSO);
            casillas.add(carcel);
        }
    }
    
    void añadeJuez() {          //Añade el juez al tablero
        if (!tieneJuez) {
            Casilla juez = new Casilla("Juez", TipoCasilla.JUEZ);
            casillas.add(juez);
            tieneJuez = true;
        }
    }
    
    Casilla getCasilla(int numCasilla) {        //Devuelve la casilla solicitada
        if (correcto(numCasilla)) {
            return casillas.get(numCasilla);
        } else return null;
    }
    
    int nuevaPosicion(int actual, int tirada) {     //Calcula la nueva posicion del jugador en el tablero
        if (!correcto()) return -1;
        return (actual+tirada) % casillas.size();
    }
    
    int calcularTirada(int origen, int destino) {       //Calcula la tirada que tendrías que sacar para acabar en cierta posicion desde tu posicion actual
        int diferencia = destino-origen;
        if (diferencia < 0) {
            diferencia += casillas.size();
        }
        return diferencia;
    }
}
