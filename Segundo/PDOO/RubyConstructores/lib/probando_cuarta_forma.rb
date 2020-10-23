#Probando método constructor de cuarta forma

require_relative "cuarta_forma_initialize_con_argumentos"

    test= Test.new(1,2)
    puts test
    puts test.object_id
    

    test= Test.new(1,2,3)
    puts test   
    puts test.object_id

    test= Test.new(1,2,3,8)
    puts test   
    puts test.object_id

