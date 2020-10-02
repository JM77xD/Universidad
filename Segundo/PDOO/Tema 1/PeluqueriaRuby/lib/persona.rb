module Basico
   
 module ColorPelo
 MORENO= :moreno
 CASTANO= :castano
 RUBIO= :rubio
 PELIROJO= :pelirojo
 end

 class Persona
   
 def initialize (n, e, p, a) # " constructor "
    # Atributos de instancia ( son siempre privados )
    @nombre=n
    @edad=e
    @pelo=p
    @altura=a
 end

 public # no es necesario , pues los métodos son públicos por defecto
 
 def saluda # Método público de instancia
     puts "Hola , soy "+@nombre
 end
 
 def pedir_cita(peluqueria)  #Método de instancia
     saluda
     return peluqueria.dar_cita #envía mensaje a peluquería para que ésta le dé la cita 
 
 end

 def ComprobarAltura #Dice si la persona es alta o baja
    if (@altura < 1.7)
        puts "Soy baj@ porque mido "+@altura.to_s
    else 
        puts "Soy alt@ porque mido "+@altura.to_s
    end
 end

 def darNombre 
    @nombre
 end


 def to_s
    puts "Me llamo "+@nombre+",tengo "+@edad.to_s+" años y el pelo de color "+@pelo.to_s+", además mido "+@altura.to_s+" metros."
 end

 def cambiarPelo(colorPelo)
    @pelo = colorPelo
 end

 def anularCita(peluqueria) 
    peluqueria.anularCita
 end




end

end
