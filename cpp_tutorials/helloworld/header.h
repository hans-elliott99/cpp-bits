/* Notes:
* Header files are typically used to "declare" certain types or functions
* A common place to store function declarations - just their names, no actual body
* simply declare that the function *does* exist.
* For ex, suppose we have a logging function Log in a script which we want to use in main.cpp.
* We could add the following line to main: `void Log(int var);` - this is the declaration
* When the code is compiled, the compiler will find Log in the other script.

* However, we can make this simpler by including the declaration in the header file instead.
* Then, any script can get access to all functions using `#include <header.h>`

* We cannot include a header file multiple times in one 'translation unit' or there will be errors
* So we may have a 'common' header file to use for main or use #ifndef, or just #pragma once 

*Finally, Note that we have to modify 'tasks.json' so that VS Code compiles all .cpp files in the folder
* (changed $(file) to ${fileDirname}\\*.cpp)
*/


// #ifndef HEADER
// #define HEADER

#pragma once
void Log(int var);

// #endif 