# Alunos: Gabriel Henrique de Paula Santos, Marina Valim, Vitor Firmino 
# Projeto Prático - Tratamento de Arquivos e Ordenação em Memória Secundária

# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -Wall -Wextra -std=c++11

# Nome do executável final
EXEC = binario

# Fonte principal
SRC = binario.cpp

# Diretório de subarquivos temporários
SUBDIR = subarquivos

# Regra principal
all: $(EXEC)

# Regra para compilar o programa
$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(SRC)

# Executa o programa
run: $(EXEC)
	./$(EXEC)

# Cria o diretório de subarquivos (caso não exista)
init:
	mkdir -p $(SUBDIR)

# Remove apenas o executável
clean:
	rm -f $(EXEC)

# Remove executável e subarquivos temporários
cleanall: clean
	rm -rf $(SUBDIR)

# Compacta o projeto para entrega (ajuste os nomes)
package:
	tar -czvf grupo_nomes_projeto_pratico.tar.gz $(SRC) Makefile README.txt RELATORIO.pdf