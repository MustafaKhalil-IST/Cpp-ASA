//compile using g++ -std=c++11 <programFileName>.cpp -o <executableName>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>
#include <fstream>

#define MIN_PER_RANK 1 /* Nodes/Rank: How 'fat' the DAG should be.  */
#define MAX_PER_RANK 1
#define MIN_RANKS 1000   /* MUDAR AQUI O NUMERO DE VERTICES.  */
#define MAX_RANKS 1000
#define PERCENT 40     /* Chance of having an Edge.  */

using namespace std;

int main (void)
{
  ofstream temp, final;
  temp.open(".temp");
  final.open("output");
  string line;

  int i, j, k,nodes = 0;
  int arestas = 0;
  srand (time (NULL));

  int ranks = MIN_RANKS
              + (rand () % (MAX_RANKS - MIN_RANKS + 1));

  for (i = 0; i < ranks; i++)
    {
      /* New nodes of 'higher' rank than all nodes generated till now.  */
      int new_nodes = MIN_PER_RANK
                      + (rand () % (MAX_PER_RANK - MIN_PER_RANK + 1));

      /* Edges from old nodes ('nodes') to new ones ('new_nodes').  */
      for (j = 0; j < nodes; j++){
         for (k = 0; k < new_nodes; k++) {
           if ( (rand () % 100) < PERCENT) {
            temp<< to_string(j+1) << " " <<to_string(k + nodes+1) << "\n"; /* An Edge.  */
            arestas++;
          }
        }
      }
      nodes += new_nodes; /* Accumulate into old node set.  */
    }
    temp.close();
    ifstream temp2;
    temp2.open(".temp");
  final<<to_string(MAX_RANKS) << " "<<to_string(arestas) <<"\n";
    while ( getline (temp2,line) )
    {
      final << line << '\n';
    }
    temp2.close();
    final.close();
    remove(".temp");
  return 0;
}
