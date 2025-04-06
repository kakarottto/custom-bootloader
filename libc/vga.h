#pragma once

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MODE 0xb8000
int vga_cursor_line = 2;
int vga_curs = 0;


int set_vga_color(int fg, int bg){
	return fg | bg<<4;
}

void clear_screen(){
	char* video = (char*) VGA_MODE;
	for(int i =0; i < VGA_WIDTH*VGA_HEIGHT;i++){
		video[i*2]=0;
	}
}

void print(unsigned char* msg){
	char* video = (char*) VGA_MODE;
	for(int i=0; msg[i]!='\0';i++){
		if(msg[i]=='\n'){
			vga_cursor_line++;
			vga_curs = 0;
		}
		else{
			if(vga_curs >= VGA_WIDTH){
				vga_curs= 0;
				if(++vga_cursor_line>=25)vga_cursor_line = 0;
			}
			video[(vga_cursor_line*VGA_WIDTH+vga_curs)*2]=((unsigned short)msg[i]); 
			vga_curs++;
		}
	}
}


