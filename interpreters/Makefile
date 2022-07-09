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
#   $ export VERSION_TAG=rel-switch-a32-c4-l1
#   $ cd $SOURCE
#   $ source spec/$VERSION_TAG.rc && make all

BUILD   = ${FORTHKIT}/build/${FAMILY}/${VERSION_TAG}

BIN	= ${BUILD}/bin
INCLUDE = ${BUILD}/include
LIB	= ${BUILD}/lib
SRC     = ${BUILD}/src

BARE_INTERPRETER	= ${BIN}/bare-interpreter
BOOTSTRAP_EVALUATOR_C	= ${SRC}/bootstrap-evaluator.c
BOOTSTRAP_EVALUATOR_O	= ${LIB}/bootstrap-evaluator.o
BOOTSTRAP_INTERPRETER	= ${BIN}/bootstrap-interpreter
ERRORS_C                = ${SRC}/errors.c
ERRORS_H                = ${INCLUDE}/errors.h
ERRORS_O		= ${LIB}/errors.o
EVALUATOR_C		= ${SRC}/evaluator.c
EVALUATOR_H		= ${INCLUDE}/evaluator.h
EVALUATOR_O		= ${LIB}/evaluator.o
EVALUATOR_IMAGE		= ${LIB}/evaluator.fi
EVALUATOR_IMAGE_O	= ${LIB}/evaluator.fi.o
INTERPRETER		= ${BIN}/interpreter

CFLAGS +=  -I${INCLUDE}
CFLAGS += -D "CELL_TYPE=${CELL_TYPE}" -D "DOUBLE_TYPE=${DOUBLE_TYPE}" -D "LENGTH_TYPE=${LENGTH_TYPE}"
CFLAGS += -D LOG=${LOG} -D TRACE=${TRACE} -D VERBOSE=${VERBOSE}
CFLAGS += -D DEBUG=${DEBUG} -D BOUNDS_CHECKING=${BOUNDS_CHECKING}

M4PATH = /usr/share/doc/m4/examples/

m4_deps =											\
	${PREAMBLE} ${MEMORY_MODEL} ${EXECUTION_MODEL}						\
	${EVALUATOR_PRIMITIVES} ${COMPILED_WORDS}						\
        ${FORTHKIT}/interpreters/errors.c.m4							\
        ${FORTHKIT}/interpreters/errors.h.m4							\
        ${FORTHKIT}/interpreters/errors.m4							\
        ${FORTHKIT}/interpreters/bootstrap.c.m4							\
	$(shell m4 ${FORTHKIT}/interpreters/primitive-dependencies.m4 ${EVALUATOR_PRIMITIVES})	\
	$(shell m4 ${FORTHKIT}/interpreters/compiled-dependencies.m4 ${COMPILED_WORDS})

${BIN} ${BUILD} ${INCLUDE} ${LIB} ${SRC} :
	mkdir -p $@

${ERRORS_C} : errors.m4 errors.c.m4
	M4PATH=${M4PATH} m4 errors.c.m4 | indent -kr -l128 >$@

${ERRORS_H} : errors.m4 errors.h.m4
	M4PATH=${M4PATH} m4 errors.h.m4 | indent -kr -l96 >$@

${BOOTSTRAP_EVALUATOR_C} : ${m4_deps} evaluator.c.m4 ${SRC}
	M4PATH=${M4PATH} m4						 \
	  --define __preamble=${PREAMBLE}				 \
	  --define __memory_model=${MEMORY_MODEL}			 \
	  --define __execution_model=${EXECUTION_MODEL}			 \
	  --define __evaluator_primitives=${EVALUATOR_PRIMITIVES}	 \
	  --define __compiled_words=${COMPILED_WORDS}			 \
	  --define __include_bootstrap                                   \
	  evaluator.c.m4 | indent -kr -l96 >$@

