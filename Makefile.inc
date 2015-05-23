BASE=/home/oddzod/Projects/Automata
BOOST=$(BASE)/lib/boost

DEBUG=-g
#DEBUG=

CC=g++
CFLAGS=-std=c++11 -Wall -I $(BOOST)

LD=g++
LDFLAGS= -L$(BASE)/bin/lib -L $(BOOST)/bin/lib



