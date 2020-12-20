# encoding:utf-8

require_relative "Casilla"
require_relative "TituloPropiedad"

module Civitas

    class CasillaCalle < Casilla
        
        attr_reader :titulo
        attr_reader :cantidad
        
        def initialize(tit)
            super(tit.nombre)
            @titulo = tit
            @cantidad = tit.precioCompra
        end

        def informe(actual, todos)
            if !@titulo.tienePropietario()
                Diario.instance.ocurre_evento("El jugador " + todos.at(actual).nombre + " ha caído en una casilla de tipo Calle, con un precio de " + @cantidad.to_s + ".")
            else
                Diario.instance.ocurre_evento("El jugador " + todos.at(actual).nombre + " ha caído en una casilla de tipo Calle.")
            end
        end

        def recibe_jugador(actual, todos)
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

        def toString
            return "Calle"
        end

    end

end