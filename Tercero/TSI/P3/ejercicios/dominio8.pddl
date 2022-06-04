(define (domain Ej8)

(:requirements :strips :fluents :adl)

(:types

    ; Defino nuestros tipos básicos entidad (personaje o edificio), localización (un cuadrado del mundo) y recurso (mineral o gas) 
    entidad localizacion recurso coste - object

    ; Una entidad puede ser una unidad o un edificio
    unidad - entidad
    edificio - entidad

    ; Definimos los tipos
    tipoUnidad - unidad

    tipoEdificio - edificio

    tipoRecurso - recurso
    
)

(:constants 

    VCE - tipoUnidad
    Marine - tipoUnidad
    Soldado - tipoUnidad

    CentroDeMando - tipoEdificio
    Barracon - tipoEdificio
    Extractor - tipoEdificio

    Mineral - tipoRecurso
    Gas - tipoRecurso
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

    ; Comprobamos si una unidad está libre
    (libre ?uni - unidad)

    ;Comprobaciones para el tipo de recurso y edificio
    (esTipoRecurso ?r1 - recurso ?r2 - recurso)
    (esTipoEdificio ?edif1 - edificio ?edif2 - edificio)
    (esTipoUnidad ?uni1 - unidad ?uni2 - unidad)

    ; Se está extrayendo un tipo de recurso
    (estaExtrayendoTipoRecurso ?r - tipoRecurso)
)

(:functions
    
    ;Un edificio necesita tanta cantidad de un recurso para ser construido
    (necesitaRecursosEdificio ?edificio - edificio ?recurso - tipoRecurso)

    ;Una unidad necesita tanta cantidad de un recurso para ser construido
    (necesitaRecursosUnidad ?unidad - unidad ?recurso - tipoRecurso)

    ; Tenemos tanta cantidad de recurso guardado
    (tenemosRecurso ?recurso - tipoRecurso)

    ; Como maximo podemos tener tanta cantidad de recurso guardado
    (MaxRecurso ?recurso - tipoRecurso)

    ; Hay tantas unidades extrayendo un recurso
    (HayExtrayendo ?recurso - tipoRecurso)

    ; Coste total de tiempo del plan
    (Coste)

    ; Velocidad de cada unidad
    (velocidadUnidad ?tipo - tipoUnidad)

    ; Coste de cada unidad
    (costeUnidad ?tipo - tipoUnidad)

    ; Coste de cada edificio
    (costeEdificio ?tipo - tipoEdificio)
)

(:action navegar
    ; Los parametros son la unidad, localización inicial y localización destino
    :parameters (?obj - unidad ?l1 - localizacion ?l2 - localizacion ?tipo - tipoUnidad)
    :precondition
    (   and
                (libre ?obj)

                (EstaEntidadEn ?obj ?l1)

                (HayCaminoEntre ?l1 ?l2)

                (esTipoUnidad ?obj ?tipo)
    )
    :effect
    (   and 

                (EstaEntidadEn ?obj ?l2)

                (not (EstaEntidadEn ?obj ?l1))
                
                ; Aumentamos el tiempo según la velocidad de cada unidad
                (increase
                    (Coste)
                    (/
                        20
                        (velocidadUnidad ?tipo)
                    )
                )
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
                
                ; Marcamos el tipo de recurso que se está extrayendo y aumentamos el contador
                (when (esTipoRecurso ?r Gas)
                    (and
                        (estaExtrayendoTipoRecurso Gas)
                        (increase (HayExtrayendo Gas) 1)
                    )
                )

                (when (esTipoRecurso ?r Mineral)
                    (and
                        (estaExtrayendoTipoRecurso Mineral)
                        (increase (HayExtrayendo Mineral) 1)
                    )
                )
    )
)

(:action construiredificio
    :parameters (?uni - unidad ?edif - edificio ?l1 - localizacion ?edificio - tipoEdificio)
    :precondition
    (   and     ; La unidad ha de estar libre, estar en el lugar correcto, que el edificio se pueda construir con ese recurso,
                ; que no esté construido el edificio, que no haya más edificios en la localización y que tengamos los recursos necesarios
                (libre ?uni)

                (EstaEntidadEn ?uni ?l1)
                
                (not (exists (?loc - localizacion) 
                        (EdificioConstruido ?edif ?loc)
                    )
                )

                (not (exists (?edific - edificio) 
                        (EdificioConstruido ?edific ?l1)
                    )
                )

                (esTipoEdificio ?edif ?edificio)

                (forall (?r1 - tipoRecurso)
                    (<=
                        (necesitaRecursosEdificio ?edificio ?r1)
                        (tenemosRecurso ?r1)
                    )
                )
    )
    :effect
    (   and     ; Tendremos el edificio construido y la entidad en la localización
                (EdificioConstruido ?edif ?l1)
                (EstaEntidadEn ?edif ?l1)

                ; Reducimos los recursos conforme los hemos gastado
                (forall (?r1 - tipoRecurso)
                    (decrease
                        (tenemosRecurso ?r1)
                        (necesitaRecursosEdificio ?edificio ?r1)
                    )
                )

                ; Aumentamos el coste dependiendo del tipo de edificio
                (increase
                    (Coste)
                    (costeEdificio ?edificio)
                )
    )
)

(:action reclutar
    :parameters (?edif - edificio ?uni - unidad ?loc - localizacion ?tipo - tipoUnidad)
    :precondition
    (   and
                ; Comprobamos que no exista la unidad
                (not (exists (?l1 - localizacion)
                        (and
                            (EstaEntidadEn ?uni ?l1)
                        )
                    )
                )

                (esTipoUnidad ?uni ?tipo)
                
                (forall (?r1 - tipoRecurso) ;Tenemos los recursos necesarios
                    (<=
                        (necesitaRecursosUnidad ?tipo ?r1)
                        (tenemosRecurso ?r1)
                    )
                )

                ; Si vamos a construir un VCE debe ser en el centro de mando, si no, en los barracones
                (or
                    (and
                        (esTipoUnidad ?uni VCE)
                        (esTipoEdificio ?edif CentroDeMando)
                        (EdificioConstruido ?edif ?loc)
                    )

                    (and
                        (esTipoEdificio ?edif Barracon)
                        (EdificioConstruido ?edif ?loc)
                    )
                )


    )
    :effect
    (   and
                ; Tendremos una unidad libre en la localización indicada
                (EstaEntidadEn ?uni ?loc)
                (libre ?uni)

                ; Reducimos los recursos conforme los hemos gastado
                (forall (?r1 - tipoRecurso)
                    (decrease
                        (tenemosRecurso ?r1)
                        (necesitaRecursosUnidad ?tipo ?r1)
                    )
                )

                ; Aumentamos el coste dependiendo del tipo de unidad
                (increase
                    (Coste)
                    (costeUnidad ?tipo)
                )
    )
)

(:action recolectar
    :parameters (?recurso - tipoRecurso)
    :precondition
    (   and
                ; Se está extrayendo el recurso
                (estaExtrayendoTipoRecurso ?recurso)

                ; No hemos llegado al máximo permitido
                (<
                    (tenemosRecurso ?recurso)
                    (MaxRecurso ?recurso)
                )
                
    )
    :effect
    (   and
                ; Aumentamos en 10 por cada unidad que esté extrayendo el recurso
                (increase 
                    (tenemosRecurso ?recurso)
                    (*
                        (HayExtrayendo ?recurso)
                        10
                    )
                )

                ; Aumentamos en 5 el coste en tiempo
                (increase
                    (Coste)
                    5
                )
    )
)


)