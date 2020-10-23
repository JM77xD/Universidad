#Probando métodos constructores de primera forma

require_relative "segunda_forma_metodos_de_clase_new"

    test= Test.newAB(1,2)
    puts test
    puts test.object_id
    

    test= Test.newCD(3,4)
    puts test   
    puts test.object_id

#    test= Test.new(1,2,3,4)

# Descomentar la última línea de código últimas y explicar el motivo del error