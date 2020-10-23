#encoding: utf-8 
#
# PRIMERA FORMA
# Ejemplo en Ruby que ilustra la creación de varios constructores en una clase 
# utilizando métodos de clase.
# Los métodos de clase asignan mejoria e invocan a initialize


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
    	# asigna memoria para el objeto
      nuevoObj=allocate      
      # inicializa el objeto, invocando al método initialize
      nuevoObj.send(:initialize,a,b,nil,nil)     
      #devuelve el objeto creado e inicializado
      nuevoObj 
  end
  
  def self.newCD(c,d)
      newObj=allocate
      newObj.send(:initialize, nil,nil,c,d)
      newObj
  end    

  
end

