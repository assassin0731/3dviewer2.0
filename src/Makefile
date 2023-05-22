UNAME:=$(shell uname -s)
ifeq ($(UNAME),Linux)
	LFLAGS=-lgtest -lsubunit -lrt -lm -lpthread
	LEAK=valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file="leak.log"
endif
ifeq ($(UNAME),Darwin)
	LFLAGS=-lgtest
	LEAK=leaks -quiet -atExit --
endif
CFLAGS=-std=c++17 # -Wall -Werror -Wextra 
GFLAGS=-fprofile-arcs -ftest-coverage
SOURCES=Model/facade.cc Model/obj_model.cc Model/command.cc Model/geometry.cc Matrix/s21_matrix_oop.cc Matrix/operators.cc Matrix/help_functions.cc

all: clean s21_viewer gcov_report dist clean

style:
	clang-format -google -n C-files/*.c C-files/*.h Qt-files/*.cpp Qt-files/*.h *.c

style_force:
	clang-format -i C-files/*.c C-files/*.h Qt-files/*.cpp Qt-files/*.h *.c

s21_viewer: clean
	g++ $(CFLAGS) -c $(SOURCES)
	ar rc s21_viewer.a *.o
	ranlib s21_viewer.a
	rm -f *.o

build: clean
	mkdir ../build/
	cp Viewer3.pro ../build/
	cd ../build/; qmake Viewer3.pro
	make -C ../build/

install: build
	mkdir 3DViewer
	cp -rf ../build/Viewer3.app 3DViewer
	cp document1.pdf 3DViewer
	make clean

uninstall:
	rm -rf 3DViewer

dvi:
	texi2dvi document.tex
	dvipdfmx document.dvi

dist: uninstall install
	tar -zcvf Viewer_Archive.tar 3DViewer

gcov_report: clean
	g++ $(GFLAGS) $(CFLAGS) $(SOURCES) test.cc $(LFLAGS) -o test
	./test
	lcov -no-external -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html
	
test: s21_viewer
	g++ $(CFLAGS) test.cc s21_viewer.a -L. $(LFLAGS) -o test
	./test

leaks: test
	CK_FORK=no $(LEAK) ./test > leak.log
	bash test_leak.sh

rebuild: clean gcov_report

clean:
	rm -f test s21_viewer.a *.gc* test.info log.xml test.log leak.log
	rm -f -rf report
	rm -f document.aux document.log document.out document.dvi document.pdf document.out.ps
	rm -rf ../build
	rm -f Viewer_Archive.tar