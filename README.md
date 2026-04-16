**sla-calc this is utility, for calculate time availability systems. Examples of usage without specifying the program extension. An example of the utility running for a 99.5% SLA:**

<span style="color: green;">$ sla-calc 99.5    

99.5000% SLA for 1 day downtime:      0.12 hour | 7.20 min    | 432 sec    
99.5000% SLA for 1 week downtime:     0.84 hour | 50.40 min   | 3024 sec    
99.5000% SLA for 1 month downtime:    3.65 hour | 219.15 min  | 13149 sec    
99.5000% SLA for 1 quartal downtime: 10.96 hour | 657.47 min  | 39448 sec    
99.5000% SLA for 1 year downtime:    43.83 hour | 2629.87 min | 157792 sec    

We have max inaccessibility system equal 219 munites in 1 month or 11 hour in quartal or 43 hour in 1 year. 
__________________________________________
**If our system must very acceccebility and sla 99.92, that:**

<span style="color: green;">$ sla-calc 99.92    

99.9200% SLA for 1 day downtime:      0.02 hour |    1.17 min | 70 sec    
99.9200% SLA for 1 week downtime:     0.14 hour |    8.17 min | 490 sec    
99.9200% SLA for 1 month downtime:    0.59 hour |   35.51 min | 2130 sec    
99.9200% SLA for 1 quartal downtime:  1.78 hour |  106.54 min | 6392 sec    
99.9200% SLA for 1 year downtime:     7.10 hour |  426.17 min | 25570 sec    

If we have ensure acceccibility system don't less 30 minutes - SLA ~ 99.2.    
__________________________________________
**Argument '--info' displays the values used for calculations. For example, if the document specifies a higher SLA level than is actually required (for manual rechecking).**

<span style="color: green;">$ sla-calc 99.5 --info    
    
99.5000% SLA for 1 day downtime: 0.12 hour | 7.20 min | 432 sec    
99.5000% SLA for 1 week downtime: 0.84 hour | 50.40 min | 3024 sec    
99.5000% SLA for 1 month downtime: 3.65 hour | 219.15 min | 13149 sec    
99.5000% SLA for 1 quartal downtime: 10.96 hour | 657.47 min | 39448 sec    
99.5000% SLA for 1 year downtime: 43.83 hour | 2629.87 min | 157792 sec    

[INFO]  1 day in seconds = 86400    
[INFO]  1 week in seconds = 604800    
[INFO]  1 month in seconds = 2629843    
[INFO]  1 quartal in seconds = 7889530    
[INFO]  1 year in seconds = 31558120    

__________________________________________
**The '--update-time' argument displays the time available for system updates (calculated based on all downtime). For example, if we have a system with an SLA of 99.7, and we estimate the probability that 20% of the SLA time can be used for system updates (calculated based on 20% of the system's downtime):**

<span style="color: green;">$ sla-calc 99.7 --update-time 20    

99.7000% SLA for 1 day downtime: 0.07 hour | 4.33 min | 260 sec    
99.7000% SLA for 1 week downtime: 0.51 hour | 30.33 min | 1820 sec    
99.7000% SLA for 1 month downtime: 2.20 hour | 131.90 min | 7914 sec    
99.7000% SLA for 1 quartal downtime: 6.59 hour | 395.70 min | 23742 sec    
99.7000% SLA for 1 year downtime: 26.38 hour | 1582.80 min | 94968 sec    

update-time = 20%    
1 day time for update:            0.01 hour | 0.87 min | 52 sec    
1 day time for unplanned downtime: 0.06 hour | 3.47 min | 208 sec    
1 week time for update:           0.10 hour | 6.07 min | 364 sec    
1 week time for unplanned downtime 0.40 hour | 24.27 min | 1456 sec    
1 month time for update:          0.44 hour | 26.37 min | 1582 sec    
1 month time for unplanned downtime: 1.76 hour | 105.52 min | 6331 sec    
1 quartal time for update:        1.32 hour | 79.13 min | 4748 sec    
1 quartal time for unplanned downtime: 5.28 hour | 316.57 min | 18994 sec    
1 year time for update:            5.28 hour | 316.55 min | 18993 sec    
1 year time for unplanned downtime: 21.10 hour | 1266.25 min | 75975 sec    

__________________________________________
**But, if we don't enough time for update 26 minutes every month (need to 1 hour), change argument 'update-time' on 50%.**

<span style="color: green;">$ sla-calc 99.7 --update-time 50    

99.7000% SLA for 1 day downtime: 0.07 hour | 4.33 min | 260 sec    
99.7000% SLA for 1 week downtime: 0.51 hour | 30.33 min | 1820 sec    
99.7000% SLA for 1 month downtime: 2.20 hour | 131.90 min | 7914 sec    
99.7000% SLA for 1 quartal downtime: 6.59 hour | 395.70 min | 23742 sec    
99.7000% SLA for 1 year downtime: 26.38 hour | 1582.80 min | 94968 sec    

update-time = 50%    
1 day time for update:            0.04 hour | 2.17 min | 130 sec    
1 day time for unplanned downtime: 0.04 hour | 2.17 min | 130 sec    
1 week time for update:           0.25 hour | 15.17 min | 910 sec    
1 week time for unplanned downtime 0.25 hour | 15.17 min | 910 sec    
1 month time for update:          1.10 hour | 65.93 min | 3956 sec    
1 month time for unplanned downtime: 1.10 hour | 65.95 min | 3957 sec    
1 quartal time for update:        3.30 hour | 197.83 min | 11870 sec    
1 quartal time for unplanned downtime: 3.30 hour | 197.87 min | 11872 sec    
1 year time for update:            13.19 hour | 791.38 min | 47483 sec    
1 year time for unplanned downtime: 13.19 hour | 791.42 min | 47485 sec    
