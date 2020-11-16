module Civitas

    class OperacionInmobiliaria
        attr_reader :gestion
        attr_reader :numPropiedad

        def initialize(gest, ip)
            @gestion = gest
            @numPropiedad = ip
        end

    end
end