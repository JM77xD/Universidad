#Probando métodos constructores de primera forma

require_relative "primera_forma_metodos_de_clase_memoria"

#Eliminamos el metodo new de la clase 
#Anula el método constructor new para que no podamos usarlo tal cual

Test.instance_eval { undef :new }  

#Probando los métodos de clase definidos como constructores

    test= Test.newAB(1,2)
    puts test
    puts test.object_id
    

    test= Test.newCD(3,4)
    puts test   
    puts test.object_id

#    test= Test.new(1,2,3,4)

#    test= Test.new   

# Descomentar una a una las líneas de código últimas y explicar el motivo del error
