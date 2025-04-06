#pragma once

void* memset(void* dst,unsigned char val, int num);
void* memcpy(void *dest, const void *src, int n);
int strcmp(const char *str1, const char *str2);
char* strncpy(char *dest, const char *src, int n);
int strncmp(const char *str1, const char *str2, int n);
int strlen(const char *str);
char* strcat(char* dest, const char* src);
char* strcpy(char* dest, const char* src);
void* memmove(void* dest, const void* src, int n);
