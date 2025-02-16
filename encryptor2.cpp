# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Target executable
TARGET = encryptor

# Source files
SRCS = encryptor.cpp

# Object files (automatically generated)
OBJS = $(SRCS:.cpp=.o)

# Default rule
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile each source file into an object file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean up generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Rule to rebuild from scratch
rebuild: clean all

# Custom rule to encrypt a file
encrypt:
	./$(TARGET) -e archivo.txt -o archivo_encriptado.txt

# Custom rule to decrypt a file
decrypt:
	./$(TARGET) -d archivo_encriptado.txt -o archivo_desencriptado.txt

# Custom rule to decrypt the default encrypted output file
decrypt_default:
	./$(TARGET) -d encrypted_output -o archivo_desencriptado.txt

# Rule to display help
help:
	@echo "Makefile options:"
	@echo "  make all                - Build the program (default)"
	@echo "  make clean              - Remove generated files"
	@echo "  make rebuild            - Clean and rebuild the program"
	@echo "  make encrypt            - Encrypt archivo.txt"
	@echo "  make decrypt            - Decrypt archivo_encriptado.txt"
	@echo "  make decrypt_default    - Decrypt encrypted_output"
	@echo "  make help               - Show this help message"

.PHONY: all clean rebuild encrypt decrypt decrypt_default help
