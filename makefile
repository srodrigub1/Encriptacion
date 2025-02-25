# Nombre del compilador
CXX = g++

# Flags del compilador (añadir optimización y activar advertencias)
CXXFLAGS = -Wall -std=c++11

# Nombre del archivo fuente
SRC = encriptacion.cpp

# Nombre del archivo ejecutable
TARGET = encryptor

# Regla por defecto para compilar el ejecutable
all: $(TARGET)
	@echo "Uso del programa:"
	@echo "./encryptor -e <archivo> -o <archivo_encriptado>    Encripta el archivo"
	@echo "./encryptor -d <archivo_encriptado> -o <archivo_desencriptado> Desencripta el archivo"
	@echo "./encryptor -h                               Muestra este mensaje de ayuda"
	@echo "./encryptor -v                               Muestra la versión del programa"

# Regla para compilar y enlazar el código
$(TARGET): $(SRC)
	@$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Regla para limpiar los archivos generados
clean:
	@rm -f $(TARGET)

# Regla para ejecutar el programa
run: $(TARGET)
	@./$(TARGET)

# Regla para mostrar el uso del programa
help:
	@echo "Uso del programa:"
	@echo "./encryptor -e <archivo> -o <archivo_encriptado>    Encripta el archivo"
	@echo "./encryptor -d <archivo_encriptado> -o <archivo_desencriptado> Desencripta el archivo"
	@echo "./encryptor -h                               Muestra este mensaje de ayuda"
	@echo "./encryptor -v                               Muestra la versión del programa"
