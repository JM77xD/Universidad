# encoding:utf-8

require_relative 'Controlador'
require_relative '../Civitas/CivitasJuego'
require_relative 'vista_textual'

module Civitas
    juego = CivitasJuego.new('Marco', 'Polo', 'Si', 'No')
    vista = Vista_textual.new
    control = Controlador.new(juego, vista)
    control.juega()
end