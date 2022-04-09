mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir := $(dir $(mkfile_path))
book_dir := ${mkfile_dir}/../

.PHONY: test testone/% copy
.PRECIOUS: .debug .real

.debug: main.cpp
	g++ "$<" -O0 -g -fsanitize=address -DLOCAL -std=gnu++17 -o "$@"

copy: main.cpp
	cat "$<" | xsel -b -i

test: .debug 
	python3 "${book_dir}/suite/manage.py" test "$<" < "$*.test_ini"

testone/%: .debug tests/%/in.txt tests/%/out.txt
