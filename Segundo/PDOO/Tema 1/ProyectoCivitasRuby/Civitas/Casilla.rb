# encoding:utf-8

require_relative "Diario"
require_relative "TituloPropiedad"
require_relative "MazoSorpresas"
require_relative "TipoCasilla"

module Civitas

    class Casilla

        attr_reader :nombre
        attr_reader :titulo

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
                @titulo = param1
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
            Diario.instance.ocurre_evento("El jugador " + todos.at(actual).nombre + " ha caído en una casilla de " + self.toString())
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

    end


end