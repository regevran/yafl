# yafl
yet another fast log
# objective
this project demonstartes a mechanism to create an exteremly fast and low foot print logging.
# features
* simple log writing
* build system that takes care for everything
* binary logs
* reader
# flow
* write your log: LOG( "hello world #", number );
* cmake
  * m4 preprocess
  * generates map files
  * make
    * your project
    * yafl-reader / yafl-tail / yafl-grep / yafl-etc
    
