package juegoTexto;

import civitas.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class VistaTextual {
  
  CivitasJuego juegoModel; 
  int iGestion=-1;
  int iPropiedad=-1;
  private static String separador = "=====================";
  
  private Scanner in;
  
  public VistaTextual () {
    in = new Scanner (System.in);
  }
  
  public void mostrarEstado(String estado) {
    System.out.println (estado);
  }
              
  public void pausa() {
    System.out.println ("Pulsa una tecla");
    in.nextLine();
  }

  int leeEntero (int max, String msg1, String msg2) {
    Boolean ok;
    String cadena;
    int numero = -1;
    do {
        System.out.println (msg1);
      cadena = in.nextLine();
      try {  
        numero = Integer.parseInt(cadena);
        ok = true;
      } catch (NumberFormatException e) { // No se ha introducido un entero
        System.out.println (msg2);
        ok = false;  
      }
      if (ok && (numero < 0 || numero >= max)) {
        System.out.println (msg2);
        ok = false;
      }
    } while (!ok);

    return numero;
  }

  int menu (String titulo, ArrayList<String> lista) {
    System.out.println(separador);
    String tab = "  ";
    int opcion;
    System.out.println (titulo);
    for (int i = 0; i < lista.size(); i++) {
      System.out.println (tab+i+"-"+lista.get(i));
    }

    opcion = leeEntero(lista.size(),
                          "\n"+tab+"Elige una opción: ",
                          tab+"Valor erróneo");
    return opcion;
  }

  public SalidasCarcel salirCarcel() {
    int opcion = menu ("Elige la forma para intentar salir de la carcel",
      new ArrayList<> (Arrays.asList("Pagando","Tirando el dado")));
    return (SalidasCarcel.values()[opcion]);
  }

  public Respuestas comprar() {
    int opcion = menu ("Desea comprar la propiedad",
      new ArrayList<> (Arrays.asList("No","Si")));
    return (Respuestas.values()[opcion]);
  }

  public void gestionar () {
      int nGestion = menu ("Seleccione la operación a realizar",
      new ArrayList<> (Arrays.asList("Vender","Hipotecar","Cancelar hipoteca","Construir casa","Construir hotel","Terminar")));
    iGestion = nGestion;
    if (iGestion != 5) {
        ArrayList<TituloPropiedad> propiedades = juegoModel.getJugador().getPropiedades();
        ArrayList<String> nombres = new ArrayList<>(Arrays.asList());
        for (int i = 0; i < propiedades.size(); i++) {
        nombres.add(propiedades.get(i).getNombre());
        }
        int nPropiedad = menu ("Seleccione la propiedad sobre la que desea realizar la gestión", nombres);
        iPropiedad = nPropiedad;
    }
  }
  
  public int getGestion(){
    return iGestion;
  }
  
  public int getPropiedad(){
    return iPropiedad;
  }
    

  public void mostrarSiguienteOperacion(OperacionesJuego operacion) {
      System.out.println(separador);
      System.out.println("La siguiente operacion a realizar es " + operacion.toString());
  }


  public void mostrarEventos() {
      if (Diario.getInstance().eventosPendientes())
        System.out.println(separador);
      while (Diario.getInstance().eventosPendientes()) {
          System.out.println(Diario.getInstance().leerEvento());
      }
  }
  
  public void setCivitasJuego(CivitasJuego civitas){ 
        juegoModel=civitas;
        this.actualizarVista();

    }
  
  public void actualizarVista(){
      System.out.println(separador);
      System.out.println(juegoModel.getJugador().toString());
      System.out.println(juegoModel.getCasillaActual().toString());
  }
  
  public void ranking() {
      System.out.println(separador);
      ArrayList<Jugador> ranking = juegoModel.ranking();
        for (int i = 1; i <= ranking.size(); i++) {
            System.out.println(ranking.get(i-1).toString() + " Además ha quedado en posición " + i + ".");
        }
  }
}
