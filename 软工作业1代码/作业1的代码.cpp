#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LEN 256
#define MAX_WORD_LEN 32

int main(int argc, char *argv[]) {
	char parameter[MAX_WORD_LEN];
	char filename[MAX_FILENAME_LEN];
	int count = 0;
	int c_word = 0; // 当前单词的长度
	int in_word = 0; // 是否在单词中

	// 解析命令行参数
	if (argc == 2) {
		strcpy(parameter, "-c");
		strcpy(filename, argv[1]);
	} else if (argc == 3) {
		strcpy(parameter, argv[1]);
		strcpy(filename, argv[2]);
	} else {
		fprintf(stderr, "Usage: %s [-c|-w] [filename]\n", argv[0]);
		exit(1);
	}

	// 打开文件
	FILE *fp;

	if ((fp = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "Error: cannot open file %s\n", filename);
		exit(1);
	}

	// 统计字符数或单词数
	int c;

	while ((c = getc(fp)) != EOF) {
		count++;

		if (c == ' ' || c == '\t' || c == '\n') { // 分隔符
			if (in_word) { // 上一个字符是单词字符
				c_word = 0; // 重置当前单词长度
				in_word = 0;
			}
		} else if (c == ',' || c == '.') { // 单词分隔符
			if (in_word) { // 上一个字符是单词字符
				c_word++;
				in_word = 0; // 进入单词外部
			}
		} else { // 单词字符
			if (!in_word) { // 上一个字符是分隔符或还未开始
				c_word = 1; // 开始新的单词
				in_word = 1;
			} else { // 上一个字符是单词字符
				c_word++; // 当前单词长度加一
			}
		}
	}

	// 关闭文件
	fclose(fp);

	// 输出结果
	if (strcmp(parameter, "-c") == 0) {
		printf("字符数：%d\n", count);
	} else if (strcmp(parameter, "-w") == 0) {
		printf("单词数：%d\n", c_word > 0 ? c_word : in_word);
	} else {
		fprintf(stderr, "Error: invalid parameter %s\n", parameter);
		exit(1);
	}

	return 0;
}