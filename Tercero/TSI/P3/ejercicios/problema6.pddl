(define (problem Ej6) (:domain Ej6)
(:objects 
    LOC11 LOC12 LOC13 LOC14 LOC21 LOC22 LOC23 LOC24 LOC31 LOC32 LOC33 LOC34 LOC44 - localizacion
    ;Hay un centro de mando, una unidad VCE y dos recursos de mineral
    VCE1 VCE2 VCE3 marine1 marine2 soldado1 - unidad
    mineral1 mineral2 gas1 - recurso
    CentroDeMando1 - edificio
    extractor1 - edificio
    barracones1 - edificio
    bahiaIngenieria1 - edificio
    investigacion1 - investigacion
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

    ; Marcamos los VCE com libres
    (libre VCE1)

    ; Asignamos los tipos
    (esTipoEdificio extractor1 Extractor)
    (esTipoEdificio CentroDeMando1 CentroDeMando)
    (esTipoEdificio barracones1 Barracones)
    (esTipoEdificio bahiaIngenieria1 BahiaIngenieria)
    (esTipoRecurso mineral1 Mineral)
    (esTipoRecurso mineral2 Mineral)
    (esTipoRecurso gas1 Gas)
    (esTipoUnidad VCE1 VCE)
    (esTipoUnidad VCE2 VCE)
    (esTipoUnidad VCE3 VCE)
    (esTipoUnidad marine1 Marine)
    (esTipoUnidad marine2 Marine)
    (esTipoUnidad soldado1 Soldado)

    ; El extractor necesita mineral para construirse
    (necesita Extractor Mineral)

    ; El Barracon necesita mineral y gas para construirse
    (necesita Barracones Mineral)
    (necesita Barracones Gas) 

    ; La bahía de ingeniería necesita mineral y gas para construirse
    (necesita BahiaIngenieria Mineral)
    (necesita BahiaIngenieria Gas) 

    ;Ponemos los minerales
    (AsignarRecursoLocalizacion mineral1 LOC22)
    (AsignarRecursoLocalizacion mineral2 LOC32)
    (AsignarRecursoLocalizacion gas1 LOC44)

    ; Recursos por unidad
    (unidadNecesita VCE Mineral)
    (unidadNecesita Soldado Mineral)
    (unidadNecesita Soldado Gas)
    (unidadNecesita Marine Mineral)
    (necesitaInvestigacion Soldado investigarSoldadoUniversal)

    ; Investigaciones
    (esTipoInvestigacion investigacion1 investigarSoldadoUniversal)
    (investigacionNecesita investigarSoldadoUniversal Gas)
    (investigacionNecesita investigarSoldadoUniversal Mineral)

    ; Coste
    (= (Coste) 0)

)

(:goal
        ( and   ; Nuestro objetivo es construir barracones en LOC14, construir bahía de ingeniería en LOC12 y tener 2 marines un soldado en LOC14
                (EdificioConstruido barracones1 LOC14)
                (EdificioConstruido bahiaIngenieria1 LOC12)
                (EstaEntidadEn marine1 LOC14)
                (EstaEntidadEn marine2 LOC14)
                (EstaEntidadEn soldado1 LOC14)
                (< 
                    (Coste)
                    25
                )
        )
)
)
