CC = g++
EXT = cpp
CFLAGS = -Iinclude -g -Wall
SRC = src
OBJ = obj
BINDIR = bin
PROJNAME = ExplorerPlus
BINNAME = $(PROJNAME).bin
SRCS = $(wildcard $(SRC)/*.$(EXT))
OBJS = $(patsubst $(SRC)/%.$(EXT), $(OBJ)/%.o, $(SRCS))
BIN = $(BINDIR)/$(BINNAME)
SYSLIBS = -lglfw3 -lGL

SUBMITNAME = $(PROJECT_NAME).zip
zip = zip

all: create_dirs
all: $(BIN)

release: CFLAGS = -Iinclude -O2
release: all

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(SYSLIBS)

$(OBJ)/%.o: $(SRC)/%.$(EXT)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: $(SRC)/%.$(EXT)
	$(CC) $(CFLAGS) -c $< -o $(OBJ)/$@	

link: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN)

clean:
	rm -r $(BINDIR) $(OBJ)

create_dirs:
	@mkdir -p $(BINDIR) $(OBJ)

new: clean
new: all

submit:
	rm -f $(SUBMITNAME)
	zip $(SUBMITNAME) $(BIN)