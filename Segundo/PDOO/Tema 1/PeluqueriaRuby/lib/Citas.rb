require_relative "persona"
require_relative "peluqueria"

module Basico

    class Citas

        def initialize()
          @citas = Array.new
          @clientes = Array.new
        end

        def DarCita(persona)
            year= 2020+rand(3) #hasta 2 años a partir de 2020
            dia= 1+ rand(31) 
            hora= 9+rand(9)
            cita= Time.new(year, 11, dia, hora)
            @citas<<cita
            @clientes<<persona
            cita
        end

        def anularCita(persona)
            if (@clientes.include?(persona))
                indice = @clientes.find_index(persona)
                puts "Cita de "+persona.darNombre+" a las "+@citas[indice].to_s+" anulada"
                @citas.delete(indice)
                @clientes.delete(indice)
                if (@citas.empty?)
                    puts "No quedan más citas"
                end
            end
        end
    end
end
