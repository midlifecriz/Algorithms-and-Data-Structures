#ifndef MY_READLINE_H
#define MY_READLINE_H

char *Readline(const char *prompt);
char *fileReadline(FILE *file);
int checkInput(const char *str, const char *correct);
int isCorrect(char ch, const char *correct);
char *antiStrtok(char *str, const char *correct);

#endif
