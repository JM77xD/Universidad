(define (problem Ej3) (:domain Ej3)
(:objects 
    LOC11 LOC12 LOC13 LOC14 LOC21 LOC22 LOC23 LOC24 LOC31 LOC32 LOC33 LOC34 LOC44 - localizacion
    ;Hay un centro de mando, una unidad VCE y dos recursos de mineral
    VCE1 VCE2 VCE3 - unidad
    CentroDeMando1 - edificio
    mineral1 mineral2 gas1 - recurso
    extractor1 - edificio
    barracones1 - edificio
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
    (EstaEntidadEn VCE2 LOC11)
    (EstaEntidadEn VCE3 LOC11)

    ; Marcamos los VCE com libres
    (libre VCE1)
    (libre VCE2)
    (libre VCE3)

    ; Asignamos los tipos
    (esTipoEdificio extractor1 Extractor)
    (esTipoEdificio CentroDeMando1 CentroDeMando)
    (esTipoEdificio barracones1 Barracones)
    (esTipoRecurso mineral1 Mineral)
    (esTipoRecurso mineral2 Mineral)
    (esTipoRecurso gas1 Gas)

    ; El extractor necesita mineral para construirse
    (necesita Extractor Mineral)

    ; El extractor necesita mineral para construirse
    (necesita Barracones Mineral)
    (necesita Barracones Gas) 

    ;Ponemos los minerales
    (AsignarRecursoLocalizacion mineral1 LOC22)
    (AsignarRecursoLocalizacion mineral2 LOC32)
    (AsignarRecursoLocalizacion gas1 LOC44)

)

(:goal
        ( and
                ; Nuestro objetivo es que se construyan unos barracones en LOC33
                (EdificioConstruido barracones1 LOC33)
        )
)
)
