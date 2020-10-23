#encoding: utf-8 

# SEGUNDA FORMA más fácil
# Ejemplo en Ruby que ilustra la creación de varios constructores en una clase 
# utilizando métodos de clase que invocan a initialize (con new)


class Test

  attr_reader :a,:b,:c,:d

  def initialize(a,b,c,d)
    @a=a
    @b=b
    @c=c
    @d=d
  end  
  
  def to_s
    "Objeto de test #{@a},#{@b},#{@c},#{@d}"
  end  
  
  #Métodos de clase que son los nuevos constructores

  def self.newAB(a,b)  
       new(a,b,nil,nil) # entrar con nil no es una buena opción, habría que entrar con valores por defecto.  
  end
  
  def self.newCD(c,d)
       new(nil,nil,c,d)
  end 
  
  #Pone como privado el método constructor new para que no podamos usarlo desde fuera de la clase  
  private_class_method :new
  
end

