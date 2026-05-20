# 実行ファイル
task12-1.out: main.o task12-1.o
	gcc -o task12-1.out main.o task12-1.o

# .c -> .o 変換ルール
.c.o:
	gcc -c $<

# オブジェクトファイル依存関係
task12-1.o: task12-1.c task12-1.h
main.o: main.c task12-1.h
