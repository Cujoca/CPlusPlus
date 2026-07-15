@echo off
setlocal
cd /d "%~dp0"

rem cc1plus lives in libexec\ but loads its DLLs from the compiler's bin\ dir, which
rem is only on PATH when CLion drives the build itself. Add it so this script works
rem from a plain cmd too; the path is read from the cache to stay version-agnostic.
for /f "tokens=1,* delims==" %%A in ('findstr /b /c:"CMAKE_CXX_COMPILER:FILEPATH=" cmake-build-debug\CMakeCache.txt') do set "CXX=%%B"
if not defined CXX (
    echo Could not read CMAKE_CXX_COMPILER from cmake-build-debug\CMakeCache.txt.
    exit /b 1
)
set "CXX=%CXX:/=\%"
for %%I in ("%CXX%") do set "PATH=%%~dpI;%PATH%"

echo === compiling ===
cmake --build cmake-build-debug --target Labs
if errorlevel 1 exit /b 1
echo.

echo === running edge case tests ===
rem One stdin stream: the student menu runs first, then the employee menu takes over
rem once 11 is entered. Comments cannot go inside the input block below (every line
rem there is fed to the program), so each test is listed here against its inputs.
rem
rem STUDENT MENU
rem   2 3 4 5 6 7 8 9        every action on an empty roster -> safe message, no data
rem   1 1 Alice 1001 ...     add one student (marks 85 90 95)
rem   8                      sort with one student -> "Not enough students to sort."
rem   1 2 Bob 1001 ...       add two; Bob's ID 1001 is a duplicate -> re-prompt, 1002 ok
rem   2                      display all three
rem   3 1001                 search, found
rem   3 9999                 search, no match
rem   4 1001 _ 92 _ _        edit Alice: blank keeps name, mark 1 -> 92, blanks keep 2 & 3
rem   4 9999                 edit, no match
rem   5 9999                 delete, no match
rem   6                      highest scorer
rem   7                      class summary
rem   8 1 / 8 2              sort by name, then by average (display after each)
rem   9 / 10                 save to file, then load back
rem   5 1001 / 5 1002 / 5 1003   delete every student, then display the empty roster
rem   11                     exit to the employee menu
rem
rem EMPLOYEE MENU
rem   2                      display on an empty roster -> "No employees to display."
rem   3                      highest paid with no data -> "No employees on record."
rem   abc / 9                menu choice rejected: non-numeric, then out of range
rem   1 5 1 _ Alice ...      type 5 rejected, blank name rejected; salaried 50000 + 5000 = 55000
rem   1 2 Bob 200 40 ...     hours 200 rejected (>168); rate 5 and 17.94 rejected below
rem                          minimum wage, 17.95 accepted -> 40 * 17.95 = 718
rem   1 3 Carl ...           commission rate 1.5 rejected; 30000 + 100000 * 0.15 = 45000
rem   1 1 Dave -100 ...      salary -100 rejected as negative; 70000 + 0 = 70000
rem   2                      display all four -> multiple additions in one session
rem   3                      highest paid across all three types -> Dave at 70000
rem   4                      exit
rem
rem ( echo. marks a deliberately blank line )
set "INPUT=%TEMP%\labs_usecase_input.txt"
> "%INPUT%" (
echo 2
echo 3
echo 4
echo 5
echo 6
echo 7
echo 8
echo 9
echo 1
echo 1
echo Alice
echo 1001
echo 85
echo 90
echo 95
echo 8
echo 1
echo 2
echo Bob
echo 1001
echo 1002
echo 45
echo 40
echo 50
echo Charlie
echo 1003
echo 70
echo 75
echo 80
echo 2
echo 3
echo 1001
echo 3
echo 9999
echo 4
echo 1001
echo.
echo 92
echo.
echo.
echo 4
echo 9999
echo 2
echo 5
echo 9999
echo 6
echo 7
echo 8
echo 1
echo 2
echo 8
echo 2
echo 2
echo 9
echo 10
echo 2
echo 5
echo 1001
echo 5
echo 1002
echo 5
echo 1003
echo 2
echo 11
echo 2
echo 3
echo abc
echo 9
echo 1
echo 5
echo 1
echo.
echo Alice
echo 50000
echo 5000
echo 1
echo 2
echo Bob
echo 200
echo 40
echo 5
echo 17.94
echo 17.95
echo 1
echo 3
echo Carl
echo 30000
echo 100000
echo 1.5
echo 0.15
echo 1
echo 1
echo Dave
echo -100
echo 70000
echo 0
echo 2
echo 3
echo 4
)

cmake-build-debug\Labs.exe < "%INPUT%"
set "RC=%ERRORLEVEL%"
del "%INPUT%" 2>nul
exit /b %RC%
