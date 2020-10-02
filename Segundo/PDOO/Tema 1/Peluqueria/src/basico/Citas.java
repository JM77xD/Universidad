
package basico;

import java.time.LocalDateTime;
import java.time.Month;
import java.util.ArrayList;


public class Citas {
    private ArrayList<LocalDateTime> citas = new ArrayList<>();
    private ArrayList<Persona> persona = new ArrayList<>();
    
    LocalDateTime DarCita(Persona p, Peluqueria pelu) {
        int year= (int)(Math.random()*2+2020);	//hasta 2 años a partir del 2020
        int dia= (int) (Math.random()*30+1);
        int hora= (int) (Math.random()*8+9);      
        LocalDateTime cita= LocalDateTime.of(year, Month.OCTOBER, dia, hora, 0);
        citas.add(cita);
        persona.add(p);
        return cita;
    }
    
    void anularCita(Persona p, Peluqueria pelu) {
        int indice = persona.indexOf(p);
        System.out.println("Cita de "+p.ConsultaNombre()+" a las "+citas.get(indice)+" anulada");
        citas.remove(indice);
        persona.remove(indice);
        if (citas.isEmpty()) {
            System.out.println("No hay mas citas en cola");
        }
    }
}
