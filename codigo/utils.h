#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

// Cores ANSI
#define RESET   "\033[0m"
#define ORANGE  "\033[38;5;208m"   // Laranja
#define BOLD    "\033[1m"

// Limpa a tela
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Ativa suporte a UTF-8 / acentos no Windows
void enableUTF8() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
}

#endif