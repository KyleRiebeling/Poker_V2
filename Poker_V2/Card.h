/*
 * File:   Card.h
 * Author: Kyle
 *
 * Created on April 21, 2023, 5:04 PM
 */

#ifndef CARD_H
#define CARD_H
#include <string>

using namespace std;

class Card {
private:
   string face;
   string suit;
public:

   Card() {
      face = "Face";
      suit = "Suit";
   }
   
   Card(string faceS, string suitS) {
      face = faceS;
      suit = suitS;
   }
   
   string toString() {
      return face + " of " + suit;
   }

   string getFace() {
      return face;
   }

   string getSuit() {
      return suit;
   }

   void setFace(string f) {
      face = f;
   }

   void setSuit(string s) {
      suit = s;
   }
};

#endif /* CARD_H */

