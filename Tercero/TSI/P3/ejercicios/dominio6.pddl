(define (domain Ej6)

(:requirements :strips :fluents :adl)

(:types

    ; Defino nuestros tipos básicos entidad (personaje o edificio), localización (un cuadrado del mundo) y recurso (mineral o gas) 
    entidad localizacion recurso investigacion coste - object

    ; Una entidad puede ser una unidad o un edificio
    unidad - entidad
    edificio - entidad

    ; Definimos los tipos
    tipoUnidad - unidad

    tipoEdificio - edificio

    tipoRecurso - recurso
    
    tipoInvestigacion - investigacion

)

(:constants 

    VCE - tipoUnidad
    Marine - tipoUnidad
    Soldado - tipoUnidad

    CentroDeMando - tipoEdificio
    Barracones - tipoEdificio
    Extractor - tipoEdificio
    BahiaIngenieria - tipoEdificio

    Mineral - tipoRecurso
    Gas - tipoRecurso

    investigarSoldadoUniversal - tipoInvestigacion
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
    (necesita ?edif - edificio ?r - recurso)

    ; Comprobamos si una unidad está libre
    (libre ?uni - unidad)

    ;Comprobaciones para el tipo de recurso y edificio
    (esTipoRecurso ?r1 - recurso ?r2 - recurso)
    (esTipoEdificio ?edif1 - edificio ?edif2 - edificio)
    (esTipoUnidad ?uni1 - unidad ?uni2 - unidad)
    (esTipoInvestigacion ?invest1 - investigacion ?invest2 - investigacion)

    ; Se está extrayendo un tipo de recurso
    (estaExtrayendoTipoRecurso ?r - tipoRecurso)

    ; Relativo al reclutamiento de unidades
    (seRecluta ?uni - tipoUnidad ?edif - tipoEdificio)
    (unidadNecesita ?uni - tipoUnidad ?r - tipoRecurso)
    (necesitaInvestigacion ?uni - tipoUnidad ?investigacion - tipoInvestigacion)

    ; Relativo a la investigacion
    (investigado ?investigacion - investigacion)
    (investigacionNecesita ?investigacion - tipoInvestigacion ?recurso - tipoRecurso)

)

(:functions
    (Coste)
)

(:action navegar
    ; Los parametros son la unidad, localización inicial y localización destino
    :parameters (?obj - unidad ?l1 - localizacion ?l2 - localizacion)
    :precondition
    (   and
                (libre ?obj)
                
                (EstaEntidadEn ?obj ?l1)

                (HayCaminoEntre ?l1 ?l2)
    )
    :effect
    (   and 

                (increase (Coste) 1)

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
                
                ; Marcamos el tipo de recurso que se está extrayendo
                (when (esTipoRecurso ?r Gas)
                        (estaExtrayendoTipoRecurso Gas)
                )

                (when (esTipoRecurso ?r Mineral)
                        (estaExtrayendoTipoRecurso Mineral)
                )

                (increase (Coste) 1)
    )
)

(:action construir
    :parameters (?uni - unidad ?edif - edificio ?l1 - localizacion)
    :precondition
    (   and     ; La unidad ha de estar libre, estar en el lugar correcto, que el edificio se pueda construir con ese recurso,
                ; que no esté construido el edificio, que no haya más edificios en la localización y que se estén extrayendo los recursos necesarios
                (libre ?uni)

                (EstaEntidadEn ?uni ?l1)
                
                (not (exists (?loc - localizacion) 
                        (EdificioConstruido ?edif ?loc)
                    )
                )

                (not (exists (?edificio - edificio) 
                        (EdificioConstruido ?edificio ?l1)
                    )
                )

                (exists (?edificio - edificio) 
                    (and
                        (esTipoEdificio ?edif ?edificio)
                        (forall (?r1 - tipoRecurso)
                            (imply (necesita ?edificio ?r1) (estaExtrayendoTipoRecurso ?r1))
                        )
                    )
                )
    )
    :effect
    (   and     ; Tendremos el edificio construido y la entidad en la localización
                (EdificioConstruido ?edif ?l1)
                (EstaEntidadEn ?edif ?l1)
                
                (increase (Coste) 1)
    )
)

(:action reclutar
    :parameters (?edif - edificio ?uni - unidad ?loc - localizacion)
    :precondition
    (   and
                ; Comprobamos que no exista la unidad
                (not (exists (?l1 - localizacion)
                        (and
                            (EstaEntidadEn ?uni ?l1)
                        )
                    )
                )

                (exists (?tipo - tipoUnidad)
                    (and
                        (esTipoUnidad ?uni ?tipo)
                        (forall (?r1 - tipoRecurso) ; Se están extrayendo los recursos necesarios
                            (imply (unidadNecesita ?tipo ?r1) (estaExtrayendoTipoRecurso ?r1))
                        )

                        ; Si vamos a construir un VCE debe ser en el centro de mando, si no, en los barracones
                        (or
                            (and
                                (esTipoUnidad ?uni VCE)
                                (esTipoEdificio ?edif CentroDeMando)
                                (EdificioConstruido ?edif ?loc)
                            )

                            (and
                                (esTipoUnidad ?uni Marine)
                                (esTipoEdificio ?edif Barracones)
                                (EdificioConstruido ?edif ?loc)
                            )

                            (and
                                (esTipoUnidad ?uni Soldado)
                                (forall (?tipoInv - tipoInvestigacion)
                                    (imply (necesitaInvestigacion Soldado ?tipoInv) (investigado ?tipoInv))
                                )
                                (esTipoEdificio ?edif Barracones)
                                (EdificioConstruido ?edif ?loc)
                            )
                        )
                    )
                )


    )
    :effect
    (   and
                ; Tendremos una unidad libre en la localización indicada
                (EstaEntidadEn ?uni ?loc)
                (libre ?uni)

                (increase (Coste) 1)
    )
)

(:action investigar
    :parameters (?edif - edificio ?inv - investigacion)
    :precondition
    (   and
                (not (investigado ?inv))

                (esTipoEdificio ?edif BahiaIngenieria)

                (exists (?tipoInv - tipoInvestigacion)
                    (and
                        (esTipoInvestigacion ?inv ?tipoInv)
                        (forall (?rec - tipoRecurso)
                            (imply (investigacionNecesita ?tipoInv ?rec) (estaExtrayendoTipoRecurso ?rec))
                        )
                    )
                )
    )
    :effect
    (   and
                ; Marcamos el tipo de investigación como completado
                (investigado ?inv)

                (when (esTipoInvestigacion ?inv investigarSoldadoUniversal)
                    (investigado investigarSoldadoUniversal)    
                )

                (increase (Coste) 1)
    )
)


)