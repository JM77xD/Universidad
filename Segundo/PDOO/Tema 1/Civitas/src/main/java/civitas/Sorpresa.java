/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

import java.util.ArrayList;

public class Sorpresa {
    private TipoSorpresa tipo;
    private String texto;
    private int valor;
    private Tablero refT;
    private MazoSorpresas refMS;
    
    
    Sorpresa(TipoSorpresa ts, Tablero tab) {
        this.init();
        tipo = ts;
        refT = tab;
    }
    
    Sorpresa(TipoSorpresa ts, Tablero tab, int v) {
        this.init();
        tipo = ts;
        refT = tab;
        valor = v;
    }
    
    Sorpresa(TipoSorpresa ts, MazoSorpresas mazo) {
        this.init();
        tipo = ts;
        refMS = mazo;
    }
    
    Sorpresa(TipoSorpresa ts, int v, String t) {
        this.init();
        tipo = ts;
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
    
    void aplicarAJugador(int actual, ArrayList<Jugador> todos) {
        String evento = "La casilla sorpresa es de tipo " + tipo.toString();
        if (texto != null)
            evento += " con efecto: " + texto + ".";
        Diario.getInstance().ocurreEvento(evento);
        if (null != tipo) switch (tipo) {
            case IRCARCEL:
                aplicarAJugador_irCarcel(actual, todos);
                break;
            case IRCASILLA:
                aplicarAJugador_irACasilla(actual, todos);
                break;
            case PAGARCOBRAR:
                aplicarAJugador_pagarCobrar(actual, todos);
                break;
            case PORCASAHOTEL:
                aplicarAJugador_porCasaHotel(actual, todos);
                break;
            case PORJUGADOR:
                aplicarAJugador_porJugador(actual, todos);
                break;
            case SALIRCARCEL:
                aplicarAJugador_salirCarcel(actual, todos);
                break;
            default:
                break;
        }
    }
    
    void aplicarAJugador_irCarcel(int actual, ArrayList<Jugador> todos) {
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            todos.get(actual).encarcelar(refT.getCarcel());
        }
    }
    
    void aplicarAJugador_irACasilla(int actual, ArrayList<Jugador> todos) {
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            int casillaAct = todos.get(actual).getNumCasillaActual();
            int tirada = refT.calcularTirada(casillaAct, valor);
            int nuevaPos = refT.nuevaPosicion(casillaAct, tirada);
            todos.get(actual).moverACasilla(nuevaPos);
            refT.getCasilla(nuevaPos).recibeJugador(actual, todos);
        }
    }
    
    void aplicarAJugador_pagarCobrar(int actual, ArrayList<Jugador> todos) {
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            todos.get(actual).modificarSaldo((float) valor);
        }
    }
    
    void aplicarAJugador_porCasaHotel(int actual, ArrayList<Jugador> todos) {
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            int edificios = todos.get(actual).cantidadCasasHoteles();
            todos.get(actual).modificarSaldo((float) valor*edificios);
        }
    }
    
    void aplicarAJugador_porJugador(int actual, ArrayList<Jugador> todos) {
        if (jugadorCorrecto(actual, todos)) {
            informe(actual, todos);
            Sorpresa suma = new Sorpresa(TipoSorpresa.PAGARCOBRAR, valor*(todos.size()-1), texto);
            Sorpresa resta = new Sorpresa(TipoSorpresa.PAGARCOBRAR, -1*valor, texto);
            
            for (int i = 0; i < todos.size(); i++) {
                if (i == actual) {
                    suma.aplicarAJugador_pagarCobrar(i, todos);
                } else {
                    resta.aplicarAJugador_pagarCobrar(i, todos);
                }
            }
        }
    }
    
    void aplicarAJugador_salirCarcel(int actual, ArrayList<Jugador> todos) {
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
        if (tipo == TipoSorpresa.SALIRCARCEL) {
            refMS.inhabilitarCartaEspecial(this);
        }
    }
    
    void usada() {
        if (tipo == TipoSorpresa.SALIRCARCEL) {
            refMS.habilitarCartaEspecial(this);
        }
    }
    
    public String toString() {
        return tipo.toString();
    }
    
}
