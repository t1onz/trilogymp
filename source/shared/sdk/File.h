#include <iostream>
#include <cstring>
#include "SString.h"

#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#include <unistd.h>
#endif


std::string GetLaunchPath() {
    char path[1024];

#ifdef _WIN32
    // No Windows, use GetModuleFileName para obter o caminho do execut�vel
    GetModuleFileName(NULL, path, sizeof(path));
#elif __linux__
    // No Linux, use readlink para obter o caminho do link simb�lico /proc/self/exe
    ssize_t count = readlink("/proc/self/exe", path, sizeof(path));
    if (count != -1) {
        path[count] = '\0';
    }
#endif

    // Normalize o caminho para garantir consist�ncia
    // (substitua barras invertidas por barras normais no Windows)
    for (char& c : path) {
        if (c == '\\') {
            c = '/';
        }
    }

    // Remova o nome do execut�vel do caminho para obter o diret�rio de inicializa��o
    char* lastSlash = strrchr(path, '/');
    if (lastSlash != nullptr) {
        *lastSlash = '\0';
    }

    return std::string();
}
