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
public class SorpresaConversion extends Sorpresa {
    
    private CivitasJuego refJuego;
    
    SorpresaConversion(int v, CivitasJuego juego) {
        super(v);
        refJuego = juego;
    }
    
    void aplicarAJugador(int actual, ArrayList<Jugador> todos) {
        String evento = "La casilla sorpresa es de tipo Conversion.";
        Diario.getInstance().ocurreEvento(evento);
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            ArrayList<Jugador> jugadores = refJuego.getJugadores();
            Jugador jugadorActual = todos.get(actual);
            if ( jugadores.contains(jugadorActual) ) {
                int indice = jugadores.indexOf(jugadorActual);
                JugadorEspeculador nuevoJugador = new JugadorEspeculador(jugadores.remove(indice), valor);
                jugadores.add(indice, nuevoJugador);
            }
        }
    }
    
}
