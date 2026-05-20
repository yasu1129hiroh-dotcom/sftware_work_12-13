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