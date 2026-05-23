@echo off
echo ============================================
echo   Solar System Simulation - Launcher
echo ============================================
echo.

cd /d "%~dp0\.."

REM === Check if build exists ===
if not exist "cpp\build\server.exe" (
    echo [ERROR] C++ server not built! Run scripts/build.bat first.
    pause
    exit /b 1
)
if not exist "java\build\solarsystem\SolarSystem.class" (
    echo [ERROR] Java client not built! Run scripts/build.bat first.
    pause
    exit /b 1
)

REM === Start C++ Physics Server ===
echo [1/2] Starting C++ physics server on port 5050...
start "C++ Physics Server" cmd /c "cpp\build\server.exe"
echo [OK] Server starting...
echo.

REM === Wait for server to be ready ===
echo Waiting for server to initialize...
timeout /t 2 /nobreak > nul

REM === Start Java GUI Client ===
echo [2/2] Launching Java simulation GUI...
java -cp "java/build;lib/gson-2.10.1.jar" solarsystem.SolarSystem
echo.
echo Simulation closed.
pause
