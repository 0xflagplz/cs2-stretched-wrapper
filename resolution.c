#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <shellapi.h>
#include <tlhelp32.h>

void ChangeResolution(int width, int height) {
    DEVMODE devMode;
    ZeroMemory(&devMode, sizeof(devMode));
    devMode.dmSize = sizeof(devMode);
    devMode.dmPelsWidth = width;
    devMode.dmPelsHeight = height;
    devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

    LONG result = ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);
    if (result != DISP_CHANGE_SUCCESSFUL) {
        printf("Failed to change resolution to %dx%d. Error code: %ld\n", width, height, result);
        exit(1);
    }
    printf("Resolution changed to %dx%d.\n", width, height);
}

void RestoreResolution() {
    DEVMODE devMode;
    ZeroMemory(&devMode, sizeof(devMode));
    devMode.dmSize = sizeof(devMode);
    devMode.dmPelsWidth = 1920;
    devMode.dmPelsHeight = 1080;
    devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

    LONG result = ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);
    if (result != DISP_CHANGE_SUCCESSFUL) {
        printf("Failed to restore resolution to 1920x1080. Error code: %ld\n", result);
    } else {
        printf("Resolution restored to 1920x1080.\n");
    }
}

BOOL IsSteamRunning() {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) {
        return FALSE;
    }

    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(processEntry);

    if (Process32First(snapshot, &processEntry)) {
        do {
            if (_stricmp(processEntry.szExeFile, "steam.exe") == 0) {
                CloseHandle(snapshot);
                return TRUE;
            }
        } while (Process32Next(snapshot, &processEntry));
    }

    CloseHandle(snapshot);
    return FALSE;
}

int main() {
    // Check if Steam is running first
    if (!IsSteamRunning()) {
        printf("Steam is not running. Please start Steam first.\n");
        return 1;
    }

    // Step 1: Change resolution to 1440x1080
    ChangeResolution(1440, 1080);

    // Step 2: Launch the game using the URL shortcut
    HINSTANCE result = ShellExecute(
        NULL,
        "open",
        "C:\\Users\\<username>\\Desktop\\Counter-Strike 2.url",
        NULL,
        NULL,
        SW_SHOW
    );

    if ((intptr_t)result <= 32) {  // ShellExecute returns a value <= 32 on failure
        printf("Failed to launch the game. Error code: %d\n", (int)(intptr_t)result);
        RestoreResolution();
        return 1;
    }

    printf("Game launched successfully.\n");
    
    // Give the game some time to start
    Sleep(5000);  // Wait 5 seconds

    printf("Restoring resolution...\n");

    // Step 3: Restore resolution to 1920x1080
    RestoreResolution();

    return 0;
}
