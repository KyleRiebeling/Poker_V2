#include <iostream>
#include <map>
#include <list>
#include <cstdlib>


#include "Table.h"

using namespace std;

int main() {
   int numPlayers = 0;
   char tempC;

   cout << "Welcome to the casino! How many people will be playing today? (2 or 3)" << endl;
   cin >> numPlayers;

   //Error check for amount of players
   while (numPlayers <= 0 || numPlayers >= 4 || cin.fail()) {
      cout << "Enter either 2 or 3: ";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cin >> numPlayers;
   }

   Table pTable = Table(numPlayers);

   cout << endl << "Welcome to the table!" << endl;
   pTable.printPlayers();


   //-----GAME LOOP-----

   //Place Buy-in Bets++++

   //Deal cards ++++

   //Ask for more bets 2 ++

   //Dealer places three cards on table ++

   //Ask for more bets/folds 3 ++

   //Dealer places one more card ++

   //Ask for bets/fold 4 ++

   //Dealer places last card ++

   //Last round of betting 5 +++

   //Reveal winner and their hand

   //Ask if you want to keep going
   
   
   
   while (tempC != 'q') {
      pTable.setTurn(1);
      for (int i = 0; i < 5; i++) {
         pTable.placeBets();
         pTable.startTurn();
      }
      system("clear");
      cout << "Would you like to keep playing? Press 'q' to quit or anything else to play again: ";
      cin >> tempC;
   }
   
   system("clear");
   cout << "------Round History------" << endl;
   pTable.displayHistory();
   
   return 0;
}

