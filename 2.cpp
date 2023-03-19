#include <windows.h>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

using namespace std;

// Define the sequence of coordinates
int coords1[][2] = {
    {100, 100},
    {200, 200},
    {300, 300},
    {400, 400},
    {500, 500},
};

// Define another sequence of coordinates
int coords2[][2] = {
    {600, 600},
    {700, 700},
    {800, 800},
    {900, 900},
    {1000, 1000},
};

// Define a coordinates table named "ak"
double ak[][2] = {
    {0.000000, -2.257792},
    {0.323242, -2.300758},
    {0.649593, -2.299759},
    {0.848786, -2.259034},
    {1.075408, -2.323947},
    {1.268491, -2.215956},
    {1.330963, -2.236556},
    {1.336833, -2.218203},
    {1.505516, -2.143454},
    {1.504423, -2.233091},
    {1.442116, -2.270194},
    {1.478543, -2.204318},
    {1.392874, -2.165817},
    {1.480824, -2.177887},
    {1.597069, -2.270915},
    {1.449996, -2.145893},
    {1.369179, -2.270450},
    {1.582363, -2.298334},
    {1.516872, -2.235066},
    {1.498249, -2.238401},
    {1.465769, -2.331642},
    {1.564812, -2.242621},
    {1.517519, -2.303052},
    {1.422433, -2.211946},
    {1.553195, -2.248043},
    {1.510463, -2.285327},
    {1.553878, -2.240047},
    {1.520380, -2.221839},
    {1.553878, -2.240047},
    {1.553195, -2.248043},
};

// Define the sensitivity and smoothing percentage
double sensitivity = 1.0;
double smoothing = 0.5;

// Define a function to smooth the mouse movement based on the smoothing percentage
void smoothMouse(double targetX, double targetY) {
double currentX, currentY;
GetCursorPos((POINT*)&currentX); // Get the current mouse position
double deltaX = targetX - currentX;
double deltaY = targetY - currentY;
for (double i = 0.0; i <= 1.0; i += smoothing) {
double smoothedX = currentX + deltaX * i;
double smoothedY = currentY + deltaY * i;
moveMouse(smoothedX, smoothedY); 

// Move the mouse to the smoothed coordinates
Sleep(10); 
// Wait for 10 milliseconds before moving the mouse again
}
moveMouse(targetX, targetY); 
// Move the mouse to the final coordinates
}
int main() {

// Initialize ImGui and the DirectX 11 renderer
ImGui::CreateContext();
ImGuiIO& io = ImGui::GetIO(); (void)io;
ImGui_ImplWin32_Init(GetActiveWindow());
ImGui_ImplDX11_Init(device, context);
bool done = false;
while (!done) {
    MSG msg;
    if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        if (msg.message == WM_QUIT) {
            done = true;
        }
    } else {
        // Get the current time in milliseconds
        DWORD currentTime = GetTickCount();

        // Move the mouse to the coordinates in sequence
        for (int i = 0; i < 5; i++) {
            double x = coords1[i][0];
            double y = coords1[i][1];
            smoothMouse(x, y);
            Sleep(500);
        }

        // Move the mouse to the other sequence of coordinates
        for (int i = 0; i < 5; i++) {
            double x = coords2[i][0];
            double y = coords2[i][1];
            smoothMouse(x, y);
            Sleep(500);
        }

        // Move the mouse to the "ak" coordinates table with smoothing
        for (int i = 0; i < sizeof(ak)/sizeof(ak[0]); i++) {
            double x = ak[i][0];
            double y = ak[i][1];
            smoothMouse(x, y);
            Sleep(50);
        }

        // Get the elapsed time in milliseconds
        DWORD elapsedTime = GetTickCount() - currentTime;

        // Calculate the time to wait before repeating the sequence
        DWORD waitTime = max(0, (int)(1000 - elapsedTime));
        Sleep(waitTime);
    }
}

// Clean up ImGui and the DirectX 11 renderer
ImGui_ImplDX11_Shutdown();
ImGui_ImplWin32_Shutdown();
ImGui::DestroyContext();
return 0;
}
