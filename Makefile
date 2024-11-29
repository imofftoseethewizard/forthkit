# Required variable definitions:
#   from shell env (generally)
#     FORTHKIT
#     FAMILY
#     VARIANT_TAG
#     ARCH_TAG
#     ADDRESS_MODEL
#     CONCURRENCY_MODEL
#     EXECUTION_MODEL
#     C_DEFINITIONS
#     COMPILED_WORDS
#     LIBRARY_WORDS
#     PRIMITIVES
#     THREAD_MODEL
#
# Usage
#   $ export FORTHKIT=~/src/forthkit
#   $ export SOURCE=$FORTHKIT/interpreters/f79
#   $ export VARIANT_TAG=rel-switch-a32-c4-l1
#   $ cd $SOURCE
#   $ source spec/$VARIANT_TAG.rc && make all

BUILD   = ${FORTHKIT}/build/${FAMILY}/${VARIANT_TAG}

BIN	= ${BUILD}/${ARCH_TAG}/bin
DOC	= ${BUILD}/doc
INCLUDE = ${BUILD}/include
LIB	= ${BUILD}/${ARCH_TAG}/lib
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
EVALUATOR_DEPS          = ${BUILD}/evaluator.deps
EVALUATOR_O		= ${LIB}/evaluator.o
EVALUATOR_IMAGE		= ${LIB}/evaluator.fi
EVALUATOR_IMAGE_O	= ${LIB}/evaluator.fi.o
INTERPRETER		= ${BIN}/interpreter

CFLAGS += -I${INCLUDE}
CFLAGS += -D "CELL_TYPE=${CELL_TYPE}" -D "DOUBLE_TYPE=${DOUBLE_TYPE}"
CFLAGS += -D LOG=${LOG} -D TRACE=${TRACE} -D VERBOSE=${VERBOSE}
CFLAGS += -D DEBUG=${DEBUG} -D BOUNDS_CHECKING=${BOUNDS_CHECKING}

# build dir and deps file will not exist at first run, `mkdir -p` and `touch`
# ensure this doesn't fail and block make.
DEPS = $(shell mkdir -p ${BUILD} && touch ${EVALUATOR_DEPS} && cat ${EVALUATOR_DEPS})

${BIN} ${BUILD} ${INCLUDE} ${LIB} ${SRC} ${DOC}:
	mkdir -p $@

${EVALUATOR_C} ${EVALUATOR_H} : ${DEPS} ${SRC}
	$(shell \
		. conf/gen-build.rc && \
		bin/fk-gen \
			--target-deps-dir ${BUILD} \
			--target-doc-dir ${DOC} \
			--target-src-dir ${SRC} \
			--target-include-dir ${INCLUDE} \
			--base-name evaluator \
	)

${BOOTSTRAP_EVALUATOR_O} : ${EVALUATOR_C} ${EVALUATOR_H} ${LIB}
	${CC} ${CFLAGS} -D BOOTSTRAP=1 -o $@ -c ${BOOTSTRAP_EVALUATOR_C}

${BOOTSTRAP_INTERPRETER} : ${EVALUATOR_H} ${BOOTSTRAP_EVALUATOR_O} ${BIN} interpreter.c
	${CC} ${CFLAGS} -o $@ interpreter.c ${LDFLAGS} ${BOOTSTRAP_EVALUATOR_O}

${EVALUATOR_O} : ${EVALUATOR_C} ${EVALUATOR_H} ${LIB}
	${CC} ${CFLAGS} -o $@ -c ${EVALUATOR_C}

${BARE_INTERPRETER} : ${EVALUATOR_H} ${EVALUATOR_O} ${BIN} interpreter.c
	${CC} ${CFLAGS} -o $@ interpreter.c ${LDFLAGS} ${EVALUATOR_O}

${INTERPRETER} : ${EVALUATOR_IMAGE_O} ${EVALUATOR_H} ${EVALUATOR_O} ${BIN} interpreter.c
	${CC} ${CFLAGS} -D BUNDLED=1 -o $@ interpreter.c ${LDFLAGS} ${EVALUATOR_IMAGE_O} ${EVALUATOR_O}

${EVALUATOR_IMAGE} : ${BOOTSTRAP_INTERPRETER} ${BUNDLED_WORDS}
	${BOOTSTRAP_INTERPRETER} -q -C $@ ${BUNDLED_WORDS} || echo "$@:" "error: failed to build image"

${EVALUATOR_IMAGE_O} : ${EVALUATOR_IMAGE}
	cd ${LIB} && ld ${EVALUATOR_IMAGE_LDFLAGS} -r -b binary evaluator.fi -o $@

deps : ${BUILD}
	echo ${m4_deps}		| tr ' ' '\n'   >  ${BUILD}/deps.txt
	echo ${BUNDLED_WORDS}	| tr ' ' '\n'   >> ${BUILD}/deps.txt
	ls ${FORTHKIT}/interpreters/*.c		>> ${BUILD}/deps.txt
	ls ${FORTHKIT}/interpreters/*.h		>> ${BUILD}/deps.txt
	ls ${FORTHKIT}/interpreters/*.m4	>> ${BUILD}/deps.txt

all : ${BARE_INTERPRETER} ${BOOTSTRAP_INTERPRETER} ${INTERPRETER}

clean :
	rm -f ${EVALUATOR_H} ${EVALUATOR_O} ${INTERPRETER}

.PHONY : all deps
