/* 
 * File:   BiMatrixGraph.h
 * Author: Kyle
 *
 * Created on June 2, 2023, 10:48 AM
 */

#ifndef BIMATRIXGRAPH_H
#define BIMATRIXGRAPH_H

#include <iostream>
#include <string>
#include <array>

using namespace std;

class BiMatrixGraph {
private:
   int **graph;
   int numVerts;

public:

   BiMatrixGraph(int verts) {
      numVerts = verts;
      graph = new int *[numVerts];
      for (int i = 0; i < numVerts; i++) {
         graph[i] = new int[numVerts];
         for (int j = 0; j < numVerts; j++) {
            graph[i][j] = 0;
         }
      }
   }
   // Modified addEdge to increment weight for specific hand results for each player

   void incEdge(int x, int y) {
      graph[x][y] += 1;
      graph[y][x] += 1;
   }

   void deleteEdge(int x, int y) {
      graph[x][y] = 0;
      graph[y][x] = 0;
   }

   //Modified for Poker

   void print(string names[]) {
      int i = 0;
      while (names[i] != " ") {
         cout << names[i] << "'s stats: ";
         cout << "\t";
         highestHand(i);
         cout << endl << "\t\t";
         commonHand(i);
         cout << endl;
         i++;
      }
   }

   void highestHand(int i) {
      int highHand = 0;
      for (int j = 4; j < 13; j++) {
         if (graph[i][j] > 0) {
            highHand = j;
         }
      }

      cout << "Highest hand: ";
      switch (highHand) {
         case 4:
            cout << "High Card! ";
            break;
         case 5:
            cout << "One Pair! ";
            break;
         case 6:
            cout << "Two Pairs! ";
            break;
         case 7:
            cout << "Three of a Kind! ";
            break;
         case 8:
            cout << "Straight! ";
            break;
         case 9:
            cout << "Flush! ";
            break;
         case 10:
            cout << "Full House! ";
            break;
         case 11:
            cout << "Four of a Kind! ";
            break;
         case 12:
            cout << "Straight Flush! ";
            break;
         case 13:
            cout << "Royal Flush! ";
            break;
      }
   }

   void commonHand(int i) {
      int commonHand = 0;
      int tmp = 0;
      for (int j = 4; j < 13; j++) {
         if (graph[i][j] >= tmp) {
            tmp = graph[i][j];
            commonHand = j;
         }
      }

      cout << "Most common hand: ";
      switch (commonHand) {
         case 4:
            cout << "High Card! ";
            break;
         case 5:
            cout << "One Pair! ";
            break;
         case 6:
            cout << "Two Pairs! ";
            break;
         case 7:
            cout << "Three of a Kind! ";
            break;
         case 8:
            cout << "Straight! ";
            break;
         case 9:
            cout << "Flush! ";
            break;
         case 10:
            cout << "Full House! ";
            break;
         case 11:
            cout << "Four of a Kind! ";
            break;
         case 12:
            cout << "Straight Flush! ";
            break;
         case 13:
            cout << "Royal Flush! ";
            break;
      }
   }
};

#endif /* BIMATRIXGRAPH_H */

