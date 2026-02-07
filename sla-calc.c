#include <stdio.h>  // printf() - print text
#include <stdlib.h> // strtol() - converting string to int, atof() - change type string to double, exit() - fast exit from programm
#include <string.h> // strlen() - length string

const int env_null = 0;                     // env, used in conditions
int num_dot = 0, i, check_dot_validity = 0; // counter for check dot
long l_update_time; // time for update (taked from all SLA time)
char *env_argv2_argc3, *env_argv2_argc4,
    *env_info_argv4; // env for check arguments argv2 (--info or --update-time)
char *p, *r, *env_result_upd_argv2, *env_argv1_help, *env_result_help,
    *env_help,
    *env_info_argv4; // env 'p', 'r' used im functions; env_* used in checks
float ex_one_down_sec, ex_two_down_sec, ex_three_down_sec, ex_four_down_sec,
    ex_five_down_sec; // env for calculate downtime in seconds (1 day, 1 week, 1
                      // month, 1 quartal, 1 year)
int ex_one_sec, oneday_sec; // env, often used in calculates
int result_info1 = 1, result_info2 = 1, result_help = 1,
    result_upd_arg =
        1; // env for result strcmp(), value = 1 know, the condition is not met
double double_SLA; // env, often used in calculates

int main(int argc, char **argv) {
  const int const_argc = argc; // that needed for don`t change value argc

  // 0_check. If no arguments - show message and exit
  if (const_argc >= 2) {
    goto goto_next_0;
  } else {
    printf("Error #0000. No arguments. Please enter desired persent SLA "
           "(example: sla-calc 99.5).\n");
    printf("If you have show help, usage argument '--help' (example: sla-calc "
           "--help).\n");
    return 1;
    exit(1);
  }

goto_next_0:

  // 1_check. Checking argv[1] to invoke help
  env_argv1_help = argv[1];
  env_help = "--help";
  env_result_help = env_help;
  result_help = strcmp(env_argv1_help, env_result_help);
  if (result_help == env_null) {
    printf("--help - Show this message.\n");
    printf(
        "--info - Show full time in seconds for 1 day/week/month/quartal/year "
        "(must be last argument, 2nd or 4nd).\n");
    printf("--update-time argument - Show time, available for update systems "
           "(calculate from all downtime time)\n");
    printf("\t\t\t Argument usage simple number 1-99 (persent).\n");
    printf("example with --info: sla-calc 99.5 --update-time 30 --info\n");
    printf("example: sla-calc 99.5\n");
    printf("-------------------------------------------------------------------"
           "--------------------\n");
    printf("99.5 %% SLA for 1 day, uptime = 85968 sec, downtime = 7.20 min "
           "(all downtime = 432 sec)\n");
    printf("99.5 %% SLA for 1 week, uptime = 601776 sec, downtime = 50.40 min "
           "(all downtime = 3024 sec)\n");
    printf("99.5 %% SLA for 1 month, uptime = 2622024 sec, downtime = 3.66 "
           "hour or 219.6 min (all downtime = 13176 sec)\n");
    printf("99.5 %% SLA for 1 quartal, uptime = 7844580 sec, downtime = 7.98 "
           "hour or 478.8 min (all downtime = 39420 sec)\n");
    printf("99.5 %% SLA for 1 year, uptime = 31378320 sec, downtime = 43.80 "
           "hour or 2628.00 min  (all downtime = 157680 sec)\n");
    printf("-------------------------------------------------------------------"
           "--------------------\n");
    goto goto_return0;
  }

  char SLA_argv = strtol(argv[1], &p, 10); // long
  char *chr = argv[1];
  double double_SLA =
      atof(chr); // often used in calculates, double_SLA as a floating point
                 // number, persent availability of information system
  int lengthargv = strlen(argv[1]);
  if (1 <= lengthargv && lengthargv <= 7) {
    long check_long = SLA_argv;
    float check_float = SLA_argv;
    if (check_long > env_null || check_float > 0.0000) {
      goto goto_next_1;
    } else {
      printf("Error #0001. Bad syntax arguments. Please enter desired persent "
             "SLA (example: sla-calc 99.5).\n");
      printf("If you have show help, usage argument '--help' (example: "
             "sla-calc --help).\n");
      return 1;
      exit(1);
    }

  goto_next_1:

    // 2_check. Checking argv[1] have dot (then type may be is float)
    if (lengthargv > 2) {
      char *hello = argv[1];
      for (int i = 0; i <= 7; ++i) {
        if (hello[i] == '.') {
          if (i == 1 || i == 2) {
            check_dot_validity = 1;
          }
          num_dot = num_dot + 1;
          if (num_dot == 2) // #[fail_1] solved the problem
          {
            printf("Error #0002. Bad syntax arguments. Please enter desired "
                   "persent SLA (example: sla-calc 99.5).\n");
            return 1;
            exit(1);
          }
        }
      }
    }
    if (lengthargv > 2 &&
        check_dot_validity != 1) // #[fail_1] solved the problem
    {
      printf("Error #0003. Bad syntax arguments. Please enter desired persent "
             "SLA (example: sla-calc 99.5).\n");
      return 1;
      exit(1);
    }

    // 3_check. Checking argv[1] have validity value
    {
      switch (check_long) // check argv[1] = 1-99
      {
      case 1 ... 99:
        goto goto_next_2;
      case 100 ... 9999999: // check argv[1] = 1-99 // #[fail_1] it works not
                            // correctly
        printf("Error #0004. Bad syntax arguments. Please enter desired "
               "persent SLA (example: sla-calc 99.5).");
        return 1;
        exit(1);
      }
    }
  } else {
    printf("Error #0005. Please enter correctly argument (example: sla-calc "
           "99.5).\n");
    return 1;
    exit(1);
  }

goto_next_2:

  // main function, calculate full time in seconds for a 1 day, 1 week, 1 month,
  // 1 quartal, 1 year
  unsigned int oneday_sec = 60 * 60 * 24;    // full time for 1 day
  unsigned int oneweek_sec = oneday_sec * 7; // full time for 1 week
  unsigned int onemonth_sec =
      oneday_sec * (float)(365.256 / 12); // full time for 1 month
  unsigned int onequartal_sec =
      oneday_sec * (float)(365.256 / 4); // full time for 1 quartal
  unsigned int oneyear_sec =
      oneday_sec * (float)365.256; // full time for 1 year

  // 1 day:
  int ex_one_sec = (oneday_sec / 100) *
                   double_SLA; // full time SLA for period '1 day' in seconds
  int ex_one_down_sec = oneday_sec - ex_one_sec;          // downtime in second
  float ex_one_down_min_float = (ex_one_down_sec / 60.0); // downtime in munutes
  float ex_one_down_hour_float = (ex_one_down_sec / 3600.0); // downtime in hour
  printf("%6.4f%% SLA for 1 day downtime: %4.2f hour | %4.2f min | %d sec\n",
         double_SLA, ex_one_down_hour_float, ex_one_down_min_float,
         ex_one_down_sec);

  // 1 week:
  int ex_two_sec = ex_one_sec * 7; // full time for period '1 week' in seconds
  int ex_two_down_sec = oneweek_sec - ex_two_sec;         // downtime in second
  float ex_two_down_min_float = (ex_two_down_sec / 60.0); // downtime in munutes
  float ex_two_down_hour_float = (ex_two_down_sec / 3600.0); // downtime in hour
  printf("%6.4f%% SLA for 1 week downtime: %4.2f hour | %4.2f min | %d sec\n",
         double_SLA, ex_two_down_hour_float, ex_two_down_min_float,
         ex_two_down_sec);

  // 1 month:
  float ex_three_sec =
      ex_one_sec * (365.256 / 12); // full time for period '1 month' in seconds
  float ex_three_down_sec = onemonth_sec - ex_three_sec; // downtime in second
  float ex_three_down_min_float =
      (ex_three_down_sec / 60.0); // downtime in munutes
  float ex_three_down_hour_float =
      (ex_three_down_sec / 3600.0); // downtime in hour
  printf(
      "%6.4f%% SLA for 1 month downtime: %4.2f hour | %4.2f min | %.0f sec\n",
      double_SLA, ex_three_down_hour_float, ex_three_down_min_float,
      ex_three_down_sec);

  // 1 quartal:
  float ex_four_sec =
      ex_one_sec * (365.256 / 4); // full time for period '1 quartal' in seconds
  float ex_four_down_sec = onequartal_sec - ex_four_sec; // downtime in second
  float ex_four_down_min_float =
      (ex_four_down_sec / 60.0); // downtime in munutes
  float ex_four_down_hour_float =
      (ex_four_down_sec / 3600.0); // downtime in hour
  printf(
      "%6.4f%% SLA for 1 quartal downtime: %4.2f hour | %4.2f min | %.0f sec\n",
      double_SLA, ex_four_down_hour_float, ex_four_down_min_float,
      ex_four_down_sec);

  // 1 year:
  float ex_five_sec =
      ex_one_sec * 365.256; // full time for period '1 year' in seconds
  float ex_five_down_sec = oneyear_sec - ex_five_sec; // downtime in second
  float ex_five_down_min_float =
      (ex_five_down_sec / 60.0); // downtime in munutes
  float ex_five_down_hour_float =
      (ex_five_down_sec / 3600.0); // downtime in hour
  printf("%6.4f%% SLA for 1 year downtime: %4.2f hour | %4.2f min | %.0f sec\n",
         double_SLA, ex_five_down_hour_float, ex_five_down_min_float,
         ex_five_down_sec);

  if (const_argc == 2) // fast finish exec programm
    goto goto_return0;

  // 4_check, --info - argc = 3
  if (const_argc == 3) {
    char *env_argv2_argc3 = argv[2];
    char *env_str3 = "--info";
    char *env_result_info_argv2 = env_str3;
    int result_info1 = strcmp(env_argv2_argc3, env_result_info_argv2);

    if (result_info1 == env_null)
      goto goto_info; // show --info
  }

  if (const_argc == 3 && result_info1 != env_null) {
    printf("Error #0006. Bad argument: '--update-time' (example: sla-calc 99.5 "
           "--update-time 20).\n");
    printf("\t\t\t  '--info'\t  (example: sla-calc 99.5 --info).\n");
    return 1;
    exit(1);
  }

  // 5_check, --update-time - argc = 4
  if (const_argc == 4 || const_argc == 5) {
    char *env_argv2_argc4 = argv[2];
    char *env_upd_argv2 = "--update-time";
    char *env_result_upd_argv2 = env_upd_argv2; // "--update-time"
    int result_upd_arg = strcmp(env_argv2_argc4, env_result_upd_argv2);

    if (result_upd_arg == env_null)
      goto goto_argv3_done; // show --update-time
  }

  if (const_argc == 4 || const_argc == 5 && result_upd_arg != 0) {
    printf("Error #0007. Bad argument: '--update-time' (example: sla-calc 99.5 "
           "--update-time 20).\n");
    return 1;
    exit(1);
  }

goto_argv3_done:

  // 6_check. Check correctly value for --update-time (argv[3])
  long l_update_time =
      strtol(argv[3], &r, 10); // time for update (taked from all SLA time)
  switch (l_update_time) // check argv[3] = 1-99 (persent for planned updates
                         // information system)
  {
  case 1 ... 99:
    goto goto_next_3;
  default:
    printf("Error #0008. Bad syntax for argument '--update-time' (example: "
           "sla-calc 99.5 --update-time 20).\n");
    return 1;
    exit(1);
  }

goto_next_3:

  // time for update:
  unsigned int upd_one_down_sec =
      ex_one_down_sec * l_update_time / 100; // 1 day time for update in seconds
  float upd_one_down_min_float =
      (upd_one_down_sec / 60.0); // 1 day time for update in minutes
  float upd_one_down_hour_float =
      (upd_one_down_sec / 3600.0); // 1 day time for update in hours

  unsigned int upd_two_down_sec =
      upd_one_down_sec * 7; // 1 week time for update in seconds
  float upd_two_down_min_float =
      (upd_two_down_sec / 60.0); // 1 week time for update in minutes
  float upd_two_down_hour_float =
      (upd_two_down_sec / 3600.0); // 1 week time for update in hours

  unsigned int upd_three_down_sec =
      upd_one_down_sec * (365.256 / 12); // 1 month time for update in seconds
  float upd_three_down_min_float =
      (upd_three_down_sec / 60.0); // 1 month time for update in minutes
  float upd_three_down_hour_float =
      (upd_three_down_sec / 3600.0); // 1 month time for update in hours

  unsigned int upd_four_down_sec =
      upd_one_down_sec * (365.256 / 4); // 1 quartal time for update in seconds
  float upd_four_down_min_float =
      (upd_four_down_sec / 60.0); // 1 quartal time for update in minutes
  float upd_four_down_hour_float =
      (upd_four_down_sec / 3600.0); // 1 quartal time for update in hours

  unsigned int upd_five_down_sec =
      (upd_one_down_sec * 365.256); // 1 year time for update in seconds
  float upd_five_down_min_float =
      (upd_five_down_sec / 60.0); // 1 year time for update in minutes
  float upd_five_down_hour_float =
      (upd_five_down_sec / 3600.0); // 1 year time for update in hours

  // unplanned downtime:
  unsigned int upd_last_one_time_SLA =
      ex_one_down_sec - upd_one_down_sec; // 1 day unplanned downtime in seconds
  float upd_last_one_time_SLA_min_float =
      (upd_last_one_time_SLA / 60.0); // 1 day unplanned downtime in minutes
  float upd_last_one_time_SLA_hour_float =
      (upd_last_one_time_SLA / 3600.0); // 1 day unplanned downtime in hours

  unsigned int upd_last_two_time_SLA =
      ex_two_down_sec -
      upd_two_down_sec; // 1 week unplanned downtime in seconds
  float upd_last_two_time_SLA_min_float =
      (upd_last_two_time_SLA / 60.0); // 1 week unplanned downtime in minutes
  float upd_last_two_time_SLA_hour_float =
      (upd_last_two_time_SLA / 3600.0); // 1 week unplanned downtime in hours

  unsigned int upd_last_three_time_SLA =
      ex_three_down_sec -
      upd_three_down_sec; // 1 month unplanned downtime in seconds
  float upd_last_three_time_SLA_min_float =
      (upd_last_three_time_SLA / 60.0); // 1 month unplanned downtime in minutes
  float upd_last_three_time_SLA_hour_float =
      (upd_last_three_time_SLA / 3600.0); // 1 month unplanned downtime in hours

  unsigned int upd_last_four_time_SLA =
      ex_four_down_sec -
      upd_four_down_sec; // 1 quartal unplanned downtime in seconds
  float upd_last_four_time_SLA_min_float =
      (upd_last_four_time_SLA /
       60.0); // 1 quartal unplanned downtime in minutes
  float upd_last_four_time_SLA_hour_float =
      (upd_last_four_time_SLA /
       3600.0); // 1 quartal unplanned downtime in hours

  unsigned int upd_last_five_time_SLA =
      ex_five_down_sec -
      upd_five_down_sec; // 1 year unplanned downtime in seconds
  float upd_last_five_time_SLA_min_float =
      (upd_last_five_time_SLA / 60.0); // 1 year unplanned downtime in minutes
  float upd_last_five_time_SLA_hour_float =
      (upd_last_five_time_SLA / 3600.0); // 1 year unplanned downtime in hours

  // show --update-time
  printf("--------------------------------------------------------------\n");
  printf("update-time = %d%%\n",
         l_update_time); // persent for planned updates information system
  printf("1 day time for update:\t\t  %4.2f hour | %4.2f min | %u sec\n",
         upd_one_down_hour_float, upd_one_down_min_float,
         upd_one_down_sec); // 1 day
  printf("1 day time for unplanned downtime: %4.2f hour | %4.2f min | %u sec\n",
         upd_last_one_time_SLA_hour_float, upd_last_one_time_SLA_min_float,
         upd_last_one_time_SLA); // 1 day

  printf("1 week time for update:\t\t  %4.2f hour | %4.2f min | %u sec\n",
         upd_two_down_hour_float, upd_two_down_min_float,
         upd_two_down_sec); // 1 week
  printf("1 week time for unplanned downtime %4.2f hour | %4.2f min | %u sec\n",
         upd_last_two_time_SLA_hour_float, upd_last_two_time_SLA_min_float,
         upd_last_two_time_SLA); // 1 week

  printf("1 month time for update:\t  %4.2f hour | %4.2f min | %u sec\n",
         upd_three_down_hour_float, upd_three_down_min_float,
         upd_three_down_sec); // 1 month
  printf(
      "1 month time for unplanned downtime: %4.2f hour | %4.2f min | %u sec\n",
      upd_last_three_time_SLA_hour_float, upd_last_three_time_SLA_min_float,
      upd_last_three_time_SLA); // 1 month

  printf("1 quartal time for update:\t  %4.2f hour | %4.2f min | %u sec\n",
         upd_four_down_hour_float, upd_four_down_min_float,
         upd_four_down_sec); // 1 quartal
  printf("1 quartal time for unplanned downtime: %4.2f hour | %4.2f min | %u "
         "sec\n",
         upd_last_four_time_SLA_hour_float, upd_last_four_time_SLA_min_float,
         upd_last_four_time_SLA); // 1 quartal

  printf("1 year time for update:\t\t   %4.2f hour | %4.2f min | %u sec\n",
         upd_five_down_hour_float, upd_five_down_min_float,
         upd_five_down_sec); // 1 year
  printf(
      "1 year time for unplanned downtime: %4.2f hour | %4.2f min | %u sec\n",
      upd_last_five_time_SLA_hour_float, upd_last_five_time_SLA_min_float,
      upd_last_five_time_SLA); // 1 year

  if (const_argc == 5) {
    env_info_argv4 = argv[4];
    char *env_str_info2 = "--info";
    char *env_result_info2 = env_str_info2;
    int result_info2 = strcmp(env_info_argv4, env_result_info2);
    if (result_info2 == env_null) // show --info

    goto_info: // show --info, if argv[2]

    {
      printf(
          "--------------------------------------------------------------\n");
      printf("[INFO]\t1 day in seconds = %u\n", oneday_sec);
      printf("[INFO]\t1 week in seconds = %u\n", oneweek_sec);
      printf("[INFO]\t1 month in seconds = %u\n", onemonth_sec);
      printf("[INFO]\t1 quartal in seconds = %u\n", onequartal_sec);
      printf("[INFO]\t1 year in seconds = %u\n", oneyear_sec);
      printf(
          "--------------------------------------------------------------\n");
    }
      else {
        printf("Error #0009. Bad argument: '--info' (example: sla-calc 99.5 "
               "--update-time 20 --info).\n");
        return 1;
        exit(1);
      }
  }

goto_return0:

  return 0;
}
