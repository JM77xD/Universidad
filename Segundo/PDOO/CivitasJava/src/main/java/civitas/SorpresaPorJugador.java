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
public class SorpresaPorJugador extends Sorpresa {
    
    SorpresaPorJugador(int v, String t) {
        super(v,t);
    }
    
    void aplicarAJugador(int actual, ArrayList<Jugador> todos) {
        String evento = "La casilla sorpresa es de tipo PorJugador, con efecto: " + texto + ".";
        Diario.getInstance().ocurreEvento(evento);
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            SorpresaPagarCobrar suma = new SorpresaPagarCobrar(valor*(todos.size()-1), texto);
            SorpresaPagarCobrar resta = new SorpresaPagarCobrar(-1*valor, texto);
            
            for (int i = 0; i < todos.size(); i++) {
                if (i == actual) {
                    suma.aplicarAJugador(i, todos);
                } else {
                    resta.aplicarAJugador(i, todos);
                }
            }
        }
    }
    
}
