# CMakeList.txt: CMake-Projekt für "Embersim". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)

project ("Embersim")

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (Embersim "Embersim.cpp" "Embersim.h" "files.cpp" "models.cpp" "interface.cpp" "gnuplot-iostream.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Embersim PROPERTY CXX_STANDARD 20)
endif()

set (CMAKE_CXX_FLAGS "-lstdc++fs -std=c++2a")
# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.