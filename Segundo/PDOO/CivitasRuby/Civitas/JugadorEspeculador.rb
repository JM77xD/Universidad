# encodign:utf-8

require_relative "Jugador"

module Civitas

    class JugadorEspeculador < Jugador

        def initialize (f)
            @fianza = f
            @FactorEspeculador = 2
            @@hotelesMax = @@hotelesMax * @FactorEspeculador
            @@casasMax = @@casasMax * @FactorEspeculador
        end

        def self.nuevoEspeculador(otro, f)
            nuevoJugador = self.new(f)
            nuevoJugador = Jugador.copiaDe(otro)
            nuevoJugador.propiedades.each do |propiedad|
                propiedad.actualizarPropietario(nuevoJugador)
            end
            
            return nuevoJugador
        end

        def quieroPagar
            ok = false
            msg1 = "Desea pagar la fianza de " + @fianza.to_s + "? (1 -> si, 0 -> no)"
            msg2 = "Valor incorrecto"
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
                if (numero > 1)
                  ok = false
                end
              end
            end while (!ok)
            
            if numero == 1
                return true
            else
                return false
            end
        end

        def debeSerEncarcelado
            if @encarcelado
                return false
            elsif tieneSalvoconducto()
                perderSalvoconducto()
                Diario.instance.ocurre_evento("El jugador " + @nombre + " se libra de la cárcel a cambio del salvoconducto.")
                return false
            elsif puedoGastar(@fianza)
                if quieroPagar()
                    paga(@fianza)
                    Diario.instance.ocurre_evento("El jugador " + @nombre + " se libra de la cárcel pagando la fianza de " + @fianza.to_s + ".")
                    return false
                else
                    return true
                end
            else
                return true
            end
        end

        def pagaImpuesto(cantidad)
            if @encarcelado
                return false
            else
                return paga(cantidad/@FactorEspeculador)
            end
        end

    end

end