#include <stdio.h>
#include <string.h>
#include "task12-1.h"

//うるう年判定

int isLeapYear(int year) {
    if (year % 400 == 0) return 1;
    if (year % 100 == 0) return 0;
    if (year % 4 == 0) return 1;
    return 0;
}

//月の最終日

int getLastDay(int year, int month) {
    if(month == 2 && isLeapYear(year) == 0)
        return 28;
    else if(month == 2 && isLeapYear(year) == 1)
        return  29;
    else if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    else
        return 31;
}

//曜日計算

int dayOfWeek(struct calendar c) {
    int year = c.year;
    int month = c.month;

    if (month == 1 || month == 2) {
        year -= 1;
        month += 12;
    }

    return (year + year / 4 - year / 100 + year / 400 + (13 * month + 8) / 5 + 1) % 7;
}

//予定入力(ポインタ)

void put_schedule(struct schedule *s) {
    
    printf("日付を入力：");
    scanf("%d", &s->day);

    printf("予定を入力：");
    scanf("%s", s->plan);

    printf("開始時刻(時 分)：");
    scanf("%d %d", &s->shour, &s->smin);

    printf("終了時刻(時 分)：");
    scanf("%d %d", &s->ehour, &s->emin);

    printf("場所を入力：");
    scanf("%s", s->place);

    printf("メモを入力(任意)：");
    getchar();
    fgets(s->memo, sizeof(s->memo), stdin);
    if (s->memo[0] == '\n') {
        s->memo[0] = '\0';
    } else {
        s->memo[strcspn(s->memo, "\n")] = '\0';
    }
}

void put_weekly_schedule(struct schedule sch[], int *count, struct calendar cal) {

    int start;
    struct schedule base;

    printf("曜日を入力（日:0,月:1,火:2,水:3,木:4,金:5,土:6）...");
    scanf("%d", &start);

    printf("予定を入力：");
    scanf("%s", base.plan);

    printf("開始時刻(時 分)：");
    scanf("%d %d", &base.shour, &base.smin);

    printf("終了時刻(時 分)：");
    scanf("%d %d", &base.ehour, &base.emin);

    printf("場所を入力：");
    scanf("%s", base.place);

    printf("メモを入力(任意)：");
    getchar();
    fgets(base.memo, sizeof(base.memo), stdin);
    if (base.memo[0] == '\n'){
        base.memo[0] = '\0';
    }
    else{
        base.memo[strcspn(base.memo, "\n")] = '\0';
    }

    int week = dayOfWeek(cal);

    for(int i = 1; i <= cal.lastday; i++){

        if(week == start && *count < 100) {
            base.day = i;
            sch[*count] = base;
            *count += 1;
        }
        if(week >= 6)
            week = 0;
        else
            week += 1;
    }
    
    printf("毎週予定を一括登録しました。\n");
}
