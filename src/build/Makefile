BOOKPATH := ${BOOKPATH}

.PHONY: setup run/% real/% copy/%
.PRECIOUS: pre/% bin/% bin/local_%

setup:
	mkdir -p pre bin

pre/%: % $(BOOKPATH)
	python3 $(BOOKPATH)/build/includer.py $(BOOKPATH) < $< > $@

bin/local_%: pre/%.cpp
	g++ $< -O0 -g -fsanitize=address -DLOCAL -std=c++17 -o $@

bin/%: pre/%.cpp
	g++ $< -O2 -std=c++17 -o $@

bin/%: pre/%.py
	echo "#!/usr/bin/env python3" > $@
	cat $< > $@
	chmod +x $@

copy/%: pre/%.cpp
	cat $< | xsel -b -i

%.cpp:
	cp $(BOOKPATH)/header.cpp $@

run/%: bin/local_%
	./$<

real/%: bin/%
	time ./$<
