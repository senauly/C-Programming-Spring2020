#include<stdio.h>

typedef struct Pixel{
	char value;
	int row;
	int column;
}Pixel;

void read_image(Pixel pixels[]);
void fill_canvas(Pixel pixels[], Pixel canvas[][9]);
void draw_image(Pixel canvas[][9]);
int search(Pixel pixels[],int i,int j);
int main(){
	int row_number = 6, col_number = 9;
	int total_pixel_number = row_number  * col_number;
	Pixel pixels[total_pixel_number];
	Pixel canvas[row_number][col_number];
	read_image(pixels);
	fill_canvas(pixels,canvas);
	draw_image(canvas);
	return 0;
}

void read_image(Pixel pixels[]){
	FILE *fp;
	char x,y;
	char temp[10];
	int i = 0;

	fp = fopen("image.txt","r");

	while(i < 54){
		
		fscanf(fp,"%[^;] %*c",temp);
		sscanf(temp,"%[^,] %*c %[^,] %*c %c",&pixels[i].value,&x,&y);
		pixels[i].row = x - '0';
		pixels[i].column = y - '0';
		i ++;
	}
}

void fill_canvas(Pixel pixels[], Pixel canvas[][9]){
	int x;
	for (int i = 0; i < 6; ++i){
		for (int j = 0; j < 9; ++j){
			x = search(pixels,i,j);
			if(x != -1){
				canvas[i][j].value = pixels[x].value;
			}
		}
	}
}

int search(Pixel pixels[],int i,int j){
	int result = -1;
	for (int a = 0; a < 54; ++a){
		if(pixels[a].row == i && pixels[a].column == j) result = a; 
	}

	return(result);
}

void draw_image(Pixel canvas[][9]){
	for (int i = 0; i < 6; ++i){
		for (int j = 0; j < 9; ++j){
			printf("%c",canvas[i][j].value);
		}

		printf("\n");
	}
}

