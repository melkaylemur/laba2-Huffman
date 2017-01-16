#include <cstdlib>
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include <time.h>
#include <vector>
using namespace std;

void writeStrFile(char *name_file, vector<unsigned char> &str, int size_str){
    FILE *file = fopen(name_file, "wb");
    for (int i = 0; i < size_str; i++){
        int k = str[i];
	fprintf(file, "%d", k);
    }
    fclose(file);
}

void generateStream(float p[5][5], int N, char *name_file){
    int state = 0;
    FILE *file = fopen(name_file, "wb");
    std::vector <unsigned char> str;
    for (int i = 0; i < N; i++){
	float vr = (float)rand()/RAND_MAX;
	if (vr < p[state][0]){
	    state = 0;
	}
	else if (vr >= p[state][0] && vr < p[state][0]+p[state][1]){
	    state = 1;
	}
	else if (vr >= p[state][0]+p[state][1] && vr < p[state][0]+p[state][1] + p[state][2]){
	    state = 2;
	}
	else if (vr >= p[state][0]+p[state][1] + p[state][2] && vr < p[state][0]+p[state][1] + p[state][2]+p[state][3]){
	    state = 3;
	}
	else if (vr >= p[state][0]+p[state][1] + p[state][2]+p[state][3] && vr < 1){
	    state = 4;
	}
        str.push_back(state);
    }
    writeStrFile(name_file, str, str.size());
}

int main(int argc, char **argv) {
    srand(time(NULL));
    int N = 100;
    char *name_stream_file = "stream.txt";
    float p_standart[5][5] = {{0.25, 0.25, 0.1, 0.2, 0.2},
			      {0.1, 0.1, 0.1, 0.65, 0.05},
			      {0.1, 0.3, 0.2, 0.2, 0.2},
			      {0.2, 0.3, 0.1, 0.1, 0.3},
			      {0.3, 0.1, 0.2, 0.3, 0.1}};
    /*float p_generate[5][5];
    for (int i = 0; i < 5; i++){
	float sum = 1.0;
	for (int j = 0; j < 4; j++){
	    p_generate[i][j] = (float)rand()/RAND_MAX;
	    while (p_generate[i][j] > sum){
		p_generate[i][j] = (float)rand()/RAND_MAX;
		if (p_generate[i][j] < 0.0001){
		    p_generate[i][j] = 0;
		}
	    }
	    sum -= p_generate[i][j];
	}
	p_generate[i][4] = sum;
    }*/
    /*for (int i = 0; i < 5; i++){
	float vr = 0;
	for (int j = 0; j < 5; j++){
	    vr += p_generate[i][j];
	    std::cout << p_generate[i][j] << " " ; 
	}
	std::cout << '\n';
	std::cout<< vr << '\n';
    }*/
    generateStream(p_standart, N, name_stream_file);
    std::cout << "Hello, world!" << std::endl;
    return 0;
}