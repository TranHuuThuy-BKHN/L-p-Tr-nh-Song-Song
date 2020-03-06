#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX 40
#define TOLERANCE 0.0001

#define MAX_TEMP 1
#define MIN_TEMP 0

void init(float *c, int rows, int cols){
	int i, j;
	for(i = 0; i < rows; i++){
		for(j = 0; j < cols; j++)
			*(c + i * cols + j) = 0;
	}
}

int main(int args, char *argv[]){
	
	int i, j;
	float *c = (float *)(malloc(MAX * MAX * sizeof(float)));
	init(c, MAX, MAX);
	
	float epsilon = 0;
	
	do{
		epsilon = 0;
		for(i = 0; i < MAX; i++){
			for(j = 0; j < MAX; j++){
				
				if(i == 0) *(c + i * MAX + j) = MAX_TEMP;
				else if(i == MAX - 1) *(c + i * MAX + j) = MIN_TEMP;
				else{
					float south = *(c + (i - 1) * MAX + j),
						  north = *(c + (i + 1) * MAX + j),
						  west  = j == 0 ? *(c + i * MAX + MAX - 1) : *(c + i * MAX + j - 1),
						  east  = j == MAX - 1 ? *(c + i * MAX) : *(c + i * MAX + j + 1);
					
					float c_new  = 0.25 * (south + north + west + east);
					float balance = fabs(c_new - *(c + i * MAX + j));
					*(c + i * MAX + j) = c_new;
					
					if(balance > TOLERANCE){
						epsilon = balance;
					}
				}
			}
		}
		
	}while(epsilon > TOLERANCE);
	
		for(i = 0; i < MAX; i++){
			for(j = 0; j < MAX; j++)
				printf("%.2f ", *(c + i*MAX + j));
			printf("\n");
		}
			printf("\n");
	
	return 0;
}
