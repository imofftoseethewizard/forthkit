( problem: locals are delimited definitions, yet no forth words explicitly )
( mark the end delimiter, deferring this to the ; at the end of the word.  )
( This complicates the definitions of : and ; . Better is to have a three  )
( part syntax with an opening delimiter, a divider between the named new   )
( locals and the code in which they apply, and a ending delimiter.         )

( simplest, conflicts with gforth locals however )
: affine { a b c | a b + c * } ;

( more in line with control structures like begin while repeat )
( conflicts with fiber's end )
: foo
    ' this-shouldn't-work fiber
    let f in
        f step
        f fr>
        f run
    end
;

( conflicts with oof's with )
( conflicts with fiber's end )
: foo
    ' this-shouldn't-work fiber
    with f in
        1 f fsteps !
        f start
        f fr> -1
        f fsteps !
        f start
    end
;

( more forth-like in that : and ; are part of the opening/closing delimiters )
( and -- is part of the stack notation already )
: foo
    ' this-shouldn't-work fiber
    :{ f --
        1 f fsteps !
        f start
        f fr> -1
        f fsteps !
        f start
    };
;

: find-applicable-methods ( s_n ... s_1 &generic -- s_n ... s_1 m_k ... m_1 k )

    let g in
        sp@
        let &call-sig in

            g generic-signature @
            g generic-method-list

            let method-list gen-sig in

                0 ( count )
                method-list sa-items @ ( &method )

                method-list sa-length @ 0
                do
                    let count &method in

                        &method @
                        let m in

                            &call-sig m method-signature-types gen-sig applicable-method?
                            if
                                m
                                count 1+
                            else
                                count
                            then

                            &method cell+
                        end
                    end
                loop

                drop ( &method )
            end
        end
    end
;

: find-applicable-methods ( s_n ... s_1 &generic -- s_n ... s_1 m_k ... m_1 k )

    :{ g --
        sp@

        :{ &call-sig --

            g generic-signature @
            g generic-method-list

            :{ method-list gen-sig --

                0 ( count )
                method-list sa-items @ ( &method )

                method-list sa-length @ 0
                do
                    :{ count &method --

                        &method @
                        :{ m --

                            &call-sig m method-signature-types gen-sig applicable-method?
                            if
                                m
                                count 1+
                            else
                                count
                            then

                            &method cell+
                        };
                    };
                loop

                drop ( &method )
            };
        };
    };
;

: find-applicable-methods ( s_n ... s_1 &generic -- s_n ... s_1 m_k ... m_1 k )

    :{
                              :> g
        sp@                   :> &call-sig

        g generic-signature @ :> gen-sig
        g generic-method-list :> method-list

        0 ( count )
        method-list sa-items @ ( &method )

        method-list sa-length @ 0
        do
            :{
                          :> count
                          :> &method
                &method @ :> m

                &call-sig m method-signature-types gen-sig applicable-method?
                if
                    m
                    count 1+
                else
                    count
                then

                &method cell+
            };
        loop

        drop ( &method )
    };
;

: find-applicable-methods ( s_n ... s_1 &generic -- s_n ... s_1 m_k ... m_1 k )

    :{
                              :> g
        sp@                   :> &call-sig

        g generic-signature @ :> gen-sig
        g generic-method-list :> method-list

        0 ( count )
        method-list sa-items @ ( &method )

        method-list sa-length @ 0
        do
                      :> count
                      :> &method
            &method @ :> m

            &call-sig m method-signature-types gen-sig applicable-method?
            if
                m
                count 1+
            else
                count
            then

            &method cell+
        loop

        drop ( &method )
    };
;

: find-applicable-methods ( s_n ... s_1 &generic -- s_n ... s_1 m_k ... m_1 k )

    locals
        local ga
        sp@ local &call-sig

        g generic-signature @ local gen-sig
        g generic-method-list local method-list

        0 ( count )
        method-list sa-items @ ( &method )

        method-list sa-length @ 0
        do
            local count
            local &method
            &method @ local m

            &call-sig m method-signature-types gen-sig applicable-method?
            if
                m
                count 1+
            else
                count
            then

            &method cell+
        loop

        drop ( &method )

    end
    ( what is a good name for the end word? )
;

:* find-applicable-methods ( s_n ... s_1 &generic -- s_n ... s_1 m_k ... m_1 k )

    local ga
    sp@ local &call-sig

    g generic-signature @ local gen-sig
    g generic-method-list local method-list

    0 ( count )
    method-list sa-items @ ( &method )

    method-list sa-length @ 0
    do
        local count
        local &method
        &method @ local m

        &call-sig m method-signature-types gen-sig applicable-method?
        if
            m
            count 1+
        else
            count
        then

        &method cell+
    loop

    drop ( &method )

*;
