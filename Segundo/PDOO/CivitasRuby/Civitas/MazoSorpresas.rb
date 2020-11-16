require_relative "Sorpresas"
module Civitas
    
    class MazoSorpresas

        def initialize(d=false)
            @sorpresas = []
            @barajada = false
            @debug = d
            @usadas = 0
            @cartasEspeciales = []
            @ultimaSorpresa
            if (d)
                Diario.instance.ocurre_evento("Modo debug del Mazo de Sorpresas activado")
            end
        end

        def alMazo(s)
            if (!@barajada)
                @sorpresas << s
            end
        end

        def siguiente
            if (!@barajada || @usadas = @sorpresas.size)
                if (!@debug)
                    @sorpresas.shuffle!
                end
                @usadas = 0
                @barajada = true
            end
            @ultimaSorpresa = @sorpresas.shift
            @usadas = @usadas + 1
            @sorpresas << @ultimaSorpresa
            return @ultimaSorpresa
        end

        def inhabilitarCartaEspecial(s)
            if (@sorpresas.include?(s))
                indice = @sorpresas.find_index(s)
                @cartasEspeciales << @sorpresas.at(indice)
                @sorpresas.delete(indice)
                Diario.instance.ocurre_evento("Se ha retirado una carta del mazo de juego y se ha añadido al mazo de descartes")
            end
        end

        def habilitarCartaEspecial(s)
            if (@cartasEspeciales.include?(s))
                indice = @cartasEspeciales.find_index(s)
                @sorpresas << @cartasEspeciales.at(indice)
                @cartasEspeciales.delete(indice)
                Diario.instance.ocurre_evento("Se ha retirado una carta del mazo de descartes y se ha añadido al mazo de juego")
            end
        end

        
    end
end