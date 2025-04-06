#include "string.h"

void* memset(void* dst,unsigned char val, int num){
	unsigned char* tmp = (unsigned char*) dst;
	for(int i=0; i < num;i++) tmp[i] = val;
	
	return dst;
}

void* memcpy(void *dest, const void *src, int n){
	unsigned char* d = (unsigned char*)dest;
	unsigned char* s = (unsigned char*)src;
	while(n--){
		*d = *s;
		d++;
		s++;
	}
	
	return dest;
}

int strcmp(const char *str1, const char *str2){
	while(*str1 && (*str1++ == *str2++));
	return int(*(unsigned char*)str1 - *(unsigned char*)str2);
}

char* strncpy(char *dest, const char *src, int n){
	int i=0;
	while(i<n && src[i]){
		dest[i] = src[i];
		i++;
	}
	
	while(i<n){
		dest[i]= '\0';
		i++;
	}
	return dest;
}

int strncmp(const char *str1, const char *str2, int n){
	int i=0;
	while(i<n){
		if(str1[i]!=str2[i]) return (unsigned char)str1[i] - (unsigned char)str2[i];
		if(!(str1[i] && str2[i])) return 0;
		i++;
	}
	return 0;
}

int strlen(const char *str){
	int len =0;
	while(str[len++]);
	return len;
}

char* strcat(char* dest, const char* src){
	char* p = dest;
	while(*p++);
	while(*src){
		*p = *src;
		p++;
		src++;
	}
	*p='\0';
	return dest;
}

char* strcpy(char* dest, const char* src){
	char* d = dest;
	while(*src){
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return d;
}

void* memmove(void* dest, const void* src, int n){
	unsigned char* d = (unsigned char*) dest;
	unsigned char* s = (unsigned char*) src;
	if(d<s) for(int i=0; i < n;i++)d[i]=s[i];
	else for(int i=n;i>0;i--) d[i-1] = s[i-1];
	return dest;
}
