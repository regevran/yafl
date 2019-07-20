#!/bin/sed -nf

/== CODE ==/,/== MAP ==/ {      # in the range of the code area
    /== CODE ==/n               # skip the line containing == CODE ==
    /== MAP ==/ !{              # for all lo=ines which do not have == MAP ==
    p                           # print
    }
}


