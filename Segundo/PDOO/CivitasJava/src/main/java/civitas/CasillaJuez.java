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
public class CasillaJuez extends Casilla{
    
    private int carcel;
    
    CasillaJuez(int nCarcel, String n) {
        super(n);
        carcel = nCarcel;
    }
    
    void recibeJugador(int actual, ArrayList<Jugador> todos) {
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            todos.get(actual).encarcelar(carcel);
        }
    }
    
    public String toString() {
        String ret = "la casilla ";
        ret += this.nombre;
        ret += ", de tipo Juez.";
        return ret;
    }
    
}
