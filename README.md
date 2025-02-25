# Encriptador XOR en C++

Este es un encriptador/desencriptador XOR desarrollado en C++ que utiliza llamadas al sistema. El encriptador permite encriptar y desencriptar archivos de texto o binarios utilizando una clave XOR.

## Requisitos

Para compilar y ejecutar este programa, necesitarás:
- Un compilador de C++ (como `g++`)
- Sistema operativo basado en UNIX (como Linux o macOS)

## Compilación

Para compilar el código, utiliza el siguiente comando:

```sh
g++ -o encryptor encryptor.cpp
```

## Uso

El programa soporta varias opciones de línea de comandos para encriptar y desencriptar archivos. A continuación se muestra cómo utilizar el programa:

```sh
./encryptor [opciones] <archivo>
```

### Opciones

- `-e, --encrypt <archivo>`: Encripta el archivo especificado
- `-d, --decrypt <archivo>`: Desencripta el archivo especificado
- `-o, --output <archivo>`: Especifica el archivo de salida
- `-h, --help`: Muestra el mensaje de ayuda
- `-v, --version`: Muestra la versión del programa

### Ejemplos

1. Encriptar un archivo:

```sh
./encryptor -e archivo.txt -o archivo_encriptado.txt
```

2. Desencriptar un archivo:

```sh
./encryptor -d archivo_encriptado.txt -o archivo_desencriptado.txt
```

### Notas

- El programa utiliza una clave XOR definida en el código (`#define XOR_KEY 0x5A`).

- ![image](https://github.com/user-attachments/assets/cb343bf5-7013-41fe-a7f4-9a92cdc7c6da)

- La encriptación XOR es reversible, por lo que el mismo programa y la misma clave se utilizan para encriptar y desencriptar.

## Verificación de tipo de archivo

El programa también verifica si el archivo es de texto o binario. Un archivo de texto no debe contener bytes nulos (`0x00`).

## Versiones

- `v1.1`: Versión actual del encriptador.

