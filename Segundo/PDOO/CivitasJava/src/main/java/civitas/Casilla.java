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
public class Casilla {
    
    protected String nombre;
    
    Casilla(String n) {
        nombre = n;
    }
    
    String getNombre() {
        return nombre;
    }
    
    void informe(int actual, ArrayList<Jugador> todos) {
        Diario.getInstance().ocurreEvento("El jugador " + todos.get(actual).getNombre() + " ha caído en " + this.toString());
    }
    
    public String toString() {
        String ret = "la casilla ";
        ret += this.nombre;
        ret += ", de tipo Descanso.";
        return ret;
    }
    
    Boolean jugadorCorrecto(int actual, ArrayList<Jugador> todos) {
        return (todos.size() > actual);
    }
    
    void recibeJugador(int actual, ArrayList<Jugador> todos) {
        informe(actual, todos);
    }
}
