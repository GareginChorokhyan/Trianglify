CXX = g++
CXXFLAGS = -g -std=c++17 -Wall -fPIC \
           -I/usr/include/x86_64-linux-gnu/qt5 \
           -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets \
           -I/usr/include/x86_64-linux-gnu/qt5/QtGui \
           -I/usr/include/x86_64-linux-gnu/qt5/QtCore

SOURCES = main.cpp triangulation.cpp
HEADERS = triangulation.hpp

MOC_FILES = moc_triangulation.cpp

OBJECTS = main.o triangulation.o moc_triangulation.o
BINARY = triangulation.bin

triangulation: $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(BINARY) -lQt5Widgets -lQt5Gui -lQt5Core
	printf '%s\n' '#!/usr/bin/env bash' > triangulation
	printf '%s\n' 'exec env -i \' >> triangulation
	printf '%s\n' '  HOME="$$HOME" USER="$$USER" LOGNAME="$$LOGNAME" \' >> triangulation
	printf '%s\n' '  PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin" \' >> triangulation
	printf '%s\n' '  DISPLAY="$$DISPLAY" XAUTHORITY="$$XAUTHORITY" XDG_RUNTIME_DIR="$$XDG_RUNTIME_DIR" \' >> triangulation
	printf '%s\n' '  QT_QPA_PLATFORM_PLUGIN_PATH=/usr/lib/x86_64-linux-gnu/qt5/plugins/platforms \' >> triangulation
	printf '%s\n' '  "$$(dirname "$$0")/$(BINARY)" "$$@"' >> triangulation
	chmod +x triangulation

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

moc_triangulation.cpp: triangulation.hpp
	moc triangulation.hpp -o moc_triangulation.cpp

clean:
	rm -f *.o triangulation $(BINARY) moc_*.cpp
