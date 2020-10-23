# encoding:utf-8

require_relative "Jugador"

module Civitas

    class TituloPropiedad

        attr_reader :nombre
        attr_reader :hipotecado
        attr_reader :nCasas
        attr_reader :nHoteles
        attr_reader :precioCompra
        attr_reader :precioEdificar
        attr_reader :propietario
        attr_reader :precioBaseHipoteca

        def initialize(nombre, precioBaseAlquiler, factorRevalorizacion, precioBaseHipoteca, precioCompra, precioEdificar )
            @nombre = nombre
            @precioBaseAlquiler = precioBaseAlquiler
            @factorRevalorizacion = factorRevalorizacion
            @precioBaseHipoteca = precioBaseHipoteca
            @precioCompra = precioCompra
            @precioEdificar = precioEdificar
            @propietario = nil
            @nCasas = 0
            @nHoteles = 0
            @hipotecado = false
            @FactorInteresHipoteca = 1.1
        end

        def to_String
            devolver = "La calle "+ @nombre + " tiene un precio base de alquiler de " + @precioBaseAlquiler.to_s + ",\nun factor de revalorización de " + @factorRevalorizacion.to_s
            devolver += ", un precio base de hipotecado de " + @precioBaseHipoteca.to_s + ",\nun precio de compra de " + @precioCompra.to_s
            devolver += " y un precio por edificar de " + @precioEdificar.to_s + ".\n\nActualmente tiene " + @nCasas.to_s + " casas y " + @nHoteles.to_s + " hoteles y se encuentra "
            if (@hipotecado)
                devolver += "hipotecada."
            else
                devolver += "no hipotecada."
            end

            return devolver
        end

        def getPrecioAlquiler
            if (@propietario.encarcelado || @hipotecado)
                return 0
            else
                return @precioBaseAlquiler
            end
        end

        def getImporteCancelarHipoteca
            return @precioBaseHipoteca*@FactorInteresHipoteca
        end

        def tramitarAlquiler(jugador)
            if (@propietario != jugador)
                precioAlq = self.getPrecioAlquiler()
                jugador.pagaAlquiler(precioAlq)
                @propietario.recibe(precioAlq)
            end
        end

        def propietarioEncarcelado
            return @propietario.encarcelado
        end

        def cantidadCasasHoteles
            return (@nCasas + @nHoteles)
        end

        def getPrecioVenta
            return (@precioCompra + @precioEdificar*self.cantidadCasasHoteles()*@factorRevalorizacion)
        end

        def derruirCasas(n, jugador)
            if (jugador == @propietario && @nCasas >= n)
                nCasas -= n
                return true
            else
                return false
            end
        end

        def vender(jugador)
            if (jugador == @propietario && !@hipotecado)
                @propietario.recibe(self.getPrecioVenta())
                @propietario = nil
                @nCasas = 0
                @nHoteles = 0
                return true
            else
                return false
            end
        end

        def tienePropietario
            if(@propietario != nil)
                return true
            else
                return false
            end
        end

        def actualizarPropietario(jugador)
            @propietario = jugador
        end

        def esElPropietario(jugador)
            return (@propietario == jugador)
        end
        
    end

end