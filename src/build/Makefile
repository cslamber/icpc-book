BOOKPATH := $(BOOKPATH)
BOOKFILES := $(shell find ${BOOTPATH} -type f)

.PRECIOUS: .bin/opt .bin/debug

main.cpp:
	cp ${BOOKPATH}/header.cpp $@

main.py:
	touch $@

.bin:
	@mkdir $@

use_python := $(shell test -f main.py && echo -n 'yes')

ifdef use_python

PRE := main.py

.bin/debug: main.py .bin
	@mkdir -p .bin
	echo "#!/usr/bin/env python3" > $@
	cat $< >> $@
	chmod +x $@

.bin/opt: .bin/debug .bin
	cp $< $@

else

PRE := pre.cpp

.PRECIOUS: pre.cpp
pre.cpp: main.cpp ${BOOKFILES}
	python3 ${BOOKPATH}/build/preprocess.py $< > $@

.bin/debug: pre.cpp .bin
	g++ $< -O0 -g -fsanitize=address -DLOCAL -std=gnu++17 -o $@

.bin/fuzz: pre.cpp .bin
	g++ $< -O2 -g -fsanitize=address -DLOCAL -DLOCAL_FUZZ -std=gnu++17 -o $@

.PHONY: fuzz
fuzz: .bin/fuzz
	./$<

.bin/opt: pre.cpp .bin
	g++ $< -O3 -std=gnu++17 -o $@

endif

.PHONY: run_debug
run_debug: .bin/debug
	./$<

.PHONY: copy
copy: ${PRE}
	cat $< | xsel -b -i

.PHONY: run_real
run_real: .bin/opt
	time ./$<

tests/%/in.txt: tests/%/gen.py
	python3 $< > $@

tests/%/out.txt:
	touch $@

.PHONY: test
test: tests/*/in.txt .bin/debug
	@for dir in tests/*; do \
		echo "$$dir:" ; \
		diff -w "$$dir/out.txt" <(./.bin/debug < "$$dir/in.txt") --color ; \
	done
