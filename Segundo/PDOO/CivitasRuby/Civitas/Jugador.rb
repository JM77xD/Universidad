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
        attr_accessor :propiedades
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
            @nCasillaActual = 0
            @PasoPorSalida = 1000
            @PrecioLibertad = 200
            @puedeComprar
            @SaldoInicial = 7500
            @saldo = @SaldoInicial
            @salvoconducto
            @propiedades = []
        end

        def self.copiaDe(otro)
            nuevo = self.new(otro.nombre)
            nuevo.nCasillaActual = otro.nCasillaActual
            nuevo.encarcelado = otro.encarcelado
            nuevo.puedeComprar = otro.puedeComprar
            nuevo.saldo = otro.saldo
            nuevo.propiedades = otro.propiedades
            nuevo.salvoconducto = otro.salvoconducto
            return nuevo
        end

        def cantidadCasasHoteles
            suma = 0
            @propiedades.each do |propiedad|
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
            return @propiedades.size > ip
        end

        def vender(ip)
            if @encarcelado
                return false
            elsif existeLaPropiedad(ip)
                if @propiedades.at(ip).vender(self)
                    @propiedades.delete_at(ip)
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
            return @propiedades.any?
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

        def cancelarHipoteca(ip)
            result = false
            if @encarcelado
                return result
            end
            if existeLaPropiedad(ip)
                propiedad = @propiedades.at(ip)
                cantidad = propiedad.getImporteCancelarHipoteca()
                puedoGastar = puedoGastar(cantidad)
                if puedoGastar
                    result = propiedad.cancelarHipoteca(self)
                    if result
                        Diario.instance.ocurre_evento("El jugador " + @nombre + " cancela la hipoteca de la propiedad " + propiedad.nombre)
                    end
                end
            end
            return result
        end

        def hipotecar(ip)
            result = false
            if @encarcelado
                return result
            end
            if existeLaPropiedad(ip)
                propiedad = @propiedades.at(ip)
                result = propiedad.hipotecar(self)
                if result
                    Diario.instance.ocurre_evento("El jugador " + @nombre + " hipoteca la propiedad " + propiedad.nombre)
                end
            end
            return result
        end

        def comprar(titulo)
            result = false
            if @encarcelado
                return result
            end
            if @puedeComprar
                precio = titulo.precioCompra
                if puedoGastar(precio)
                    result = titulo.comprar(self)
                    if result 
                        @propiedades << titulo
                        Diario.instance.ocurre_evento("El jugador " + @nombre + " compra la propiedad " + titulo.nombre)
                    end
                end
                @puedeComprar = false
            end
            return result
        end

        def puedoEdificarHotel(propiedad)
            return (propiedad.nCasas == @CasasPorHotel && propiedad.nHoteles < @HotelesMax)
        end

        def puedoEdificarCasa(propiedad)
            return (propiedad.nCasas < @CasasMax)
        end

        def construirHotel(ip)
            result = false
            if @encarcelado
                return result
            end
            if existeLaPropiedad(ip)
                propiedad = @propiedades.at(ip)
                puedoEdificar = puedoEdificarHotel(propiedad)
                precio = propiedad.precioEdificar
                if (puedoGastar(precio) && puedoEdificar)
                    result = propiedad.construirHotel(self)
                    if result
                        propiedad.derruirCasas(@CasasPorHotel, self)
                        Diario.instance.ocurre_evento("El jugador " + @nombre + " ha construido un hotel en la propiedad " + propiedad.nombre)
                    end
                end
            end
            return result
        end

        def construirCasa(ip)
            result = false
            if @encarcelado
                return result
            end
            if existeLaPropiedad(ip)
                propiedad = @propiedades.at(ip)
                puedoEdificar = puedoEdificarCasa(propiedad)
                precio = propiedad.precioEdificar
                if (puedoGastar(precio) && puedoEdificar)
                    result = propiedad.construirCasa(self)
                    if result
                        Diario.instance.ocurre_evento("El jugador " + @nombre + " ha construido una casa en la propiedad " + propiedad.nombre)
                    end
                end
            end
            return result
        end

    end
end