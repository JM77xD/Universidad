/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

import java.util.ArrayList;
import java.util.Collections;

public class MazoSorpresas {
    private ArrayList<Sorpresa> sorpresas;
    private Boolean barajada;
    private int usadas;
    private Boolean debug;
    private ArrayList<Sorpresa> cartasEspeciales;
    private Sorpresa ultimaSorpresa;
    
    private void init() {       //Inicializa el mazo de cartas tipo sorpresa
        sorpresas = new ArrayList<>();
        cartasEspeciales = new ArrayList<>();
        usadas = 0;
        barajada = false;
    }
    
    MazoSorpresas(Boolean d) {  //Constructor con booleano para activar o desactivar el debug
        debug = d;
        init();
        if (d) {
            Diario.getInstance().ocurreEvento("Se ha fijado el estado del debug a true");
        } else {
            Diario.getInstance().ocurreEvento("Se ha fijado el estado del debug a false");
        }
    }
    
    MazoSorpresas() {   //Constructor por defecto, inicia el debug a false
        init();
        debug = false;
    }
    
    void alMazo(Sorpresa s) {   //Añade una sorpresa al mazo
        if (!barajada) {
            sorpresas.add(s);
        }
    }
    
    Sorpresa siguiente() {      //Lee la siguiente sorpresa de la lista
        if (!barajada || usadas == sorpresas.size()) {  //Si no se ha barajado o todas las cartas han sido iguales
            if (!debug) {       //si no se ha activado el debug
                Collections.shuffle(sorpresas); //Baraja y establece las usadas a 0
            }
            usadas = 0;
            barajada = true;
        }
        usadas++;       //Saca la primera carta y la añade en la ultima posición
        ultimaSorpresa = sorpresas.remove(0);
        sorpresas.add(ultimaSorpresa);
        return ultimaSorpresa;
    }
    
    void inhabilitarCartaEspecial(Sorpresa sorpresa) {      //Saca una de las cartas y la añade al mazo de cartas especiales, sacándola del mazo de juego
        if (sorpresas.contains(sorpresa)) {
            int indice = sorpresas.indexOf(sorpresa);
            cartasEspeciales.add(sorpresas.remove(indice));
            Diario.getInstance().ocurreEvento("Una carta sorpresa ha sido retirada del mazo de juego y añadida al mazo de descartes");
        }
    }
    
    void habilitarCartaEspecial(Sorpresa sorpresa) {        //Incluye una de las cartas retiradas al mazo de cartas especiales y la vuelve a poner en el mazo de juego
        if(cartasEspeciales.contains(sorpresa)) {
            int indice = cartasEspeciales.indexOf(sorpresa);
            sorpresas.add(cartasEspeciales.remove(indice));
            Diario.getInstance().ocurreEvento("Una carta sorpresa ha sido retirada del mazo de descartes y añadida al mazo de juego");
        }
    }
}
