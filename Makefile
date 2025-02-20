# Variáveis
CC = gcc
CFLAGS = -Wall -fPIC
LDFLAGS = -shared
LIBRARY = libtrace.so
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# Diretórios
LIB_DIR = lib

# Arquivos de origem
SRC_FILES = $(SRC_DIR)/trace.c
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Regras
all: $(OBJ_DIR) $(LIB_DIR) $(LIBRARY)

$(OBJ_DIR):
	mkdir obj

$(LIB_DIR):
	mkdir lib

# Regra para gerar a biblioteca compartilhada
$(LIBRARY): $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $(LIB_DIR)/$@ $^

# Regra para compilar arquivos .c em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Limpeza
clean:
	rm -rf $(OBJ_DIR)/*.o $(LIB_DIR)/$(LIBRARY)

distclean:
	rm -rf $(OBJ_DIR) $(LIB_DIR)

# Instalação (ajustar o destino conforme necessário)
install: $(LIBRARY)
	cp $(LIB_DIR)/$(LIBRARY) /usr/local/lib/
	cp $(INC_DIR)/trace.h /usr/local/include/

# Desinstalação
uninstall:
	rm -f /usr/local/lib/$(LIBRARY)
	rm -f /usr/local/include/trace.h

# Verificação de dependências
deps:
	$(CC) -MM $(SRC_FILES) > $(OBJ_DIR)/dependencias.mk
	include $(OBJ_DIR)/dependencias.mk

