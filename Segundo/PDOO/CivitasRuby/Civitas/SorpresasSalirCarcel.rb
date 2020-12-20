# encoding:utf-8

require_relative "MazoSorpresas"

module Civitas

    class SorpresasSalirCarcel < Sorpresas

        def initialize(mazo)
            @refMS = mazo
        end
        
        def aplicarAJugador(actual, todos)
            if jugadorCorrecto(actual, todos)
                informe(actual,todos)
                tomada = false

                todos.each do |jugador|
                    if !tomada
                        tomada = jugador.tieneSalvoconducto()
                    end
                end
            
                if !tomada
                    todos.at(actual).obtenerSalvoconducto(self)
                    self.salirDelMazo()
                end
            end
        end

        def salirDelMazo
            @refMS.inhabilitarCartaEspecial(self)
        end

        def usada
            @refMS.habilitarCartaEspecial(self)
        end

        def to_String
            return "SalirCarcel"
        end

    end

end