#include<bits/stdc++.h>
#include<stdlib.h>
using namespace std;
const long long max_size = 2000;         // max length of strings
//const long long N = 40;                  // number of closest words that will be shown
const long long max_w = 50;              // max length of vocabulary entries


int main(int argc, char **argv) {
  	FILE* f;
	FILE* f1;
  	char st1[max_size];
  //	char *bestw[N];
  	char file_name[max_size], st[100][max_size];
  	float dist, len, vec[max_size];
  	long long words, size, a, b, c, d, cn, bi[100], numsense;
  	char ch;
  	float *M;
  	char *vocab;
  	//if (argc < 2) {
    	//
	//	printf("Usage: ./distance <FILE>\nwhere FILE contains word projections in the BINARY FORMAT\n");
    	//	return 0;
  	//}
  	//strcpy(file_name, argv[1]);
  	f = fopen("vectors.bin", "rb");
  	if (f == NULL) {
    		printf("Input file not found\n");
    		return -1;
  	}
  	fscanf(f, "%lld", &words);
  	fscanf(f, "%lld", &size);
  	vocab = (char *)malloc((long long)words * max_w * sizeof(char));
  	//for (a = 0; a < N; a++) bestw[a] = (char *)malloc(max_size * sizeof(char));
  	M = (float *)malloc((long long)words * (long long)size * sizeof(float));
  	if (M == NULL) {
    		printf("Cannot allocate memory: %lld MB    %lld  %lld\n", (long long)words * size * sizeof(float) / 1048576, words, size);
    		return -1;
  	}
  	for (b = 0; b < words; b++) {
    		a = 0;
    		while (1) {
      			vocab[b * max_w + a] = fgetc(f);
      			if (feof(f) || (vocab[b * max_w + a] == ' ')) break;
      			if ((a < max_w) && (vocab[b * max_w + a] != '\n')) a++;
    		}
    		vocab[b * max_w + a] = 0;
    		for (a = 0; a < size; a++) fread(&M[a + b * size], sizeof(float), 1, f);
    		len = 0;
    		for (a = 0; a < size; a++) len += M[a + b * size] * M[a + b * size];
    		len = sqrt(len);
    		for (a = 0; a < size; a++) M[a + b * size] /= len;
  	}
  	fclose(f);
  	f=fopen("my_output.txt","r");
	f1=fopen("sensevector.txt","w+");
	fscanf(f,"%lld\n",&numsense);
	fprintf(f1,"%lld\n",numsense);
	for(int i=0;i<numsense;i++){
    		a = 0;
    		while (1) {
      			st1[a] = fgetc(f);
      			if ((st1[a] == '\n') || (a >= max_size - 1)) {
        			st1[a] = 0;
        			break;
      			}
      			a++;
    		}
    		//if (!strcmp(st1, "EXIT")) break;
    		cn = 0;
    		b = 0;
    		c = 0;
    		while (1) {
      			st[cn][b] = st1[c];
      			b++;
      			c++;
      			st[cn][b] = 0;
      			if (st1[c] == 0) break;
      			if (st1[c] == ' ') {
        			cn++;
        			b = 0;
        			c++;
      			}
    		}
    		cn++;
	//	for(a=0;a<words;a++)
			cout<<cn;
    		for (a = 0; a < cn; a++) {
      			for (b = 0; b < words; b++) if (!strcmp(&vocab[b * max_w], st[a])) break;
      			if (b == words) b = -1;
      			bi[a] = b;
      			printf("\nWord: %s  Position in vocabulary: %lld\n", st[a], bi[a]);
    		}
    		for (a = 0; a < size; a++) vec[a] = 0;
    		for (b = 0; b < cn; b++) {
      			if (bi[b] == -1) continue;
      			for (a = 0; a < size; a++) vec[a] += M[a + bi[b] * size];
    		}
    		len = 0;
    		for (a = 0; a < size; a++) len += vec[a] * vec[a];
    		len = sqrt(len);
    		for (a = 0; a < size; a++) vec[a] /= len;
	//	printf("%lf",vec[0]);
		int tmp=i;
		char str[30];
		int d=0;
		if(!tmp){
			str[0]=48;
			d++;
		}
		while(tmp){
			str[d]=tmp%10+48;
			tmp/=10;
			d++;
		}
    		for(int y=d-1;y>=0;y--)	fputc(str[y],f1);
		fputc(' ',f1);
		for(a=0;a<size-1;a++)	fprintf(f1,"%f ",vec[a]);
		fprintf(f1,"%f\n",vec[size-1]);
		
  	}
	return 0;
}
