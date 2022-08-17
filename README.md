# CyanLogger
 
This is a C++17 single-header logging library made for my personal use, but you can use it if you want! It helps me to standardise my console messages which results in a much cleaner console output.

## How to use

Include the header and instantiate a logger class. The main method will be `Logger::Output`, it can take these arguments:
 - (string) An error type to indicate the level of severity of the message
 - (string) A program module path, for example if your renderer fails to extract a texture from the texture atlas, you would output an error with this module path: "MYENGINE::RENDERER::TEXTURECROP"
 - Finally, the error message itself

```cpp
#include "CyanLogger.hpp"

#include <any>

int main(int argc, char* argv[]) {
    cyan::Logger log;

    log.Output(cyan::Errors::INFO, "main", "Hello world");

    log.Output("This porgram is useless!");

    try {
        //will cause an exception
        int x = std::any_cast<int>(std::any("apple"));
    } catch (...) {
        log.Output(cyan::Errors::INFO, "main::stupidexample", "Inevitable error");
    }

    return 0;
}
```

This will output:

```shell
11:29:34 [Info]: {main} - Hello world
11:29:34 [Info]: {Anonymous} - This porgram is useless!
11:29:34 [Info]: {main::stupidexample} - Inevitable error
```

### Customizing the output format

The message output format can be changed by supplying a schema string to either the logger constructor or with the `Logger::SetSchema` method:

The schema placeholders are:
 - %t = Current time (hh::mm::ss), The logging class makes its method public so that you may also get a time string for your own uses: `Logger::GetTimeString()`
 - %y = Error type
 - %m = Module path
 - %o = The message itself

You can omit placeholders if you want as well.

```cpp
log.SetSchema("{%t}--%y===%o - End log");
```

This will change the output of the previous program to:

```shell
{11:37:29}--Info===Hello world - End log
{11:37:29}--Info===This porgram is useless! - End log
{11:37:29}--Info===Inevitable error - End log
```

### Dumping history to file

All logger output messages are recorded in an std::list and this can be dumped to a file with the `Logger::SaveToFile` method:

```cpp
log.SaveToFile("log.txt");

//You can also give a path
log.SaveToFile("debug/log.txt");
```

You can clear the message history with `Logger::ClearMessageHistory()`.
You can also get the list of strings for yourself with `Logger::GetMessageHistory()`.

### Provided error types class

As seen in the provious examples, this library provides a class of error type strings for my convienince, while these are probably sufficient for most situations, you can always not include them by defining `cyanLog_NOERRORCLASS` before including `CyanLogger.hpp`.

```cpp
#define NOERRORCLASS
#include "CyanLogger.hpp"

int main(int argc, char* argv[]) {
	cyan::Logger log;

    //you may use your own system/convention of error types here.
    log.Output("Output", "main", "Hello world");
}
```

## Building

This library uses CMake, you can use cmake-gui to build it like any other library, there are no special settings.
