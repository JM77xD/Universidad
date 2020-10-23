require_relative "TituloPropiedad"
require_relative "MazoSorpresas"
require_relative "Sorpresas"

module Civitas

    class Jugador

        include Comparable
       
        attr_reader :CasasMax
        attr_reader :CasasPorHotel
        attr_reader :HotelesMax
        attr_reader :nombre
        attr_accessor :nCasillaActual
        attr_reader :PrecioLibertad
        attr_reader :PasoPorSalida
        attr_accessor :Propiedades
        attr_accessor :puedeComprar
        attr_accessor :saldo
        attr_accessor :encarcelado
        attr_accessor :salvoconducto


        def initialize(nombre)
            @nombre = nombre
            @CasasMax = 4
            @CasasPorHotel = 4
            @encarcelado = false
            @HotelesMax = 4
            @nCasillaActual
            @PasoPorSalida = 1000
            @PrecioLibertad = 200
            @puedeComprar
            @saldo
            @SaldoInicial = 7500
            @salvoconducto
            @Propiedades = []
        end

        def self.copiaDe(otro)
            nuevo = self.new(otro.nombre)
            nuevo.nCasillaActual = otro.nCasillaActual
            nuevo.encarcelado = otro.encarcelado
            nuevo.puedeComprar = otro.puedeComprar
            nuevo.saldo = otro.saldo
            nuevo.Propiedades = otro.Propiedades
            nuevo.salvoconducto = otro.salvoconducto
            return nuevo
        end

        def cantidadCasasHoteles
            suma = 0
            @Propiedades.each do |propiedad|
                suma += propiedad.cantidadCasasHoteles()
            end
            return suma
        end

        def enBancarrota
            return @saldo <= 0
        end

        def debeSerEncarcelado
            if @encarcelado
                return false
            elsif !tieneSalvoconducto()
                return true
            else
                perderSalvoconducto()
                Diario.instance.ocurre_evento("El jugador " + @nombre + " se libra de la cárcel a cambio del salvoconducto")
                return false
            end
        end

        def encarcelar(numCasillaCarcel)
            if debeSerEncarcelado()
                moverACasilla(numCasillaCarcel)
                @encarcelado = true
                Diario.instance.ocurre_evento("El jugador " + @nombre + " ha sido encarcelado")
            end
            return @encarcelado
        end

        def obtenerSalvoconducto(sorpresa)
            if @encarcelado
                return false
            else
                @salvoconducto = sorpresa
                return true
            end
        end

        def perderSalvoconducto
            @salvoconducto.usada()
            @salvoconducto = nil
        end

        def tieneSalvoconducto
            return @salvoconducto != nil
        end

        def puedeComprarCasilla
            @puedeComprar = !@encarcelado
            return @puedeComprar
        end

        def paga(cantidad)
            return modificarSaldo(-1*cantidad)
        end

        def pagaImpuesto(cantidad)
            if @encarcelado
                return false
            else
                return paga(cantidad)
            end
        end

        def pagaAlquiles(cantidad)
            if @encarcelado
                return false
            else
                return paga(cantidad)
            end
        end

        def recibe(cantidad)
            if @encarcelado
                return false
            else
                return modificarSaldo(cantidad)
            end
        end

        def modificarSaldo(cantidad)
            @saldo += cantidad
            Diario.instance.ocurre_evento("El jugador " + @nombre + " modifica su saldo en " + cantidad.to_s + ".")
            return true
        end

        def moverACasilla(nCasilla)
            if @encarcelado
                return false
            else
                @nCasillaActual = nCasilla
                @puedeComprar = false
                Diario.instance.ocurre_evento("El jugador " + @nombre + " ha sido movido a la casilla " + nCasilla.to_s + ".")
                return true
            end
        end

        def puedoGastar(precio)
            return @encarcelado ? false : @saldo >= precio
        end

        def existeLaPropiedad(ip)
            return @Propiedades.size > ip
        end

        def vender(ip)
            if @encarcelado
                return false
            elsif existeLaPropiedad(ip)
                if @Propiedades.at(ip).vender(self)
                    @Propiedades.delete_at(ip)
                    Diario.instance.ocurre_evento("El jugador " + @nombre + " ha realizado la venta de una propiedad.")
                    return true
                else
                    return false
                end
            else
                return false
            end
        end

        def tieneAlgoQueGestionar
            return @Propiedades.any?
        end

        def puedeSalirCarcelPagando
            return @saldo >= @PrecioLibertad
        end

        def salirCarcelPagando
            if @encarcelado && puedeSalirCarcelPagando()
                paga(@PrecioLibertad)
                Diario.instance.ocurre_evento("El jugador " + @nombre + " sale de la cárcel pagando.")
                return true
            else
                return false
            end
        end

        def salirCarcelTirando
            if Dado.instance.salgoDeLaCarcel() && @encarcelado
                @encarcelado = false
                Diario.instance.ocurre_evento("El jugador " + @nombre + " sale de la cárcel tirando el dado.")
                return true
            else
                return false
            end
        end

        def pasaPorSalida
            modificarSaldo(@PasoPorSalida)
            Diario.instance.ocurre_evento("El jugador " + @nombre + " ha pasado por la salida")
            return true
        end

        def <=>(otro)
            return @saldo <=> otro.saldo
        end

    end
end