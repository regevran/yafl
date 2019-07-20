m4_divert(-1)

### NOTE: essuming using --prefix-builtins (-P), to seperate from functions such as substr which are common to m4 and std.


### --- log message structure - developer point of view ---
YAFL_LOG( <level>, "module", <params>... )

<level> - either: DEBUG, ERROR, WARNNG, INFO
e.g.: YAFL_LOG( DEBUG, "DFM", var1, "text1", "text2", var2, ... )

### --- log message structure - compiler point of view (the result of the processing ---
yafl::log::Msg{ <file-id>, __LINE__, <debug-level>,std::this_thread::get_id(),<module>,...}
<file-id>       - as defined when calling m4. currently: # m4 yaflpp.m4 -DCOMPILED_FILE=$(md5sum <file> | head -c8) <file>
<debug-level>   - see values in the definitions below for debug values
<module>        - computed as any other string

0x269aab6c,__LINE__,0xcdcd0000,std::this_thread::get_id(),0xbeef000 ,var1,0xbeef0001,0xbeef0002,var2,var3,0xbeef0005,var4
############ definitions ###############

m4_changequote(`[*',`*]')

#####  CONSTANTS  #####

### -- TRUE, FALSE --
m4_define(YAFL_TRUE, 1)
m4_define(YAFL_FALSE, 0)

### -- log levels --
m4_define(YAFL_DEBUG, 0x00000000ababab00)
m4_define(YAFL_ERROR, 0x00000000ababab01)
m4_define(YAFL_WARNING, 0x00000000ababab02)
m4_define(YAFL_INFO, 0x00000000ababab03)

### -- marks --
m4_define(END_OF_RECORD, 0xcdcdcdcdcdcdcdcd)


### -- THE_HEX --
m4_define(THE_HEX,0) 

### -- area CODES --
m4_define( ORIG_AREA,   10)
m4_define( CODE_AREA,   10)
m4_define( MAPP_AREA,   20)
m4_define( NULL_AREA,   -1)

### -- areas --
m4_define( _code_area_dnl,
[*m4_divert(m4_eval(CODE_AREA))*]m4_dnl
$@m4_dnl
[*m4_divert(m4_eval(NULL_AREA))*]m4_dnl
)m4_dnl

m4_define( _code_area_nl,
[*m4_divert(m4_eval(CODE_AREA))*]m4_dnl
$@
[*m4_divert(m4_eval(NULL_AREA))*]m4_dnl
)m4_dnl

m4_define( _map_area_dnl,
[*m4_divert(m4_eval(MAPP_AREA))*]m4_dnl
$@m4_dnl
[*m4_divert(m4_eval(NULL_AREA))*]m4_dnl
)m4_dnl

m4_define( _map_area_nl,
[*m4_divert(m4_eval(MAPP_AREA))*]m4_dnl
$@
[*m4_divert(m4_eval(NULL_AREA))*]m4_dnl
)m4_dnl

m4_define( _orig_area, [*m4_divert(ORIG_AREA)*])m4_dnl


### -- _next_hex --
### _next_hex( <hex number> ) 
### => <hex number> + 1
### returns the next hexadecimal number 
m4_define(_next_hex, [*m4_eval(0x$1+1,16)*])m4_dnl

### -- _code_comma --
m4_define(_code_comma, [*_code_area_dnl([*,*])*])

### -- _map_comma --
m4_define(_map_comma, [*_map_area_dnl([*,*])*])

### -- _ped -- 
### peds the given input ($2) with $1 zeros
### _ped(7,4)
### => 0000004                                                                                        
m4_define(_ped,[*m4_ifelse( m4_eval(m4_eval($1)<m4_len($2)), 1, $2, [*m4_ifelse( m4_eval($1),m4_len($2), $2, _ped($1,0[**]$2))*])*])m4_dnl

### -- _beef -- 
### adding 0xbeef[*8 pedded number*] to the input
### _beef(5) => 0xbeef00000005
m4_define( _beef,
[*[*0xbeef*]*][*_ped(12,$1)*]m4_dnl
)m4_dnl 

### -- _map1 --
### map1 stand for: _map one_ pair 
### maps a number to a string.
### outputs the map to the _mapp_area
### and the number to the code_area
### e.g.: 
### _map1( 0x4534, "my name is ran" )
### => map-area:  0xbeef4534 - "my name is ran"
### => code-area: 0xbeef4534

m4_define( _map1,
        [*m4_ifelse(
            m4_regexp($2,".*"), 0,
            [*_map_area_dnl('_beef($1)':$2)*][*_map_comma*]
            [*_code_area_dnl(_beef($1))*]
            [*m4_define([*THE_HEX*],_next_hex($1))*],m4_dnl 
            [*_code_area_dnl($2)*]
        )*]m4_dnl    
)m4_dnl

### -- _mapper --
### _mapper( first-hex, ... )
### _mapper( 0x4534, "eer", fgrt, "my name is ran" ... )
### => 
### map-area
### 0xbeef4534 - "eer"
### 0xbeef4535 - "my name is ran"
### ...
### code-area
### 0xbeef4534, fgrt,  0xbeef4535
m4_define( _mapper,
        [*m4_ifelse(
            $#, 2,
            [*_map1($1,$2)*],
            [*_mapper($1,$2)*][*_code_area_dnl(,)*][*_mapper(THE_HEX,m4_shift(m4_shift($@)))*]
        )*]m4_dnl
)

### -- _module --
### _module( 0x4534, "DFM" )
### => 
### map-area
### 0xbeef4534 - "DFM"
### code-area
### 0xbeef4534
m4_define( _module, [*_map1($1,$2)*]m4_dnl
)m4_dnl

### -- working_thread --
m4_define(_working_thread, pthread_self())m4_dnl

### -- _line --
m4_define(_line, __LINE__)

### -- call_prefix --
m4_define( _call_prefix, yafl::log::g_logQ.push[*[*(*]*]yafl::log::Log[*[*(*]*])m4_dnl

### -- call_suffix --
m4_define( _call_suffix, END_OF_RECORD[*[*))*]*])m4_dnl


### -- YAFL_LOG --
m4_define( YAFL_LOG,
        [*_code_area_dnl(_call_prefix)*]m4_dnl                              prefix
        [*_code_area_dnl(0x[**]COMPILED_FILE)*][*_code_comma*]m4_dnl        file
        [*_code_area_dnl(_line)*][*_code_comma*]m4_dnl                      line
        [*_code_area_dnl($1)*][*_code_comma*]m4_dnl                         debug level 
        [*_code_area_dnl(_working_thread)*][*_code_comma*]m4_dnl            thread
        [*_module(THE_HEX,[*$2*])*]m4_dnl                                   module
        [*m4_ifelse( 
            m4_eval($# > 2), YAFL_TRUE,
           [*_code_comma*]m4_dnl                   
        )*]m4_dnl
        [*_mapper(THE_HEX,m4_shift(m4_shift($@)))*][*_code_comma*]m4_dnl     all the rest
        [*_code_area_dnl(_call_suffix)*]m4_dnl                               suffix
        [*_orig_area*]m4_dnl
)m4_dnl

############ work area ###############
_code_area_nl(== CODE ==)
_map_area_nl(== MAP ==)
_orig_area()m4_dnl
m4_undefine([*__unix__*])m4_dnl
m4_changecom([*//*])m4_dnl
