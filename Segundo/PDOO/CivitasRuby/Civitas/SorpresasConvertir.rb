# encoding:utf-8

require_relative "JugadorEspeculador"

module Civitas

    class SorpresasConvertir < Sorpresas

        def initialize(f, juego)
            @fianza = f
            @refJuego = juego
        end

        def aplicarAJugador(actual, todos)
            if jugadorCorrecto(actual, todos)
                informe(actual,todos)
                jugadorActual = todos.at(actual)
                jugadores = @refJuego.jugadores
                if jugadores.include?(jugadorActual)
                    indice = jugadores.find_index(jugadorActual)
                    jugadorNuevo = JugadorEspeculador.nuevoEspeculador(jugadorActual, @fianza)
                    jugadores.delete(jugadorActual)
                    jugadores[indice] = jugadorNuevo
                end
            end
        end

        def to_String
            return "ConvertirEnEspeculador"
        end

    end

end