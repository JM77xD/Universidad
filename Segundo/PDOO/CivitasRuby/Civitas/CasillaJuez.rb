# encoding:utf-8


module Civitas

    class CasillaJuez < Casilla

        def initialize(numCarcel, n)
            super(n)
            @nCarcel = numCarcel
        end

        def informe(actual, todos)
            Diario.instance.ocurre_evento("El jugador " + todos.at(actual).nombre + " ha caído en una casilla de tipo Juez.")
        end

        def recibe_jugador(actual, todos)
            if jugadorCorrecto(actual, todos)
                informe(actual, todos)
                todos.at(actual).encarcelar(@nCarcel)
            end
        end

        def toString
            return "La casilla actual es " + @nombre + " y es de tipo Juez.\n"
        end

    end

end