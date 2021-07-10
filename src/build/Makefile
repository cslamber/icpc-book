BOOKPATH := $(BOOKPATH)/src

.PHONY: setup run/% real/% copy/%
.PRECIOUS: pre/% bin/% bin/local_%

setup:
	mkdir -p pre bin

# core
pre/%: % ${BOOKPATH}
	python3 ${BOOKPATH}/build/preprocess.py ${BOOKPATH} < $< > $@

bin/local_%: pre/%.cpp
	g++ $< -O0 -g -fsanitize=address -DLOCAL -std=gnu++17 -o $@

run/%: bin/local_%
	./$<

copy/%: pre/%.cpp
	cat $< | xsel -b -i

# opt tests
bin/%: pre/%.cpp
	g++ $< -O2 -g -static -std=gnu++17 -o $@

real/%: bin/%
	time ./$<

# python
bin/%: pre/%.py
	echo "#!/usr/bin/env python3" > $@
	cat $< > $@
	chmod +x $@

# header, low prec
%.cpp:
	cp ${BOOKPATH}/header.cpp $@
