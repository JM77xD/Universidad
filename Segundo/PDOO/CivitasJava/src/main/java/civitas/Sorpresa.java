/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

import java.util.ArrayList;

public abstract class Sorpresa {
    protected String texto;
    protected int valor;
    protected Tablero refT;
    protected MazoSorpresas refMS;
    
    Sorpresa(int v) {
        this.init();
        valor = v;
    }
    
    
    Sorpresa(Tablero tab) {
        this.init();
        refT = tab;
    }
    
    Sorpresa(Tablero tab, int v) {
        this.init();
        refT = tab;
        valor = v;
    }
    
    Sorpresa(MazoSorpresas mazo) {
        this.init();
        refMS = mazo;
    }
    
    Sorpresa(int v, String t) {
        this.init();
        valor = v;
        texto = t;
    }
    
    private void init() {
        texto = null;
        valor = -1;
        refT = null;
        refMS = null;
    }
    
    Boolean jugadorCorrecto(int actual, ArrayList<Jugador> todos) {
        return todos.size() > actual;
    }
    
    void informe(int actual, ArrayList<Jugador> todos) {
        if (jugadorCorrecto(actual, todos)) {
            Jugador sorprendido = todos.get(actual);
            Diario.getInstance().ocurreEvento("Se está aplicando una sorpresa al jugador " + sorprendido.getNombre());
        }
    }
    
    abstract void aplicarAJugador(int actual, ArrayList<Jugador> todos);
    
}
