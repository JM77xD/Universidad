# encoding:utf-8


module Civitas

    class SorpresasPorCasaHotel < Sorpresas

        public_class_method :new

        def initialize(v, text)
            @valor = v
            @texto = text
        end

        def aplicarAJugador(actual, todos)
            if jugadorCorrecto(actual, todos)
                informe(actual,todos)
                edificios = todos.at(actual).cantidadCasasHoteles()
                todos.at(actual).modificarSaldo(edificios*@valor)
            end
        end

        def to_String
            return "PorCasaHotel"
        end

    end

end