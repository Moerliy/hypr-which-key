CXXFLAGS=-shared -fPIC --no-gnu-unique -DWLR_USE_UNSTABLE -Wall -g -std=c++2b -O2
INCLUDES = `pkg-config --cflags pixman-1 libdrm hyprland pangocairo libinput libudev wayland-server xkbcommon`
SRC = $(wildcard src/*.cpp)
TARGET = hypr-which-key.so

all:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) -o $(TARGET)

clean:
	rm ./$(TARGET)

withhyprpmheaders: export PKG_CONFIG_PATH = $(XDG_DATA_HOME)/hyprpm/headersRoot/share/pkgconfig
withhyprpmheaders: all
