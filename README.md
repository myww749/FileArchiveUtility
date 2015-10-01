# FileArchiveUtility

* Compiles only on linux (uses time.h which is linux specific)
* Requires the right libraries
  * Qt, uses system gzip command, sqlite3
  * 

## Using git

Be careful about which branch you are working in and committing to, it was sometimes hard to tell if I was in the right branch locally.

## Some notes of FileRec

The requirements of the assignment (non-functional) are:

1. The “Archiver” will run on Ubuntu 14.04 (or higher) and on compatible versions of Linux, Unix, or Solaris. A MinGW/Cygwin version could also be created to run on Windows.
2. The “Archiver” will be implemented in C++.
3. The “Archiver” will present a GUI interface built using Qt 4.8 (or higher).
4. Data persistence will use either MySQL, or MongoDB.

FileRec is currently using linux specific function from the time.h, which is problematic, since it must also compile of Unix, Solaris and Windows. There is also use of C++ 11 features like std::to_string, not sure if we have to stick to C++ 95.

## Setting up sqlite3
Make sure to set the linker to add the correct include directories for sqlite3 and the correct library files.
My sqlite3 installing was in /usr/local/opt/sqlite and in there, there was the libs and includes.

## Setting up zlib

### Mac

If not installed install homebrew package manager.

Then run these commands:
brew tap homebrew/dupes <br>
brew install zlib <br>
brew list zlib <br>

The last command will tell you where the includes and library files are, add them to the netbeans properties for linker and compiler then include <zlib.h>

## gdb problems

You must install gdb using brew (I think on windows it is not a problem) and set up a certificate to let gdb
work, solution is here http://stackoverflow.com/questions/11504377/gdb-fails-with-unable-to-find-mach-task-port-for-process-id-error
