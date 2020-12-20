# encoding:utf-8

require_relative "Diario"

module Civitas

    class Casilla

        attr_reader :nombre

        def initialize(n)
            @nombre = n
        end

        def informe(actual, todos)
            Diario.instance.ocurre_evento("El jugador " + todos.at(actual).nombre + " ha caído en una casilla de tipo Descanso.")
        end

        def toString
            return "Descanso"
        end

        def jugadorCorrecto(actual, todos)
            return todos.size > actual
        end

        def recibe_jugador(actual, todos)
            informe(actual, todos)             
        end

    end


end