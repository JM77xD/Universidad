# encoding:utf-8

require_relative "Casilla"

module Civitas

    class CasillaImpuesto < Casilla

        attr_reader :cantidad

        def initialize(n, cant)
            super(n)
            @cantidad=cant
        end

        def informe(actual, todos)
            Diario.instance.ocurre_evento("El jugador " + todos.at(actual).nombre + " ha caído en una casilla de tipo Impuesto.")
        end

        def recibe_jugador(actual, todos)
            if jugadorCorrecto(actual, todos)
                informe(actual, todos)
                todos.at(actual).pagaImpuesto(@cantidad)
            end
        end

        def toString
            return "La casilla actual es " + @nombre + " y es de tipo Impuesto.\n"
        end

    end

end