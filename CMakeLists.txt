# Set the name and the supported language of the project
PROJECT(canviewer CXX)
# Set the minimum version of cmake required to build this project
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE RelWithDebInfo)
#set(CMAKE_CXX_COMPILER /usr/bin/g++-8)

# Use the package PkgConfig to detect GTK+ headers/library files
FIND_PACKAGE(PkgConfig REQUIRED)
find_package (Threads)

PKG_CHECK_MODULES(GTK3 REQUIRED gtkmm-3.0)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})

LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})


# Add other flags to the compiler
ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

# Add an executable compiled from hello.c
ADD_EXECUTABLE(canviewer canviewer.cpp
                    #gtkmm
                    gtkmm/MainWindow.cpp 
                    gtkmm/TreeModel.cpp 
                    gtkmm/ListModel.cpp
                    #can
                    can/message.cpp
                    can/variable.cpp
                    can/bit_variable.cpp
                    can/char_variable.cpp
                    can/double_variable.cpp
                    can/float_variable.cpp
                    can/string_variable.cpp
                    can/signed_variable.cpp
                    can/unsigned_variable.cpp
                    can/raw_variable.cpp
                    can/var_enum.cpp
                    can/json.cpp
                    can/util.cpp
                    can/frame.cpp
                    can/linux_socket.cpp
                    can/to_string.cpp
                    can/to_intermediate.cpp)


configure_file(window.glade window.glade COPYONLY)
#configure_file(ecap_logo.svg ecap_logo.svg COPYONLY)
#configure_file(icon.png icon.png COPYONLY)

# Link the target to the GTK+ libraries
TARGET_LINK_LIBRARIES(canviewer ${GTK3_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})