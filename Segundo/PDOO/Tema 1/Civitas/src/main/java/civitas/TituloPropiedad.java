/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

/**
 *
 * @author jmramirez
 */
public class TituloPropiedad {
    
    private String nombre;
    private float PrecioBaseAlquiler;
    private double FactorRevalorizacion;
    private float PrecioBaseHipoteca;
    private float PrecioCompra;
    private float PrecioEdificar;
    private int nCasas;
    private int nHoteles;
    private Boolean Hipotecado;
    private final double FactorInteresesHipoteca = 1.1;
    private Jugador Propietario;
    private Boolean Comprada;
    
    
    TituloPropiedad(String n, float PBA, double FR, float PBH, float PC, float PE) {
        nombre = n;
        PrecioBaseAlquiler = PBA;
        FactorRevalorizacion = FR;
        PrecioBaseHipoteca = PBH;
        PrecioCompra = PC;
        PrecioEdificar = PE;
        Hipotecado = false;
        Comprada = false;
        nCasas = 0;
        nHoteles = 0;
    }
    
    public String toString() {
        String Devolver;
        Devolver = "La calle " + nombre + " tiene un precio base de alquiler " + PrecioBaseAlquiler;
        Devolver += ",\nun factor de revalorización de " + FactorRevalorizacion + ", un precio base de hipotecado " + PrecioBaseHipoteca + ",\nun precio de compra de " + PrecioCompra;
        Devolver += " y un precio por edificar de " + PrecioEdificar + ".\nActualmente tiene " + nCasas + " casas y " + nHoteles + " hoteles y se encuentra ";
        if (Hipotecado) {
            Devolver += "hipotecada.\n";
        } else {
            Devolver += "no hipotecada.\n";
        }
        
        return Devolver;
    }
    
    float getPrecioAlquiler() {
        if (Propietario.isEncarcelado() || Hipotecado) {
            return 0;
        } else {
            return (float) (PrecioBaseAlquiler*(1+(nCasas*0.5) + (nHoteles*2.5)));
        }
    }
    
    float getImporteCancelarHipoteca() {
        return (float) (PrecioBaseHipoteca*FactorInteresesHipoteca);
    }
    
    void tramitarAlquiler(Jugador jugador) {
        if (Comprada && !esElPropietario(jugador)) {
            float precioAlq = this.getPrecioAlquiler();
            jugador.pagaAlquiler(precioAlq);
            Propietario.recibe(precioAlq);
        }
    }
    
    Boolean propietarioEncarcelado() {
        return (Comprada && Propietario.isEncarcelado());
    }
    
    int cantidadCasasHoteles() {
        return (nCasas + nHoteles);
    }
    
    float getPrecioVenta() {
        return (float) (PrecioCompra + PrecioEdificar*this.cantidadCasasHoteles()*FactorRevalorizacion);
    }
    
    Boolean derruirCasas(int n, Jugador jugador) {
        if (jugador == Propietario && nCasas >= n) {
            nCasas -= n;
            return true;
        } else return false;
    }
    
    Boolean vender(Jugador jugador) {
        if (jugador == Propietario && Comprada && !Hipotecado) {
            Propietario.recibe(this.getPrecioVenta());
            Comprada = false;
            Propietario = null;
            nCasas = 0;
            nHoteles = 0;
            return true;
        } else return false;
    }
    
    void actualizarPropietario(Jugador jugador) {
        Propietario = jugador;
        Comprada = true;
    }
    
    Boolean esElPropietario(Jugador jugador) {
        return (jugador == Propietario && Comprada);
    }
    
    Boolean getHipotecado() {
        return Hipotecado;
    }
    
    public String getNombre() {
        return nombre;
    }
    
    int getNCasas() {
        return nCasas;
    }
    
    int getNHoteles() {
        return nHoteles;
    }
    
    float getPrecioCompra() {
        return PrecioCompra;
    }
    
    float getPrecioEdificar() {
        return PrecioEdificar;
    }
    
    Jugador getPropietario() {
        return Comprada ? Propietario : null;
    }
    
    Boolean tienePropietario() {
        return Comprada;
    }
    
    float getImporteHipoteca() {
        return PrecioBaseHipoteca;
    }
    
    Boolean cancelarHipoteca(Jugador jugador) {
        if (esElPropietario(jugador) && Hipotecado) {
            jugador.paga(getImporteCancelarHipoteca());
            Hipotecado = false;
            return true;
        } else
            return false;
    }
    
    Boolean hipotecar(Jugador jugador) {
        if (!Hipotecado && esElPropietario(jugador)) {
            jugador.recibe(PrecioBaseHipoteca);
            Hipotecado = true;
            return true;
        }
        return false;
    }
    
    Boolean comprar(Jugador jugador) {
        if (!tienePropietario()) {
            actualizarPropietario(jugador);
            jugador.paga(PrecioCompra);
            return true;
        }
        return false;
    }
    
    Boolean construirCasa(Jugador jugador) {
        if (esElPropietario(jugador)) {
            jugador.paga(PrecioEdificar);
            nCasas++;
            return true;
        }
        return false;
    }
    
    Boolean construirHotel(Jugador jugador) {
        if (esElPropietario(jugador)) {
            jugador.paga(PrecioEdificar);
            nHoteles++;
            return true;
        }
        return false;
    }
}
