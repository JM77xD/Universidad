
package basico ;

import java.time.LocalDateTime;



public class Persona { // Clase con visibilidad pública
 // Atributos de instancia privados
 private String nombre ; 
 private int edad ;
 private ColorPelo pelo ;
 private double altura;

 public Persona ( String n , int e , ColorPelo p , double a ) { // "Constructor" público
     nombre = n ;
     edad = e ;
     pelo = p ;
     altura = a;
 }

 void saluda() { // Visibilidad de paquete. Método de instancia
 System.out.println( "Hola , soy "+nombre );
 }

 
LocalDateTime pedirCita(Peluqueria peluqueria) {// Visibilidad de paquete. Método de instancia
     return peluqueria.darCita(); //envía mensaje a peluquería para que ésta le dé la cita
 }

String consultarAltura() {  //Consulta la altura de la persona
    if(altura < 1.60) {
        return "baja";  //Si mide menos de 1.6m se considera una persona baja
    } else {
        return "alta";
    }
}

String ConsultaNombre() {
    return nombre;
}

 @Override
 public String toString() {  //Enuncia los datos relevantes de la persona
    return ("Hola soy "+nombre+", mido "+altura+", tengo el pelo "+pelo+" y tengo "+edad+" años.");
}

void cambiarPelo(ColorPelo p) { //Cambia el color del pelo de la persona
    pelo = p;
}

void anularCita(Peluqueria peluqueria) { //Anula la cita de la peluquería
    peluqueria.anular();
}
 



 }