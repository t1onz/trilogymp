#include "Utils.h"
#include "Main.h"
#include "Injector.h"


BOOL RunGameProcess(const SString& ApplicationName, const SString& CommandLine, const SString& CurrentDirectory,
    LPPROCESS_INFORMATION ProcessInformation, DWORD& dwOutError, SString& strOutErrorContext)
{
    STARTUPINFOW startupInfo{};
    startupInfo.cb = sizeof(startupInfo);
    BOOL wasProcessCreated = CreateProcessW(*FromUTF8(ApplicationName), FromUTF8(CommandLine).data(), NULL, NULL, FALSE, 0, nullptr,
        NULL, &startupInfo, ProcessInformation);

    if (wasProcessCreated)
        return true;


    return wasProcessCreated;
}



int LaunchGame()
{

    SString gameExecutable = GetGameExecutable().u8string();
    SString gamePath = GetGamePath();

    // Launch  the game
    PROCESS_INFORMATION piLoadee;
    DWORD dwError;
    SString errorContext;

    if (FALSE == RunGameProcess(gameExecutable, "", gamePath, &piLoadee, dwError, errorContext))
    {
        return 0;
    }

    #ifdef TRILOGY_DEBUG
        SString loaderDllFilename = "core_d.dll";
    #else
        SString loaderDllFilename = "core.dll";
    #endif

    SString launcherPath = PathJoin(GetLaunchPath(), "binaries");
    SString loaderDllPath = PathJoin(launcherPath, loaderDllFilename);

    Injector::Get()->InjectLib(piLoadee.dwProcessId, loaderDllPath);


    if (piLoadee.hProcess)
    {
        DWORD launchStatus;

        for (uint i = 0; i < 20; i++) {
            launchStatus = WaitForSingleObject(piLoadee.hProcess, INFINITE);
            if (launchStatus != WAIT_TIMEOUT)
            {
                TerminateProcess(piLoadee.hProcess, 0);
                break;
            }
        }


    }


    return piLoadee.dwProcessId;
}
