#ifndef TASK12_1
#define TASK12_1


//構造体

struct schedule {
    int day;
    char plan[100]; 
    int shour;
    int smin;
    int ehour;
    int emin;
    char place[100];
    char memo[100];
};

struct calendar {
    int year;
    int month;
    int lastday;
};

int isLeapYear(int year);
int getLastDay(int year, int month);
int dayOfWeek(struct calendar c);
void put_schedule(struct schedule *s);
void put_weekly_schedule(struct schedule sch[], int *count, struct calendar cal);

#endif