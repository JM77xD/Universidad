package aplicacionperros;


public class Perro {
    private String raza;
    private int peso;
    boolean agresivo;
    public String nombre;
    
    public Perro(){ //constructor  dar valor a todos los atributos
        this.raza="Chiguagua";
        this.peso=2;
        this.agresivo=false;
        this.nombre="Chi";   
    }
    
    public String getNombre(){ //consultor
        return nombre;
    }
    
    public void ladrar(){  //comportamiento para objetos de la clase
        System.out.println("guau guau");
        
    }
    
    public void setNombre(String nuevoNombre){ //modificador
        nombre=nuevoNombre;
    }
    
    public void ponteAgresivo(){
        agresivo=true;
    }
    
    public boolean getAgresivo(){
        return agresivo;
    }
       
    
    public String getRaza(){
        return raza;
        
    }
    
}
