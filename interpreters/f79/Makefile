# Required variable definitions:
#   from shell env (generally)
#     FORTHKIT
#     SOURCE
#     VERSION_TAG
#   from spec file
#     CONFIG_H
#     PREAMBLE
#     MEMORY_MODEL
#     EXECUTION_MODEL
#     EVALUATOR_PRIMITIVES
#     EXECUTION_MODEL
#
# Usage
#   $ export FORTHKIT=~/src/forthkit
#   $ export SOURCE=$FORTHKIT/interpreters/f79
#   $ export VERSION_TAG=rel-switch-a32-c4
#   $ cd $SOURCE
#   $ source spec/$VERSION_TAG.rc && make all

BUILD   = ${FORTHKIT}/build/${VERSION_TAG}

BIN	= ${BUILD}/bin
INCLUDE = ${BUILD}/include
LIB	= ${BUILD}/lib
SRC     = ${BUILD}/src

EVALUATOR_C = ${SRC}/evaluator.c
EVALUATOR_H = ${INCLUDE}/evaluator.h
EVALUATOR_O = ${LIB}/evaluator.o
INTERPRETER = ${BIN}/interpreter
TEST_RUNNER = ${BIN}/test_runner

CFLAGS += -include ${CONFIG_H} -I${SOURCE} -I${INCLUDE}

m4_deps =											 \
	${PREAMBLE} ${MEMORY_MODEL} ${EXECUTION_MODEL}						 \
	${EVALUATOR_PRIMITIVES} ${COMPILED_WORDS}						 \
	$(shell m4 ${FORTHKIT}/interpreters/primitive-dependencies.m4 ${EVALUATOR_PRIMITIVES})	 \
	$(shell m4 ${FORTHKIT}/interpreters/compiled-dependencies.m4 ${COMPILED_WORDS})

${BIN} ${INCLUDE} ${LIB} ${SRC} :
	mkdir -p $@

${EVALUATOR_C} : ${m4_deps} evaluator.c.m4 ${SRC}
	m4								 \
	  --define __preamble=${PREAMBLE}				 \
	  --define __memory_model=${MEMORY_MODEL}			 \
	  --define __execution_model=${EXECUTION_MODEL}			 \
	  --define __evaluator_primitives=${EVALUATOR_PRIMITIVES}	 \
	  --define __compiled_words=${COMPILED_WORDS}			 \
	  evaluator.c.m4 | indent -kr -l96 >$@

${EVALUATOR_H} : ${m4_deps} evaluator.h.m4 ${INCLUDE}
	m4								 \
	  --define __preamble=${PREAMBLE}				 \
	  --define __memory_model=${MEMORY_MODEL}			 \
	  --define __execution_model=${EXECUTION_MODEL}			 \
	  --define __evaluator_primitives=${EVALUATOR_PRIMITIVES}	 \
	  --define __compiled_words=${COMPILED_WORDS}			 \
	  evaluator.h.m4 | indent -kr -l96 >$@

${EVALUATOR_O} : ${EVALUATOR_C} ${EVALUATOR_H} bounds.h ${CONFIG_H} debug.h errors.h log.h ${LIB}
	gcc ${CFLAGS} -o ${EVALUATOR_O} -c ${EVALUATOR_C}

${INTERPRETER} : ${EVALUATOR_H} ${CONFIG_H} ${BIN}
	gcc ${CFLAGS} -o ${INTERPRETER} interpreter.c ${LDFLAGS} ${EVALUATOR_O}

${TEST_RUNNER} : ${EVALUATOR_O} test-runner.c ${CONFIG_H} ${BIN}
	gcc ${CFLAGS} -o ${TEST_RUNNER} test-runner.c ${EVALUATOR_O} ${LDFLAGS}

test_runner : ${TEST_RUNNER}

all : ${EVALUATOR_H} ${EVALUATOR_O} ${INTERPRETER} ${TEST_RUNNER}

.PHONY : all test_runner
