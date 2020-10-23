#encoding: utf-8 

# CUARTA FORMA 
# Ejemplo en Ruby con valores por defecto en parámetros del constructor


class Test

  attr_reader :a,:b,:c,:d
  
  # Ejemplo en el que el constructor da valor por defecto a algunos parámetros
  
  def initialize(a, b, c=nil, d=4)
		@a=a
    @b=b
    @c=c
    @d=d
	end
  
  
  def to_s
    "Objeto de test #{@a},#{@b},#{@c},#{@d}"
  end  
  
  
  
end

