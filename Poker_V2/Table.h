/*
 * File:   Card.h
 * Author: Kyle
 *
 * Created on April 21, 2023, 5:04 PM
 */

#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <map>
#include <list>
#include <string>
#include <set>

#include "DeckOfCards.h"
#include "AVLTree.h"
#include "BiMatrixGraph.h"

using namespace std;

class Table {
private:
   DeckOfCards myDeck;
   map<string, int> players;
   map<string, int> activePlayers;
   list<Card> player1Cards;
   list<Card> player2Cards;
   list<Card> player3Cards;
   list<Card> dealerCards;
   int highBet;
   int pot;
   int turn;
   int round = 0;
   AVLTree<int> roundHist;
   BiMatrixGraph *handHist;

public:

   Table(int num_Players) {
      pot = 0;
      turn = 1;
      myDeck.shuffleDeck(52);
      handHist = new BiMatrixGraph(14);

      int tempN;
      string tempS;
      cout << "Enter starting cash for all players: ";
      cin >> tempN;

      while (tempN < 5 || cin.fail()) {
         cout << "Please enter a number >= 5: ";
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
         cin >> tempN;
      }

      for (int i = 0; i < num_Players; i++) { //Setting up player maps
         cout << "Enter player " << i + 1 << "'s name: ";
         cin >> tempS;
         players.insert(pair<string, int>(tempS, tempN));
      }
   }

   void setTurn(int t) {
      turn = t;
   }

   void printPlayers() {
      cout << "Player   Cash" << endl;
      cout << "-------------" << endl;
      for (auto pair : players) {
         cout << pair.first << " - $";
         cout << pair.second << endl;
      }
      cout << endl;
      cout << "Press any key and enter to continue: ";
      char dummy;
      cin >> dummy;
   }

   void placeBets() {
      int currBet;
      char tempC;

      if (turn == 1) {
         round++;
         //Add node to history AVL tree
         roundHist.insert(round);
         currBet = 5;
         cout << "Everyone places the buy-in bet of $5." << endl;
         activePlayers.clear();
         activePlayers = players;
         for (auto it = activePlayers.begin(); it != activePlayers.end(); it++) {
            pot += currBet;
            it->second -= currBet;
         }
         cout << "The pot is up to $" << pot << "!" << endl;
      } else if (turn >= 2 && turn <= 5) {
         highBet = 0;
         for (auto it = activePlayers.begin(); it != activePlayers.end(); it++) {
            if (tempC == 'f') {
               if (activePlayers.size() == 1) {
                  cout << "Everyone else folded, ";
                  declareWinner(1);
                  return;
               }
               it = activePlayers.begin();
            }
            tempC = ' ';
            while (tempC != 'f' && tempC != 'c' && tempC != 'r') {
               cout << it->first << ", make a choice: 'f' for fold, 'c' for call, or 'r' for raise: ";
               cin.clear();
               cin.ignore(numeric_limits<streamsize>::max(), '\n');
               cin >> tempC;
            }
            switch (tempC) {
               case 'f':
                  players[it->first] = it->second;
                  cout << it->first << " is out of the game!" << endl;
                  activePlayers.erase(it->first);
                  break;
               case 'c':
                  break;
               case 'r':
                  if (it->second <= 0) {
                     cout << "Unable to raise, calling instead. Press any key and enter to continue.";
                     cin >> tempC;
                     break;
                  }
                  string currPlay = it->first;
                  cout << "Enter amount to raise: ";
                  cin >> highBet;
                  if (it->second >= highBet) {
                     it->second -= highBet;
                     pot += highBet;
                  } else {
                     cout << "All in!" << endl;
                     highBet = it->second;
                     it->second = 0;
                     pot += highBet;
                  }
                  raise(currPlay);
                  cout << "New pot is $" << pot << "! Press any key and enter to continue: " << endl;
                  cin >> tempC;
                  return;
            }
         }
      }
   }

