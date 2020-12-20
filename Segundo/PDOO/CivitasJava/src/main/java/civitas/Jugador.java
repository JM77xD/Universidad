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
public class Jugador implements Comparable<Jugador> {
    
    protected int CasasMax = 4;
    private int CasasPorHotel = 4;
    private Boolean encarcelado;
    protected int HotelesMax = 4;
    private String nombre;
    private int numCasillaActual;
    private final float PasoPorSalida = 1000;
    private final float PrecioLibertad = 200;
    private Boolean puedeComprar;
    private Float saldo;
    private float SaldoInicial = 7500;
    private SorpresaSalirCarcel Salvoconducto;
    private ArrayList<TituloPropiedad> propiedades = new ArrayList<>();
    
    Jugador(String n) {
        nombre = n;
        saldo = SaldoInicial;
        encarcelado = false;
    }
    
    protected Jugador(Jugador n) {
        nombre = n.nombre;
        encarcelado = n.encarcelado;
        numCasillaActual = n.numCasillaActual;
        puedeComprar = n.puedeComprar;
        saldo = n.saldo;
        propiedades = n.propiedades;
        Salvoconducto = n.Salvoconducto;
    }
    
    int cantidadCasasHoteles() {
        int suma = 0;
        for (TituloPropiedad propiedad : propiedades) {
            suma += propiedad.cantidadCasasHoteles();
        }
        return suma;
    }
    
    Boolean enBacarrota() {
        return saldo < 0;
    }
    
    int getCasasMax() {
        return CasasMax;
    }
    
    int getCasasPorHotel() {
        return CasasPorHotel;
    }
    
    int getHotelesMax() {
        return HotelesMax;
    }
    
    String getNombre() {
        return nombre;
    }
    
    int getNumCasillaActual() {
        return numCasillaActual;
    }    
    
    float getPrecioLibertad() {
        return PrecioLibertad;
    }
    
    float getPremioPasoSalida() {
        return PasoPorSalida;
    }
    
    public ArrayList<TituloPropiedad> getPropiedades() {
        return propiedades;
    }
    
    Boolean getPuedeComprar() {
        return puedeComprar;
    }
    
    float getSaldo() {
        return saldo;
    }
    
    Boolean isEncarcelado() {
        return encarcelado;
    }
    
    Boolean debeSerEncarcelado() {
        if (encarcelado) {
            return false;
        } else if (!tieneSalvoconducto()) {
            return true;
        } else {
            perderSalvoconducto();
            Diario.getInstance().ocurreEvento("El jugador " + nombre + " se libra de la cárcel a cambio del salvoconducto");
            return false;
        }
    }
    
    Boolean encarcelar(int numCasillaCarcel) {
        if (debeSerEncarcelado()) {
            moverACasilla(numCasillaCarcel);
            encarcelado = true;
            Diario.getInstance().ocurreEvento("El jugador " + nombre + " ha sido encarcelado");
        }
        return encarcelado;
    }
    
    Boolean obtenerSalvoconducto(SorpresaSalirCarcel s) {
        if (encarcelado) {
            return false;
        } else {
            Salvoconducto = s;
            return true;
        }
    }
    
    void perderSalvoconducto() {
        Salvoconducto.usada();
        Salvoconducto = null;
    }
    
    Boolean tieneSalvoconducto() {
        return (Salvoconducto != null);
    }
    
    Boolean puedeComprarCasilla() {
        puedeComprar = !encarcelado;
        return puedeComprar;
    }
    
    Boolean paga(float cantidad) {
        return modificarSaldo(-1*cantidad);
    }
    
    Boolean pagaImpuesto(float cantidad) {
        if (encarcelado) {
            return false;
        } else {
            return paga(cantidad);
        }
    }
    
    Boolean pagaAlquiler(float cantidad) {
        if (encarcelado) {
            return false;
        } else {
            return paga(cantidad);
        }
    }
    
    Boolean recibe(float cantidad) {
        if (encarcelado) {
            return false;
        } else {
            return modificarSaldo(cantidad);
        }
    }
    
    Boolean modificarSaldo(float cantidad) {
        saldo += cantidad;
        Diario.getInstance().ocurreEvento("El jugador " + nombre +" ha modificado su saldo en " + cantidad + ".");
        return true;
    }
    
    Boolean moverACasilla(int numCasilla) {
        if (encarcelado) {
            return false;
        } else {
            numCasillaActual = numCasilla;
            puedeComprar = false;
            Diario.getInstance().ocurreEvento("El jugador " + nombre + " ha sido movido a la casilla " + numCasilla);
            return true;
        }
    }
    
    Boolean puedoGastar(float precio) {
        return encarcelado ? false : saldo >= precio;
    }
    
    Boolean existeLaPropiedad(int ip) {
        return propiedades.size() > ip;
    }
    
    Boolean vender(int ip) {
        if (encarcelado) {
            return false;
        } else if (existeLaPropiedad(ip)) {
            if(propiedades.get(ip).vender(this)) {
                propiedades.remove(ip);
                Diario.getInstance().ocurreEvento("El jugador " + nombre + " ha realizado satisfactoriamente la venta de una propiedad.");
                return true;
            } else
                return false;
        } else
            return false;
    }
    
