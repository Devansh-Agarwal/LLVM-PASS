int main(){
	int a[7] = {10,3,5,8,4,6,7};
	int odd[7];
	for(int l=0;l<7;l++)
		odd[l]=a[l]%2==0?1:0;
	return 0;
}
