/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

/**
 *
 * @author jmramirez
 */
public class Casilla {
    private String nombre;
    private TipoCasilla tipo;
    
    Casilla(String p, TipoCasilla t) {
        nombre = p;
        tipo = t;
    }
    
    String getNombre() {
        return nombre;
    }
    
    TipoCasilla getTipo() {
        return tipo;
    }
}
