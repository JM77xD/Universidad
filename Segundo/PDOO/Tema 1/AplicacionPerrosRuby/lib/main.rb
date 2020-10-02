require_relative "perro"


perrilla=Perro.new("Chiguagua", 5, false, "Mini")

puts perrilla.nombre   #consultor de atributo nombre

perrilla.nombre="Filomena"  #modificador del atributo nombre

perrilla.raza="doberman"

puts perrilla.inspect    #mostrar estado del objeto, identidad
