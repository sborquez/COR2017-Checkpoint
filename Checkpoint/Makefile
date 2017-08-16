CXX := g++
SRCDIR := src
BUILDDIR := build
TARGETDIR := bin
APPNAME := Checkpoint
TARGET := $(TARGETDIR)/$(APPNAME)

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
INC := -I include
CFLAGS := -O3
LDFLAGS := -std=c++14

all: $(TARGET)

SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs) -lSDL2_image -LSDL2_ttf

GPIO_LDFLAG := -lwiringPi

override CFLAGS += $(SDL_CFLAGS)
override LIBS += $(SDL_LDFLAGS)
override LIBS += $(GPIO_LDFLAG)

$(TARGET): $(OBJECTS)
	@echo " Linking... $(APPNAME)"
	@mkdir -p $(TARGETDIR)
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
