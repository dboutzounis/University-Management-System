# compile with gcc
CC=g++ # CHANGE TO g++

# Compiler options:
#
# -pg is used for profiling (gprof)
CXXFLAGS = -g -Wall -Werror # CHANGE TO CXXFLAGS

# Linker options:
#
# -lm: link with the math library
LDFLAGS += -lm

# set the name of the executable file to compile here
PROGRAM = main

OBJS = ./src/main.o ./src/person.o ./src/student.o ./src/professor.o ./src/secretary.o ./src/extrafuncs.o

$(PROGRAM): $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) $(LDFLAGS) -o $(PROGRAM)

clean:
	rm -f $(PROGRAM) $(PROGRAM_CPP)  $(OBJS)