# encoding:utf-8

require_relative "Diario"
require_relative "TituloPropiedad"
require_relative "MazoSorpresas"
require_relative "TipoCasilla"

module Civitas

    class Casilla

        attr_reader :nombre
        attr_reader :titulo
        attr_reader :cantidad
        attr_reader :TipoCasilla

        def initialize(tipo, param1 = nil, param2 = nil)
            @TipoCasilla = tipo
            @titulo = nil
            @nombre = nil
            @cantidad = nil
            @mazo = nil
            @nCasillaCarcel = nil

            case tipo
            when TipoCasilla::DESCANSO
                @nombre = param1
            when TipoCasilla::CALLE
                @nombre = param1.nombre
                @titulo = param1
                @cantidad = param1.precioCompra
            when TipoCasilla::IMPUESTO
                @cantidad = param1
                @nombre = param2
            when TipoCasilla::JUEZ
                @nCasillaCarcel = param1
                @nombre = param2
            when TipoCasilla::SORPRESA
                @mazo = param1
                @nombre = param2
            end
        end

        def informe(actual, todos)
            Diario.instance.ocurre_evento("El jugador " + todos.at(actual).nombre + " ha caído en una casilla de tipo " + self.toString())
        end

        def toString
            return @TipoCasilla.to_s
        end

        def jugadorCorrecto(actual, todos)
            return todos.size > actual
        end

        def recibe_jugadorImpuesto(actual, todos)
            if jugadorCorrecto(actual, todos)
                informe(actual, todos)
                todos.at(actual).pagaImpuesto(@cantidad)
            end
        end

        def recibe_jugadorJuez(actual, todos)
            if jugadorCorrecto(actual, todos)
                informe(actual, todos)
                todos.at(actual).encarcelar(@nCasillaCarcel)
            end
        end

        def recibe_jugadorCalle(actual, todos)
            if jugadorCorrecto(actual, todos)
                informe(actual, todos)
                jugador = todos.at(actual)
                if !@titulo.tienePropietario()
                    jugador.puedeComprarCasilla()
                else
                    @titulo.tramitarAlquiler(jugador)
                end
            end
        end

        def recibe_jugadorSorpresa(actual, todos)
            if jugadorCorrecto(actual, todos)
                informe(actual, todos)
                sorpresa = @mazo.siguiente()
                sorpresa.aplicarAJugador(actual, todos)
            end
        end

        def recibeJugador(actual, todos)
            case @TipoCasilla
            when TipoCasilla::CALLE
                recibe_jugadorCalle(actual, todos)
            when TipoCasilla::SORPRESA
                recibe_jugadorSorpresa(actual, todos)
            when TipoCasilla::JUEZ
                recibe_jugadorJuez(actual, todos)
            when TipoCasilla::IMPUESTO
                recibe_jugadorImpuesto(actual, todos)
            else
                informe(actual, todos)
            end               
        end

    end


end