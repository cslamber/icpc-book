mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir := $(dir $(mkfile_path))
book_dir := ${mkfile_dir}/../

.PHONY: run/% copy/%
.PRECIOUS: .pre_%.cpp .dbg_%

.pre_%.cpp: %.cpp
	python3 "${book_dir}/suite/manage.py" pre "${book_dir}" < "$<" > "$@"

.dbg_%: .pre_%.cpp
	g++ "$<" -O0 -g -fsanitize=address -DLOCAL -std=gnu++17 -o "$@"

copy/%: .pre_%.cpp
	cat "$<" | xsel -b -i

run/%: .dbg_% %.test_ini
	python3 "${book_dir}/suite/manage.py" test "$<" < "$*.test_ini"
