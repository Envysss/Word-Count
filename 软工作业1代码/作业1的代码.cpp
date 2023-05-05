#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LEN 256
#define MAX_WORD_LEN 32

int main(int argc, char *argv[]) {
	char parameter[MAX_WORD_LEN];
	char filename[MAX_FILENAME_LEN];
	int count = 0;
	int c_word = 0; // ��ǰ���ʵĳ���
	int in_word = 0; // �Ƿ��ڵ�����

	// ���������в���
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

	// ���ļ�
	FILE *fp;

	if ((fp = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "Error: cannot open file %s\n", filename);
		exit(1);
	}

	// ͳ���ַ����򵥴���
	int c;

	while ((c = getc(fp)) != EOF) {
		count++;

		if (c == ' ' || c == '\t' || c == '\n') { // �ָ���
			if (in_word) { // ��һ���ַ��ǵ����ַ�
				c_word = 0; // ���õ�ǰ���ʳ���
				in_word = 0;
			}
		} else if (c == ',' || c == '.') { // ���ʷָ���
			if (in_word) { // ��һ���ַ��ǵ����ַ�
				c_word++;
				in_word = 0; // ���뵥���ⲿ
			}
		} else { // �����ַ�
			if (!in_word) { // ��һ���ַ��Ƿָ�����δ��ʼ
				c_word = 1; // ��ʼ�µĵ���
				in_word = 1;
			} else { // ��һ���ַ��ǵ����ַ�
				c_word++; // ��ǰ���ʳ��ȼ�һ
			}
		}
	}

	// �ر��ļ�
	fclose(fp);

	// ������
	if (strcmp(parameter, "-c") == 0) {
		printf("�ַ�����%d\n", count);
	} else if (strcmp(parameter, "-w") == 0) {
		printf("��������%d\n", c_word > 0 ? c_word : in_word);
	} else {
		fprintf(stderr, "Error: invalid parameter %s\n", parameter);
		exit(1);
	}

	return 0;
}