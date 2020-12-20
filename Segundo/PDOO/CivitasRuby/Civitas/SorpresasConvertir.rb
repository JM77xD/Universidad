# encoding:utf-8

require_relative "JugadorEspeculador"

module Civitas

    class SorpresasConvertir < Sorpresas

        public_class_method :new

        def initialize(f, juego)
            @fianza = f
            @refJuego = juego
        end

        def aplicarAJugador(actual, todos)
            if jugadorCorrecto(actual, todos)
                informe(actual,todos)
                jugadorActual = todos.at(actual)
                jugadorNuevo = JugadorEspeculador.nuevoEspeculador(jugadorActual, @fianza)
                todos.delete_at(actual)
                todos.insert(actual, jugadorNuevo)
            end
        end

        def to_String
            return "ConvertirEnEspeculador"
        end

    end

end