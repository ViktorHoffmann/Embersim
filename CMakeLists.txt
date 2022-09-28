# CMakeList.txt: CMake-Projekt für "Embersim". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)

project ("Embersim")

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (Embersim "Embersim.cpp" "Embersim.h" "files.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Embersim PROPERTY CXX_STANDARD 20)
endif()

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
