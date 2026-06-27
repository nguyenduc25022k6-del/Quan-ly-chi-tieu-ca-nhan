@echo off
REM ============================================================
REM  build.bat — Quan ly Chi tieu Ca nhan
REM  MI3310 | Nhom 12 | HUST 2026
REM  Dung tren Windows (can g++ trong PATH)
REM  Cach chay: double-click hoac goi tu cmd: build.bat
REM ============================================================

set CXX=g++
set CXXFLAGS=-std=c++11 -Wall -Iinclude
set TARGET=build\quanlychitieu.exe
set SRCDIR=src

REM Tao thu muc neu chua co
if not exist build mkdir build
if not exist data  mkdir data

REM Thu thap tat ca file .cpp trong src\
set SRCS=
for %%f in (%SRCDIR%\*.cpp) do set SRCS=!SRCS! %%f

REM Bien dich
%CXX% %CXXFLAGS% %SRCDIR%\*.cpp -o %TARGET%

if %ERRORLEVEL% == 0 (
    echo =^> Build thanh cong: %TARGET%
) else (
    echo =^> Build THAT BAI. Kiem tra lai cai dat g++.
    pause
    exit /b 1
)

REM Hoi co muon chay ngay khong
set /p RUN="Chay chuong trinh ngay? (y/n): "
if /i "%RUN%"=="y" (
    %TARGET%
)
