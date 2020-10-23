#encoding: utf-8 

# TERCERA FORMA 
# Ejemplo en Ruby que ilustra la creación de un constructor que recibe una colección de argumentos
# En su interior se puede decidir qué hacer en función de su número, sus valores o su tipo, por ejemplo.


class Test

  attr_reader :a,:b,:c,:d
  
  # Ejemplo en el que el constructor acepta solo dos o tres argumentos
  def initialize(*args)
		case args.size
			when 2
				@a, @b=args
			when 3
				@a, @b, @c =args
        @d=4
			else
				raise ArgumentError, "faltan o sobran argumentos"    # Se lanza una excepción
			end
	end
  
  
  def to_s
    "Objeto de test #{@a},#{@b},#{@c},#{@d}"
  end  
  
  
  
end

