#include <stdio.h>
//将数组逆序
void invert(int *pdata,int n);
void main(){
	int i;
	int data[] = {1,2,90,45,32,90,88};
	int *p = data;
	printf("Original array:\n");
	for(i=0;i<7;i++){
		printf("%-4d",*(p+i));
	}
	printf("\n");
	invert(p,7);
	printf("Inverted array:\n");
	for(i=0;i<7;i++)
		printf("%-4d",p[i]);
}

void invert(int *pdata,int n){
	int i,j,temp;
	for(i=0,j=n-1;i<j;i++,j--){
		temp=pdata[i];
		pdata[i]=pdata[j];
		pdata[j]=temp;
	}
}
