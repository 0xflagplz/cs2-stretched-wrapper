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

BOOL IsCS2Running() {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) {
        return FALSE;
    }

    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(processEntry);

    if (Process32First(snapshot, &processEntry)) {
        do {
            if (_stricmp(processEntry.szExeFile, "cs2.exe") == 0) {
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
    char gamePath[MAX_PATH];
    char username[MAX_PATH];
    DWORD size = MAX_PATH;
    
    if (GetEnvironmentVariable("USERPROFILE", username, size) == 0) {
        printf("Failed to get user profile path. Error code: %lu\n", GetLastError());
        RestoreResolution();
        return 1;
    }
    
    // Construct the full path
    snprintf(gamePath, MAX_PATH, "%s\\Desktop\\Counter-Strike 2.url", username);
    
    HINSTANCE result = ShellExecute(
        NULL,
        "open",
        gamePath,
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
    
    // Wait for CS2 to start and then monitor until it closes
    printf("Waiting for CS2 to start...\n");
    while (!IsCS2Running()) {
        Sleep(1000);  // Check every second
    }
    
    printf("CS2 is running. Waiting for it to close...\n");
    while (IsCS2Running()) {
        Sleep(1000);  // Check every second
    }

    printf("CS2 has closed. Restoring resolution...\n");
    RestoreResolution();

    return 0;
}
