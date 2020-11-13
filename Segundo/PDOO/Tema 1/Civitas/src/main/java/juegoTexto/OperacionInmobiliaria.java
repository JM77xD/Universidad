/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package juegoTexto;

public class OperacionInmobiliaria {
    private int numPropiedad;
    private GestionesInmobiliarias gestion;
    
    public OperacionInmobiliaria(GestionesInmobiliarias gest, int ip) {
        gestion = gest;
        numPropiedad = ip;
    }
    
    int getNumPropiedad() {
        return numPropiedad;
    }
    
    GestionesInmobiliarias getGestion() {
        return gestion;
    }
}
