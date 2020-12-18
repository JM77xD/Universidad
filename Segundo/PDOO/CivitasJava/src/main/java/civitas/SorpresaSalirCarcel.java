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
public class SorpresaSalirCarcel extends Sorpresa {
    
    SorpresaSalirCarcel(MazoSorpresas mazo) {
        super(mazo);
    }
    
    void aplicarAJugador(int actual, ArrayList<Jugador> todos) {
        String evento = "La casilla sorpresa es de tipo SalirCarcel";
        Diario.getInstance().ocurreEvento(evento);
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);            
            Boolean tomada = false;
            
            for (Jugador jugador : todos) {
                if (!tomada) {
                    tomada = jugador.tieneSalvoconducto();
                }
            }
            
            if(!tomada) {
                todos.get(actual).obtenerSalvoconducto(this);
                salirDelMazo();
            }
        }
    }
    
    void salirDelMazo() {
        refMS.inhabilitarCartaEspecial(this);
    }
    
    void usada() {
        refMS.habilitarCartaEspecial(this);
    }
    
}
