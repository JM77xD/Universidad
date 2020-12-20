#encoding:utf-8
require_relative '../Civitas/CivitasJuego'
require_relative '../Civitas/Operaciones_juego'
require_relative '../Civitas/Respuestas'
require_relative '../Civitas/SalidasCarcel'
require 'io/console'

module Civitas

  class Vista_textual


    def mostrar_estado(estado)
      puts estado
    end

    
    def pausa
      print "Pulsa una tecla"
      STDIN.getch
      print "\n"
    end

    def lee_entero(max,msg1,msg2)
      ok = false
      begin
        print msg1
        cadena = gets.chomp
        begin
          if (cadena =~ /\A\d+\Z/)
            numero = cadena.to_i
            ok = true
          else
            raise IOError
          end
        rescue IOError
          puts msg2
        end
        if (ok)
          if (numero >= max)
            ok = false
          end
        end
      end while (!ok)

      return numero
    end



    def menu(titulo,lista)
      tab = "  "
      puts titulo
      index = 0
      lista.each { |l|
        puts tab+index.to_s+"-"+l
        index += 1
      }

      opcion = lee_entero(lista.length,
                          "\n"+tab+"Elige una opción: ",
                          tab+"Valor erróneo")
      return opcion
    end

    
    def comprar
      lista_Respuestas = [Respuestas::SI, Respuestas::NO]
      opciones = ["Si", "No"]
      opcion = menu("Desea comprar la propiedad?", opciones)
      return lista_Respuestas[opcion]
    end

    def gestionar
      opciones = ["Vender", "Hipotecar", "Cancelar hipoteca", "Construir casa", "Construir hotel", "Terminar"]
      opcion = menu("Seleccione la gestión a realizar", opciones)
      @iGestion = opcion
      if opcion != 5
        propiedades = @juegoModel.getJugador().propiedades
        nombres = []
        propiedades.each { |p|
          nombres << p.nombre
        }
        ip = menu("Seleccione la propiedad en la que desea realizar la gestión", nombres)
        @iPropiedad = ip
      end
    end

    def getGestion
      return @iGestion
    end

    def getPropiedad
      return @iPropiedad
    end

    def mostrarSiguienteOperacion(operacion)
      print "\nLa siguiente operación a realizar es " + operacion.to_s + ".\n\n"
    end

    def mostrarEventos
      while(Diario.instance.eventos_pendientes())
        puts Diario.instance.leer_evento()
      end
    end

    def salirCarcel
      lista_SalidasCarcel = [SalidasCarcel::PAGANDO, SalidasCarcel::TIRANDO]
      opciones =["Pagando", "Tirando"]
      opcion = menu("Seleccione como desea salir de la cárcel", opciones)
      return lista_SalidasCarcel[opcion]
    end

    def setCivitasJuego(civitas)
      @iGestion
      @iPropiedad  
      @juegoModel=civitas
      self.actualizarVista
    end

    def actualizarVista
      jugador = @juegoModel.getJugador()
      print "\nEl jugador actual es " + jugador.nombre + " y tiene un saldo de " + jugador.saldo.to_s + ".\n"
      casilla = @juegoModel.getCasillaActual()
      print "La casilla actual es " + casilla.nombre + " y es de tipo " + casilla.toString() + "."
      if (casilla.is_a?(CasillaCalle))
        if (!casilla.titulo.tienePropietario)
          print " Además, tiene un precio de " + casilla.cantidad.to_s + "."
        end
      end
      print "\n"
    end

    def ranking
      jugadores = @juegoModel.ranking()
      posicion = 1

      jugadores.each { |j|
        puts "El jugador " + j.nombre + " ha quedado en la posición " + posicion.to_s + " con un saldo de " + j.saldo.to_s + ".\n"
        posicion = posicion + 1
      }
    end

    
  end

end
