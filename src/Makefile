TARGET = tetris_game
TEST_NAME = tetris_test
LIB_NAME = libtetris.a
DIST_DIR = dist

CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
LFLAGS = -lncurses
DLL = -lcheck -lsubunit -lm -pthread -lrt
COVERAGE_FLAGS = --coverage
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

PATH_LIB = ./brick_game/tetris/
PATH_GUI = ./gui/cli/
PATH_OBJ = ./obj/
PATH_INC = ./inc/
PATH_TEST = ./tests/
PATH_COV = ./cov/

SRC_MAIN = $(wildcard *.c)
SRC_LIB = $(wildcard $(PATH_LIB)*.c)
SRC_GUI = $(wildcard $(PATH_GUI)*.c)
SRC_TEST = $(wildcard $(PATH_TEST)*.c)

OBJ_MAIN = $(patsubst %.c, $(PATH_OBJ)%.o, $(SRC_MAIN))
OBJ_LIB = $(patsubst $(PATH_LIB)%.c, $(PATH_OBJ)%.o, $(SRC_LIB))
OBJ_GUI = $(patsubst $(PATH_GUI)%.c, $(PATH_OBJ)%.o, $(SRC_GUI))

OBJ_TEST = $(patsubst $(PATH_TEST)%.c, $(PATH_COV)%.o, $(SRC_TEST))
OBJ_LIB_COV = $(patsubst $(PATH_LIB)%.c, $(PATH_COV)%_gcov.o, $(SRC_LIB))

BUILD_DIR = dist-build

all : install gcov_report dist

install : $(OBJ_MAIN) $(OBJ_GUI) $(OBJ_LIB)
	$(CC) $(CFLAGS) $(OBJ_MAIN) $(OBJ_GUI) $(OBJ_LIB) -o $(TARGET) $(LFLAGS)

test : libtetris_cov.a $(OBJ_TEST)
	$(CC) $(CFLAGS) $(OBJ_TEST) -o $(TEST_NAME) $(COVERAGE_FLAGS) -L. -l:libtetris_cov.a $(DLL)
	./$(TEST_NAME)

libtetris_cov.a : $(PATH_COV)backend_gcov.o $(PATH_COV)fsm_gcov.o
	ar rcs libtetris_cov.a $(PATH_COV)backend_gcov.o $(PATH_COV)fsm_gcov.o

gcov_report : test
	lcov -t "tetris_test" -o test.info -c -d .
	-mkdir report
	genhtml -o report test.info
	open report/index.html

$(PATH_OBJ)%.o : %.c
	-mkdir obj
	$(CC) $(CFLAGS) -c $< -o $@

$(PATH_OBJ)%.o : $(PATH_GUI)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LFLAGS)

$(PATH_OBJ)%.o : $(PATH_LIB)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(PATH_COV)%.o : $(PATH_TEST)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(PATH_COV)%_gcov.o : $(PATH_LIB)%.c
	-mkdir cov
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -c $< -o $@

rebuild : clean install

dvi :
	doxygen Doxyfile
	cd ./docs/latex && make refman.pdf
	
dist : dvi
	@mkdir $(DIST_DIR)
	@cp -r ./brick_game $(DIST_DIR)
	@cp -r ./gui $(DIST_DIR)
	@cp -r ./inc $(DIST_DIR)
	@cp tetris.c $(DIST_DIR)
	@cp Makefile $(DIST_DIR)
	@cp ./docs/latex/refman.pdf $(DIST_DIR)
	tar -cf dist.tar ./dist
	@rm -r $(DIST_DIR)
	
uninstall:
	-rm -rf $(PATH_OBJ)*.o
	-rm -r $(PATH_OBJ)
	-rm -rf $(TARGET)
	-rm -rf score.txt
	-rm -rf $(LIB_NAME)
	-rm -rf *.a
	-rm -r $(PATH_COV)
	-rm -rf test.info
	-rm -r report
	-rm -r cov
	-rm -rf $(TEST_NAME)
	-rm -r ./docs
	-rm -r ./dist
	-rm -rf dist.tar

clean :
	-rm -rf $(PATH_OBJ)*.o
	-rm -r $(PATH_OBJ)
	-rm -rf $(LIB_NAME)
	-rm -rf *.a
	-rm -r $(PATH_COV)

format :
	clang-format -i *.c
	clang-format -i $(PATH_LIB)*.c 
	clang-format -i $(PATH_GUI)*.c
	clang-format -i $(PATH_INC)*.h  
	clang-format -i $(PATH_TEST)*.c  $(PATH_TEST)*.h
	
cppcheck :
	cppcheck --enable=all --suppress=missingIncludeSystem ./

valgrind :
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TEST_NAME)



# install for dvi:

# sudo apt install texlive-base texlive-latex-recommended
# sudo apt-get install doxygen
# sudo apt-get install doxygen-gui
# sudo apt-get install texlive-xetex
# sudo apt install texlive-lang-cyrillic texlive-fonts-recommended texlive-fonts-extra