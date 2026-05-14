@echo on

if not exist %LIBRARY_PREFIX%\bin\vrsplayer.exe exit /b 1
if not exist %LIBRARY_PREFIX%\bin\vrs.exe exit /b 1

cmake tests ^
  -G Ninja ^
  -B tests\build ^
  -DCMAKE_BUILD_TYPE=Release ^
  -DCMAKE_PREFIX_PATH=%LIBRARY_PREFIX%
if errorlevel 1 exit /b 1

cmake --build tests\build --config Release
if errorlevel 1 exit /b 1

tests\build\vrs_consumer_test.exe
if errorlevel 1 exit /b 1

if not exist my_record_file.vrs exit /b 1
