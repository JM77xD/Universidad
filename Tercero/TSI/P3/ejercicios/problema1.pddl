(define (problem Ej1) (:domain Ej1)
(:objects 
    LOC11 LOC12 LOC13 LOC14 LOC21 LOC22 LOC23 LOC24 LOC31 LOC32 LOC33 LOC34 LOC44 - localizacion
    ;Hay un centro de mando, una unidad VCE y dos recursos de mineral
    CentroDeMando1 - tipoCentroDeMando
    VCE1 - tipoVCE
    mineral1 mineral2 - tipoMineral
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

    ;Ponemos los minerales
    (AsignarRecursoLocalizacion mineral1 LOC22)
    (AsignarRecursoLocalizacion mineral2 LOC32)

)

(:goal (and
            ; Tenemos que extraer recursos de tipo mineral, por lo que nuestro objetivo es que exista alguna relación
            ; del tipo "VCE1 está extrayendo algún recurso", puesto que solo tenemos recursos del tipo mineral, estará correcto
            (exists (?x - recurso)
                (estaExtrayendoRecurso VCE1 ?x)
            )
        )
)
)
