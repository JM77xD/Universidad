# encoding:utf-8

require_relative "Jugador"

module Civitas

    class TituloPropiedad

        attr_reader :nombre
        attr_reader :hipotecado
        attr_reader :nCasas
        attr_reader :nHoteles
        attr_reader :PrecioCompra
        attr_reader :PrecioEdificar
        attr_reader :Propietario
        attr_reader :PrecioBaseHipoteca

        def initialize(nombre, PrecioBaseAlquiler, FactorRevalorizacion, PrecioBaseHipoteca, PrecioCompra, PrecioEdificar )
            @nombre = nombre
            @PrecioBaseAlquiler = PrecioBaseAlquiler
            @FactorRevalorizacion = FactorRevalorizacion
            @PrecioBaseHipoteca = PrecioBaseHipoteca
            @PrecioCompra = PrecioCompra
            @PrecioEdificar = PrecioEdificar
            @Propietario = nil
            @nCasas = 0
            @nHoteles = 0
            @hipotecado = false
            @FactorInteresHipoteca = 1.1
        end

        def to_String
            Devolver = "La calle "+ @nombre + " tiene un precio base de alquiler de " + @PrecioBaseAlquiler.to_s + ",\nun factor de revalorización de " + @FactorRevalorizacion.to_s
            Devolver += ", un precio base de hipotecado de " + @PrecioBaseHipoteca.to_s + ",\nun precio de compra de " + @PrecioCompra.to_s
            Devolver += " y un precio por edificar de " + @PrecioEdificar.to_s + ".\n\nActualmente tiene " + @nCasas.to_s + " casas y " + @nHoteles.to_s + " hoteles y se encuentra "
            if (@hipotecado)
                Devolver += "hipotecada."
            else
                Devolver += "no hipotecada."
            end

            return Devolver
        end

        def getPrecioAlquiler
            if (@Propietario.encarcelado || @hipotecado)
                return 0
            else
                return @PrecioBaseAlquiler
            end
        end

        def getImporteCancelarHipoteca
            return @PrecioBaseHipoteca*@FactorInteresHipoteca
        end

        def tramitarAlquiler(jugador)
            if (@Propietario != jugador)
                precioAlq = self.getPrecioAlquiler()
                jugador.pagaAlquiler(precioAlq)
                @Propietario.recibe(precioAlq)
            end
        end

        def propietarioEncarcelado
            return @Propietario.encarcelado
        end

        def cantidadCasasHoteles
            return (@nCasas + @nHoteles)
        end

        def getPrecioVenta
            return (@PrecioCompra + @PrecioEdificar*self.cantidadCasasHoteles()*@FactorRevalorizacion)
        end

        def derruirCasas(n, jugador)
            if (jugador == @Propietario && @nCasas >= n)
                nCasas -= n
                return true
            else
                return false
            end
        end

        def vender(jugador)
            if (jugador == @Propietario && !@hipotecado)
                @Propietario.recibe(self.getPrecioVenta())
                @Propietario = nil
                @nCasas = 0
                @nHoteles = 0
                return true
            else
                return false
            end
        end

        def tienePropietario
            if(@Propietario != nil)
                return true
            else
                return false
            end
        end

        def actualizarPropietario(jugador)
            @Propietario = jugador
        end

        def esElPropietario(jugador)
            return (@Propietario == jugador)
        end
        
    end

end