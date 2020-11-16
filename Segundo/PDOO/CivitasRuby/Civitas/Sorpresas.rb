require_relative "Tablero"
require_relative "MazoSorpresas"
require_relative "Jugador"
require_relative "TipoSorpresa"
require_relative "Diario"

module Civitas

    class Sorpresas

        attr_reader :nombre
        attr_reader :TipoSorpresa

        def initialize(tipo, param1 = nil, param2 = nil)
          @TipoSorpresa = tipo
          @texto = nil
          @valor = -1
          @refT = nil
          @refMS = nil

          if tipo == TipoSorpresa::IRCARCEL
            @refT = param1
          elsif tipo == TipoSorpresa::IRCASILLA
            @refT = param1
            @valor = param2
          elsif tipo == TipoSorpresa::SALIRCARCEL
            @refMS = param1
          else
            @valor = param1
            @texto = param2
          end
        end

        def jugadorCorrecto(actual, todos)
          return todos.size > actual
        end

        def informe(actual, todos)
          Diario.instance.ocurre_evento("Se le aplica una sorpresa al jugador " + todos.at(actual).nombre + " de tipo " + self.to_String + ".")
        end

        def aplicarAJugador(actual, todos)
          if (nil != @TipoSorpresa && self.jugadorCorrecto(actual, todos))
            informe(actual, todos)

            case @TipoSorpresa            
              when TipoSorpresa::IRCARCEL
                self.aplicarAJugador_irCarcel(actual, todos)
              when TipoSorpresa::IRCASILLA
                self.aplicarAJugador_irACasilla(actual, todos)
              when TipoSorpresa::PAGARCOBRAR
                self.aplicarAJugador_pagarCobrar(actual, todos)
              when TipoSorpresa::PORJUGADOR
                self.aplicarAJugador_porJugador(actual, todos)
              when TipoSorpresa::SALIRCARCEL
                self.aplicarAJugador_salirCarcel(actual, todos)
              when TipoSorpresa.PORCASAHOTEL
                self.aplicarAJugador_porCasaHotel(actual, todos)
            end
          end
        end

        def aplicarAJugador_irCarcel(actual, todos)
          todos.at(actual).encarcelar()
        end

        def aplicarAJugador_irACasilla(actual, todos)
          casillaAct = todos.at(actual).casillaActual
          tirada = @refT.calcularTirada(casillaAct, valor)
          nuevaPos = @refT.nuevaPosicion(casillaAct, tirada)
          todos.at(actual).moverACAsilla(nuevaPos)
          casilla = @refT.getCasilla(nuevaPos)
          casilla.recibeJugador(actual, todos)
        end

        def aplicarAJugador_pagarCobrar(actual, todos)
          todos.at(actual).modificarSaldo(@valor)
        end

        def aplicarAJugador_porCasaHotel(actual, todos)
          edificios = todos.at(actual).cantidadCasasHoteles()
          todos.at(actual).modificarSaldo(edificios*@valor)
        end

        def aplicarAJugador_porJugador(actual, todos)
          suma = Sorpresa.new(TipoSorpresa::PAGARCOBRAR, @valor*(todos.size - 1), "suma")
          resta = Sorpresa.new(TipoSorpresa::PAGARCOBRAR, -1*@valor, "resta")

          for i in 0..todos.size-1
            if (actual != i)
              resta.aplicarAJugador_pagarCobrar(i, todos)
            else
              suma.aplicarAJugador_pagarCobrar(actual, todos)
            end
          end
        end

        def aplicarAJugador_salirCarcel(actual, todos)
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

        def salirDelMazo
          if @TipoSorpresa == TipoSorpresa::SALIRCARCEL
            @refMS.inhabilitarCartaEspecial(self)
          end
        end

        def usada
          if @TipoSorpresa == TipoSorpresa::SALIRCARCEL
            @refMS.habilitarCartaEspecial(self)
          end
        end

        def to_String
          return @TipoSorpresa.to_s
        end

    end
end