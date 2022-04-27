evaluator.c evaluator.h : % : %.m4
	m4 \
	  --define __memory_model=${memory_model} \
	  --define __execution_model=${execution_model} \
	  --define __evaluator_primitives=${evaluator_primitives} \
	  --define __compiled_words=${compiled_words} \
	  $< | indent -kr -l96 > $@
