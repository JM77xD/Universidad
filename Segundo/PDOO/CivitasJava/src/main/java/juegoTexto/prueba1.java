/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package juegoTexto;

import civitas.CivitasJuego;


public class prueba1 {

    public static void main(String[] args) {
        String [] nombres = {"Marco", "Polo", "Si", "No"};
        CivitasJuego juego = new CivitasJuego(nombres);
        VistaTextual vista = new VistaTextual();
        Controlador controlador = new Controlador(juego, vista);
        controlador.setDebug(false);
        controlador.juega();
    }
    
}
