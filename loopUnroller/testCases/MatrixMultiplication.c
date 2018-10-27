int main(){
	int a[103][103];
	int b[103][103];
	int c[103][103];
	for(int i=0; i<103 ; i++){
		for(int j=0;j<103;j++){
			for(int k=0;k<103;k++){
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return 0;
}
