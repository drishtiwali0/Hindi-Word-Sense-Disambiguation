#include<bits/stdc++.h>
using namespace std;
int main()
{
	int num=0,final=0,s1,s2;
	FILE*f1;
	FILE*f2;
	f1=fopen("final_sense_100.txt","r");
	f2=fopen("man150.txt","r");
	while(!feof(f2)){
		fscanf(f1,"%d",&s1);
		fscanf(f2,"%d",&s2);
		if(s1==s2)
			final++;
		num++;
	}
	fclose(f1);
	fclose(f2);
	printf("Percentage accuaracy %f\n",(final*100.0)/(num*1.0));
	printf("Number of sentences %d\n",num);
	return 0;
}
