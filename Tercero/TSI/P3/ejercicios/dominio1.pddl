(define (domain Ej1)

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

    tipoMineral - recurso
    tipoGas - recurso
    
)

(:constants 

    VCE - tipoVCE

    CentroDeMando - tipoCentroDeMando
    Barracones - tipoBarracones

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
    (estaExtrayendoRecurso ?obj - unidad ?r - recurso)

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
    :parameters (?obj - unidad ?loc - localizacion ?r - recurso)
    :precondition
    (   and 
                        ; La primera precondición es que la unidad esté en la misma localización
                        ; que el recurso
                        (EstaEntidadEn ?obj ?loc)

                        ; La segunda precondición es que el recurso esté en la localización en la que
                        ; debería esta (la que hemos pasado por parámetro)
                        (AsignarRecursoLocalizacion ?r ?loc)
    )
    :effect
    (   and 
                        ; Cuando completemos la acción la unidad estará extrayendo el recurso.
                        (estaExtrayendoRecurso ?obj ?r)
    )
)
)