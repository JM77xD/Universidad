# encoding:utf-8

require_relative "Casilla"
require_relative "Jugador"
require_relative "Tablero"
require_relative "gestor_estados"
require_relative "TituloPropiedad"
require_relative "TipoCasilla"
require_relative "TipoSorpresa"
require_relative "MazoSorpresas"
require_relative "Dado"



module Civitas

    class CivitasJuego
        
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
                casilla = Casilla.new(TipoCasilla::CALLE, calle)
                @tablero.añadeCasilla(casilla)
            end

            impuesto = Casilla.new(TipoCasilla::IMPUESTO, -600, "Impuestos")
            @tablero.añadeCasilla(impuesto)

            for i in 4..6
                calle = TituloPropiedad.new("Calle"+i.to_s, 100*i, 1+(i/10), 150*i, 250*i, 100*i)
                casilla = Casilla.new(TipoCasilla::CALLE, calle)
                @tablero.añadeCasilla(casilla)
            end
            @tablero.añadeJuez()

            sorpresa1 = Casilla.new(TipoCasilla::SORPRESA, mazo, "Sorpresa1")
            @tablero.añadeCasilla(sorpresa1)

            for i in 7..9
                calle = TituloPropiedad.new("Calle"+i.to_s, 100*i, 1+(i/10), 150*i, 250*i, 100*i)
                casilla = Casilla.new(TipoCasilla::CALLE, calle)
                @tablero.añadeCasilla(casilla)
            end

            sorpresa2 = Casilla.new(TipoCasilla::SORPRESA, mazo, "Sorpresa2")
            @tablero.añadeCasilla(sorpresa2)

            parking = Casilla.new(TipoCasilla::DESCANSO, "Parking")
            @tablero.añadeCasilla(parking)

            for i in 10..11
                calle = TituloPropiedad.new("Calle"+i.to_s, 100*i, 1+(i/10), 150*i, 250*i, 100*i)
                casilla = Casilla.new(TipoCasilla::CALLE, calle)
                @tablero.añadeCasilla(casilla)
            end

            sorpresa3 = Casilla.new(TipoCasilla::SORPRESA, mazo, "Sorpresa3")
            @tablero.añadeCasilla(sorpresa3)

            calle12 = TituloPropiedad.new("Calle12", 1200, 2.2, 1800, 3000, 1200)
            casilla12 = Casilla.new(TipoCasilla::CALLE, calle12)
            @tablero.añadeCasilla(casilla12)
        end

        def inicializaMazoSorpresas(tablero)

            ircarcel = Sorpresas.new(TipoSorpresa::IRCARCEL, tablero)
            @mazoSorpresas.alMazo(ircarcel)

            pagar500 = Sorpresas.new(TipoSorpresa::PAGARCOBRAR, -500, "Pagar 500")
            @mazoSorpresas.alMazo(pagar500)

            irCasilla12 = Sorpresas.new(TipoSorpresa::IRCASILLA, tablero, 12)
            @mazoSorpresas.alMazo(irCasilla12)

            evitarCarcel = Sorpresas.new(TipoSorpresa::SALIRCARCEL, @mazoSorpresas)
            @mazoSorpresas.alMazo(evitarCarcel)

            porJugador130 = Sorpresas.new(TipoSorpresa::PORJUGADOR, 130, "Pago de 130 de cada jugador al jugador actual")
            @mazoSorpresas.alMazo(porJugador130)

            porCasaHotel60 = Sorpresas.new(TipoSorpresa::PORCASAHOTEL, -60, "Pago de 60 por cada edificio.")
            @mazoSorpresas.alMazo(porCasaHotel60)
        end

        def contabilizarPasoPorSalida(jugadorActual)
            while @tablero.attr_porSalida() != 0
                jugadorActual.pasaPorSalida()
            end
        end

        def pasarTurno
            @indiceJugadorActual = (@indiceJugadorActual + 1) % @jugadores.size
        end

        def siguientePasoCompletado(operacion)
            @estado = @Gestor.siguienteEstado(@jugadores.at(@indiceJugadorActual) , @estado , operacion)
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

        def ranking
            @jugadores.sort { |a,b| -a <=> -b }
            return @jugadores
        end

    end
end
