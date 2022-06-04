(define (domain Ej2)

(:requirements :strips :fluents :adl)

(:types

    ; Defino nuestros tipos básicos entidad (personaje o edificio), localización (un cuadrado del mundo) y recurso (mineral o gas) 
    entidad localizacion recurso - object

    ; Una entidad puede ser una unidad o un edificio
    unidad - entidad
    edificio - entidad

    ; Definimos los tipos, esto indica que podemos tener unidades tipo VCE, edificios tipo CentroDeMando o Barracones...
    tipoVCE - unidad

    tipoCentroDeMando - edificio
    tipoBarracones - edificio
    tipoExtractor - edificio

    tipoMineral - recurso
    tipoGas - recurso
    
)

(:constants 

    VCE - tipoVCE

    CentroDeMando - tipoCentroDeMando
    Barracones - tipoBarracones
    Extractor - tipoExtractor

    Mineral - tipoMineral
    Gas - tipoGas
)

(:predicates

    ; Comprobar si una entidad (unidad o edificio) está en una localización
    (EstaEntidadEn ?obj - entidad ?l1 - localizacion)

    ; Comprobar la existencia de un camino entre dos localizaciones
    (HayCaminoEntre ?l1 - localizacion ?l2 - localizacion)

    ; Comprobar si hay un edificio construido en una localización concreta
    (EdificioConstruido ?e - edificio ?l1 - localizacion)

    ; Asignar un recurso a una localización
    (AsignarRecursoLocalizacion ?r1 - recurso ?l1 - localizacion)

    ; Comprobar si una unidad está extrayendo un recurso
    (estaExtrayendoRecurso ?r - recurso)

    ;Un edificio necesita un recurso para ser construido
    (necesitaRecurso ?edif - edificio ?r - recurso)

    ; Comprobamos si una unidad está libre
    (libre ?uni - unidad)

    ;Comprobaciones para el tipo de recurso y edificio
    (esTipoRecurso ?r1 - recurso ?r2 - recurso)
    (esTipoEdificio ?edif1 - edificio ?edif2 - edificio)

)

(:action navegar
    ; Los parametros son la unidad, localización inicial y localización destino
    :parameters (?obj - unidad ?l1 - localizacion ?l2 - localizacion)
    :precondition
    (   and

                        (EstaEntidadEn ?obj ?l1)

                        (HayCaminoEntre ?l1 ?l2)
    )
    :effect
    (   and 

                    (EstaEntidadEn ?obj ?l2)

                    (not (EstaEntidadEn ?obj ?l1))
    )
)

(:action asignar

    ; Los parametros son la unidad, localizacion del recurso y tipo de recurso
    :parameters (?uni - unidad ?loc - localizacion ?r - recurso)
    :precondition
    (   and 

                        (EstaEntidadEn ?uni ?loc)

                        (libre ?uni)

                        (AsignarRecursoLocalizacion ?r ?loc)

                        ; O el tipo de recurso es mineral, o bien existe un extractor construido en la posición del recurso
                        (or
                            (and
                                (esTipoRecurso ?r Gas)

                                (exists (?edif - edificio)
                                    (and
                                        (esTipoEdificio ?edif Extractor)
                                        (EdificioConstruido ?edif ?loc)
                                    )                    
                                )
                            )

                            (esTipoRecurso ?r Mineral)
                        )
    )
    :effect
    (   and 
                        ; Estaremos extrayendo el recurso y la unidad dejará de estar libre
                        (estaExtrayendoRecurso ?r)
                        (not (libre ?uni))
    )
)

(:action construir
    :parameters (?uni - unidad ?edif - edificio ?l1 - localizacion ?rec - recurso)
    :precondition
    (   and             ; La unidad ha de estar libre, estar en el lugar correcto, que el edificio se pueda construir
                        ; con ese recurso y que haya una unidad extrayendo el recurso necesario
                        (libre ?uni)

                        (EstaEntidadEn ?uni ?l1)

                        (exists (?r1 - recurso ?edificio - edificio) 
                            (and
                                (esTipoEdificio ?edif ?edificio)
                                (esTipoRecurso ?rec ?r1)
                                (estaExtrayendoRecurso ?rec)   
                                (necesitaRecurso ?edificio ?r1)
                            )
                        )
    )
    :effect
    (   and             ; Tendremos el edificio construido y la entidad en la localización
                        (EdificioConstruido ?edif ?l1)
                        (EstaEntidadEn ?edif ?l1)
    )
)

)