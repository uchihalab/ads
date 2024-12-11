#include<stdio.h>

int linearSearch(int arr[], int size,int target) {
	for (int i=0;i<size;i++){
		if(arr[i]== target){
			return i;
		}
	}
	return -1;
}

int main(){
	int arr[]={10,20,30,40,50};
	int size = sizeof(arr)/sizeof(arr[0]);
	int target ;
	
	printf("Enter the target to search: ");
	scanf("%d",&target);

	int result=linearSearch(arr,size,target);

	if (result != -1){
		printf("%d",result);
	}
	else{
		printf("element Not Found");
	}
	
}
