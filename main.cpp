#include <cstdlib>
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <bitset>
#include "HuffmanCoder.h"
#include "ContecstHuffmanCoder.h"

using namespace std;

void writeStrFile(char *name_file, vector<unsigned char> &str, int size_str){
    FILE *file = fopen(name_file, "wb");
    for (int i = 0; i < size_str; i++){
        int k = str[i];
	fprintf(file, "%d", k);
    }
    fclose(file);
}

void writeBitsStr(char *name_file, vector <bool> &encod_str){
    FILE *file = fopen(name_file, "wb");
    bitset <8> byte;
    unsigned char ch;
    bool exit = false;
    for (int i = 0; i < encod_str.size(); i += 8){
        for (int j = i; j < i + 8; j++){
            if (j >= encod_str.size()){
                exit = true;
            }
            else            {
                byte[j - i] = encod_str[j];
            }
        }
        ch = byte.to_ulong();
        fwrite(&ch, 1, sizeof(unsigned char), file);
        if (exit == true)
            break;
    }
    fclose(file);
}

void readStrFile(char *name_file, vector<unsigned char> &str, int size_str){
    FILE *file = fopen(name_file, "rb");
    char *ch = new char [size_str];
    fread(ch, 1, size_str, file);	
    for (int i = 0; i < size_str; i++){
	str.push_back(ch[i]);
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

void prov(vector<unsigned char>stream, vector<unsigned char>stream2){
    for (int i = 0; i < stream2.size(); i++){
        int dif = stream2[i] - stream[i];
        if (dif != 0){
            printf("Erorr dif = %d/n", i);
        }
    }
}

int main(int argc, char **argv) {
    srand(time(NULL));
    int N = 1000000;
    char *name_stream_file = "stream.txt";
    char *name_file_en_hc_1 = "stream_encode_ch_1.txt";
    char *name_file_en_hc_2 = "stream_encode_ch_2.txt";
    char *name_file_dec_hc_1 = "stream_decode_ch_1.txt";
    char *name_file_dec_hc_2 = "stream_decode_ch_2.txt";
    /*float p_standart[5][5] = {{0.25, 0.25, 0.1, 0.2, 0.2},
			      {0.1, 0.1, 0.1, 0.65, 0.05},
			      {0.1, 0.3, 0.2, 0.2, 0.2},
			      {0.2, 0.3, 0.1, 0.1, 0.3},
			      {0.3, 0.1, 0.2, 0.3, 0.1}};*/
    float p_generate[5][5];
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
    }
    for (int i = 0; i < 5; i++){
	float vr = 0;
	for (int j = 0; j < 5; j++){
	    vr += p_generate[i][j];
	    std::cout << p_generate[i][j] << " " ; 
	}
	std::cout << '\n';
	std::cout<< vr << '\n';
    }
    generateStream(p_generate, N, name_stream_file);
    
    vector<unsigned char>stream;
    readStrFile(name_stream_file, stream, N);
    
    //Huffman
    HuffmanCoder *hc = new HuffmanCoder();
    hc->buildTree(stream);
    Node *root = hc->tree.front();
    hc->printTree(root, 0);
    hc->buildTableTree(root);
    
    for (map<char,vector<bool> >::iterator itr = hc->table.begin(); itr != hc->table.end(); ++itr){
        for (vector<bool>::iterator it_b = itr->second.begin(); it_b != itr->second.end(); ++it_b){
            cout << *it_b;
        }
        cout << " - " << itr->first << '\n';
    }
    vector<unsigned char>stream_encode;
    vector<unsigned char>stream_decode;
    hc->encode(stream, stream_encode);
    hc->decode(stream_encode, stream_decode);   
    prov(stream, stream_decode);
     
    
    //Contecst Huffman 1
    float p_statistic[5][5];
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            p_statistic[i][j] = 0;
        }
    }
    int pre = stream[0]-'0';
    for (int i = 1 ; i < stream.size(); i++){
        int post = stream[i]-'0';
        p_statistic[pre][post]++;
        pre = stream[i]-'0';
    }
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            p_statistic[i][j] /= stream.size();
        }
    }  
    vector<unsigned char>con_stream_encode_1;
    vector<unsigned char>con_stream_decode_1;
    ContecstHuffmanCoder *chc = new ContecstHuffmanCoder();
    chc->buildTree(p_statistic);
    chc->encode(stream, con_stream_encode_1, name_file_en_hc_1);
    chc->decode(con_stream_encode_1, con_stream_decode_1, name_file_en_hc_1, name_file_dec_hc_1);    
    prov(stream, con_stream_decode_1);
    
    //Contecst Huffman 2
    vector<unsigned char>con_stream_encode_2;
    vector<unsigned char>con_stream_decode_2;
    ContecstHuffmanCoder *chc2 = new ContecstHuffmanCoder();
    chc2->buildTree(p_generate);
    chc2->encode(stream, con_stream_encode_2, name_file_en_hc_2);
    chc2->decode(con_stream_encode_2, con_stream_decode_2, name_file_en_hc_2, name_file_dec_hc_2);    
    prov(stream, con_stream_decode_2);
    
    std::cout << "Hello, world!" << std::endl;
    return 0;
}