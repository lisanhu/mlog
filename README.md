# mlog -- My Log library

__By:__ [Sanhu Li](mailto:lisanhu2014@hotmail.com), [Sunita Chandrasekaran](mailto:schandra@udel.edu)

## Intro
It's a simple library for every to easily print log information and time information at the same time. The library by default will print out a fixed-width left banner like `[ Verbose     0.00 ]`. The numbers are the seconds from a timer you set. By sending the initialization function with NULL, the library will use the time for *now* as the start timer and report the time elapse since the object is created. The library is reporting time up to 0.01 seconds and it's reporting wall-clock time instead of CPU clock time.

## Usage
It's quite easy to use the library. There's a `logger_use.c` file containing code example to show its usage.

Put a simple example here:
```C
mlog logger = new_mlogger(NULL);
logger.mvlog(&logger, "This is a verbose log without any dynamic values.");
```

By sending `NULL` to initializer, the logger will report time from that moment.

The mlog data structure:
```C
struct mlog {
    ts_t start;
    FILE *stream;
    ml_mp_ptr mprint;
    ml_mv_ptr mvlog;
    ml_me_ptr melog;
};
```
`mprint` is a general log function that you can customize the log level for the information. The default implementation of the library only support "Verbose", and "Error" logging levels. Currently, there's no structure to model the log levels and these two are the current supported ones. If you need more log levels, you can easily implement you self or wait for a further update of the repo to support customized logging levels.

`mvlog` is short for `my verbose log`, `melog` for `my error log`. They are printing different banner text, just an easier version of `mprint`.

By default, the library will write log information to stderr, but you can easily change the output stream to wherever you want.

The `logger_use.c` contains a little more complex example to use the library.

## Compiling
You will need CMake 3.5 or above to compile the project. But it's quite easy to create a Makefile for it if you prefer.

## Contact
Feel free to contact [me](mailto:lisanhu2014@hotmail.com) if you have any questions or concerns about it. Please do not bother my professor about this repo 😅.