   void startTurn() {
      string tempS;
      int currPlayer = 1;

      if (activePlayers.size() == 1 && turn < 10) {
         cout << "Everyone else folded, ";
         map<string, int>::iterator it = activePlayers.begin();
         players[it->first] = it->second;
         declareWinner(1);
         return;
      }

      if (turn == 1) {
         while (!player1Cards.empty()) {
            player1Cards.pop_back();
         }
         while (!player2Cards.empty()) {
            player2Cards.pop_back();
         }
         while (!player3Cards.empty()) {
            player3Cards.pop_back();
         }
         while (!dealerCards.empty()) {
            dealerCards.pop_back();
         }
         myDeck.dealHand(player1Cards, 2); //Give each player 2 cards
         myDeck.dealHand(player2Cards, 2);
         myDeck.dealHand(player3Cards, 2);


         for (auto it = activePlayers.begin(); it != activePlayers.end(); it++) {
            system("clear");
            cout << it->first << ", press any key and then enter to view your hand: ";
            cin >> tempS;
            switch (currPlayer) {
               case 1:
                  myDeck.viewHand(player1Cards);
                  break;
               case 2:
                  myDeck.viewHand(player2Cards);
                  break;
               case 3:
                  myDeck.viewHand(player3Cards);
                  break;
               default:
                  break;
            }

            currPlayer++;
         }
      } else if (turn == 2) {
         myDeck.dealHand(dealerCards, 3); // Give the dealer 3 cards
         for (auto it = activePlayers.begin(); it != activePlayers.end(); it++) {
            system("clear");
            cout << it->first << ", press any key and then enter to view your hand with the cards on the table: ";
            cin >> tempS;
            switch (currPlayer) {
               case 1:
                  myDeck.viewHand(player1Cards, dealerCards);
                  break;
               case 2:
                  myDeck.viewHand(player2Cards, dealerCards);
                  break;
               case 3:
                  myDeck.viewHand(player3Cards, dealerCards);
                  break;
               default:
                  break;
            }
            currPlayer++;
         }
      } else if (turn == 3) {
         dealerCards.push_front(myDeck.dealCard()); // Give the dealer 1 more card
         for (auto it = activePlayers.begin(); it != activePlayers.end(); it++) {
            system("clear");
            cout << it->first << ", press any key and then enter to view your hand with the cards on the table: ";
            cin >> tempS;
            switch (currPlayer) {
               case 1:
                  myDeck.viewHand(player1Cards, dealerCards);
                  break;
               case 2:
                  myDeck.viewHand(player2Cards, dealerCards);
                  break;
               case 3:
                  myDeck.viewHand(player3Cards, dealerCards);
                  break;
               default:
                  break;
            }
            currPlayer++;
         }
      } else if (turn == 4) {
         dealerCards.push_front(myDeck.dealCard()); // Give the dealer 1 more card
         for (auto it = activePlayers.begin(); it != activePlayers.end(); it++) {
            system("clear");
            cout << it->first << ", press any key and then enter to view your hand with the cards on the table: ";
            cin >> tempS;
            switch (currPlayer) {
               case 1:
                  myDeck.viewHand(player1Cards, dealerCards);
                  break;
               case 2:
                  myDeck.viewHand(player2Cards, dealerCards);
                  break;
               case 3:
                  myDeck.viewHand(player3Cards, dealerCards);
                  break;
               default:
                  break;
            }
            currPlayer++;
         }
      } else if (turn == 5) {
         pair<int, int> p1(0, 0);
         pair<int, int> p2(0, 0);
         pair<int, int> p3(0, 0);
         for (auto itr = activePlayers.begin(); itr != activePlayers.end(); itr++) {
            cout << endl << itr->first << "'s hand result: ";
            players[itr->first] = itr->second;
            switch (currPlayer) {
               case 1:
                  p1 = myDeck.evaluateHand(player1Cards, dealerCards);
                  break;
               case 2:
                  p2 = myDeck.evaluateHand(player2Cards, dealerCards);
                  break;
               case 3:
                  p3 = myDeck.evaluateHand(player3Cards, dealerCards);
                  break;
               default:
                  break;
            }
            currPlayer++;
         }
         int winner = findWinner(p1, p2, p3);
         declareWinner(winner);
      }

      turn++;
   }

   int findWinner(pair<int, int> p1, pair<int, int> p2, pair<int, int> p3) {
      //Add each hands weight to hand history
      handHist->incEdge(0, p1.first + 3);
      handHist->incEdge(1, p2.first + 3);
      handHist->incEdge(2, p3.first + 3);

      pair<int, int> largest = p1;
      if (p2.first > largest.first || (p2.first == largest.first && p2.second > largest.second)) {
         largest = p2;
      }
      if (p3.first > largest.first || (p3.first == largest.first && p3.second > largest.second)) {
         largest = p3;
      }

      //Add players hand value to round history
      roundHist.addHandVal(largest.first, round);

      if (largest.first == p1.first && largest.second == p1.second) {
         return 1;
      }
      if (largest.first == p2.first && largest.second == p2.second) {
         return 2;
      }
      if (largest.first == p3.first && largest.second == p3.second) {
         return 3;
      }
      return 1;
   }

   void declareWinner(int player) {
      map<string, int>::iterator it;
      it = activePlayers.begin();
      for (int i = 1; i < player; i++) {
         it++;
      }

      cout << it->first << " Wins!" << endl;

      addEarnings(it->first);
   }

   void addEarnings(string winner) {
      map<string, int>::iterator itr = players.begin();
      while (itr->first != winner) {
         itr++;
      }

      turn = 100;
      itr->second += pot;

      //Add winner name and winnings
      roundHist.addNameMoney(winner, pot, round);

      pot = 0;
      printPlayers();
   }

   void raise(string raiser) {
      char tempC = ' ';
      int timesAsked = 0;

      for (auto itr = activePlayers.begin(); itr != activePlayers.end(); itr++) {
         timesAsked++;
         if (itr->first != raiser) {
            while (tempC != 'y' && tempC != 'n') {
               cout << itr->first << ", would you like to match the raise of " << highBet << "? 'y' or 'n': ";
               cin.clear();
               cin.ignore(numeric_limits<streamsize>::max(), '\n');
               cin >> tempC;
            }
            if (tempC == 'y') {
               if (itr->second >= highBet) {
                  itr->second -= highBet;
                  pot += highBet;
               } else {
                  cout << "All in!" << endl;
                  pot += itr->second;
                  itr->second = 0;
               }
            }
            if (tempC == 'n') {
               players[itr->first] = itr->second;
               cout << itr->first << " is out of the game!" << endl;
               activePlayers.erase(itr->first);
               if (activePlayers.size() == 1 || activePlayers.size() <= timesAsked) {
                  return;
               }
            }\
            tempC = ' ';
         }
      }
   }

   void displayHistory() {
      string names[4] = {" ", " ", " ", " "};
      int i = 0;
      for (auto it = players.begin(); it != players.end(); it++) {
         names[i] = it->first;
         i++;
      }
      roundHist.inOrder();
      handHist->print(names);
   }
};

#endif /* Table.h */

