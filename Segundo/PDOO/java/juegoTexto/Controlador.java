/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package juegoTexto;

import civitas.*;


public class Controlador {
    private CivitasJuego juego;
    private VistaTextual vista;
    
    Controlador(CivitasJuego refJuego, VistaTextual refVista) {
        juego = refJuego;
        vista = refVista;
    }
    
    void juega() {
        vista.setCivitasJuego(juego);
        Boolean fin = juego.finalDelJuego();
        OperacionesJuego operacion;
        while (!fin) {
            vista.actualizarVista();
            vista.pausa();
            operacion = juego.siguientePaso();
            vista.mostrarSiguienteOperacion(operacion);
            if (operacion != OperacionesJuego.PASAR_TURNO) {
                vista.mostrarEventos();
            }
            fin = juego.finalDelJuego();
            if (!fin) switch (operacion) {
                case COMPRAR:
                    Respuestas respuesta = vista.comprar();
                    if (respuesta == Respuestas.SI) {
                        if (juego.comprar())
                            juego.siguientePasoCompletado(operacion);                            
                    } else
                        juego.siguientePasoCompletado(operacion);
                    break;
                case GESTIONAR:
                    vista.gestionar();
                    int iGestion = vista.getGestion();
                    int iPropiedad = vista.getPropiedad();
                    GestionesInmobiliarias gestion = GestionesInmobiliarias.values()[iGestion];
                    OperacionInmobiliaria nuevaOperacion = new OperacionInmobiliaria(gestion, iPropiedad);
                    if (null != gestion) switch (gestion) {
                        case VENDER:
                            juego.vender(iPropiedad);
                            break;
                        case HIPOTECAR:
                            juego.hipotecar(iPropiedad);
                            break;
                        case CANCELAR_HIPOTECA:
                            juego.cancelarHipoteca(iPropiedad);
                            break;
                        case CONSTRUIR_CASA:
                            juego.construirCasa(iPropiedad);
                            break;
                        case CONSTRUIR_HOTEL:
                            juego.construirHotel(iPropiedad);
                            break;
                        case TERMINAR:
                            juego.siguientePasoCompletado(operacion);
                            break;
                        default:
                            break;
                    }
                    break;
                case SALIR_CARCEL:
                    SalidasCarcel salida = vista.salirCarcel();
                    if (salida == SalidasCarcel.PAGANDO) {
                        juego.salirCarcelPagando();
                    } else {
                        juego.salirCarcelTirando();
                    }
                    juego.siguientePasoCompletado(operacion);
                    break;
                default:
                    break;                    
            }
        }
        vista.ranking();
    }
    
    void setDebug(Boolean d) {
        Dado.getInstance().setDebug(d);
    }
    
}
