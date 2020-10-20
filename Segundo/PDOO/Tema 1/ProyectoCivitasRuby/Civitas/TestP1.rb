# encoding:utf-8

require_relative "Casilla"
require_relative "Dado"
require_relative "Diario"
require_relative "Estados_juego"
require_relative "MazoSorpresas"
require_relative "Operaciones_juego"
require_relative "Sorpresas"
require_relative "Tablero"
require_relative "TipoCasilla"
require_relative "TipoSorpresa"

module Civitas
    for i in 0..99
        puts Dado.instance.quienEmpieza(4).to_s
    end

    Dado.instance.setDebug(true)
    for i in 0..9
        puts Dado.instance.tirar().to_s
    end
    
    Dado.instance.setDebug(false)
    for i in 0..9
        puts Dado.instance.tirar().to_s
    end

    puts Dado.instance.ultimoResultado.to_s

    if (Dado.instance.salgoDeLaCarcel())
        puts "Salgo de la carcel"
    else
        puts "No salgo de la carcel"
    end

    puts TipoCasilla::CALLE.to_s
    puts Operaciones_juegos::AVANZAR.to_s
    puts TipoSorpresa::IRCARCEL.to_s
    puts Estados_juego::INICIO_TURNO.to_s

    mazo = MazoSorpresas.new()
    s1 = Sorpresas.new("S1")
    s2 = Sorpresas.new("S2")

    mazo.alMazo(s1)
    mazo.alMazo(s2)

    puts mazo.siguiente().nombre
    mazo.inhabilitarCartaEspecial(s1)
    mazo.habilitarCartaEspecial(s1)

    while Diario.instance.eventos_pendientes
        puts Diario.instance.leer_evento
    end

    
    c1 = Casilla.new("c1")
    c2 = Casilla.new("c2")
    c3 = Casilla.new("c3")
    c4 = Casilla.new("c4")
    c5 = Casilla.new("c5")
    tablero = Tablero.new(4)
    tablero.añadeCasilla(c1)
    tablero.añadeCasilla(c2)
    tablero.añadeCasilla(c3)
    tablero.añadeCasilla(c4)
    tablero.añadeCasilla(c5)
    tablero.añadeJuez()
    tirar = Dado.instance.tirar()
    puts tirar.to_s
    puts tablero.nuevaPosicion(6, tirar).to_s
end