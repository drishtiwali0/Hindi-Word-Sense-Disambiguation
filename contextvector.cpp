#include<bits/stdc++.h>
using namespace std;
const long long max_size = 2000;         // max length of strings
//const long long N = 40;                  // number of closest words that will be shown
const long long max_w = 50;              // max length of vocabulary entries
const float threshold=0.3;

int main(int argc, char **argv) {
  	FILE *f,*f2,*f1;
  	char st1[max_size];
  	int bestw,tun,wordvocab;
  	char file_name[max_size], st[100][max_size];
  	float dist, len, bestd, vec[max_size],myinit;
  	long long words, size, a, b, c, d, cn, bi[100];
  	char ch;
  	float *M,*Sen;
  	char *vocab;
	char* tmp;
	char* disWord;
	disWord = (char*)malloc(max_size*sizeof(char));
  	//strcpy(, argv[1]);
  	f = fopen("vectors.bin", "rb");
  	if (f == NULL) {
    		printf("Input file not found\n");
    		return -1;
  	}
  	fscanf(f, "%lld", &words);
  	fscanf(f, "%lld", &size);
  	vocab = (char *)malloc((long long)words * max_w * sizeof(char));
	tmp = (char *)malloc (sizeof(char));
  	//bestw = (char *)malloc(max_size * sizeof(char));
	Sen = (float *)malloc((long long)words * (long long)size * sizeof(float));
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
	f=fopen("sensevector.txt","r");
	f1=fopen("sense_output.txt","w");
	f2=fopen("testfile.txt","r");   
	tun=0;     
        while(1){       
        	disWord[tun]=fgetc(f2);
                if((disWord[tun]=='\n')||(tun>=max_size-1)){
                	disWord[tun]=0;
                        break;
                }    
                tun++;
       }       
       	tun--;
	char tmp1;
	for (b = 0; b < words; b++) {
        	a = 0;
                while (1) {
                	tmp1 = fgetc(f);
                        if (feof(f) || (tmp1 == ' ')){
                                 //      cout<<tmp1<<' '<<a<<endl;
                        	break;
                        }                                 
			if ((a < max_w) && (tmp1 != '\n')) a++;
                                 //cout<<tmp1<<' '<<a-1<<endl;
                }
                for (a = 0; a < size; a++){
                        fscanf(f,"%f",&Sen[a + b * size]);
                                //if(Sen[a+b*size]<0)   cout<<a<<" ";
                }
      	}
        fclose(f); 
	int time=1;
  	while (!feof(f2)) {
    		bestd = 0;
    		bestw = 0;
    		a = 0;
    		while (1) {
      			st1[a] = fgetc(f2);
      			if (st1[a] == '\n') {
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
		wordvocab=-1;
		for(b=0;b<words;b++)
			if(!strcmp(&vocab[b*max_w],disWord))
				break;
		wordvocab=b;
    		for (a = 0; a < cn; a++) {
      			for (b = 0; b < words; b++) if (!strcmp(&vocab[b * max_w], st[a])) break;
      			if (b == words) b = -1;
			if(b==wordvocab)	b=-1;
			myinit=0;
			if(b>0){
				for(tun=0;tun<size;tun++)
					myinit+=	M[tun+wordvocab*size]*M[tun+b*size];
			}
			
			if(myinit<threshold)	b=-1;
      			bi[a] = b;
      			//printf("\nWord: %s  Position in vocabulary: %lld\n with similarity:%f", st[a], bi[a],myinit);
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
		//for (a = 0; a < size; a++) cout<<vec[a]<<' ';
		fscanf(f,"%lld\n",&words);
                //char tmp1;
		/*for (b = 0; b < words; b++) {
                	a = 0;
                	while (1) {
                        	tmp1 = fgetc(f);
                        	if (feof(f) || (tmp1 == ' ')){
				//	cout<<tmp1<<' '<<a<<endl;
					break;
				}
                        	if ((a < max_w) && (tmp1 != '\n')) a++;
				//cout<<tmp1<<' '<<a-1<<endl;
                	}
                	for (a = 0; a < size; a++){ 
				fscanf(f,"%f",&Sen[a + b * size]);
				//if(Sen[a+b*size]<0)	cout<<a<<" ";
			}
        	}
		fclose(f);*/
		
		bestd = -1;
    		bestw= 0;
    		for (c = 0; c < words; c++) {
      			dist = 0;
      			for (a = 0; a < size; a++){
				if(c==0&&vec[a]==Sen[a+c*size])
					cout<<"yo";
				 dist += vec[a] * Sen[a + c * size];
			}
			//cout<<dist<<' ';
        		if (dist > bestd) {
          			bestd=dist;
          			bestw=c;
			}
        	}
		fprintf(stdout,"%d\n",bestw);
      	}
  	return 0;
}

