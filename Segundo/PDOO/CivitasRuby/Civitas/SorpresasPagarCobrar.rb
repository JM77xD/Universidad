# encoding:utf-8


module Civitas

    class SorpresasPagarCobrar < Sorpresas

        def initialize(v, text)
            @valor = v
            @texto = text
        end
        
        def aplicarAJugador(actual, todos)
            if jugadorCorrecto(actual, todos)
                informe(actual,todos)
                todos.at(actual).modificarSaldo(@valor)
            end
        end

        def to_String
            return "PagarCobrar"
        end

    end

end