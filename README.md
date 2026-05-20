# sftware_work_12-13
課題12-13-1のためのリポジトリ

・コード
main.c
#include <stdio.h>
#include <string.h>
#include "task12-1.h"


//メイン部分の実装

int main(void) {
    FILE *fp;
    struct calendar cal;
    struct schedule sch[999];

    int weekcount;
    int menu;
    int count = 0;
    int schcount = 0;

    char *weekname[] = {"日", "月", "火", "水", "木", "金", "土"};

    //カレンダーの初期化

    for (int i = 0; i < 999; i++) {
        sch[i].day = 32;
    }

    printf("このプログラムはある月の予定表を作ります。\n");

    printf("年を入力：");
    scanf("%d", &cal.year);

    while (1) {
        printf("月を入力(1-12)：");
        scanf("%d", &cal.month);

        if (cal.month >= 1 && cal.month <= 12)
            break;

        printf("間違った値です。入力し直してください。\n");
    }

    cal.lastday = getLastDay(cal.year, cal.month);
    weekcount = dayOfWeek(cal);

    printf("終了:0, 単発予定を入力する:1, 毎週予定を入力する:2...");
    scanf("%d", &menu);

    while (menu != 0 && count < 999) {
        if(menu == 1){
            put_schedule(&sch[count]);
            count += 1;
        }
        else if(menu == 2){
            put_weekly_schedule(sch, &count, cal);
        }

        printf("終了:0, 単発予定を入力する:1, 毎週予定を入力する:2...");
        scanf("%d", &menu);

    }

    //入力された予定をソートする

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if(sch[j].day > sch[j+1].day){
                    struct schedule tmp = sch[j];
                    sch[j] = sch[j+1];
                    sch[j+1] = tmp;
            }
            else if(sch[j].day == sch[j+1].day && sch[j].shour > sch[j+1].shour){
                    struct schedule tmp = sch[j];
                    sch[j] = sch[j+1];
                    sch[j+1] = tmp;
            }
            else if(sch[j].shour == sch[j+1].shour && sch[j].smin > sch[j+1].smin){
                    struct schedule tmp = sch[j];
                    sch[j] = sch[j+1];
                    sch[j+1] = tmp;
            }
        }
    }

    //予定表の出力
    
    fp = fopen("calendar.txt", "w");
    if (fp == NULL) {
        printf("ファイルを開けませんでした\n");
        return 1;
    }

    printf("%d年 %d月 の予定表\n", cal.year, cal.month);
    fprintf(fp, "%d年 %d月 の予定表\n", cal.year, cal.month);

    for (int i = 1; i <= a.lastday; i++) {
        int printed = 0;
        while (schcount < count && sch[schcount].day == i) {

        if (!printed) {
            printf("%s %2d %02d:%02d-%02d:%02d %s @%s memo:%s\n",
                   weekname[weekcount], i,
                   sch[schcount].shour, sch[schcount].smin,
                   sch[schcount].ehour, sch[schcount].emin,
                   sch[schcount].plan, sch[schcount].place,
                   sch[schcount].memo);

            fprintf(fp, "%s %2d %02d:%02d-%02d:%02d %s @%s memo:%s\n",
                    weekname[weekcount], i,
                    sch[schcount].shour, sch[schcount].smin,
                    sch[schcount].ehour, sch[schcount].emin,
                    sch[schcount].plan, sch[schcount].place,
                    sch[schcount].memo);
            printed = 1;
        } 
        else {
            printf("      %02d:%02d-%02d:%02d %s @%s memo:%s\n",
                   sch[schcount].shour,sch[schcount].smin,
                   sch[schcount].ehour,sch[schcount].emin,
                   sch[schcount].plan,sch[schcount].place,
                   sch[schcount].memo);

            fprintf(fp, "      %02d:%02d-%02d:%02d %s @%s memo:%s\n",
                    sch[schcount].shour,sch[schcount].smin,
                    sch[schcount].ehour,sch[schcount].emin,
                    sch[schcount].plan,sch[schcount].place,
                    sch[schcount].memo);
        }
            schcount++;
        }

        if (!printed) {
            printf("%s %2d\n", weekname[weekcount], i);
            fprintf(fp, "%s %2d\n", weekname[weekcount], i);
        }

        printf("\n");
        fprintf(fp, "\n");

        if(weekcount == 6)
            weekcount = 0;
        else
            weekcount += 1;
    }

    fclose(fp);
    return 0;
}


task12-1.c
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


task12-2.c
#include <stdio.h>
#include <stdlib.h>

int main(void){
    int n;
    int a;
    
    printf("要素数:");
    scanf("%d",&n);

    int *x = calloc(n,sizeof(int));

    if(x == NULL)
        puts("記憶領域の確保に失敗しました。");
    else{
        for(int i = 0; i < n; i++){
                printf("x[%d] = ", i);
                scanf("%d", &a);
                x[i] = a;
            }
        for(int i = 0; i < n; i++)
            printf("x[%d] = %d\n", i, x[i]);
        free(x);
    }
    return 0;
}


・使い方
実行すると予定を立てたい年と月を入力する。その後指示に従って日にちと時間を決め予定を入力する。

・使用例
2026年 2月 の予定表
日  1

月  2

火  3 19:00-20:00 run @park memo:

水  4

木  5

金  6

土  7

日  8

月  9

火 10 19:00-20:00 run @park memo:

水 11

木 12

金 13

土 14

日 15

月 16

火 17 19:00-20:00 run @park memo:

水 18

木 19

金 20

土 21

日 22

月 23

火 24 19:00-20:00 run @park memo:

水 25

木 26

金 27

土 28

