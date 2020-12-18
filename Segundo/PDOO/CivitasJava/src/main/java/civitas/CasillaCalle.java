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
public class CasillaCalle extends Casilla {
    private TituloPropiedad titulo;
    
    CasillaCalle(TituloPropiedad tit) {
        super(tit.getNombre());
        titulo = tit;
    }
    
    void recibeJugador(int actual, ArrayList<Jugador> todos) {
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            Jugador jugador = todos.get(actual);
            if (!titulo.tienePropietario()) {
                jugador.puedeComprarCasilla();                
            } else {
                titulo.tramitarAlquiler(jugador);
            }
        }
    }
    
    public String toString() {
        String ret = "la casilla ";
        ret += nombre;
        ret += ", de tipo Calle ";
        if (!titulo.tienePropietario()) {
            ret += "con un precio de ";
            ret += titulo.getPrecioCompra();
        }
        ret += ".";
        return ret;
    }
    
    TituloPropiedad getTituloPropiedad() {
        return titulo;
    }
}
