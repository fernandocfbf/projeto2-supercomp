// libraries
#include <random>
#include <iostream>
#include <vector> //to use vector
#include <string> //to use string
#include <algorithm> // max
#include<bits/stdc++.h>
#include <cmath>

struct item {
    int value;
    int x;
    int y;
};

// typedefs
typedef std::vector<std::vector<item>> matriz;

using namespace std;

//functions
matriz initialize_matriz(int n, int m);
void calculate_score(matriz &sequencies, string &s1, string &s2, int i, int j);
int compare_letters(matriz &sequencies, string &s1, string &s2, int i, int j);
item compute_score(matriz &filled_matriz, int n, int m);

int main(){
    // initialize variables
    int len_sequence1=0;
    int len_sequence2=0;
    string sequence1;
    string sequence2;
    item score;

    //reads input file
    cin >> len_sequence1;
    cin >> len_sequence2;
    cin >> sequence1;
    cin >> sequence2;

    matriz dna = initialize_matriz(len_sequence1, len_sequence2);
    for (int i=1; i <= len_sequence1; i++){
        for (int j=1; j<= len_sequence2; j++){
            calculate_score(dna, sequence1, sequence2, i, j);
        }
    }

    score = compute_score(dna, len_sequence1, len_sequence2);
    
    return 0;
}

matriz initialize_matriz(int n, int m){
    /*
    input: number of lines and columns (int)
    output: matriz variables [n, m]
    description: initialize a zero matriz variable
    */
    matriz init;
    for (int i=0; i<=n; i++){
        std::vector<item> line;
        for(int j=0; j<=m; j++){
            item e = {value: 0, x: -1, y: -1};
            line.push_back(e);
        }
        init.push_back(line);
    }
    return init;
}

void calculate_score(matriz &sequencies, string &s1, string &s2, int i, int j){
    /*
    input: matriz [n,m], sequence1 and sequence2 (string) ,line (int), column (int)
    output: 
    description: calculates the score for a specific line and column
    */
    int diagonal = compare_letters(sequencies, s1, s2, i, j);
    int delection = sequencies[i-1][j].value-1;
    int inserction = sequencies[i][j-1].value-1;
    item new_item;
    new_item.value = max({0, diagonal, delection, inserction});
    gps(new_item, j, i, delection, inserction, diagonal);
    sequencies[i][j] = new_item;
    return;
}

int compare_letters(matriz &sequencies, string &s1, string &s2, int i, int j){
    /*
    input: matriz [n,m], sequence1 and sequence2 (string) ,line (int), column (int)
    output: result (int)
    decription: calculates the diagonal for a specific line (i) and column (j) on the matriz (sequencies)
    */
    int diagonal1 = sequencies[i-1][j-1].value+2; //match
    int diagonal2 = sequencies[i-1][j-1].value-1; //mismatch
    int diagonal3 = sequencies[i-1][j-1].value-1; //gap
    
    if((s1[i-1] == s2[j-1]) && (i-1 != s1.size() && j-1 != s2.size())){
        return max({diagonal1, diagonal2, diagonal3});
    }
    return max({diagonal2, diagonal3});
}

item compute_score(matriz &filled_matriz, int n, int m){
    /*
    input: filled matriz [n, m]
    output: result (int)
    description: get the max score from the filled matriz 
    */
   item max_score = {value: 0, x: 0, y: 0};
   for(int i=1; i<=n; i++){
       for (int j=1; j<=m; j++){
           if (filled_matriz[i][j].value > max_score.value){
               max_score.value = filled_matriz[i][j].value;
               max_score.x = j; 
               max_score.y = i; 
           }
       }
   }
   return max_score;
}