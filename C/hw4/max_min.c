#include <stdio.h>

void max_min(int arr[]);

void main(){
	int arr[10] = {1,2,3,4,5,6,7,8,9,10};
	
	max_min(arr);
}

void max_min(int arr[]){
	int max = arr[0];
	int min = arr[0];
	
	for(int i = 1; i < 10; i++) { 
		if(arr[i] > max) { 
			max = arr[i]; 
		} 
		if(arr[i] < min) { 
			min = arr[i]; 
		} 
	}

	printf("�}�C�����̤j�ȬO: %d\n", max); 
	printf("�}�C�����̤p�ȬO: %d\n", min);
}
