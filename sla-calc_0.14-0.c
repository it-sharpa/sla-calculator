#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void display_no_args(void), display_help(void), display_invalid_argument(const char *arg);
static void display_invalid_value(const char *what_value, double a);
static void display_info(void);

int is_a_number(const char *str);

int main(int argc, char **argv) {

  if (argc < 2) {
    display_no_args();
    return -1;
  }

  if (argc > 5) {
    puts("Error syntax, too many arguments");
    return -2;
  }

if (argc == 2) {
  if (strcmp(argv[1], "--help") == 0) {
    display_help();
    return 0;
  }

  if (!is_a_number(argv[1])) {
    display_invalid_argument(argv[1]);
    return -3;
  }
}

  char *chk_num = NULL;
  errno = 0;
  double sla = strtod(argv[1], &chk_num);
    if (errno != 0 || *chk_num != '\0' || sla <= 0.0 || sla >= 100.0) {
      display_invalid_value ("SLA percent", sla);
      return -4;
    }

  #define DAY_SEC (60 * 60 * 24)
  #define DAY_TIME_MULTIPLIER 1.0
  #define WEEK_TIME_MULTIPLIER 7.0
  #define MONTH_TIME_MULTIPLIER (365.256 / 12)
  #define QUARTAL_TIME_MULTIPLIER (365.256 / 4)
  #define YEAR_TIME_MULTIPLIER 365.256
  double update_time_percent = 0.0;

  static const double time_multipliers[5] = {
      DAY_TIME_MULTIPLIER,     WEEK_TIME_MULTIPLIER, MONTH_TIME_MULTIPLIER,
      QUARTAL_TIME_MULTIPLIER, YEAR_TIME_MULTIPLIER,
  };

  // SLA times for day, week, month, quartal and year
  puts("-----------------------------------------------------------------------"
       "-----------------------------------");
  for (int i = 0; i < 5; i++) {
    double ex_down_per_second = ((double)DAY_SEC / 100) * sla * time_multipliers[i];
    double ex_time = DAY_SEC * time_multipliers[i] - ex_down_per_second;

    static const char *period_names[5] = {
        "day downtime:       ", "week downtime:      ", "month downtime:     ",
        "quartal downtime:   ", "year downtime:      ",
    };
    printf("%6.4lf%% SLA for 1 %s"
           "\t\t%10.2lf hours | %10.2lf min |\t%10.0f sec\n",
           sla, period_names[i], ex_time / 3600.0, ex_time / 60.0, ex_time);
  }
  puts("-----------------------------------------------------------------------"
       "-----------------------------------");

if (argc == 3) {
  if (strcmp(argv[2], "--info") != 0) {
    display_invalid_argument(argv[2]);
    return -5;
  }

  if (strcmp(argv[2], "--info") == 0) {
    display_info();
    return 0;
  }
}

//check value for argument '--update-time'
if (argc == 4 || argc == 5) {
  if (strcmp(argv[2], "--update-time") != 0) {
    display_invalid_argument(argv[2]);
    return -6;
  }
  if (!is_a_number(argv[3])) {
    display_invalid_argument(argv[3]);
    return -7;
  }

  errno = 0;
  update_time_percent = strtod(argv[3], &chk_num);
    if (errno != 0 || *chk_num != '\0' || update_time_percent <= 0.0 || 
      update_time_percent >= 100.0) {
      display_invalid_value ("Update time percent", update_time_percent);
      return -8;
    }

  printf("update-time = %.2lf%%\n", update_time_percent);
  for (int i = 0; i < 5; i++) {
    double ex_down_per_second = ((double)DAY_SEC / 100) * sla * time_multipliers[i];
    double ex_time = DAY_SEC * time_multipliers[i] - ex_down_per_second;
    double upd_down = ex_time * update_time_percent / 100;
    double unplanned_down = ex_time - upd_down;

    const char *period_strs[5] = {
        "1 day", "1 week", "1 month", "1 quartal", "1 year",
    };

    printf("%s time for update (planned downtime):\t%10.2lf hours | %10.2lf min |\t%10.0f sec\n"
           "%s time for unplanned downtime:\t\t%10.2lf hours | %10.2lf min |\t%10.0f sec\n",
           period_strs[i], upd_down / 3600.0, upd_down / 60.0, upd_down,
           period_strs[i], unplanned_down / 3600.0, unplanned_down / 60.0,
           unplanned_down);
  }
  puts("-----------------------------------------------------------------------"
       "-----------------------------------");
  }

  if (argc == 5 && strcmp(argv[4], "--info") != 0)
  {
    display_invalid_argument(argv[4]);
    return -9;
  }

  if (argc == 5 && strcmp(argv[4], "--info") == 0)
  {
    display_info();
  }

return 0;
}

static void display_no_args(void) {
  puts("No arguments. Please enter the desired SLA percent. Example: sla-calc 99.5\n"
       "If you have show help, usage argument \"--help\". Example: sla-calc --help");
}

static void display_help(void) {
  puts("Usage:\n"
       "sla-calc <percent> ([--info], [--update-time <percent>] "
       "[--info])\n"
       "\t  --help                  - Show this message.\n"
       "\t  --info                  - Show time in seconds for "
       "1 day/week/month/quartal/year "
       "(must be the last argument, 2nd or 4th).\n"
       "\t  --update-time <percent> - Show time available for "
       "system update.");
}

static void display_invalid_value(const char *what_value, double a) {
  printf("Invalid value for \"%s\": %.0lf\n"
         "Value must be in range of %s-%s.\n",
         what_value, a, "0.0001", "99.9999");
}

static void display_info(void) {
  printf("[INFO] 1 day in seconds     = %" PRId64 "\n"
         "[INFO] 1 week in seconds    = %" PRId64 "\n"
         "[INFO] 1 month in seconds   = %" PRId64 "\n"
         "[INFO] 1 quartal in seconds = %" PRId64 "\n"
         "[INFO] 1 year in seconds    = %" PRId64 "\n"
         "---------------------------------------------------------------------"
         "-------------------------------------\n",
         (int64_t)(DAY_SEC), (int64_t)(DAY_SEC * WEEK_TIME_MULTIPLIER),
         (int64_t)(DAY_SEC * MONTH_TIME_MULTIPLIER),
         (int64_t)(DAY_SEC * QUARTAL_TIME_MULTIPLIER),
         (int64_t)(DAY_SEC * YEAR_TIME_MULTIPLIER));
}

static void display_invalid_argument(const char *arg) {
  printf("Invalid argument \"%s\".\n", arg);
}

int is_a_number(const char *str) {
  for (; *str; str++)
    if (!isdigit(*str) && *str != '.' && *str != '-' && *str != '+')
      return 0;
  return 1;
}