    Boolean tieneAlgoQueGestionar() {
        return (!propiedades.isEmpty());
    }
    
    Boolean puedeSalirCarcelPagando() {
        return saldo >= PrecioLibertad;
    }
    
    Boolean salirCarcelPagando() {
        if (encarcelado && puedeSalirCarcelPagando()) {
            paga(PrecioLibertad);
            encarcelado = false;
            Diario.getInstance().ocurreEvento("El jugador " + nombre + " ha salido de la cárcel pagando el precio (" + PrecioLibertad+").");
            return true;
        } else
            return false;
    }
    
    Boolean salirCarcelTirando() {
        if(Dado.getInstance().salgoDeLaCarcel()) {
            encarcelado = false;
            Diario.getInstance().ocurreEvento("El jugador " + nombre + " ha salido de la cárcel tirando el dado.");
            return true;
        } else
            return false;
    }
    
    Boolean pasaPorSalida() {
        modificarSaldo(PasoPorSalida);
        Diario.getInstance().ocurreEvento("El jugador " + nombre + " ha pasado por la salida y ha aumentado su saldo en " + PasoPorSalida +".");
        return true;
    }
    
    public int compareTo(Jugador otro) {
        return saldo.compareTo(otro.saldo);
    }
    
    public String toString() {
        return "el jugador " + nombre + " posee " + propiedades.size() + " propiedades y tiene un saldo de " + saldo + ".";
    }
    
    Boolean puedoEdificarHotel(TituloPropiedad propiedad) {
        return (propiedad.getNCasas() >= CasasPorHotel && propiedad.getNHoteles() < HotelesMax );
    }
    
    Boolean puedoEdificarCasa(TituloPropiedad propiedad) {
        return propiedad.getNCasas() < CasasMax;
    }
    
    Boolean cancelarHipoteca(int ip) {
        Boolean result = false;
        if (encarcelado) {
            return result;
        } else if (existeLaPropiedad(ip)) {
            TituloPropiedad propiedad = propiedades.get(ip);
            float cantidad = propiedad.getImporteCancelarHipoteca();
            if (puedoGastar(cantidad)) {
                result = propiedades.get(ip).cancelarHipoteca(this);
                if (result) {
                    Diario.getInstance().ocurreEvento("El jugador " + nombre + " ha cancelado la hipoteca de la propiedad " + propiedades.get(ip).getNombre() + ".");
                }
            }
        }
        return result;
    }
    
    Boolean hipotecar(int ip) {
        Boolean result = false;
        if (encarcelado)
            return result;
        if (existeLaPropiedad(ip)) {
            TituloPropiedad propiedad = propiedades.get(ip);
            result = propiedad.hipotecar(this);
            if (result)
                Diario.getInstance().ocurreEvento("El jugador " + nombre + " ha hipotecado la propiedad " + propiedades.get(ip).getNombre() + ".");
        }
        return result;
    }
    
    Boolean construirCasa(int ip) {
        Boolean result = false;
        if (encarcelado)
            return result;
        if (existeLaPropiedad(ip)) {
            TituloPropiedad propiedad = propiedades.get(ip);
            Boolean puedoedificarcasa = puedoEdificarCasa(propiedad);
            float precioEdificar = propiedad.getPrecioEdificar();
            if (puedoGastar(precioEdificar) && puedoedificarcasa) {
                result = propiedades.get(ip).construirCasa(this);
                if (result)
                    Diario.getInstance().ocurreEvento("El jugador " + nombre + " ha construido una casa en la propiedad " + propiedad.getNombre() + ".");
            }
        }
        return result;
    }
    
    Boolean construirHotel(int ip) {
        Boolean result = false;
        if (encarcelado)
            return result;
        if (existeLaPropiedad(ip)) {
            TituloPropiedad propiedad = propiedades.get(ip);
            Boolean puedoedificarhotel = puedoEdificarHotel(propiedad);
            float precioEdificar = propiedad.getPrecioEdificar();
            if (puedoGastar(precioEdificar) && puedoedificarhotel) {
                result = propiedades.get(ip).construirHotel(this);
                if (result) {
                    propiedades.get(ip).derruirCasas(CasasPorHotel, this);
                    Diario.getInstance().ocurreEvento("El jugador " + nombre + " ha construido un hotel en la propiedad " + propiedad.getNombre() + ".");
                }
            }
            
        }
        return result;
    }
    
    Boolean comprar(TituloPropiedad titulo) {
        Boolean result = false;
        if (encarcelado)
            return result;
        if (puedeComprar) {
            float precio = titulo.getPrecioCompra();
            if (puedoGastar(precio)) {
                result = titulo.comprar(this);
                if (result) {
                    propiedades.add(titulo);
                    Diario.getInstance().ocurreEvento("El jugador " + nombre + " ha comprado la propiedad " + titulo.getNombre() + ".");
                    puedeComprar = false;
                }
            }
        }
        return result;
    }
    
    void actualizaPropietarioPorConversion() {
        propiedades.forEach(propiedad -> {
            propiedad.actualizarPropietario(this);
        });
    }
}
