#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_readline.h"
//#include "errors.h"

enum {
	OK,
	ALLOCATION_ERROR,
	INCORRECT_INPUT,
	POINTER_IS_NULL,
	EMPTY_QUEUE,
	OVERFLOW
};

#define BUF_SIZE	20


char *Readline(const char *prompt){
	if (prompt != NULL) {
		printf("%s", prompt);
	}

	size_t capacity = BUF_SIZE + 1; 
	size_t len = 0;

	char buf[BUF_SIZE + 1];
	char *str = (char *)malloc(sizeof(char));

	//if (str == NULL) { //Обработка ошибок
	//	return NULL;
	//}

	int op = 1;
	*str = '\0';

	size_t buf_len = 0;

	while (op > 0) {
		op = scanf("%21[^\n]", buf);

		if (op < 0) {
			free(str);
			return NULL;
		}

		if (op == 0) {
			scanf("%*c");
		}

		else {
			buf_len = strlen(buf);
			str = (char *)realloc(str, (len + buf_len + 1) * sizeof(char));
			//if (str == NULL) { // Обработка ошибок
			//	return NULL;
			//}

			memcpy(str + len, buf, buf_len * sizeof(char));
			len += buf_len;
			str = (char *)realloc(str, (capacity + BUF_SIZE) * sizeof(char));

			//if (str == NULL) { // Обработка ошибок
			//	return NULL;
			//}

			capacity += BUF_SIZE;
		}
	}

	*(str + len) = '\0';
	return str;
}


char *fileReadline(FILE *file){
        //if (prompt != NULL) {
        //       printf("%s", prompt);
        //}

        size_t capacity = BUF_SIZE + 1;
        size_t len = 0;

        char buf[BUF_SIZE + 1];
        char *str = (char *)malloc(sizeof(char));

        //if (str == NULL) { //Обработка ошибок
        //      return NULL;
        //}

        int op = 1;
        *str = '\0';

        size_t buf_len = 0;

        while (op > 0) {
                op = fscanf(file, "%21[^\n]", buf);

                if (op < 0) {
                        free(str);
                        return NULL;
                }

                if (op == 0) {
                        fscanf(file, "%*c");
                }

                else {
                        buf_len = strlen(buf);
                        str = (char *)realloc(str, (len + buf_len + 1) * sizeof(char));
                        //if (str == NULL) { // Обработка ошибок
                        //      return NULL;
                        //}

                        memcpy(str + len, buf, buf_len * sizeof(char));
                        len += buf_len;
                        str = (char *)realloc(str, (capacity + BUF_SIZE) * sizeof(char));

                        //if (str == NULL) { // Обработка ошибок
                        //      return NULL;
                        //}

                        capacity += BUF_SIZE;
                }
        }

        *(str + len) = '\0';
        return str;
}





int checkInput(const char *str, const char *correct) {
	if (str == NULL) {
		return POINTER_IS_NULL;
	}

	char *tmp = strdup(str);
	tmp = antiStrtok(tmp, correct); // Режем строку, как только встретим неккоректный символ
	if (tmp != NULL) {
		free(tmp);
		return INCORRECT_INPUT;
	}
	
	free(tmp);
	return OK;
}


int isCorrect(char ch, const char *correct) { // Проверяет, является ли символ корректным
	if (correct == NULL) {
		return POINTER_IS_NULL;
	}

	for (size_t i = 0; i < strlen(correct); i++) {
		if (ch == *(correct + i)) {
			return 1;
		}
	}
	return 0;
}


char *antiStrtok(char *str, const char *correct) { // Делит строку по символам, которые не содержатся в строке correct
	static char *curr = NULL;

	if (str != NULL) {
		curr = str;
	}

	else if (curr == NULL) {
		return NULL;
	}

	while (*curr != '\0' && isCorrect(*curr, correct) == 1) { //Идем по строке, пока не встретим начало слова
		curr++;
	}

	if (*curr == '\0') {
		return NULL; // Строку нельзя разделить на токены
	}

	char *token = curr; // Указатель на начало слова

	while (*curr != '\0' && isCorrect(*curr, correct) == 0) {
		curr++; // Ищем символ-разделитель (некорректный)
	}

	if (*curr != '\0') {
		*curr = '\0'; // Портим исходную строку 
		curr++;
	}

	return token;
}

