# encoding:utf-8

require_relative 'CivitasJuego'
require_relative 'vista_textual'
require_relative 'Respuestas'
require_relative 'GestionesInmobiliarias'
require_relative 'OperacionInmobiliaria'

module Civitas

    class Controlador
        


        def initialize(civitas, vis)
            @juego = civitas
            @vista = vis
        end

        def juega

            @vista.setCivitasJuego(@juego)
            fin = @juego.finalDelJuego()
            while ( !fin )

                @vista.actualizarVista()
                @vista.pausa()

                siguientepaso = @juego.siguientePaso()

                @vista.mostrarSiguienteOperacion(siguientepaso)

                if (siguientepaso != Operaciones_juego::PASAR_TURNO)
                    @vista.mostrarEventos()
                end

                fin = @juego.finalDelJuego()

                if !fin
                    
                    case siguientepaso
                    when Operaciones_juego::COMPRAR

                        respuesta = @vista.comprar()
                        if respuesta == Respuestas::SI
                            @juego.comprar
                        end
                        @juego.siguientePasoCompletado(siguientepaso)

                    when Operaciones_juego::GESTIONAR
                        lista_Gestiones = [GestionesInmobiliarias::VENDER, GestionesInmobiliarias::HIPOTECAR, GestionesInmobiliarias::CANCELAR_HIPOTECA, GestionesInmobiliarias::CONSTRUIR_CASA, GestionesInmobiliarias::CONSTRUIR_HOTEL, GestionesInmobiliarias::TERMINAR]

                        @vista.gestionar()
                        indiceg = @vista.getGestion()
                        indicep = @vista.getPropiedad()
                        operacion = OperacionInmobiliaria.new(indiceg, indicep)

                        case lista_Gestiones[indiceg]

                        when GestionesInmobiliarias::VENDER
                            @juego.vender(indicep)
                            @juego.siguientePasoCompletado(siguientepaso)

                        when GestionesInmobiliarias::HIPOTECAR
                            @juego.hipotecar(indicep)
                            @juego.siguientePasoCompletado(siguientepaso)

                        when GestionesInmobiliarias::CANCELAR_HIPOTECA
                            @juego.cancelarHipoteca(indicep)
                            @juego.siguientePasoCompletado(siguientepaso)

                        when GestionesInmobiliarias::CONSTRUIR_CASA
                            @juego.construirCasa(indicep)
                            @juego.siguientePasoCompletado(siguientepaso)

                        when GestionesInmobiliarias::CONSTRUIR_HOTEL
                            @juego.construirHotel(indicep)
                            @juego.siguientePasoCompletado(siguientepaso)

                        when GestionesInmobiliarias::TERMINAR
                            @juego.siguientePasoCompletado(siguientepaso)
                        end
                        
                    when Operaciones_juego::SALIR_CARCEL

                        salidaCarcel = @vista.salirCarcel()
                        if salidaCarcel == SalidasCarcel::PAGANDO
                            @juego.salirCarcelPagando()
                        else
                            @juego.salirCarcelTirando()
                        end

                    end
                end
            end

            @vista.ranking(9)

        end

    end

end