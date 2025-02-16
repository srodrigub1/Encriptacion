#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <getopt.h>

#define BUFFER_SIZE 1024
#define XOR_KEY 0x5A // Clave de encriptación simple XOR

void encryptFile(const char* inputFile, const char* outputFile) {
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
            buffer[i] ^= XOR_KEY; // Encriptación XOR
        }
        write(outputFd, buffer, bytesRead);
    }

    close(inputFd);
    close(outputFd);
    std::cout << "Archivo encriptado: " << outputFile << std::endl;
}

void decryptFile(const char* inputFile, const char* outputFile) {
    // La desencriptación XOR es idéntica a la encriptación XOR
    encryptFile(inputFile, outputFile);
}

void showHelp() {
    std::cout << "Uso: ./encryptor [opciones]\n"
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
    const char* outputFile = "output_file";
    bool encrypt = false;
    bool decrypt = false;

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
                std::cout << "Encryptor v1.0\n";
                exit(EXIT_SUCCESS);
            default:
                showHelp();
                exit(EXIT_FAILURE);
        }
    }

    if (encrypt && decrypt) {
        std::cerr << "Error: No se puede encriptar y desencriptar al mismo tiempo.\n";
        showHelp();
        exit(EXIT_FAILURE);
    }

    if (encrypt) {
        encryptFile(inputFile, outputFile);
    } else if (decrypt) {
        decryptFile(inputFile, outputFile);
    } else {
        showHelp();
    }

    return 0;
}
