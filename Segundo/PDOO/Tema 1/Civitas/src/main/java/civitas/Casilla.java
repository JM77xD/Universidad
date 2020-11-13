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
        Diario.getInstance().ocurreEvento("El jugador " + todos.get(actual).getNombre() + " ha caído en " + this.toString());
    }
    
    public String toString() {
        String ret = "la casilla ";
        ret += this.nombre;
        ret += ", de tipo ";
        ret += tipo.toString();
        if (tipo == TipoCasilla.CALLE && !titulo.tienePropietario()) {
            ret += " con un precio de ";
            ret += titulo.getPrecioCompra();
        }
        ret += ".";
        return ret;
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
    
    void recibeJugador_calle(int actual, ArrayList<Jugador> todos) {
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            Jugador jugador = todos.get(actual);
            if (!titulo.tienePropietario()) {
                jugador.puedeComprarCasilla();                
            } else {
                titulo.tramitarAlquiler(jugador);
            }
        }
    }
    
    void recibeJugador_sorpresa(int actual, ArrayList<Jugador> todos) {
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            Sorpresa siguiente = refMS.siguiente();
            siguiente.aplicarAJugador(actual, todos);
        }
    }
    
    void recibeJugador(int actual, ArrayList<Jugador> todos) {
        if (null != tipo) switch (tipo) {
            case CALLE:
                recibeJugador_calle(actual,todos);
                break;
            case SORPRESA:
                recibeJugador_sorpresa(actual,todos);
                break;
            case JUEZ:
                recibeJugador_Juez(actual,todos);
                break;
            case IMPUESTO:
                recibeJugador_impuesto(actual,todos);
                break;
            default:
                informe(actual, todos);
                break;
        }
    }
}
