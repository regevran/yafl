# yafl
yet another fast log
# Objective
this project demonstartes a mechanism to create an exteremly fast and low foot print logging.
# Features
* simple log writing
* build system that takes care for everything
* binary logs
* reader
# Flow
* write your log
 * LOG( "hello world #", number );
* cmake
  * m4 preprocess generates
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
