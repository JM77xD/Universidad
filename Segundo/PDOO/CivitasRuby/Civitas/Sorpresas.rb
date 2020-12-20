require_relative "Jugador"
require_relative "Diario"

module Civitas

    class Sorpresas

        def jugadorCorrecto(actual, todos)
            return todos.size > actual
        end

        def informe(actual, todos)
            Diario.instance.ocurre_evento("La casilla sorpresa es de tipo " + to_String() + ".")
            Diario.instance.ocurre_evento("Se le aplica una sorpresa al jugador " + todos.at(actual).nombre + ".")
        end

    end
end