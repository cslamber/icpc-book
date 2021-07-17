BOOKPATH := $(BOOKPATH)

.PHONY: run real copy test
.PRECIOUS: pre.cpp .bin/opt .bin/debug

do_python := $(shell test -f main.py && echo -n 'yes')

main.cpp:
	cp ${BOOKPATH}/header.cpp $@

main.py:
	touch $@

ifdef do_python

.bin/debug: main.py
	echo "#!/usr/bin/env python3" > $@
	cat $< >> $@
	chmod +x $@

copy: main.py
	cat $< | xsel -b -i

else

pre.cpp: main.cpp ${BOOKPATH}
	python3 ${BOOKPATH}/build/preprocess.py $< > $@

.bin/debug: pre.cpp
	@mkdir -p .bin
	g++ $< -O0 -g -fsanitize=address -DLOCAL -std=gnu++17 -o $@

run: .bin/debug
	./$<

copy: pre.cpp
	cat $< | xsel -b -i

.bin/opt: pre.cpp
	@mkdir -p .bin
	g++ $< -O2 -g -static -std=gnu++17 -o $@

real: .bin/opt
	time ./$<

endif

test: tests/* .bin/debug
	@for dir in tests/*; do \
		echo "$$dir:" ; \
		diff -w "$$dir/out.txt" <(./.bin/debug < "$$dir/in.txt") --color ; \
	done
