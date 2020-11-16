# encoding:utf-8
require_relative "Casilla"

module Civitas

    class Tablero

        def initialize (c)  #Constructor con un parametro para saber cual será la casilla carcel
            @numCasillaCarcel
            if (c>=1)
                @numCasillaCarcel = c
            else
                @numCasillaCarcel = 1
            end
            @casillas = []
            casilla = Casilla.new(TipoCasilla::DESCANSO, "Salida")
            @casillas << casilla
            @porSalida = 0
            @tieneJuez = false
        end


        attr_reader :numCasillaCarcel
        

        def correcto    #Evalua si el tablero como conjunto es correcto para iniciar una partida
            return (@casillas.length > @numCasillaCarcel && @tieneJuez)
        end


        def correcta(numCasilla)    #Evalua si una casilla en concreto es correcta
            return (correcto() && numCasilla.to_i < @casillas.size)
        end


        def getPorSalida  #Devuelve el numero de veces que se ha pasado por la salida
            if(@porSalida > 0)
                @porSalida--
                valor = @porSalida + 1
                return valor
            else
                return @porSalida
            end
        end


        def añadeCasilla(c)     #Añade una casilla al tablero, comprobando antes que no sea en la posicion de la casilla carcel
            if (@casillas.size == @numCasillaCarcel)
                casilla = Civitas::Casilla.new(TipoCasilla::DESCANSO, "Cárcel")
                @casillas<< casilla
            end
            @casillas.push(c)
            if (@casillas.size == @numCasillaCarcel)
                casilla = Civitas::Casilla.new(TipoCasilla::DESCANSO, "Cárcel")
                @casillas << casilla
            end
        end

        def añadeJuez       #Añade el juez al tablero
            if(!@tieneJuez)
                juez = Casilla.new(TipoCasilla::JUEZ, "Juez")
                @casillas << juez
                @tieneJuez = true
            end
        end

        def getCasilla(numCasilla)    #Consultor de una casilla dada su posición en el tablero
            if (correcta(numCasilla))
                return @casillas.at(numCasilla)
            else
                return nil
            end
        end

        def nuevaPosicion(actual, tirada)   #Calcula la nueva posicion del jugador y la devuelve
            if (!correcto)
                return -1
            end
            return (actual+tirada) % @casillas.size
        end

        def calcularTirada(origen, destino)     #Calcula la tirada que habría sido necesaria para acabar en la posicion 'destino'
            resultado = destino-origen
            if (resultado < 0)
                resultado += @casillas.size
            end
            return resultado
        end
        
        
    end
end