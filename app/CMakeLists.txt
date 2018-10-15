# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
            opengles

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).

             # 公共
             src/main/cpp/position_chanage/PositionChanage.cpp
             # 三角形
             src/main/cpp/triangle/triangle.cpp
             # 着色器
             src/main/cpp/shaders/shaders.cpp
             # 纹理
             src/main/cpp/textures/texture.cpp
             # 公共
             src/main/cpp/utils/gl_utils.cpp


              )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

# opengles start
find_library( OPENGLES3_LIBRARY GLESv3 "OpenGL ES v3.0 library")
find_library( EGL_LIBRARY EGL "EGL 1.4 library" )
# opengles end


find_library( # Sets the name of the path variable.
              log-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log
              android)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       opengles

                       # Links the target library to the log library
                       # included in the NDK.

                       ${log-lib}
                       android

                       # opengles start
                       ${OPENGLES3_LIBRARY}
                       ${EGL_LIBRARY}
                       # opengles end

                        )