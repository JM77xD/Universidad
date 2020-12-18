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
public class CasillaImpuesto extends Casilla {
    
    private float importe;
    
    CasillaImpuesto(float cantidad, String n) {
        super(n);
        importe = cantidad;
    }
    
    void recibeJugador(int actual, ArrayList<Jugador> todos) {
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            todos.get(actual).pagaImpuesto(importe);
        }
    }
    
    public String toString() {
        String ret = "la casilla ";
        ret += this.nombre;
        ret += ", de tipo Impuesto.";
        return ret;
    }
    
}
