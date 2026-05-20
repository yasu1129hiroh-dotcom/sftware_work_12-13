#include <stdio.h>
#include <string.h>
#include "task12-1.h"


//メイン部分の実装

int main(void) {
    FILE *fp;
    struct calendar a;
    struct schedule sch[999];

    int weekcount;
    int x;
    int count = 0;
    int schcount = 0;

    char *weekname[] = {"日", "月", "火", "水", "木", "金", "土"};

    //カレンダーの初期化

    for (int i = 0; i < 999; i++) {
        sch[i].day = 32;
    }

    printf("このプログラムはある月の予定表を作ります。\n");

    printf("年を入力：");
    scanf("%d", &a.year);

    while (1) {
        printf("月を入力(1-12)：");
        scanf("%d", &a.month);

        if (a.month >= 1 && a.month <= 12)
            break;

        printf("間違った値です。入力し直してください。\n");
    }

    a.lastday = getLastDay(a.year, a.month);
    weekcount = dayOfWeek(a);

    printf("終了:0, 単発予定を入力する:1, 毎週予定を入力する:2...");
    scanf("%d", &x);

    while (x != 0 && count < 999) {
        if(x == 1){
            put_schedule(&sch[count]);
            count += 1;
        }
        else if(x == 2){
            put_weekly_schedule(sch, &count, a);
        }

        printf("終了:0, 単発予定を入力する:1, 毎週予定を入力する:2...");
        scanf("%d", &x);

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

    printf("%d年 %d月 の予定表\n", a.year, a.month);
    fprintf(fp, "%d年 %d月 の予定表\n", a.year, a.month);

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
