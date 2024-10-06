CC = gcc -std=c++17 -g
FLAGS := -Wall -Werror -Wextra
LDFLAGS := -lgtest_main -lgtest -lstdc++ -lm
OS = $(shell uname)

SRC_QUEUE_TEST = ./tests/tests_queue.cpp
SRC_MAP_TEST = ./tests/tests_map.cpp
SRC_SET_TEST = ./tests/tests_set.cpp
SRC_MULTISET_TEST = ./tests/tests_multiset.cpp
SRC_STACK_TEST = ./tests/tests_stack.cpp
SRC_ARRAY_TEST = ./tests/tests_array.cpp
SRC_VECTOR_TEST = ./tests/tests_vector.cpp
SRC_LIST_TEST = ./tests/tests_list.cpp
SRC_MAIN_TEST = ./tests/tests_main.cpp


OBJ_QUEUE_TEST = ./tests/tests_queue.o
OBJ_MAP_TEST = ./tests/tests_map.o
OBJ_SET_TEST = ./tests/tests_set.o
OBJ_MULTISET_TEST = ./tests/tests_multiset.o
OBJ_STACK_TEST = ./tests/tests_stack.o
OBJ_ARRAY_TEST = ./tests/tests_array.o
OBJ_VECTOR_TEST = ./tests/tests_vector.o
OBJ_LIST_TEST = ./tests/tests_list.o
OBJ_MAIN_TEST = ./tests/tests_main.o

# Build object files
%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

ifeq ($(OS), Linux)
    OPEN_REPORT += xdg-open
    LDFLAGS += -lm
endif

ifeq ($(OS), Darwin)
    OPEN_REPORT += open
endif

all: clean test

test: $(OBJ_QUEUE_TEST) $(OBJ_MAP_TEST) $(OBJ_SET_TEST) $(OBJ_MULTISET_TEST) $(OBJ_STACK_TEST) $(OBJ_ARRAY_TEST) $(OBJ_VECTOR_TEST) $(OBJ_LIST_TEST) $(OBJ_MAIN_TEST)
	@$(CC) $(FLAGS) $(OBJ_QUEUE_TEST) $(OBJ_MAP_TEST) $(OBJ_SET_TEST) $(OBJ_MULTISET_TEST) $(OBJ_STACK_TEST) $(OBJ_ARRAY_TEST) $(OBJ_VECTOR_TEST) $(OBJ_LIST_TEST) $(OBJ_MAIN_TEST) $(LDFLAGS) -o test && ./test
	@rm -f $(OBJ_QUEUE_TEST) $(OBJ_MAP_TEST) $(OBJ_SET_TEST) $(OBJ_MULTISET_TEST) $(OBJ_STACK_TEST) $(OBJ_ARRAY_TEST) $(OBJ_MAIN_TEST) $(OBJ_VECTOR_TEST) $(OBJ_LIST_TEST)

test_list:
	@$(CC) $(CFLAGS) tests/tests_list.cpp $(LDFLAGS) -o test && ./test
clangdo:
	@cp ../materials/linters/.clang-format .clang-format
	clang-format -i *.h containers/*.h containersplus/*.h tests/*.cpp
	@rm .clang-format

clangcheck:
	@cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.h containers/*.h containersplus/*.h tests/*.cpp
	@rm .clang-format

valgrind: test
	valgrind --tool=memcheck --leak-check=yes ./test

clean:
	@rm -rf ./test ./tests/*.o