${EVALUATOR_C} : ${m4_deps} evaluator.c.m4 ${SRC}
	M4PATH=${M4PATH} m4						 \
	  --define __preamble=${PREAMBLE}				 \
	  --define __memory_model=${MEMORY_MODEL}			 \
	  --define __execution_model=${EXECUTION_MODEL}			 \
	  --define __evaluator_primitives=${EVALUATOR_PRIMITIVES}	 \
	  --define __compiled_words=${COMPILED_WORDS}			 \
	  evaluator.c.m4 | indent -kr -l96 >$@

${EVALUATOR_H} : ${m4_deps} evaluator.h.m4 ${INCLUDE} bounds.h log.h
	M4PATH=${M4PATH} m4						 \
	  --define __evaluator_family_name=${EVALUATOR_FAMILY_NAME}	 \
	  --define __preamble=${PREAMBLE}				 \
	  --define __memory_model=${MEMORY_MODEL}			 \
	  --define __execution_model=${EXECUTION_MODEL}			 \
	  --define __evaluator_primitives=${EVALUATOR_PRIMITIVES}	 \
	  --define __compiled_words=${COMPILED_WORDS}			 \
	  evaluator.h.m4 | indent -kr -l96 >$@

${BOOTSTRAP_EVALUATOR_O} : ${BOOTSTRAP_EVALUATOR_C} ${EVALUATOR_H} ${LIB}
	${CC} ${CFLAGS} -o $@ -c ${BOOTSTRAP_EVALUATOR_C}

${BOOTSTRAP_INTERPRETER} : ${ERRORS_H} ${ERRORS_O} ${EVALUATOR_H} ${BOOTSTRAP_EVALUATOR_O} ${BIN} interpreter.c
	${CC} ${CFLAGS} -o $@ interpreter.c ${LDFLAGS} ${ERRORS_O} ${BOOTSTRAP_EVALUATOR_O}

${ERRORS_O} : ${ERRORS_C} ${ERRORS_H} ${LIB}
	${CC} ${CFLAGS} -o $@ -c ${ERRORS_C}

${EVALUATOR_O} : ${EVALUATOR_C} ${EVALUATOR_H} ${LIB}
	${CC} ${CFLAGS} -o $@ -c ${EVALUATOR_C}

${BARE_INTERPRETER} : ${ERRORS_H} ${ERRORS_O} ${EVALUATOR_H} ${EVALUATOR_O} ${BIN} interpreter.c
	${CC} ${CFLAGS} -o $@ interpreter.c ${LDFLAGS} ${ERRORS_O} ${EVALUATOR_O}

${INTERPRETER} : ${ERRORS_H} ${ERRORS_O} ${EVALUATOR_IMAGE_O} ${EVALUATOR_H} ${EVALUATOR_O} ${BIN} interpreter.c
	${CC} ${CFLAGS} -D BUNDLED=1 -o $@ interpreter.c ${LDFLAGS} ${ERRORS_O} ${EVALUATOR_IMAGE_O} ${EVALUATOR_O}

${EVALUATOR_IMAGE} : ${BOOTSTRAP_INTERPRETER}
	${BOOTSTRAP_INTERPRETER} -q -C $@ ${BUNDLED_WORDS}

${EVALUATOR_IMAGE_O} : ${EVALUATOR_IMAGE}
	cd ${LIB} && ld ${EVALUATOR_IMAGE_LDFLAGS} -r -b binary evaluator.fi -o $@

deps : ${BUILD}
	echo ${m4_deps} | tr ' ' '\n'    >  ${BUILD}/deps.txt
	ls ${FORTHKIT}/interpreters/*.c  >> ${BUILD}/deps.txt
	ls ${FORTHKIT}/interpreters/*.h  >> ${BUILD}/deps.txt
	ls ${FORTHKIT}/interpreters/*.m4 >> ${BUILD}/deps.txt

all : ${BARE_INTERPRETER} ${BOOTSTRAP_INTERPRETER} ${INTERPRETER}

clean :
	rm -f ${EVALUATOR_H} ${EVALUATOR_O} ${INTERPRETER}

.PHONY : all deps
