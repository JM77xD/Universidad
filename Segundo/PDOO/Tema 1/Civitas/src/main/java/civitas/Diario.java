package civitas;



import java.util.ArrayList;

public class Diario {
  static final private Diario instance = new Diario();
  
  private ArrayList<String> eventos;
  
  static public Diario getInstance() {
    return instance;
  }
  
  private Diario () {
    eventos = new ArrayList<>();
  }
  
  void ocurreEvento (String e) {        //Añade un evento a la lista
    eventos.add (e);
  }
  
  public boolean eventosPendientes () { //Mira si quedan eventos por leer
    return !eventos.isEmpty();
  }
  
  public String leerEvento () {     //Lee el siguiente evento
    String salida = "";
    if (!eventos.isEmpty()) {
      salida = eventos.remove(0);
    }
    return salida;
  }
}
