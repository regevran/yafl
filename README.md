# yafl
yet another fast log
# Objective
The project demonstartes a mechanism to create an exteremly fast and low foot print logging.
# Features
* simple log writing
* build system that takes care for everything
* binary logs
* reader
# Flow
* write your log
	* LOG( "hello world #", number );
* cmake
	* m4 preprocess generate
  	* log messages with numbers
  	* map files: numbers <--> text   
 	* make
  		* your project
  		* yafl-reader / yafl-tail / yafl-grep / yafl-etc
* run
    * generates binary logs
* post processing
	* translate the logs to text
   	    * use standard text tools.
    * yafl-grep (yet to implement)  
    * yafl-tail (yet to implement)
    * yafl-etc (etc.)
    
# BUILD
download the repo
it is a CMake project, create a build directory, cd into it and cmake and make this project.
When everything is compiled run from the build directory ./logger/demo/logger_demo
it runs current code in logger/demo/main.cpp whatever it is.

# Look Around
Take a look at any: .cpp .h .sh and .map files in the binary directory.
Take a look at the m4 directory to see how numbers are created from strings.


