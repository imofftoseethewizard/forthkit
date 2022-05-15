# preamble=../preamble.m4 memory_model=./../../address/relocatable.c execution_model=./../../execution-models/thr.m4 evaluator_primitives=./f79-primitives.m4 compiled_words=./f79-compiled-words.m4 make all

CFLAGS = -m32

m4_deps = \
	${preamble} ${memory_model} ${execution_model} \
	${evaluator_primitives} ${compiled_words} \
	$(shell m4 ../primitive-dependencies.m4 ${evaluator_primitives}) \
	$(shell m4 ../compiled-dependencies.m4 ${compiled_words})

evaluator.c evaluator.h : ${m4_deps} evaluator.c.m4 evaluator.h.m4
	m4 \
	  --define __preamble=${preamble} \
	  --define __memory_model=${memory_model} \
	  --define __execution_model=${execution_model} \
	  --define __evaluator_primitives=${evaluator_primitives} \
	  --define __compiled_words=${compiled_words} \
	  $@.m4 | indent -kr -l96 >$@

test-evaluator: evaluator.o test-evaluator.c test-config.h
	gcc ${CFLAGS} -o test-evaluator test-evaluator.c evaluator.o -lreadline

f79 : evaluator.c evaluator.h bounds.h config.h debug.h errors.h log.h
	gcc ${CFLAGS} -o f79 evaluator.c -lreadline

% : %.m4

.PHONY : all

all : f79
