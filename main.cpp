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

// Define the sensitivity
double sensitivity = 1.0;

// Define the smoothing percentage
double smoothingPercent = 0.0;

// Define a function to move the mouse to the given coordinates with smoothing
void moveMouseWithSmoothing(double x, double y) {
    double scaledX = x * sensitivity * 65535 / GetSystemMetrics(SM_CXSCREEN);
    double scaledY = y * sensitivity * 65535 / GetSystemMetrics(SM_CYSCREEN);
    double dx = scaledX - GetSystemMetrics(SM_CXSCREEN) / 2.0;
    double dy = scaledY - GetSystemMetrics(SM_CYSCREEN) / 2.0;
    double px = GetSystemMetrics(SM_CXSCREEN) / 2.0;
    double py = GetSystemMetrics(SM_CYSCREEN) / 2.0;
    double stepX = dx * smoothingPercent / 100.0;
    double stepY = dy * smoothingPercent /

// Define the sensitivity and smoothing percentage
double sensitivity = 1.0;
double smoothing = 0.5;

// Define a function to smooth the mouse movement based on the smoothing percentage
void smoothMove(double targetX, double targetY) {
double currentX, currentY;
POINT cursorPos;
GetCursorPos(&cursorPos);
currentX = cursorPos.x;
currentY = cursorPos.y;
double diffX = targetX - currentX;
double diffY = targetY - currentY;
double totalDistance = sqrt(pow(diffX, 2) + pow(diffY, 2));
double steps = totalDistance * smoothing;

double stepX = diffX / steps;
double stepY = diffY / steps;

for (int i = 1; i <= steps; i++) {
    double nextX = currentX + stepX * i;
    double nextY = currentY + stepY * i;
    moveMouse(nextX, nextY);
    Sleep(1);
}

// Move the mouse to the final target position
moveMouse(targetX, targetY);
}
int main(int argc, char** argv) {
// Initialize the GUI
HWND hwnd = GetForegroundWindow();
ID3D11Device* device = NULL;
ID3D11DeviceContext* context = NULL;
ImGui_ImplWin32_Init(hwnd);
ImGui_ImplDX11_Init(device, context);
ImGui::StyleColorsDark();
// Main loop
while (true) {
// Start the GUI frame
ImGui_ImplDX11_NewFrame();
ImGui_ImplWin32_NewFrame();
ImGui::NewFrame();

// Add a checkbox for the ak coordinate table
static bool isAkEnabled = false;
ImGui::Checkbox("AK", &isAkEnabled);

// Add a slider for the sensitivity
ImGui::SliderDouble("Sensitivity", &sensitivity, 0.1, 2.0);

// Add a slider for the smoothing percentage
ImGui::SliderDouble("Smoothing", &smoothing, 0.0, 1.0);

// Show the AK coordinate table if the checkbox is checked
if (isAkEnabled) {
    ImGui::Begin("AK Table");
    ImGui::Columns(2, "AK");
    ImGui::Text("X");
    ImGui::NextColumn();
    ImGui::Text("Y");
    ImGui::NextColumn();
    for (int i = 0; i < 30; i++) {
        ImGui::Text("%.6f", ak[i][0]);
        ImGui::NextColumn();
        ImGui::Text("%.6f", ak[i][1]);
        ImGui::NextColumn();
    }
    ImGui::End();
}

// End the GUI frame
ImGui::Render();
ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

// Move the mouse to the ak coordinate table if the checkbox is checked
if (isAkEnabled) {
    for (int i = 0; i < 30; i++) {
        smoothMove(ak[i][0] * GetSystemMetrics(SM_CXSCREEN), ak[i][1] * GetSystemMetrics(SM_CYSCREEN));
        Sleep(50);
    }
}

}
// Cleanup
ImGui_ImplDX11_Shutdown();
ImGui_ImplWin32_Shutdown();
ImGui::DestroyContext();
return 0;
}
