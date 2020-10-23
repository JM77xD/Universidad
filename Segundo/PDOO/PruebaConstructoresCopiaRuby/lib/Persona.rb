

class Persona
  
  attr_accessor :edad
  attr_reader :nombre
  
  def initialize (n) #constructor
    @nombre=n
    @edad=20
  end
  
  def copiaDe(otra)  #alternativa 1. metodo de instancia para copiar en el receptor del mensaje los datos del argumento
    @nombre=otra.nombre
    @edad=otra.edad
  end
  
  def self.copiaDe(otra) #Alternativa 2. metodo de clase que crea un objeto nuevo con los datod del argumento
    nuevo= new(otra.nombre) #crea un objeto nuevo con el nombre del receptor pero el valor de edad del constructor
    nuevo.edad=otra.edad #pone al nuevo la misma edad que tenga el argumento en este momento
    return nuevo
  end
  
  
  
end
