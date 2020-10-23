  # prueba con run file
  # pruebas de método de instancia y de clase para copia y construcción por copia
 
 require_relative "Persona"
 require_relative "Estudiante"

  #------------ pruebas con una clase
  
  p1= Persona.new("Ana")
  p1.edad=22
  puts "p1"
  puts p1.inspect
  p2= Persona.new("Lola")
  puts "p2"
  puts p2.inspect
  
  p2.copiaDe(p1) # uso de método de instancia para copiar
  puts "El objeto p2 se modifica despues de la copia desde p1"
  puts p2.inspect
  
  p3=Persona.copiaDe(p2) #uso de método de clase para copiar
  puts "Nuevo objeto Persona p3 construido por copia de otro objeto de Persona p2"
  puts p3.inspect
  
  
  #--------------------pruebas de copia con herencia
  
  # prueba con run file. Comentar la prueba en Persona y descomentar esta
  
  p1= Persona.new("Ana")
  puts "p1"
  puts p1.inspect
 
  e1=Estudiante.nuevoEstudiante1(p1,3)  #uso de metodo de clase para copiar
  puts "Se crea un objeto nuevo de la clase Estudiante y sus atributos son copia de una instancia p1 de Persona"
  puts e1.inspect
  
  
  e2=Estudiante.new(4)  
  e2.copiaDe(p1) #uso de metodo de instancia heredado para copiar. poner metodo new publico para poder probar.
  puts "Se modifica el objeto e2  de la clase Estudiante y sus atributos pasan a ser copia de una instancia p1 de Persona"
  puts e2.inspect
 