#include <stdio.h>    
#include <stdlib.h>  
int main(){  
	int a[256],n,i;    
	printf("Enter the number to convert: ");    
	scanf("%d",&n);    
	for(i=0;n>0;i++){
		a[i]=n%2;    
		n=n/2;    
	}    
	printf("%d\n",i); 
	printf("Binary of Given Number is: ");    
	for(i=i-1;i>=0;i--){    
		printf("%d",a[i]);    
	}
	printf("\n");   
	return 0;  
}  