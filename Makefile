SRCDIR := src
TESTDIR := tests
OBJDIR := obj
INCLUDEDIR := include

# Compilador
CXX := g++
# Flags do compilador
CXXFLAGS := -std=c++17 -Wall -Wextra -g
# Flags de inclusão
INCLUDES := -I$(INCLUDEDIR)

# Lista de todos os arquivos em src/ excluindo main.cpp
SRCS := $(filter-out $(SRCDIR)/main.cpp, $(wildcard $(SRCDIR)/*.cpp))

# Lista de todos os arquivos em tests/
TEST_SRCS := $(wildcard $(TESTDIR)/*.cpp)

# Lista de todos os arquivos-objeto correspondentes aos arquivos em src/
OBJS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

# Lista de todos os arquivos-objeto correspondentes aos arquivos em tests/
TEST_OBJS := $(patsubst $(TESTDIR)/%.cpp, $(OBJDIR)/%.o, $(TEST_SRCS))

# Nome do executável do programa principal
PROGRAM := searchEngine.out
# Nome do executável dos testes
TEST_PROGRAM := test.out

# Regras de compilação do programa principal
$(PROGRAM): $(OBJS) $(OBJDIR)/main.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Regras de compilação dos testes
$(TEST_PROGRAM): $(filter-out $(OBJDIR)/main.o, $(OBJS)) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: all test clean

all: $(PROGRAM)

test: $(TEST_PROGRAM)

clean:
	rm -f $(PROGRAM)
	rm -f $(TEST_PROGRAM)
	rm -f $(OBJDIR)/*.o
	
