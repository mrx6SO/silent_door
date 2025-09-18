# Makefile para o projeto silent_door
# Compila para Linux (nativo) e Windows (cross-compilation com MinGW)

# --- Compiladores e Ferramentas ---
CC = gcc
WINCC = x86_64-w64-mingw32-gcc

# --- Nomes dos Executáveis ---
TARGET_LINUX = silent_door_linux
TARGET_WINDOWS = silent_door.exe

# --- Arquivos Fonte ---
# Lista de todos os arquivos .c na pasta backdoor/
SRCS = $(wildcard backdoor/*.c)

# --- Flags de Compilação ---
CFLAGS = -Wall -Wextra -Ibackdoor
LDFLAGS_LINUX = -lX11

# --- Alvos Principais ---

# O alvo padrão será compilar para Linux
all: $(TARGET_LINUX)

# Alvo para compilar a versão Linux
linux: $(TARGET_LINUX)

# Alvo para compilar a versão Windows
windows: $(TARGET_WINDOWS)

# --- Regras de Compilação ---

# Regra para compilar o executável Linux
$(TARGET_LINUX): $(SRCS)
	@echo "Compilando para Linux..."
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS_LINUX)
	@echo "Executável Linux '$(TARGET_LINUX)' criado com sucesso."

# Regra para compilar o executável Windows
$(TARGET_WINDOWS): $(SRCS)
	@echo "Cross-compilando para Windows..."
	$(WINCC) $(CFLAGS) -o $@ $^ -lws2_32 -mwindows
	@echo "Executável Windows '$(TARGET_WINDOWS)' criado com sucesso."

# Alvo para limpar os arquivos compilados
clean:
	@echo "Limpando arquivos compilados..."
	rm -f $(TARGET_LINUX) $(TARGET_WINDOWS)
	@echo "Limpeza concluída."

.PHONY: all linux windows clean