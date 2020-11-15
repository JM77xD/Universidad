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
                return (@PrecioBaseAlquiler*(1+(@nCasas*0.5) + (@nHoteles*2.5)))
            end
        end

        def getImporteCancelarHipoteca
            return @precioBaseHipoteca*@FactorInteresHipoteca
        end

        def tramitarAlquiler(jugador)
            if (@propietario != jugador)
                precioAlq = getPrecioAlquiler()
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

        def getImporteHipoteca
            return (@PrecioBaseHipoteca*(1+(@nCasas*0.5) + (@nHoteles*2.5)))
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

        def cancelarHipoteca(jugador)
            result = false
            if @hipotecado
                if esElPropietario(jugador)
                    if jugador.paga(getImporteCancelarHipoteca())
                        @hipotecado = false
                        result = true
                    end
                end
            end
            return result
        end

        def hipotecar(jugador)
            result = false
            if (!@hipotecado && esElPropietario(jugador))
                jugador.recibe(getImporteHipoteca())
                @hipotecado = true
                result = true
            end
            return result
        end

        def comprar(jugador)
            result = false
            if !tienePropietario()
                @propietario = jugador
                result = true
                jugador.paga(@precioCompra)
            end
            return result
        end

        def construirHotel(jugador)
            result = false
            if esElPropietario(jugador)
                jugador.paga(@precioEdificar)
                @nHoteles++
                result = true
            end
            return result
        end

        def construirCasa(jugador)
            result = false
            if esElPropietario(jugador)
                jugador.paga(@precioEdificar)
                @nCasas++
                result = true
            end
            return result
        end
        
    end

end