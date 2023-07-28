@REM ExplorerPlus build script
@ECHO OFF
ECHO Use "ALL" to compile with libraries
SetLocal EnableDelayedExpansion

SET CC=g++
SET EXT=cpp
SET BASELIB=lib
SET LIB=%BASELIB%/x86-windows
SET PROJECT=ExplorerPlus
SET SRC=src
SET OBJ=obj
SET LIBOBJ=%BASELIB%/%OBJ%
SET BINDIR=bin

IF "%1"=="CLEAN" (
    ECHO Cleaning dirs
    RMDIR /Q /S "%BINDIR%"
    RMDIR /Q /S "%OBJ%"
    RMDIR /Q /S "%LIBOBJ%"
    EXIT /B 0
)

IF NOT EXIST "%OBJ%" MKDIR "%OBJ%"
IF NOT EXIST "%BINDIR%" MKDIR "%BINDIR%"
IF NOT EXIST "%BASELIB%" MKDIR "%BASELIB%"
IF NOT EXIST "%LIBOBJ%" MKDIR "%LIBOBJ%"

SET SRCS=
FOR /R %SRC% %%f IN (*.%EXT%) DO (
    SET SRCS=!SRCS! %%f
)

SET LIBS=
FOR /R %LIB% %%f IN (*.a) DO (
    SET LIBS=!LIBS! %%f
)

SET BASELIBS=
FOR /R %BASELIB% %%f IN (*.cpp) DO (
    SET BASELIBS=!BASELIBS! %%f
)

IF "%2"=="RELEASE" (
    SET RELEASE=for release
    SET CFLAGS=-O2
) ELSE (
    SET CFLAGS=-g -Wall
)
SET IFLAGS=-Iinclude -I%LIB%/include -I%BASELIB%/include
SET LFLAGS=-lopengl32 -lgdi32

ECHO Building %PROJECT% %RELEASE%

FOR %%f IN (%BASELIBS%) DO (
    IF "%1"=="ALL" (
        ECHO Compiling lib %%~nf
        %CC% %CFLAGS% -c %IFLAGS% -I%BASELIB%/internal "%%f" -o "%LIBOBJ%/%%~nf.o"
    )
    SET "LIBOBJS=!LIBOBJS! %LIBOBJ%/%%~nf.o"
)

FOR %%f IN (%SRCS%) DO (
    IF "%1"=="" (
        ECHO Compiling %%~nf
        %CC% %CFLAGS% -c %IFLAGS% "%%f" -o "%OBJ%/%%~nf.o"
    )
    IF "%1"=="ALL" (
        ECHO Compiling %%~nf
        %CC% %CFLAGS% -c %IFLAGS% "%%f" -o "%OBJ%/%%~nf.o"
    )
    IF "%1"=="NOLIB" (
        ECHO Compiling %%~nf
        %CC% %CFLAGS% -c %IFLAGS% "%%f" -o "%OBJ%/%%~nf.o"
    )
    IF "%1"=="%%~nf" (
        ECHO Compiling %%~nf
        %CC% %CFLAGS% -c %IFLAGS% "%%f" -o "%OBJ%/%%~nf.o"
    )
    SET "OBJS=!OBJS! %OBJ%/%%~nf.o"
)
ECHO Linking objects
%CC% %CFLAGS% %IFLAGS% %OBJS% %LIBOBJS% %LIBS% %LFLAGS% -o %BINDIR%/%PROJECT%.exe 
@REM -mwindows