#
# Makefile
# zhangyule, 2017-06-08 12:18
#

FLAGS=-g -Wall -std=c++11 -lglog -lgflags -lgtest -lpthread
CC=g++

all: object_pool_test
	@echo "Makefile needs your attention"


# vim:ft=make
#
#
object_pool_test: ./object_pool.h ./object_pool_test.cc test.cc
	${CC} -o object_pool_test ./test.cc ./object_pool_test.cc ${FLAGS}

parser_test: ./graph_token.h ./graph_token_test.cc test.cc
	${CC} -o parser_test ./graph_token_test.cc test.cc ${FLAGS}
