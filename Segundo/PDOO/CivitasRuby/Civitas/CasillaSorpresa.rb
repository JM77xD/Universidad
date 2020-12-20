# encoding:utf-8

require_relative "MazoSorpresas"

module Civitas

    class CasillaSorpresa < Casilla

        def initialize(mazoSor, n)
            super(n)
            @mazo = mazoSor
        end

        def informe(actual, todos)
            Diario.instance.ocurre_evento("El jugador " + todos.at(actual).nombre + " ha caído en una casilla de tipo Sorpresa.")
        end

        def recibe_jugador(actual, todos)
            if jugadorCorrecto(actual, todos)
                informe(actual, todos)
                sorpresa = @mazo.siguiente()
                sorpresa.aplicarAJugador(actual, todos)
            end
        end

        def toString
            return "La casilla actual es " + @nombre + " y es de tipo Sorpresa.\n"
        end

    end

end