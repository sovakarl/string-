GCC = gcc -Wall -Werror -Wextra -std=c11
TESTFLAGS = -lcheck
RM = rm -rf
CP= cp -R
CLF = clang-format
OCAT = -o
.C = *.c

all: s21_string.a

s21_string.a:
	$(GCC) -c $(.C)
	ar rc s21_string.a *.o
	mkdir binary_files
	mv *.o binary_files

test: s21_string.a
	$(GCC) $(TESTFLAGS) -I/Users/sheriffl/.brew/include -L/Users/sheriffl/.brew/lib old_test/s21_test.c s21_string.a -o s21_string_test
	./s21_string_test

clean:
	$(RM) binary_files s21_string s21_string_test gcovreport *.a *.o *.gcno *.gcda *.info binary_files report

clang:
	$(CP) ../materials/linters/.$(CLF) .$(CLF)
	$(CLF) -n *.c *.h
	$(CLF) -i *.c *.h
	$(RM) .$(CLF)

gcov_report:
	$(GCC) --coverage -lcheck -I/Users/sheriffl/.brew/include -L/Users/sheriffl/.brew/lib $(.C) old_test/s21_test.c -o gcovreport \
	`pkg-config --cflags --libs check`
	./gcovreport
	lcov -t "gcovreport" -o gcovreport.info -c -d .
	genhtml -o report gcovreport.info
	open report/index.html
	