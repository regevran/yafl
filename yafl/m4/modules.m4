m4_divert(m4_eval(NULL_AREA))m4_dnl

### m4 adds spaces to the results,
### it doesn't really matter, but for now we prefer to prevent them.
### this is the reason everything is so tight.

m4_define(MODULE_DEMO,"Demo")m4_dnl
m4_define(LOG_DEMO_DEBUG,[*YAFL_LOG(YAFL_DEBUG,MODULE_DEMO, $@)*] )m4_dnl
m4_define(LOG_DEMO_ERROR,[*YAFL_LOG(YAFL_ERROR,MODULE_DEMO, $@)*] )m4_dnl
m4_define(LOG_DEMO_WARNING,[*YAFL_LOG(YAFL_WARNING,MODULE_DEMO,$@)*])m4_dnl
m4_define(LOG_DEMO_INFO,[*YAFL_LOG(YAFL_INFO,MODULE_DEMO,$@)*])m4_dnl

m4_define(MODULE_INFRA,"infra")m4_dnl
m4_define(LOG_INFRA_DEBUG,[*YAFL_LOG(YAFL_DEBUG,MODULE_INFRA, $@)*] )m4_dnl
m4_define(LOG_INFRA_ERROR,[*YAFL_LOG(YAFL_ERROR,MODULE_INFRA, $@)*] )m4_dnl
m4_define(LOG_INFRA_WARNING,[*YAFL_LOG(YAFL_WARNING,MODULE_INFRA,$@)*])m4_dnl
m4_define(LOG_INFRA_INFO,[*YAFL_LOG(YAFL_INFO,MODULE_INFRA,$@)*])m4_dnl

_orig_area()m4_dnl
