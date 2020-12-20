# encoding:utf-8

require_relative "CasillaCalle"
require_relative "CasillaJuez"
require_relative "CasillaSorpresa"
require_relative "CasillaImpuesto"
require_relative "Casilla"
require_relative "Jugador"
require_relative "Tablero"
require_relative "gestor_estados"
require_relative "TituloPropiedad"
require_relative "MazoSorpresas"
require_relative "Dado"
require_relative "SorpresasIrCarcel"
require_relative "SorpresasIrACasilla"
require_relative "SorpresasConvertir"
require_relative "SorpresasPagarCobrar"
require_relative "SorpresasPorCasaHotel"
require_relative "SorpresasPorJugador"
require_relative "SorpresasSalirCarcel"



module Civitas

    class CivitasJuego

        attr_accessor :jugadores
        
        def initialize(*nombres)
            @jugadores = []

            nombres.each do |nombre|
                jugador = Jugador.new(nombre)
                @jugadores << jugador
            end

            @Gestor = Gestor_estados.new
            @estado = @Gestor.estado_inicial()
            @indiceJugadorActual = Dado.instance.quienEmpieza(@jugadores.size)
            @mazoSorpresas = MazoSorpresas.new
            @numCasillaCarcel = 5
            @tablero = Tablero.new(@numCasillaCarcel)
            inicializaMazoSorpresas(@tablero)
            inicializaTablero(@mazoSorpresas)
        end

        def inicializaTablero(mazo)

            for i in 1..3
                calle = TituloPropiedad.new("Calle"+i.to_s, 100*i, 1+(i/10), 150*i, 250*i, 100*i)
                casilla = CasillaCalle.new(calle)
                @tablero.añadeCasilla(casilla)
            end

            impuesto = CasillaImpuesto.new("Impuestos", 600)
            @tablero.añadeCasilla(impuesto)

            for i in 4..6
                calle = TituloPropiedad.new("Calle"+i.to_s, 100*i, 1+(i/10), 150*i, 250*i, 100*i)
                casilla = CasillaCalle.new(calle)
                @tablero.añadeCasilla(casilla)
            end
            @tablero.añadeJuez()

            sorpresa1 = CasillaSorpresa.new(mazo, "Sorpresa1")
            @tablero.añadeCasilla(sorpresa1)

            for i in 7..9
                calle = TituloPropiedad.new("Calle"+i.to_s, 100*i, 1+(i/10), 150*i, 250*i, 100*i)
                casilla = CasillaCalle.new(calle)
                @tablero.añadeCasilla(casilla)
            end

            sorpresa2 = CasillaSorpresa.new(mazo, "Sorpresa2")
            @tablero.añadeCasilla(sorpresa2)

            parking = Casilla.new("Parking")
            @tablero.añadeCasilla(parking)

            for i in 10..11
                calle = TituloPropiedad.new("Calle"+i.to_s, 100*i, 1+(i/10), 150*i, 250*i, 100*i)
                casilla = CasillaCalle.new(calle)
                @tablero.añadeCasilla(casilla)
            end

            sorpresa3 = CasillaSorpresa.new(mazo, "Sorpresa3")
            @tablero.añadeCasilla(sorpresa3)

            calle12 = TituloPropiedad.new("Calle12", 1200, 2.2, 1800, 3000, 1200)
            casilla12 = CasillaCalle.new(calle12)
            @tablero.añadeCasilla(casilla12)
        end

        def inicializaMazoSorpresas(tablero)

            ircarcel = SorpresasIrCarcel.new(tablero)
            @mazoSorpresas.alMazo(ircarcel)

            pagar500 = SorpresasPagarCobrar.new(-500, "Pagar 500")
            @mazoSorpresas.alMazo(pagar500)

            irCasilla12 = SorpresasIrACasilla.new(tablero, 12)
            @mazoSorpresas.alMazo(irCasilla12)

            evitarCarcel = SorpresasSalirCarcel.new(@mazoSorpresas)
            @mazoSorpresas.alMazo(evitarCarcel)

            porJugador130 = SorpresasPorJugador.new(130, "Pago de 130 de cada jugador al jugador actual")
            @mazoSorpresas.alMazo(porJugador130)

            porCasaHotel60 = SorpresasPorCasaHotel.new(-60, "Pago de 60 por cada edificio.")
            @mazoSorpresas.alMazo(porCasaHotel60)

            convertir = SorpresasConvertir.new(250, self)
            @mazoSorpresas.alMazo(convertir)
        end

        def setDebug(d)
            Dado.instance.setDebug(d)
        end

        def contabilizarPasoPorSalida(jugadorActual)
            while @tablero.getPorSalida() != 0
                jugadorActual.pasaPorSalida()
            end
        end

        def comprar
            titulo = getCasillaActual().titulo
            @jugadores.at(@indiceJugadorActual).comprar(titulo)
        end
            

        def pasarTurno
            @indiceJugadorActual = (@indiceJugadorActual + 1) % @jugadores.size
        end

        def siguientePasoCompletado(operacion)
            @estado = @Gestor.siguiente_estado(@jugadores.at(@indiceJugadorActual) , @estado , operacion)
        end

        def construirCasa(ip)
            return @jugadores.at(@indiceJugadorActual).construirCasa(ip)
        end

        def construirHotel(ip)
            return @jugadores.at(@indiceJugadorActual).construirHotel(ip)
        end

        def vender(ip)
            return @jugadores.at(@indiceJugadorActual).vender(ip)
        end

        def hipotecar(ip)
            return @jugadores.at(@indiceJugadorActual).hipotecar(ip)
        end

        def cancelarHipoteca(ip)
            return @jugadores.at(@indiceJugadorActual).cancelarHipoteca(ip)
        end

        def salirCarcelTirando
            return @jugadores.at(@indiceJugadorActual).salirCarcelTirando()
        end

        def salirCarcelPagando
            return @jugadores.at(@indiceJugadorActual).salirCarcelPagando()
        end

        def finalDelJuego
            @jugadores.each do |jugador|
                if jugador.enBancarrota()
                    return true
                end
            end
            return false
        end

        def getJugador
            return @jugadores.at(@indiceJugadorActual)
        end

        def getCasillaActual
            indice = getJugador().nCasillaActual
            return @tablero.getCasilla(indice)
        end

        def ranking
            sorted = @jugadores.sort { |a,b| b <=> a }
            return sorted
        end

        def avanzaJugador
            jugadorActual = @jugadores.at(@indiceJugadorActual)
            posicionActual = jugadorActual.nCasillaActual
            tirada = Dado.instance.tirar()
            posicionNueva = @tablero.nuevaPosicion(posicionActual, tirada)
            casilla = @tablero.getCasilla(posicionNueva)
            contabilizarPasoPorSalida(jugadorActual)
            jugadorActual.moverACasilla(posicionNueva)
            casilla.recibe_jugador(@indiceJugadorActual, @jugadores)
            contabilizarPasoPorSalida(jugadorActual)
        end

        def siguientePaso
            jugadorActual = @jugadores.at(@indiceJugadorActual)
            operacion = @Gestor.operaciones_permitidas(jugadorActual, @estado)
            if operacion == Operaciones_juego::PASAR_TURNO
                pasarTurno()
                siguientePasoCompletado(operacion)
            elsif operacion == Operaciones_juego::AVANZAR
                avanzaJugador()
                siguientePasoCompletado(operacion)
            end
            return operacion
        end

    end
end
