CXX := g++
SRCDIR := src
BUILDDIR := build
TARGET := bin/Checkpoint

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
INC := -I include
CFLAGS := -O3
LDFLAGS := -std=c++14

all: $(TARGET)

SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs) -lSDL2_image -LSDL2_ttf

override CFLAGS += $(SDL_CFLAGS)
override LIBS += $(SDL_LDFLAGS)

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CXX) $(CFLAGS) $(LDFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."
	$(RM) -r $(BUILDDIR)

purge:
	@echo " Purging..."
	$(RM) -rf $(BUILDDIR) $(TARGET)

.PHONY: all clean purge