# Required variable definitions:
#   VERSION_TAG
#   CONFIG_H
#   PREAMBLE
#   MEMORY_MODEL
#   EXECUTION_MODEL
#   EVALUATOR_PRIMITIVES
#   EXECUTION_MODEL
#   FORTHKIT
#
# Usage
#   $ export FORTHKIT=~/src/forthkit
#   $ cd $FORTHKIT
#   $ export VERSION_TAG=rel-switch-a32-c4-f4-t2-small
#   $ cd interpreters/f79
#   $ source spec/$VERSION_TAG.rc && make all

EVALUATOR_C = ${FORTHKIT}/build/src/evaluator-${VERSION_TAG}.c
EVALUATOR_H = ${FORTHKIT}/build/include/evaluator-${VERSION_TAG}.h
EVALUATOR_O = ${FORTHKIT}/build/lib/evaluator-${VERSION_TAG}.o
INTERPRETER = ${FORTHKIT}/build/bin/interpreter-${VERSION_TAG}
TEST_RUNNER = ${FORTHKIT}/build/bin/test_runner-${VERSION_TAG}

CFLAGS += -include ${CONFIG_H} -include ${EVALUATOR_H}

m4_deps =											 \
	${PREAMBLE} ${MEMORY_MODEL} ${EXECUTION_MODEL}						 \
	${EVALUATOR_PRIMITIVES} ${COMPILED_WORDS}						 \
	$(shell m4 ${FORTHKIT}/interpreters/primitive-dependencies.m4 ${EVALUATOR_PRIMITIVES})	 \
	$(shell m4 ${FORTHKIT}/interpreters/compiled-dependencies.m4 ${COMPILED_WORDS})

${EVALUATOR_C} : ${m4_deps} evaluator.c.m4
	m4								 \
	  --define __preamble=${PREAMBLE}				 \
	  --define __memory_model=${MEMORY_MODEL}			 \
	  --define __execution_model=${EXECUTION_MODEL}			 \
	  --define __evaluator_primitives=${EVALUATOR_PRIMITIVES}	 \
	  --define __compiled_words=${COMPILED_WORDS}			 \
	  evaluator.c.m4 | indent -kr -l96 >$@

${EVALUATOR_H} : ${m4_deps} evaluator.h.m4
	m4								 \
	  --define __preamble=${PREAMBLE}				 \
	  --define __memory_model=${MEMORY_MODEL}			 \
	  --define __execution_model=${EXECUTION_MODEL}			 \
	  --define __evaluator_primitives=${EVALUATOR_PRIMITIVES}	 \
	  --define __compiled_words=${COMPILED_WORDS}			 \
	  evaluator.h.m4 | indent -kr -l96 >$@

${EVALUATOR_O} : ${EVALUATOR_C} ${EVALUATOR_H} bounds.h ${CONFIG_H} debug.h errors.h log.h
	gcc ${CFLAGS} -o ${EVALUATOR_O} -c ${EVALUATOR_C}

${INTERPRETER} : ${EVALUATOR_H} bounds.h ${CONFIG_H} debug.h errors.h log.h
	gcc ${CFLAGS} -o ${INTERPRETER} interpreter.c ${LDFLAGS} ${EVALUATOR_O}

${TEST_RUNNER} : ${EVALUATOR_O} test-runner.c ${CONFIG_H}
	gcc ${CFLAGS} -o ${TEST_RUNNER} test-runner.c ${EVALUATOR_O} ${LDFLAGS}

test_runner : ${TEST_RUNNER}

all : ${EVALUATOR_H} ${EVALUATOR_O} ${INTERPRETER} ${TEST_RUNNER}

.PHONY : all test_runner
