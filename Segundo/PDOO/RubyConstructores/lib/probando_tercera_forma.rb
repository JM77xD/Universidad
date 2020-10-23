#Probando método constructor de tercera forma

require_relative "tercera_forma_initialize_con_argumentos"

    test= Test.new(1,2)
    puts test
    puts test.object_id
    

    test= Test.new(1,2,3)
    puts test   
    puts test.object_id

#    test= Test.new(1,2,3,4)

# Descomentar la última línea de código últimas y explicar el motivo del error