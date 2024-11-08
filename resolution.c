#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <shellapi.h>

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

int main() {
    // Step 1: Change resolution to 1440x1080
    ChangeResolution(1440, 1080);

    // Step 2: Launch the game
    STARTUPINFO si = {0};
    PROCESS_INFORMATION pi = {0};
    si.cb = sizeof(si);

    LPCSTR gamePath = "E:\\SteamLibrary\\steamapps\\common\\Counter-Strike Global Offensive\\game\\bin\\win64\\cs2.exe";

    if (!CreateProcess(
            NULL,
            (LPSTR)gamePath,
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &si,
            &pi)) {
        printf("Failed to launch the game. Error code: %ld\n", GetLastError());
        RestoreResolution();
        return 1;
    }

    printf("Game launched successfully.\n");

    // Step 3: Wait for the game process to exit
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Step 4: Clean up
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    printf("Game exited. Restoring resolution...\n");

    // Step 5: Restore resolution to 1920x1080
    RestoreResolution();

    return 0;
}
