# CMake generated Testfile for 
# Source directory: C:/Users/tfunk/chatgptyardage/gptgolf
# Build directory: C:/Users/tfunk/chatgptyardage/gptgolf/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test([=[physics_tests]=] "C:/Users/tfunk/chatgptyardage/gptgolf/build/Debug/physics_tests.exe")
  set_tests_properties([=[physics_tests]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/tfunk/chatgptyardage/gptgolf/CMakeLists.txt;49;add_test;C:/Users/tfunk/chatgptyardage/gptgolf/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test([=[physics_tests]=] "C:/Users/tfunk/chatgptyardage/gptgolf/build/Release/physics_tests.exe")
  set_tests_properties([=[physics_tests]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/tfunk/chatgptyardage/gptgolf/CMakeLists.txt;49;add_test;C:/Users/tfunk/chatgptyardage/gptgolf/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test([=[physics_tests]=] "C:/Users/tfunk/chatgptyardage/gptgolf/build/MinSizeRel/physics_tests.exe")
  set_tests_properties([=[physics_tests]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/tfunk/chatgptyardage/gptgolf/CMakeLists.txt;49;add_test;C:/Users/tfunk/chatgptyardage/gptgolf/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test([=[physics_tests]=] "C:/Users/tfunk/chatgptyardage/gptgolf/build/RelWithDebInfo/physics_tests.exe")
  set_tests_properties([=[physics_tests]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/tfunk/chatgptyardage/gptgolf/CMakeLists.txt;49;add_test;C:/Users/tfunk/chatgptyardage/gptgolf/CMakeLists.txt;0;")
else()
  add_test([=[physics_tests]=] NOT_AVAILABLE)
endif()
subdirs("_deps/googletest-build")
