# FileArchiveUtility

* Compiles only on linux (uses time.h which is linux specific)
* Requires the right libraries
  * Qt, uses system gzip command

## Some notes of FileRec

The requirements of the assignment (non-functional) are:

1. The “Archiver” will run on Ubuntu 14.04 (or higher) and on compatible versions of Linux, Unix, or Solaris. A MinGW/Cygwin version could also be created to run on Windows.
2. The “Archiver” will be implemented in C++.
3. The “Archiver” will present a GUI interface built using Qt 4.8 (or higher).
4. Data persistence will use either MySQL, or MongoDB.

FileRec is currently using linux specific function from the time.h, which is problematic, since it must also compile of Unix, Solaris and Windows. There is also use of C++ 11 features like std::to_string, not sure if we have to stick to C++ 95.
