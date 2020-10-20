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
public class Casilla {
    private String nombre;
    private TipoCasilla tipo;
    private TituloPropiedad titulo;
    private float importe;
    private int carcel;
    private MazoSorpresas refMS;
    
    Casilla(String n) {
        init();
        tipo = TipoCasilla.DESCANSO;
        nombre = n;
    }
    
    Casilla(TituloPropiedad tit) {
        init();
        tipo = TipoCasilla.CALLE;
        titulo = tit;
        nombre = tit.getNombre();
    }
    
    Casilla(float cant, String n) {
        init();
        tipo = TipoCasilla.IMPUESTO;
        nombre = n;
        importe = cant;
    }
    
    Casilla(int nCasillaCarcel, String n) {
        init();
        tipo = TipoCasilla.JUEZ;
        nombre = n;
        carcel = nCasillaCarcel;
    }
    
    Casilla(MazoSorpresas mazo, String n) {
        init();
        tipo = TipoCasilla.SORPRESA;
        nombre = n;
        refMS = mazo;
    }
    
    private void init() {
        nombre = null;
        titulo = null;
        refMS = null;
    }
    
    TituloPropiedad getTituloPropiedad() {
        return titulo;
    }
    
    String getNombre() {
        return nombre;
    }
    
    void informe(int actual, ArrayList<Jugador> todos) {
        Diario.getInstance().ocurreEvento("El jugador " + todos.get(actual).getNombre() + " ha caído en la casilla " + this.toString());
    }
    
    public String toString() {
        return nombre + ", de tipo " + tipo.toString();
    }
    
    Boolean jugadorCorrecto(int actual, ArrayList<Jugador> todos) {
        return (todos.size() > actual);
    }
    
    void recibeJugador_impuesto(int actual, ArrayList<Jugador> todos) {
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            todos.get(actual).pagaImpuesto(importe);
        }
    }
    
    void recibeJugador_Juez(int actual, ArrayList<Jugador> todos) {
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            todos.get(actual).encarcelar(carcel);
        }
    }
}
