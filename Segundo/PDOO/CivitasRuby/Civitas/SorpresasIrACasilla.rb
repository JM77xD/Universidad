# encoding:utf-8

require_relative "Tablero"

module Civitas

    class SorpresasIrACasilla < Sorpresas

        public_class_method :new

        def initialize(tablero, v)
            @refT = tablero
            @valor = v
        end

        def aplicarAJugador(actual, todos)
            if jugadorCorrecto(actual, todos)
                informe(actual,todos)
                casillaAct = todos.at(actual).nCasillaActual
                tirada = @refT.calcularTirada(casillaAct, @valor)
                nuevaPos = @refT.nuevaPosicion(casillaAct, tirada)
                todos.at(actual).moverACasilla(nuevaPos)
                casilla = @refT.getCasilla(nuevaPos)
                casilla.recibe_jugador(actual, todos)
            end
        end

        def to_String
            return "IrACasilla"
        end

    end

end