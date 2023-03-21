#include <bits/stdc++.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>

#define M_PI 3.14159
#define RIGHT_ANGLE 1.5708f

int
    nScreenWidth = 683,
    nScreenHeight = 186,
    screenSize = nScreenWidth*nScreenHeight;

const int
    nMapWidth = 64,
    nMapHeight = 32;

float
    fPlayerX = (float)nMapWidth / 2.0f,
    fPlayerY = (float)nMapHeight / 2.0f,
    fPlayerA = 0.0f,
    fPlayerVel = 4.0f,
    fPlayerRotVel = 0.5f,
    fFOV = 50.0f * M_PI / 180.0f,
    fDepth = 16.0f;

int main() {
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 4;
    cfi.dwFontSize.Y = 4;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    LPSTR screen = new char[screenSize];
    DWORD dwBytesWritten = 0;

    std::wstring map;
    map += L"################################################################";
    map += L"#                                                              #";
    map += L"#                                                              #";
    map += L"#                ####                      ####                #";
    map += L"#               ######                    ######               #";
    map += L"#               ######                    ######               #";
    map += L"#               ######                    ######               #";
    map += L"#               ######                    ######               #";
    map += L"#               ######                    ######               #";
    map += L"#               ######                    ######               #";
    map += L"#               ######                    ######               #";
    map += L"#               ######                    ######               #";
    map += L"#                ####                      ####                #";
    map += L"#                                                              #";
    map += L"#                                                              #";
    map += L"#                                                              #";
    map += L"#                                                              #";
    map += L"#                                                              #";
    map += L"#       ################################################       #";
    map += L"#       ################################################       #";
    map += L"#       #####                                      #####       #";
    map += L"#       #####                                      #####       #";
    map += L"#       #####                                      #####       #";
    map += L"#       #####                                      #####       #";
    map += L"#        ######                                  ######        #";
    map += L"#        ########                              ########        #";
    map += L"#          #########                        #########          #";
    map += L"#            #############            #############            #";
    map += L"#                ##############################                #";
    map += L"#                      ##################                      #";
    map += L"#                                                              #";
    map += L"################################################################";

    SetConsoleScreenBufferSize(hConsole, {(short)nScreenWidth, (short)nScreenHeight});

    auto T0 = std::chrono::system_clock::now();
    auto T1 = std::chrono::system_clock::now();

    while (1) {
        T1 = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsedTime = T1 - T0;
        T0 = T1;
        float fElapsedTime = elapsedTime.count();

        if (GetAsyncKeyState('Q') & 0x8000)
            fPlayerA -= fPlayerRotVel * fElapsedTime;
        if (GetAsyncKeyState('E') & 0x8000)
            fPlayerA += fPlayerRotVel * fElapsedTime;
        if (GetAsyncKeyState('A') & 0x8000) {
            fPlayerX -= sinf(fPlayerA + RIGHT_ANGLE) * fPlayerVel * fElapsedTime;
            fPlayerY -= cosf(fPlayerA + RIGHT_ANGLE) * fPlayerVel * fElapsedTime;

            if (map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#') {
                fPlayerX += sinf(fPlayerA + RIGHT_ANGLE) * fPlayerVel * fElapsedTime;
                fPlayerY += cosf(fPlayerA + RIGHT_ANGLE) * fPlayerVel * fElapsedTime;
            }
        }
        if (GetAsyncKeyState('D') & 0x8000) {
            fPlayerX += sinf(fPlayerA + RIGHT_ANGLE) * fPlayerVel * fElapsedTime;
            fPlayerY += cosf(fPlayerA + RIGHT_ANGLE) * fPlayerVel * fElapsedTime;

            if (map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#') {
                fPlayerX -= sinf(fPlayerA + RIGHT_ANGLE) * fPlayerVel * fElapsedTime;
                fPlayerY -= cosf(fPlayerA + RIGHT_ANGLE) * fPlayerVel * fElapsedTime;
            }
        }
        if (GetAsyncKeyState('W') & 0x8000) {
            fPlayerX += sinf(fPlayerA) * fPlayerVel * fElapsedTime;
            fPlayerY += cosf(fPlayerA) * fPlayerVel * fElapsedTime;

            if (map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#') {
                fPlayerX -= sinf(fPlayerA) * fPlayerVel * fElapsedTime;
                fPlayerY -= cosf(fPlayerA) * fPlayerVel * fElapsedTime;
            }
        }
        if (GetAsyncKeyState('S') & 0x8000) {
            fPlayerX -= sinf(fPlayerA) * fPlayerVel * fElapsedTime;
            fPlayerY -= cosf(fPlayerA) * fPlayerVel * fElapsedTime;

            if (map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#') {
                fPlayerX += sinf(fPlayerA) * fPlayerVel * fElapsedTime;
                fPlayerY += cosf(fPlayerA) * fPlayerVel * fElapsedTime;
            }
        }
        if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
            fPlayerVel = 7.5f;
            if (GetAsyncKeyState('W') & 0x8000 ||
            GetAsyncKeyState('A') & 0x8000 ||
            GetAsyncKeyState('S') & 0x8000 ||
            GetAsyncKeyState('D') & 0x8000)
                fFOV = 70.0f * M_PI / 180.0f;
            else
                fFOV = 50.0f * M_PI / 180.0f;
        } else {
            fPlayerVel = 4.0f;
            fFOV = 50.0f * M_PI / 180.0f;
        }

        for (int x = 0; x < nScreenWidth; x++) {
            float fRayAngle = (fPlayerA - fFOV / 2.0f) + ((float)x / (float)nScreenWidth) * fFOV;

            float fDistanceToWall = 0;
            bool bHitWall = false;
            bool bBoundary = false;

            float fEyeX = sinf(fRayAngle);
            float fEyeY = cosf(fRayAngle);

            while (!bHitWall && fDistanceToWall < fDepth) {
                fDistanceToWall += 0.005f;

                int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
                int nTestY = (int)(fPlayerY + fEyeY * fDistanceToWall);

                if (nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight) {
                    bHitWall = true;
                    fDistanceToWall = fDepth;
                } else if (map[nTestY * nMapWidth + nTestX] == '#') {
                    bHitWall = true;
                    std::vector<std::pair<float,float>> p;

                    for (int tx = 0; tx < 2; tx++) {
                        for (int ty = 0; ty < 2; ty++) {
                            float vx = (float)nTestX + tx - fPlayerX;
                            float vy = (float)nTestY + ty - fPlayerY;
                            float d = sqrt(vx*vx + vy*vy);
                            float dot = (fEyeX * vx/d) + (fEyeY * vy/d);
                            p.push_back(std::make_pair(d, dot));
                        }
                    }

                    std::sort(p.begin(), p.end(), [](const std::pair<float,float> &left, const std::pair<float,float> &right) {
                        return left.first < right.first;
                    });

                    float fBound = 0.0025f;
                    if (acos(p.at(0).second) < fBound) bBoundary = true;
                    if (acos(p.at(1).second) < fBound) bBoundary = true;
                }
            }

            fDistanceToWall *= cosf(fPlayerA - fRayAngle);

            int nCeiling = (float)(nScreenHeight / 2.0f) - nScreenHeight / (float)fDistanceToWall;
            int nFloor = nScreenHeight - nCeiling;
            
            short nShade = "@#%M+=-:.  "[(int)((fDistanceToWall/fDepth)*10.0f)];
            if (bBoundary) nShade = ' ';

            for (int y = 0; y < nScreenHeight; y++) {
                if (y < nCeiling)
                    screen[y*nScreenWidth+x] = ' ';
                else if (y >= nCeiling && y <= nFloor)
                    screen[y*nScreenWidth+x] = nShade;
                else if (y >= nFloor)
                    screen[y*nScreenWidth+x] = '.';
            }
        }

        for (int nx = 0; nx < nMapWidth; nx++) {
            for (int ny = 0; ny < nMapHeight; ny++) {
                screen[ny*nScreenWidth + nx] = map[ny*nMapWidth + nx];
            }
        }

        screen[(int)fPlayerY*nScreenWidth + (int)fPlayerX] = '@';

        screen[screenSize-1] = '\0';
        WriteConsoleOutputCharacter(hConsole, screen, screenSize, {0,0}, &dwBytesWritten);
    }
}