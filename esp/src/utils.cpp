
void invert(char* a, int start, int end)
{
	for(;start<end;++start,--end)
	{
		char temp=a[start];
		a[start]=a[end];
		a[end]=temp;
	}
}

char* tochar(int it)
{
	char * temp=new char[1000];
	int mod=10;
	int left=it%mod;
	int size=it/mod;
	int i=0;
	while(size!=0 || left!=0)
	{
		temp[i]=left+'0';
		it/=10;
		left=it%mod;
		size=it/mod;
		++i;
	}
	temp[i]=0;//注意最后补上终止符号0
	invert(temp, 0, i-1);
	return temp;
}
