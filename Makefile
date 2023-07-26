CC = g++
EXT = cpp
CFLAGS = -g -Wall
SRC = src
OBJ = obj
LIB = lib
IFLAGS = -Iinclude -I$(LIB)/include
BINDIR = bin
PROJNAME = ExplorerPlus
BINNAME = $(PROJNAME).bin
SRCS = $(wildcard $(SRC)/*.$(EXT))
OBJS = $(patsubst $(SRC)/%.$(EXT), $(OBJ)/%.o, $(SRCS))
LIBS = $(wildcard $(LIB)/*.$(EXT))
LIBOBJ = $(LIB)/$(OBJ)
LIBOBJS = $(patsubst $(LIB)/%.$(EXT), $(LIBOBJ)/%.o, $(LIBS))
INTERNALINC = -I$(LIB)/internal
BIN = $(BINDIR)/$(BINNAME)
SYSLIBS = -lglfw3 -lGL

SUBMITNAME = $(PROJECT_NAME).zip
zip = zip

all: create_dirs
all: $(BIN)

release: CFLAGS = -O2
release: all

$(BIN): $(LIBOBJS) $(OBJS)
	$(CC) $(IFLAGS) $(CFLAGS) $(OBJS) $(LIBOBJS) -o $@ $(SYSLIBS)

$(OBJ)/%.o: $(SRC)/%.$(EXT)
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $@

$(LIB)/$(OBJ)/%.o: $(LIB)/%.$(EXT)
	$(CC) $(IFLAGS) $(INTERNALINC) $(CFLAGS) -c $< -o $@
# %.o: $(SRC)/%.$(EXT)
# 	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $(OBJ)/$@	

link: $(OBJS)
	$(CC) $(IFLAGS) $(CFLAGS) $(OBJS) -o $(BIN)

clean:
	rm -r $(BINDIR) $(OBJ) $(LIBOBJ)

create_dirs:
	@mkdir -p $(BINDIR) $(OBJ) $(LIBOBJ)

new: clean
new: all

submit:
	rm -f $(SUBMITNAME)
	zip $(SUBMITNAME) $(BIN)