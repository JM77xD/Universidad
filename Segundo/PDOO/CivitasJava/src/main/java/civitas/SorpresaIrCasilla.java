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
public class SorpresaIrCasilla extends Sorpresa {
    
    SorpresaIrCasilla(Tablero tab, int v) {
        super(tab, v);
    }
    
    void aplicarAJugador(int actual, ArrayList<Jugador> todos) {
        String evento = "La casilla sorpresa es de tipo IrCasilla";
        Diario.getInstance().ocurreEvento(evento);
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            int casillaAct = todos.get(actual).getNumCasillaActual();
            int tirada = refT.calcularTirada(casillaAct, valor);
            int nuevaPos = refT.nuevaPosicion(casillaAct, tirada);
            todos.get(actual).moverACasilla(nuevaPos);
            refT.getCasilla(nuevaPos).recibeJugador(actual, todos);
        }
    }
    
}
