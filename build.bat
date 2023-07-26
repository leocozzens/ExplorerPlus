REM Project build script
@ECHO OFF
SetLocal EnableDelayedExpansion

SET CC=g++
SET EXT=cpp
SET LIB=lib/x86-windows
SET PROJECT=ExplorerPlus
SET SRC=src
SET OBJ=obj
SET BINDIR=bin

IF NOT EXIST %OBJ% MKDIR %OBJ%
IF NOT EXIST %BINDIR% MKDIR %BINDIR%

SET SRCS=
FOR /R %SRC% %%f IN (*.%EXT%) DO (
    SET SRCS=!SRCS! %%f
)
SET LIBS=
FOR /R %LIB% %%f IN (*.a) DO (
    SET LIBS=!LIBS! %%f
)

IF "%2"=="RELEASE" (
    SET RELEASE=for release
    SET CFLAGS=-O2
) ELSE (
    SET CFLAGS=-g -Wall -Werror
)
SET IFLAGS=-Iinclude -I%LIB%/include
SET LFLAGS=-lopengl32 -lgdi32

ECHO Building %PROJECT% %RELEASE%

FOR %%f IN (%SRCS%) DO (
    IF NOT "%1"=="" (
        IF NOT "%1"=="ALL" (
            IF NOT "%1"=="%%~nf" (
                goto :BREAK
            )
        )
    )
    ECHO Compiling %%~nf
    %CC% %CFLAGS% -c %IFLAGS% "%%f" -o "%OBJ%/%%~nf.o"
    SET "OBJS=!OBJS! %OBJ%/%%~nf.o"
)
:BREAK
ECHO Linking objects
%CC% %CFLAGS% %OBJS% %LIBS% %LFLAGS% -o %BINDIR%/%PROJECT%.exe