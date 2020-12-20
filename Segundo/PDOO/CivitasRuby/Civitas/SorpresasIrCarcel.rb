# encoding:utf-8

require_relative "Tablero"

module Civitas

    class SorpresasIrCarcel < Sorpresas

        def initialize(tablero)
            @refT = tablero
        end

        def aplicarAJugador(actual, todos)
            if jugadorCorrecto(actual, todos)
                informe(actual,todos)
                todos.at(actual).encarcelar(@refT.numCasillaCarcel)
            end
        end

        def to_String
            return "IrCarcel"
        end

    end

end
