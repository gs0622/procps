/* This is a trivial uptime program.  I hereby release this program
 * into the public domain.  I disclaim any responsibility for this
 * program --- use it at your own risk.  (as if there were any.. ;-)
 * -michaelkjohnson (johnsonm@sunsite.unc.edu)
 *
 * Modified by Larry Greenfield to give a more traditional output,
 * count users, etc.  (greenfie@gauss.rutgers.edu)
 *
 * Modified by mkj again to fix a few tiny buglies.
 *
 * Modified by J. Cowley to add printing the uptime message to a
 * string (for top) and to optimize file handling.  19 Mar 1993.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <utmp.h>
#include <sys/ioctl.h>
#include "whattime.h"
#include "sysinfo.h"

static char buf[128];
static double av[3];

static char *lib_uptime(int abbreviated) {
  struct utmp *utmpstruct;
  int upminutes, uphours, updays, upweeks, upyears, updecades;
  int pos;
  int comma;
  struct tm *realtime;
  time_t realseconds;
  int numuser;
  double uptime_secs, idle_secs;

/* first get the current time */

  if (!abbreviated) {
    time(&realseconds);
    realtime = localtime(&realseconds);
    pos = sprintf(buf, " %02d:%02d:%02d ",
      realtime->tm_hour, realtime->tm_min, realtime->tm_sec);
  }

/* read and calculate the amount of uptime */

  uptime(&uptime_secs, &idle_secs);

  if (abbreviated) {
    updecades = (int) uptime_secs / (60*60*24*365*10);
    upyears = ((int) uptime_secs / (60*60*24*365)) % 10;
    upweeks = ((int) uptime_secs / (60*60*24*7)) % 52;
    updays = ((int) uptime_secs / (60*60*24)) % 7;
  }
  else
    updays = (int) uptime_secs / (60*60*24);

  strcat (buf, "up ");
  pos += 3;

  if (!abbreviated) {
    if (updays)
      pos += sprintf(buf + pos, "%d day%s, ", updays, (updays != 1) ? "s" : "");
  }

  upminutes = (int) uptime_secs / 60;
  uphours = upminutes / 60;
  uphours = uphours % 24;
  upminutes = upminutes % 60;

  if (!abbreviated) {
    if(uphours)
      pos += sprintf(buf + pos, "%2d:%02d, ", uphours, upminutes);
    else
      pos += sprintf(buf + pos, "%d min, ", upminutes);

/* count the number of users */

    numuser = 0;
    setutent();
    while ((utmpstruct = getutent())) {
      if ((utmpstruct->ut_type == USER_PROCESS) &&
         (utmpstruct->ut_name[0] != '\0'))
        numuser++;
    }
    endutent();

    pos += sprintf(buf + pos, "%2d user%s, ", numuser, numuser == 1 ? "" : "s");

    loadavg(&av[0], &av[1], &av[2]);

    pos += sprintf(buf + pos, " load average: %.2f, %.2f, %.2f", av[0], av[1], av[2]);
  }

  if (abbreviated) {
    comma = 0;

    if (updecades) {
      pos += sprintf(buf + pos, "%d %s", updecades,
                     updecades > 1 ? "decades" : "decade");
      comma += 1;
    }

    if (upyears) {
      pos += sprintf(buf + pos, "%s%d %s", comma > 0 ? ", " : "", upyears,
                     upyears > 1 ? "years" : "year");
      comma += 1;
    }

    if (upweeks) {
      pos += sprintf(buf + pos, "%s%d %s", comma > 0 ? ", " : "", upweeks,
                     upweeks > 1 ? "weeks" : "week");
      comma += 1;
    }

    if (updays) {
      pos += sprintf(buf + pos, "%s%d %s", comma > 0 ? ", " : "", updays,
                     updays > 1 ? "days" : "day");
      comma += 1;
    }

    if (uphours) {
      pos += sprintf(buf + pos, "%s%d %s", comma > 0 ? ", " : "", uphours,
                     uphours > 1 ? "hours" : "hour");
      comma += 1;
    }

    if (upminutes) {
      pos += sprintf(buf + pos, "%s%d %s", comma > 0 ? ", " : "", upminutes,
                     upminutes > 1 ? "minutes" : "minute");
      comma += 1;
    }
  }

  return buf;
}

char *sprint_uptime(void) {
  return lib_uptime(0);
}

char *sprint_uptime_abbrv(void) {
  return lib_uptime(1);
}

void print_uptime(void) {
  printf("%s\n", lib_uptime(0));
}

void print_uptime_abbrv(void) {
  printf("%s\n", lib_uptime(1));
}
