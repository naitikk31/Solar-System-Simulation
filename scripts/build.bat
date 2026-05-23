@echo off
echo ============================================
echo   Solar System Simulation - Build Script
echo ============================================
echo.

cd /d "%~dp0\.."

REM === Build C++ Physics Server ===
echo [1/2] Building C++ physics server...
if not exist "cpp\build" mkdir "cpp\build"
g++ -o cpp/build/server.exe cpp/src/SolarSystemSimulation.cpp cpp/src/cpp_server.cpp -I cpp/include -lws2_32 -std=c++17
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] C++ build failed!
    pause
    exit /b 1
)
echo [OK] C++ server built successfully.
echo.

REM === Build Java GUI Client ===
echo [2/2] Building Java GUI client...
if not exist "java\build" mkdir "java\build"
javac -cp "lib/gson-2.10.1.jar" -d java/build java/src/solarsystem/*.java
if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Java build failed!
    pause
    exit /b 1
)
echo [OK] Java client built successfully.
echo.

echo ============================================
echo   Build complete! Run scripts/run.bat
echo ============================================
pause
