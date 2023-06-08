/* 
 * File:   BiMatrixGraph.h
 * Author: Kyle
 *
 * Created on June 2, 2023, 10:48 AM
 */

#ifndef BIMATRIXGRAPH_H
#define BIMATRIXGRAPH_H

#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <array>

using namespace std;

class BiMatrixGraph {
private:
   int **graph;
   int numVerts;

   //Neither functions used in this project

   void printMST(int parent[]) {
      int total = 0;
      cout << "Edge \tWeight" << endl;
      for (int i = 1; i < numVerts; i++) {
         cout << parent[i] << " - " << i << " \t"
                 << graph[i][parent[i]] << endl;
         total += graph[i][parent[i]];
      }

      cout << "Total weight: " << total << endl << endl;
   }

   int minKey(int distance[], bool visited[]) {

      int min = INT_MAX, min_index;

      for (int v = 0; v < numVerts; v++) {
         if (visited[v] == false && distance[v] <= min) {
            min = distance[v], min_index = v;
         }
      }

      return min_index;
   }

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

   //Last 5 functions not used in this project, but tested and are working in separate tester file

   void primMST() {
      // Array to store constructed MST
      int parent[numVerts];

      // Key values used to pick minimum weight edge in cut
      int distance[numVerts];

      // To represent set of vertices included in MST
      bool visited[numVerts];

      // Initialize all keys as INFINITE
      for (int i = 0; i < numVerts; i++) {
         distance[i] = INT_MAX, visited[i] = false;
      }

      // Distance to first vertex to itself is 0
      distance[0] = 0;

      // First node is always root of MST
      parent[0] = -1;

      for (int count = 0; count < numVerts - 1; count++) {

         // Pick the minimum weighted distance to the vertices not visited
         int u = minKey(distance, visited);

         // Add the picked vertex to the visited set
         visited[u] = true;

         for (int v = 0; v < numVerts; v++)

            if (graph[u][v] && visited[v] == false && graph[u][v] < distance[v]) {
               parent[v] = u, distance[v] = graph[u][v];
            }
      }

      // Print the constructed MST
      printMST(parent);
   }

   void minDistDijk(int main) {
      int distance[numVerts];
      bool visited[numVerts];

      for (int i = 0; i < numVerts; i++) {
         distance[i] = INT_MAX;
         visited[i] = false;
      }

      distance[main] = 0; // Distance to itself is 0

      for (int i = 0; i < numVerts; i++) {
         //Find min distance
         int min = minKey(distance, visited);
         visited[min] = true;
         for (int j = 0; j < numVerts; j++) {
            //Update distances to neighboring nodes if needed
            if (!visited[j] && graph[min][j] && distance[min] != INT_MAX && distance[min] + graph[min][j] < distance[j]) {
               distance[j] = distance[min] + graph[min][j];
            }
         }
      }

      cout << "Vertex\t\tDistance from selected vertex" << endl;
      for (int i = 0; i < numVerts; i++) {
         cout << i << "\t\t\t" << distance[i] << endl;
      }

   }

   void addVertex() {
      graph[numVerts] = new int[numVerts];

      for (int i = 0; i < numVerts + 1; i++) {
         graph[numVerts][i] = 0;
      }

      numVerts++;
   }

   void delVertex(int v) {
      if (v > numVerts) {
         cout << "Invalid Vertex" << endl;
         return;
      }
      //Shift Up
      for (int i = 0; i < numVerts; i++) {
         for (int j = v; j < numVerts; j++) {
            graph[i][j] = graph[i][j + 1];
         }
      }
      //Shift Left
      for (int i = v; i < numVerts - 1; i++) {
         graph[i] = graph[i + 1];
      }

      numVerts--;
      delete [] graph[numVerts];
   }

   void deleteEdge(int x, int y) {
      graph[x][y] = 0;
      graph[y][x] = 0;
   }


};

#endif /* BIMATRIXGRAPH_H */

