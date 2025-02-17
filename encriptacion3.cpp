#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <getopt.h>
#include <cstdlib>

#define BUFFER_SIZE 1024
#define XOR_KEY 0x5A // Clave de encriptación XOR

// Función para verificar si un archivo es de texto o binario
bool isTextFile(const char* filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error al abrir el archivo para verificación");
        return false;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead = read(fd, buffer, BUFFER_SIZE);
    close(fd);

    if (bytesRead < 0) {
        perror("Error al leer el archivo");
        return false;
    }

    for (ssize_t i = 0; i < bytesRead; ++i) {
        if ((unsigned char)buffer[i] == 0) { // Un byte nulo indica un archivo binario
            return false;
        }
    }
    return true;
}

// Función para encriptar/desencriptar un archivo (XOR reversible)
void encryptDecryptFile(const char* inputFile, const char* outputFile) {
    int inputFd = open(inputFile, O_RDONLY);
    if (inputFd < 0) {
        perror("Error al abrir el archivo de entrada");
        exit(EXIT_FAILURE);
    }

    int outputFd = open(outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outputFd < 0) {
        perror("Error al abrir el archivo de salida");
        close(inputFd);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    while ((bytesRead = read(inputFd, buffer, BUFFER_SIZE)) > 0) {
        for (ssize_t i = 0; i < bytesRead; ++i) {
            buffer[i] ^= XOR_KEY; // Encriptación/Desencriptación XOR
        }
        write(outputFd, buffer, bytesRead);
    }

    close(inputFd);
    close(outputFd);
    std::cout << "Proceso completado: " << outputFile << std::endl;
}

// Función de ayuda
void showHelp() {
    std::cout << "Uso: ./encryptor [opciones] <archivo>\n"
              << "Opciones:\n"
              << "  -e, --encrypt <archivo>   Encripta el archivo\n"
              << "  -d, --decrypt <archivo>   Desencripta el archivo\n"
              << "  -o, --output <archivo>    Especifica el archivo de salida\n"
              << "  -h, --help                Muestra este mensaje\n"
              << "  -v, --version             Muestra la versión\n";
}

int main(int argc, char* argv[]) {
    int opt;
    const char* inputFile = nullptr;
    const char* outputFile = nullptr;
    bool encrypt = false, decrypt = false;

    struct option long_options[] = {
        {"encrypt", required_argument, nullptr, 'e'},
        {"decrypt", required_argument, nullptr, 'd'},
        {"output", required_argument, nullptr, 'o'},
        {"help", no_argument, nullptr, 'h'},
        {"version", no_argument, nullptr, 'v'},
        {nullptr, 0, nullptr, 0}
    };

    while ((opt = getopt_long(argc, argv, "e:d:o:hv", long_options, nullptr)) != -1) {
        switch (opt) {
            case 'e':
                inputFile = optarg;
                encrypt = true;
                break;
            case 'd':
                inputFile = optarg;
                decrypt = true;
                break;
            case 'o':
                outputFile = optarg;
                break;
            case 'h':
                showHelp();
                exit(EXIT_SUCCESS);
            case 'v':
                std::cout << "Encryptor v1.1\n";
                exit(EXIT_SUCCESS);
            default:
                showHelp();
                exit(EXIT_FAILURE);
        }
    }

    // Verifica que se haya proporcionado un archivo
    if (!inputFile) {
        std::cerr << "Error: Debe proporcionar un archivo con -e o -d\n";
        showHelp();
        exit(EXIT_FAILURE);
    }

    // Verifica que no se intenten encriptar y desencriptar al mismo tiempo
    if (encrypt && decrypt) {
        std::cerr << "Error: No puede encriptar y desencriptar al mismo tiempo\n";
        exit(EXIT_FAILURE);
    }

    // Si no se especifica salida, genera una predeterminada
    if (!outputFile) {
        outputFile = encrypt ? "encrypted_output" : "decrypted_output";
    }

    // Determina si es un archivo de texto o binario
    bool isText = isTextFile(inputFile);
    std::cout << "El archivo '" << inputFile << "' es "
              << (isText ? "de texto." : "binario.") << std::endl;

    // Ejecuta el proceso de encriptación/desencriptación
    encryptDecryptFile(inputFile, outputFile);

    return 0;
}
