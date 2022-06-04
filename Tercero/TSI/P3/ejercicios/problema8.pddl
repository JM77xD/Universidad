(define (problem Ej8) (:domain Ej8)
(:objects 
    LOC11 LOC12 LOC13 LOC14 LOC21 LOC22 LOC23 LOC24 LOC31 LOC32 LOC33 LOC34 LOC44 - localizacion
    ;Hay un centro de mando, una unidad VCE y dos recursos de mineral
    VCE1 VCE2 VCE3 marine1 marine2 soldado1 - unidad
    mineral1 mineral2 gas1 - recurso
    CentroDeMando1 - edificio
    extractor1 - edificio
    barracon1 - edificio
)

(:init
    ;Establecemos el grafo que se puede observar en el guión de prácticas
    (HayCaminoEntre LOC11 LOC12)
    (HayCaminoEntre LOC11 LOC21)
    (HayCaminoEntre LOC12 LOC11)
    (HayCaminoEntre LOC12 LOC22)
    (HayCaminoEntre LOC13 LOC14)
    (HayCaminoEntre LOC13 LOC23)
    (HayCaminoEntre LOC14 LOC13)
    (HayCaminoEntre LOC14 LOC24)
    (HayCaminoEntre LOC21 LOC11)
    (HayCaminoEntre LOC21 LOC31)
    (HayCaminoEntre LOC22 LOC12)
    (HayCaminoEntre LOC22 LOC32)
    (HayCaminoEntre LOC22 LOC23)
    (HayCaminoEntre LOC23 LOC22)
    (HayCaminoEntre LOC23 LOC13)
    (HayCaminoEntre LOC23 LOC33)
    (HayCaminoEntre LOC24 LOC14)
    (HayCaminoEntre LOC24 LOC34)
    (HayCaminoEntre LOC31 LOC21)
    (HayCaminoEntre LOC31 LOC32)
    (HayCaminoEntre LOC32 LOC31)
    (HayCaminoEntre LOC32 LOC22)
    (HayCaminoEntre LOC33 LOC23)
    (HayCaminoEntre LOC33 LOC34)
    (HayCaminoEntre LOC34 LOC33)
    (HayCaminoEntre LOC34 LOC24)
    (HayCaminoEntre LOC34 LOC44)
    (HayCaminoEntre LOC44 LOC34)

    ;Ponemos las entidades 
    (EstaEntidadEn CentroDeMando1 LOC11)
    (EstaEntidadEn VCE1 LOC11)
    (EdificioConstruido CentroDeMando1 LOC11)

    ; Marcamos los VCE como libres
    (libre VCE1)

    ; Asignamos los tipos
    (esTipoEdificio extractor1 Extractor)
    (esTipoEdificio CentroDeMando1 CentroDeMando)
    (esTipoEdificio barracon1 Barracon)
    (esTipoRecurso mineral1 Mineral)
    (esTipoRecurso mineral2 Mineral)
    (esTipoRecurso gas1 Gas)
    (esTipoUnidad VCE1 VCE)
    (esTipoUnidad VCE2 VCE)
    (esTipoUnidad VCE3 VCE)
    (esTipoUnidad marine1 Marine)
    (esTipoUnidad marine2 Marine)
    (esTipoUnidad soldado1 Soldado)

    ;Ponemos los minerales
    (AsignarRecursoLocalizacion mineral1 LOC22)
    (AsignarRecursoLocalizacion mineral2 LOC32)
    (AsignarRecursoLocalizacion gas1 LOC44)

    ; Recursos por unidad
    (= (necesitaRecursosUnidad VCE Mineral) 5)
    (= (necesitaRecursosUnidad VCE Gas) 0)
    (= (necesitaRecursosUnidad Marine Mineral) 10)
    (= (necesitaRecursosUnidad Marine Gas) 15)
    (= (necesitaRecursosUnidad Soldado Mineral) 30)
    (= (necesitaRecursosUnidad Soldado Gas) 30)

    ; Recursos por edificio
    (= (necesitaRecursosEdificio Barracon Mineral) 30)
    (= (necesitaRecursosEdificio Barracon Gas) 10)
    (= (necesitaRecursosEdificio Extractor Mineral) 10)
    (= (necesitaRecursosEdificio Extractor Gas) 0)

    ; Recursos iniciales
    (= (tenemosRecurso Gas) 0)
    (= (tenemosRecurso Mineral) 0)

    ; Máximos de cada recurso
    (= (MaxRecurso Gas) 60)
    (= (MaxRecurso Mineral) 60)

    ; Unidades extrayendo al comienzo
    (= (HayExtrayendo Gas) 0)
    (= (HayExtrayendo Mineral) 0)

    ; Coste inicial
    (= (Coste) 0)

    ; Coste por unidad
    (= (costeUnidad VCE) 10)
    (= (costeUnidad Marine) 20)
    (= (costeUnidad Soldado) 30)

    ; Velocidad de las unidades
    (= (velocidadUnidad VCE) 1)
    (= (velocidadUnidad Marine) 5)
    (= (velocidadUnidad Soldado) 10)

    ; Coste por edificio
    (= (costeEdificio Extractor) 20)
    (= (costeEdificio Barracon) 50)

)

(:goal
        ( and   ; Nuestro objetivo es construir barracones en LOC32, tener 2 marines, en LOC31 y LOC24 y un soldado en LOC12
                (EdificioConstruido barracon1 LOC32)
                (EstaEntidadEn marine1 LOC31)
                (EstaEntidadEn marine2 LOC24)
                (EstaEntidadEn soldado1 LOC12)
        )
)

(:metric minimize (Coste))
)
