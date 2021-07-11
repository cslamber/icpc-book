BOOKPATH := $(BOOKPATH)

.PHONY: setup run real copy test
.PRECIOUS: pre.cpp .bin/opt .bin/debug

main.cpp:
	cp ${BOOKPATH}/header.cpp $@

# core
pre.cpp: main.cpp ${BOOKPATH}
	python3 ${BOOKPATH}/build/preprocess.py $< > $@

.bin/debug:: pre.cpp
	@mkdir -p .bin
	g++ $< -O0 -g -fsanitize=address -DLOCAL -std=gnu++17 -o $@

./bin/debug:: main.py
	echo "#!/usr/bin/env python3" > $@
	cat $< > $@
	chmod +x $@

run: .bin/debug
	./$<

test: tests/* .bin/debug
	@for dir in tests/*; do \
		echo "$$dir:" ; \
		diff $$dir/out.txt <(./.bin/debug < $$dir/in.txt) --color ; \
	done

copy: pre.cpp
	cat $< | xsel -b -i

# opt tests
.bin/opt: pre.cpp
	@mkdir -p .bin
	g++ $< -O2 -g -static -std=gnu++17 -o $@

real: .bin/opt
	time ./$<
