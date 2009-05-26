a some stuff
$(set:hello=Greetings)
--->$(hello)<---

$(hello) some more
$(ifset:hello:Hello is set.)
$(ifset:!igloo:Igloo is not set.)
$(set:forval=four;five;six)
$(for:;:one;two;three: >%arg%< )$(for:;:$forval: >%arg%< )
$(if:$hello=Greetings: Hello is set to Greetings.)
$(if:$hello!=Greetings: ERROR!)
$(if:$hello!=Fred: Hello is not set to fred)
$(include:template.x)

$(set:docentry=1.2.3)
$(for:.:$docentry:$(print:%arg%
)$(silent:
		    $(ifset:parent:$(set:parent=$(parent).%arg%)
                                   $(set:indent=$(indent)#))
	            $(else:$(set:parent=%arg%)$(set:indent=#))
)$(indent)$(if:$docentry!=$parent:[$(parent)]<%arg%>
)$(else:<%arg%>))
