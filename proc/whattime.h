#ifndef PROC_WHATTIME_H
#define PROC_WHATTIME_H

#include "procps.h"

EXTERN_C_BEGIN

        /*
         * write to stdout either:
         *     10:35:52 up  2:33,  1 user,  load average: 1.69, 1.65, 1.63
         * or
         *     up 2 hours, 33 minutes
         */
extern void print_uptime(void);
extern void print_uptime_abbrv(void);

        /*
         * provide a buffer containing either:
         *     10:35:52 up  2:33,  1 user,  load average: 1.69, 1.65, 1.63
         * or
         *     up 2 hours, 33 minutes
         */
extern char *sprint_uptime(void);
extern char *sprint_uptime_abbrv(void);

EXTERN_C_END

#endif
