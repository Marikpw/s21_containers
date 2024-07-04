CC = g++
flags = -Werror -Wall -Wextra -std=c++17
gtest_flag = -lgtest
gcov_flags = -fprofile-arcs -ftest-coverage
valgrind_flags = --log-file="valgrind.txt" --track-origins=yes --trace-children=yes --leak-check=full --leak-resolution=med --show-leak-kinds=all

test_files = ./tests/*.cc
out_file = ./s21_containers

ifeq ($(shell uname -s), Linux)
	open=xdg-open
else
	open=open
endif

all: test

test:
	-rm -f $(out_file)
	$(CC) -g $(flags) $(test_files) -o $(out_file) $(gtest_flag)
	$(out_file)
	
gcov_report:
	-rm -f $(out_file)
	$(CC) $(flags) $(gcov_flags) $(test_files) $(files) -o $(out_file) $(gtest_flag)
	./s21_containers
	lcov --capture --directory . --output-file test.info
	lcov --remove test.info '/usr/*' --output-file test_filtered.info
	genhtml -o report test_filtered.info 
	$(open) report/index.html
	make rm_gcov
	-rm -f *.info

clean:
	-rm -f *.o
	-rm -f *.a
	-rm -f $(out_file)
	-rm -rf report
	-make rm_gcov
	-rm -f valgrind.txt

rebuild:
	make clean
	make all

rm_gcov:
	-rm -f *.gcno	
	-rm -f *.gcda

clang:
	@if [ -f ../materials/linters/.clang-format ]; then \
		cp ../materials/linters/.clang-format ./; \
	fi
	clang-format -i $(shell find . -name '*.cpp' -or -name '*.h')

format_check:
	@if [ -f ../materials/linters/.clang-format ]; then \
		cp ../materials/linters/.clang-format ./; \
	fi
	clang-format -n $(shell find . -name '*.cpp' -or -name '*.h')

valgrind: test
	valgrind $(valgrind_flags) $(out_file)
	cat valgrind.txt
