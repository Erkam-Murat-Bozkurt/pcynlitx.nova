

if (EXISTS "${CMAKE_BINARY_DIR}/BUILD/Mingw64_Config.txt")

   return()

endif()


execute_process(COMMAND cmd /c echo %USERPROFILE%

   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
   OUTPUT_VARIABLE USER_PROFILE_PATH
)


string(REPLACE "\n" "" USER_PROFILE_PATH "${USER_PROFILE_PATH}")

string(REPLACE "/" "\\" USER_PROFILE_PATH "${USER_PROFILE_PATH}")


file(DOWNLOAD  https://github.com/brechtsanders/winlibs_mingw/releases/download/15.2.0posix-13.0.0-msvcrt-r3/winlibs-x86_64-posix-seh-gcc-15.2.0-mingw-w64msvcrt-13.0.0-r3.zip ${CMAKE_SOURCE_DIR}/BUILD/winlibs-x86_64-posix-seh-gcc-15.2.0-mingw-w64msvcrt-13.0.0-r3.zip SHOW_PROGRESS)

set(COMPILER_ZIP_PATH ${CMAKE_SOURCE_DIR}/BUILD/winlibs-x86_64-posix-seh-gcc-15.2.0-mingw-w64msvcrt-13.0.0-r3.zip)

set(MINGW64_SOURCE_PATH ${CMAKE_SOURCE_DIR}/BUILD)



string(REPLACE "/" "\\" COMPILER_ZIP_PATH "${COMPILER_ZIP_PATH}")

string(REPLACE "/" "\\" MINGW64_SOURCE_PATH "${MINGW64_SOURCE_PATH}")


file(ARCHIVE_EXTRACT INPUT ${COMPILER_ZIP_PATH} DESTINATION ${MINGW64_SOURCE_PATH} VERBOSE)


if(MINGW)
   
   message("The mingw compiler toolchain detected")

else()

   message("The mingw compiler toolchain can not be detected")

   message("The mingw compiler will be installed")

   file(ARCHIVE_EXTRACT INPUT ${COMPILER_ZIP_PATH} DESTINATION ${USER_PROFILE_PATH} VERBOSE)

   execute_process(COMMAND cmd /c echo %PATH% 

      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
      OUTPUT_VARIABLE PATH_ENV
   )


   string(REPLACE "\n" "" PATH_ENV "${PATH_ENV}")

   set(new_paths ";${USER_PROFILE_PATH}/mingw64")

   string(APPEND new_paths ";${USER_PROFILE_PATH}/mingw64/bin")

   string(APPEND new_paths ";${USER_PROFILE_PATH}/mingw64/include")

   string(APPEND new_paths ";${USER_PROFILE_PATH}/mingw64/lib")

   string(APPEND new_paths ";${USER_PROFILE_PATH}/mingw64/x86_64-w64-mingw32")

   string(APPEND new_paths ";${USER_PROFILE_PATH}/mingw64/x86_64-w64-mingw32/include")

   string(APPEND new_paths ";${USER_PROFILE_PATH}/mingw64/x86_64-w64-mingw32/lib")


   string(REPLACE "\n" "" new_paths "${new_paths}")

   string(REPLACE "/" "\\" new_paths "${new_paths}")


   execute_process(

       COMMAND cmd /c reg.exe add "HKEY_CURRENT_USER\\Environment" /v PATH /t REG_SZ /d "${PATH_ENV};${new_paths}" /f
       WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
       RESULT_VARIABLE REG_EXE_RETURN_VALUE
       OUTPUT_QUIET
   )

   if(REG_EXE_RETURN_VALUE EQUAL 0)

      message("The compiler paths are set")
   
   else()
   
      message("The compiler paths are not set successfuly")

   endif()

endif()

file(REMOVE ${COMPILER_ZIP_PATH})

file(WRITE "${CMAKE_BINARY_DIR}/BUILD/Mingw64_Config.txt"  "MINGW64 configuration complated")
