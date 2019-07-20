#!/bin/sed -nf

/== MAP ==/,$ {                # in the range of the map 
    /== MAP ==/n               # skip the line containing == MAP ==
    p                          # print
} 

