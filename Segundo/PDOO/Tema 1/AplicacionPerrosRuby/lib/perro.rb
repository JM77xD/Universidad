
class Perro
  
  attr_accessor :nombre, :agresivo   #consultor y modificador
  
  attr_reader :peso  #consultor solo
  
  attr_writer :raza  #modificador solo
  
  def initialize(raza, peso, agresivo, nombre)  #todos los atributos son privados y no se pueden cambiar
    @raza=raza
    @peso=peso
    @agresivo=agresivo
    @nombre=nombre  
  end
  

  def ladrar
    "guau guau"
  end
  
  
  def get_peso  #consultor de peso
    @peso   #importante no olvidar @ para atributos. No da error, piensa que son variables locales
  end
  
  
  private :get_peso, :nombre=
  
end
