
package aplicacionperros;


public class AplicacionPerros {

   
    public static void main(String[] args) {
        
        Perro perrilla= new Perro();
        
        Perro p2= perrilla;
        p2.setNombre("Tobi");
        
        Perro otroPerrillo = new Perro();
        
        System.out.println(perrilla.getNombre()); //envío de mensaje
        
        perrilla.ladrar();
        
        perrilla.setNombre("Filomena");
        
        System.out.println(perrilla.getNombre());
        
        perrilla.ponteAgresivo();
        
        System.out.println(perrilla.agresivo);
        
        System.out.println(perrilla.nombre);
        
        System.out.println(perrilla.getRaza());
        
    }
    
}
