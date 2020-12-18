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
public class CasillaSorpresa extends Casilla {
    
    private MazoSorpresas refMS;
    
    CasillaSorpresa(MazoSorpresas mazo, String n) {
        super(n);
        refMS = mazo;
    }
    
    void recibeJugador(int actual, ArrayList<Jugador> todos) {
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            var siguiente = refMS.siguiente();
            siguiente.aplicarAJugador(actual, todos);
        }
    }
    
    public String toString() {
        String ret = "la casilla ";
        ret += this.nombre;
        ret += ", de tipo Sorpresa.";
        return ret;
    }
}
