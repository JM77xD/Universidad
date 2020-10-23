

require_relative "persona"

class Estudiante < Persona
  
  attr_reader :curso
  
  def initialize (c) #constructor. No llama a super
    @curso=c
  end
  
  def self.nuevoEstudiante1(otro, c)  # Alternativa 1: metodo de clase para copiar en el receptor del mensaje los datos del argumento y añadir nuevos atributos
    nuevo=new(c) #creo un estudiante nuevo solo con valor en el atributo curso
    nuevo.copiaDe(otro) #usa el metodo de instancia heredado copia de Persona para dar valor a los otros atributos.
    return nuevo
  end
  
   
  
  
  
  
end
