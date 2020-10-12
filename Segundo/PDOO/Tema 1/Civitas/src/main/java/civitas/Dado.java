/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

import java.util.Objects;
import java.util.Random;

/**
 *
 * @author jmramirez
 */
public class Dado {
    
    private Random random;
    private int ultimoResultado;
    private Boolean debug;
    
    static final private Dado instance = new Dado();    //Crea una nueva instancia de dado que se mantiene toda la partida
    static final private int salidaCarcel = 5;          //Establece el resultado para salir de la carcel en 5
    
    private Dado() {        //Inicializa el dado
        ultimoResultado = 0;
        debug = false;
        random = new Random();
    }
    
    static public Dado getInstance() {      //Obtiene la estancia del dado
        return instance;
    }
    
    int tirar() {       //Realiza una tirada
        if (debug) {    //Si el modo debug está activo, devuelve siempre 1
            ultimoResultado = 1;
            return 1;
        } else {
            ultimoResultado = random.nextInt(6) + 1;    //Devuelve un numero aleatorio entre 1 y 6
            return ultimoResultado;
        }
    }
    
    Boolean salgoDeLaCarcel() {     //evalua si sales de la cárcel o no
        return tirar() == salidaCarcel;
    }
    
    int quienEmpieza(int n) {       //Genera un numero aleatorio entre 0 y n-1, siendo n el numero de jugadores
        return random.nextInt(n);
    }
    
    void setDebug(Boolean d) {
        if (!Objects.equals(debug, d)) {    //Si el estado solicitado es distinto al actual, efectua el cambio de estado
            debug = d;
            if (d) {    //Añade una entrada al diario
                Diario.getInstance().ocurreEvento("El estado del debug ha cambiado a 'true'");
            } else {
                Diario.getInstance().ocurreEvento("El estado del debug ha cambiado a 'false'");
            }
        }
    }
    
    int getUltimoResultado() {      //Devuelve el último resultado obtenido
        return ultimoResultado;
    }
    
}