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
public class SorpresaIrCarcel extends Sorpresa {
    
    SorpresaIrCarcel(Tablero tab) {
        super(tab);
    }
    
    void aplicarAJugador(int actual, ArrayList<Jugador> todos) {
        String evento = "La casilla sorpresa es de tipo IrCarcel";
        Diario.getInstance().ocurreEvento(evento);
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            todos.get(actual).encarcelar(refT.getCarcel());
        }
    }
}
