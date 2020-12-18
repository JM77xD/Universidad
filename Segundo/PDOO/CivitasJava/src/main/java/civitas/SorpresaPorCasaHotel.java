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
public class SorpresaPorCasaHotel extends Sorpresa {
    
    SorpresaPorCasaHotel(int v, String t) {
        super(v,t);
    }
    
    void aplicarAJugador(int actual, ArrayList<Jugador> todos) {
        String evento = "La casilla sorpresa es de tipo PorCasaHotel, con efecto: " + texto + ".";
        Diario.getInstance().ocurreEvento(evento);
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            int edificios = todos.get(actual).cantidadCasasHoteles();
            todos.get(actual).modificarSaldo((float) valor*edificios);
        }
    }
    
}
