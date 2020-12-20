/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

import java.util.Scanner;


/**
 *
 * @author jmramirez
 */
public class JugadorEspeculador extends Jugador {
    private final int FactorEspeculador = 2;
    private final float fianza;
    
    JugadorEspeculador(Jugador jugador, float f) {
        super(jugador);
        fianza = f;
        HotelesMax = HotelesMax*FactorEspeculador;
        CasasMax = CasasMax*FactorEspeculador;
        actualizaPropietarioPorConversion();
    }
    
    Boolean pagaImpuesto(float cantidad) {
        if (isEncarcelado()) {
            return false;
        } else {
            return paga(cantidad/FactorEspeculador);
        }
    }
    
    Boolean debeSerEncarcelado() {
        if (isEncarcelado()) {
            return false;
        } else if (tieneSalvoconducto()) {
            perderSalvoconducto();
            Diario.getInstance().ocurreEvento("El jugador especulador " + getNombre() + " se libra de la cárcel a cambio del salvoconducto");
            return false;
        } else if (puedoGastar(fianza)){
            System.out.println("Desea Pagar una fianza de " + fianza + " y así evitar la cárcel? (y/n)");
            Scanner in = new Scanner(System.in);
            String cadena = in.nextLine();
            if ("y".equals(cadena)) {
                Diario.getInstance().ocurreEvento("El jugador especulador " + getNombre() + " se libra de la cárcel pagando una fianza");
                paga(fianza);
                return false;
            } else {
                return true;
            }
        } else {
            return true;
        }
    }
    
    public String toString() {
        return "el jugador especulador " + getNombre() + " posee " + getPropiedades().size() + " propiedades y tiene un saldo de " + getSaldo() + ".";
    }
}
