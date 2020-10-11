require 'singleton'
module Civitas

    class Dado
        include Singleton

        SalidaCarcel = 5

        attr_reader :ultimoResultado

        def inititialize
            @ultimoResultado
            @debug = false
        end

        def tirar
            if (@debug)
                @ultimoResultado = 1
                return @ultimoResultado
            else
                @ultimoResultado = 1 + rand(6)
                return @ultimoResultado
            end
        end

        def salgoDeLaCarcel
            return tirar == SalidaCarcel
        end

        def quienEmpieza(n)
            return rand(n)
        end

        def setDebug(d)
            if (d!=@debug)
                @debug = d
                if (d)
                    Diario.instance.ocurre_evento("Se ha cambiado el estado del debug a 'true'")
                else
                    Diario.instance.ocurre_evento("Se ha cambiado el estado del debug a 'false'")
                end
            end
        end
        
    end
end