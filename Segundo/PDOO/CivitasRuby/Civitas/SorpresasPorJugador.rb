# encoding:utf-8

require_relative "SorpresasPagarCobrar"

module Civitas

    class SorpresasPorJugador < Sorpresas

        def initialize(v, text)
            @valor = v
            @texto = text
        end

        def aplicarAJugador(actual, todos)
            if jugadorCorrecto(actual, todos)
                informe(actual,todos)
                suma = SorpresasPagarCobrar.new(@valor*(todos.size - 1), "suma")
                resta = SorpresasPagarCobrar.new(-1*@valor, "resta")

                for i in 0..todos.size-1
                    if (actual != i)
                        resta.aplicarAJugador(i, todos)
                    else
                        suma.aplicarAJugador(actual, todos)
                    end
                end

            end
        end

        def to_String
            return "PorJugador"
        end

    end

end