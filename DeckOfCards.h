/* 
 * File:   DeckOfCards.h
 * Author: Kyle
 *
 * Created on April 21, 2023, 5:13 PM
 */

#ifndef DECKOFCARDS_H
#define DECKOFCARDS_H
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <queue>
#include <random>       
#include <chrono>
#include <iterator>
#include <algorithm>
#include <utility>
#include <iostream>

#include "Card.h"

using namespace std;

class DeckOfCards {
private:
   Card deck[52];
   int currentCard = 0;

   pair<int, int> checkHand(int faces[], int suits[]) {
      bool flush = false;
      bool straight = false;
      bool three = false;
      bool pairs = false;
      int highCard;
      int highStraight;


      //Check for errors
      if (faces[0] != 0 || suits[0] != 0) {
         return make_pair(-1, -1);
      }

      //Check highest card
      for (int i = 0; i < 14; i++) {
         if (faces[i] > 0) {
            highCard = i;
         }
      }


      //Check for flush
      for (int i = 0; i < 4; i++) {
         if (suits[i] == 5) {
            flush = true;
            break;
         }
      }

      //Check for straight
      int counter = 0;
      for (int i = 0; i < 14; i++) {
         if (faces[i] == 1) {
            counter++;
         } else {
            counter = 0;
         }
         if (counter == 5) {
            highStraight = i;
            straight = true;
         }
      }

      //Check for special flushes
      if (flush && straight) {
         if (faces[10] == 1 && faces[11] == 1 && faces[12] == 1 && faces[13] == 1 && faces[14] == 1) {
            cout << "Royal Flush!" << endl;
            return make_pair(10, 0);
         } else {
            cout << "Straight Flush!" << endl;
            return make_pair(9, 0);
         }
      }

      //Check for 4 of a kind
      for (int i = 0; i < 14; i++) {
         if (faces[i] == 4) {
            cout << "Four of a kind!" << endl;
            return make_pair(8, i);
         }
      }

      //Check for full house
      int highestPair = 0;
      for (int i = 2; i <= 14; i++) {
         if (faces[i] == 3) {
            three = true;
            highestPair = i;
         } else if (faces[i] == 2) {
            pairs = true;
            highestPair = i;
         }
      }
      if (three && pairs) {
         cout << "Full House!" << endl;
         return make_pair(7, highestPair);
      }

      if (flush) {
         cout << "Flush!" << endl;
         return make_pair(6, highCard);
      }

      if (straight) {
         cout << "Straight!" << endl;
         return make_pair(5, highStraight);
      }

      if (three) {
         cout << "Three of a kind!" << endl;
         return make_pair(4, highestPair);
      }

      //Check for two pairs
      int numPairs = 0;
      for (int i = 0; i <= 14; i++) {
         if (faces[i] == 2) {
            numPairs++;
            highestPair = i;
         }
      }
      if (numPairs == 2) {
         cout << "Two pairs!" << endl;
         return make_pair(3, highestPair);
      }
      if (numPairs == 1) {
         cout << "One pair!" << endl;
         return make_pair(2, highestPair);
      }
      cout << "Nothing :(" << endl;
      return make_pair(1, highCard);
   }
public:

   DeckOfCards() {
      string faces[] = {"Ace", "Two", "Three", "Four", "Five", "Six",
         "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
      string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
      int i = 0;
      // populate deck with Card objects 
      for (int i = 0; i < 52; i++) {
         deck[i].setFace(faces[i % 13]);
         deck[i].setSuit(suits[i / 13]);
      }
   }

   void shuffleDeck(int size) {
      if (size < 2) {
         // resets dealCard counter
         currentCard = 0;
         return;
      }
      shuffleDeck(size - 1);
      srand(time(0));
      int randCard = rand() % size;
      
      swap(deck[size-1], deck[randCard]);
      
      //Card temp = deck[size];
      //deck[size] = deck[randCard];
      //deck[randCard] = temp;
      
      
   }

   Card dealCard() {
      if (currentCard >= 52) {
         shuffleDeck(52);
      }
      currentCard++;
      return deck[currentCard - 1];
   }

   void dealHand(list<Card> &playerHand, int amount) {
      for (int i = 0; i < amount; i++) {
         Card temp = dealCard();
         playerHand.push_front(temp);
      }
   }

   void viewHand(list<Card> hand) {
      for (auto it = hand.begin(); it != hand.end(); it++) {
         cout << it->toString() << endl;
      }
      cout << "When done viewing hand, enter any key and then enter to hide it from the next player.";
      string temp;
      cin >> temp;
      system("clear");
   }

   void viewHand(list<Card> hand, list<Card> dealer) {
      cout << "Your hand: " << endl;
      for (auto it = hand.begin(); it != hand.end(); it++) {
         cout << it->toString() << endl;
      }

      cout << "Cards on the table: " << endl;
      dealerPrint(dealer);
      cout << "When done viewing hand, enter any key and then enter to hide it from the next player.";
      string temp;
      cin >> temp;
      system("clear");
   }

   void dealerPrint(list<Card> d) {
      for (auto it = d.begin(); it != d.end(); it++) {
         cout << it->toString() << endl;
      }
   }

   pair<int, int> evaluateHand(list<Card> player, list<Card> dealer) {
      list<Card> combined;
      while (!combined.empty()) {
         combined.pop_back();
      }
      combined.splice(combined.begin(), player);
      combined.splice(combined.begin(), dealer);

      int suitsFound[5] = {0, 0, 0, 0, 0};
      int facesFound[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};



      for (auto itr = combined.begin(); itr != combined.end(); itr++) {
         if (itr->getSuit() == "Hearts") {
            suitsFound[4]++;
         } else if (itr->getSuit() == "Clubs") {
            suitsFound[1]++;
         } else if (itr->getSuit() == "Spades") {
            suitsFound[2]++;
         } else if (itr->getSuit() == "Diamonds") {
            suitsFound[3]++;
         } else {
            suitsFound[0]++;
         }

         if (itr->getFace() == "Ace") {
            facesFound[13]++;
         } else if (itr->getFace() == "Two") {
            facesFound[1]++;
         } else if (itr->getFace() == "Three") {
            facesFound[2]++;
         } else if (itr->getFace() == "Four") {
            facesFound[3]++;
         } else if (itr->getFace() == "Five") {
            facesFound[4]++;
         } else if (itr->getFace() == "Six") {
            facesFound[5]++;
         } else if (itr->getFace() == "Seven") {
            facesFound[6]++;
         } else if (itr->getFace() == "Eight") {
            facesFound[7]++;
         } else if (itr->getFace() == "Nine") {
            facesFound[8]++;
         } else if (itr->getFace() == "Ten") {
            facesFound[9]++;
         } else if (itr->getFace() == "Jack") {
            facesFound[10]++;
         } else if (itr->getFace() == "Queen") {
            facesFound[11]++;
         } else if (itr->getFace() == "King") {
            facesFound[12]++;
         } else {
            facesFound[0]++;
         }
      }

      return checkHand(facesFound, suitsFound);

   }

};
#endif /* DECKOFCARDS_H */

