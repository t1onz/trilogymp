#include "StdInc.h"

BOOL StartGtaProcess()
{
    LPCWSTR lpApplicationName = L"E:\\Games\\GTA San Andreas - Definitive Edition\\Gameface\\Binaries\\Win64\\SanAndreas.exe";
    LPWSTR lpCommandLine = L"";

    STARTUPINFOW si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);

    if (CreateProcessW(
        lpApplicationName,   // Caminho para o execut�vel
        lpCommandLine,       // Comando a ser passado para o processo
        NULL,                // Atributos de seguran�a do processo (padr�o)
        NULL,                // Atributos de seguran�a do thread (padr�o)
        FALSE,               // Heran�a de identificadores do processo e thread (n�o herdar)
        0,                   // Flags de cria��o (padr�o)
        NULL,                // Vari�veis de ambiente do processo pai (herdar)
        NULL,                // Diret�rio inicial do processo (padr�o)
        &si,                 // Informa��es de inicializa��o do processo
        &pi                  // Informa��es sobre o processo criado
    ))
    {
        // Aguarda o t�rmino do processo filho
        WaitForSingleObject(pi.hProcess, INFINITE);

        // Fecha os identificadores do processo e do thread
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        return 0;
    }
    else
    {
        // Se CreateProcessW falhar, imprime uma mensagem de erro
        wprintf(L"Erro %d ao criar o processo: %s\n", GetLastError(), lpApplicationName);
        return 1;
    }
}

int LaunchGame() {
    StartGtaProcess();
    return 0;
}


