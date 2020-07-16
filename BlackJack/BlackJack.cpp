#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
#undef max

//Structure containing each variable type of a card.
struct CardType {

	char CardName[10];	 //Name of card.
	char CardSuit[10];   //Suit of card.
	int CardValue;  //Value of card in BlackJack.

};

//PrepareDeck function is called to get a deck ready. It calls other functions to create a shuffled deck to be used in the game.
void PrepareDeck(CardType Deck[]);
//CreateDeck function is used to fill the array of cards with an ordered deck of cards starting from ace of diamonds and ending with king of spades.
void CreateDeck(CardType Deck[]);
//ShuffleTheDeck function is used to randomise the deck to create a shuffled deck of cards at the end.
void ShuffleTheDeck(CardType Deck[]);

//PlayerBet function asks the player how much they want to bet for that round. It makes sure the input is valid and then outputs the bet as the current bet for the round.
int PlayerBet(int TotalPlayerMoney);
//NextGameCheck function asks the player if they want to start a new round. It makes sure the input is valid and then either starts a new round or ends the game.
int NextGameCheck();
//PlayerMove function asks the player what they want to do for their move. It makes sure the input is valid and then hits or stands.
int PlayerMove();

//Function to show the player's cards and the value of the cards in their hand.
void ShowPlayerCards(CardType PlayerHand[],int numPlayerCards);
//Function to show the dealer's cards
void ShowDealerCards(CardType DealerHand[], int numDealerCards);
//Function to calculate the value of the hand. It is used for both the player and the dealer's hand.
int CalculateHandValue(CardType Hand[], int HandCardCount);
//Function to check how many cards are left in the deck and shuffles a new deck if there are no cards left.
void CheckDeckCardCount(CardType Deck[], int& DeckCardCount);

int main()
{

	srand(time(0));
	

	//Creates and shuffles a new deck.
	CardType Deck[52];
	PrepareDeck(Deck);

	//Gives the player £100 to start betting in the game.
	int TotalPlayerMoney = 100;
	//Sets the pointer for the deck of cards to 0.
	int DeckCardCount = 0;
	//Variable to store the player's choices.
	int PlayerTurnChoice = 0;

	//Do loop that loops until the player doesn't want to start a new round.
	do {

		//Declares an array of cards for the dealer's hand.
		CardType DealerHand[11];
		//Count for how many cards are in the dealer's hand.
		int DealerHandCardCount = 0;

		//Declares an array of cards for the player's hand.
		CardType PlayerHand[11];
		//Count for how many cards are in the player's hand.
		int PlayerHandCardCount = 0;
		//Integer storing how much money the player has bet for that round.
		int CurrentBet;

		//Calls another function which gets the player to place a bet and stores it as current bet.
		CurrentBet = PlayerBet(TotalPlayerMoney);

		//Subtracts the current bet from the player money pot.
		TotalPlayerMoney -= CurrentBet;

		//Clears screen.
		system("CLS");

		//Adds first two cards to the players hand and increases the player hand card count.
		PlayerHand[PlayerHandCardCount] = Deck[DeckCardCount];
		CheckDeckCardCount(Deck, DeckCardCount);
		PlayerHandCardCount++;
		PlayerHand[PlayerHandCardCount] = Deck[DeckCardCount];
		CheckDeckCardCount(Deck, DeckCardCount);
		PlayerHandCardCount++;

		//Adds first two cards to the dealers hand and increases the dealer hand card count.
		DealerHand[DealerHandCardCount] = Deck[DeckCardCount];
		CheckDeckCardCount(Deck, DeckCardCount);
		DealerHandCardCount++;
		DealerHand[DealerHandCardCount] = Deck[DeckCardCount];
		CheckDeckCardCount(Deck, DeckCardCount);
		DealerHandCardCount++;

		//Checks if the dealer's hand value equals 21 as that would mean the dealer automatically wins that round.
		if (CalculateHandValue(DealerHand, DealerHandCardCount) == 21) {

			//Checks if the player doesn't also have 21. This is to confirm the dealer has won.
			if (CalculateHandValue(PlayerHand, PlayerHandCardCount) < 21) {

				ShowDealerCards(DealerHand, DealerHandCardCount);
				ShowPlayerCards(PlayerHand, PlayerHandCardCount);

				std::cout << "Total Money: " << TotalPlayerMoney << "\n";

				std::cout << "\n";

				std::cout << "Dealer Wins!\n";

			}
			//If the player and the dealer both have 21 then the round is a draw.
			else {

				ShowDealerCards(DealerHand, DealerHandCardCount);
				ShowPlayerCards(PlayerHand, PlayerHandCardCount);

				TotalPlayerMoney += CurrentBet;
				std::cout << "Total Money: " << TotalPlayerMoney << "\n";

				std::cout << "\n";

				std::cout << "You Draw!\n";

			}

		}
		//Carries on the game if the dealer doesn't have a hand value of 21.
		else {

			//Loops through turns so that the player can hit or stand multiple times.
			do {

				std::cout << "Dealer's Cards\n";
				std::cout << "Hole Card\n";
				std::cout << DealerHand[1].CardName << " of " << DealerHand[1].CardSuit << "\n";

				std::cout << "\n";

				ShowPlayerCards(PlayerHand, PlayerHandCardCount);

				std::cout << "Current Bet: " << CurrentBet << "\n";
				std::cout << "Total Money: " << TotalPlayerMoney << "\n";

				std::cout << "\n";

				PlayerTurnChoice = 2;

				//Lets the player chose a move for their turn if they dont have a hand value of 21.
				if (CalculateHandValue(PlayerHand, PlayerHandCardCount) < 21) {

					PlayerTurnChoice = PlayerMove();

					//Adds a card to the player's hand if they want to hit for that turn.
					if (PlayerTurnChoice == 1) {

						PlayerHand[PlayerHandCardCount] = Deck[DeckCardCount];
						CheckDeckCardCount(Deck, DeckCardCount);
						PlayerHandCardCount++;

					}

				}

				system("CLS");

			} while (PlayerTurnChoice == 1);

			//If the player doesn't have 21 then the dealer carries out their turn.
			if (CalculateHandValue(PlayerHand, PlayerHandCardCount) < 21) {

				while (CalculateHandValue(DealerHand, DealerHandCardCount) < 17) {

					// Adds cards into the dealer's hand until the dealer has a hand value over 16.
					DealerHand[DealerHandCardCount] = Deck[DeckCardCount];
					CheckDeckCardCount(Deck, DeckCardCount);
					DealerHandCardCount++;

				}

			}

			//Displays both the dealer's and the player's hands and game information.
			ShowDealerCards(DealerHand, DealerHandCardCount);
			ShowPlayerCards(PlayerHand, PlayerHandCardCount);

			//If the player's hand value is over 21 and they busted, the dealer wins that round.
			if (CalculateHandValue(PlayerHand, PlayerHandCardCount) > 21) {

				std::cout << "Total Money: " << TotalPlayerMoney << "\n";

				std::cout << "\n";

				std::cout << "Dealer Wins!\n";

			}
			//If the dealer's hand value is over 21 and they busted, the player wins that round.
			else if (CalculateHandValue(DealerHand, DealerHandCardCount) > 21) {

				TotalPlayerMoney += (2 * CurrentBet);
				std::cout << "Total Money: " << TotalPlayerMoney << "\n";

				std::cout << "\n";

				std::cout << "You Win!\n";

			}
			else {

				//If the dealer's hand value is greater than the player's hand value, the dealer wins that round.
				if (CalculateHandValue(DealerHand, DealerHandCardCount) > CalculateHandValue(PlayerHand, PlayerHandCardCount)) {

					std::cout << "Total Money: " << TotalPlayerMoney << "\n";

					std::cout << "\n";

					std::cout << "Dealer Wins!\n";

				}
				//If the player's hand value is greater than the dealer's hand value, the player wins that round.
				else if (CalculateHandValue(DealerHand, DealerHandCardCount) < CalculateHandValue(PlayerHand, PlayerHandCardCount)) {

					TotalPlayerMoney += (2 * CurrentBet);
					std::cout << "Total Money: " << TotalPlayerMoney << "\n";

					std::cout << "\n";

					std::cout << "You Win!\n";

				}
				//If the player and the dealer's hand values are equal, then they draw that round.
				else {

					TotalPlayerMoney += CurrentBet;
					std::cout << "Total Money: " << TotalPlayerMoney << "\n";

					std::cout << "\n";

					std::cout << "You Draw!\n";

				}

			}

		}

		//If the player still has money left in their money pot, then ask them if they want to play another round.
		if (TotalPlayerMoney != 0) {

			PlayerTurnChoice = NextGameCheck();

		}
		//If the player has no money left in their money pot, then they have lost and must exit the game.
		else {

			std::cout << "You have no money left!\n";
			std::cout << "Press 'Enter' to quit\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.get();
			PlayerTurnChoice = 2;
		}

		system("CLS");
	} while (PlayerTurnChoice == 1);

	return 0;
}

//Simple function which was originally used to group up the creation and the shuffling of the deck. Can be used in the future for multiple decks.
void PrepareDeck(CardType Deck[]) {

	CreateDeck(Deck);
	ShuffleTheDeck(Deck);

}

//Creates an unshuffled, ordered deck of cards.
void CreateDeck(CardType Deck[]) {

	int CardCount = 0;

	//Loops through each suit and each card name to populate an array of cards with ordered deck of cards.
	for (int suits = 0; suits < 4; suits++) {

		for (int nameofcard = 0; nameofcard < 13; nameofcard++) {

			switch (suits) {
			case 0:
				strcpy_s(Deck[CardCount].CardSuit, "Diamonds");
				break;
			case 1:
				strcpy_s(Deck[CardCount].CardSuit, "Clubs");
				break;
			case 2:
				strcpy_s(Deck[CardCount].CardSuit, "Hearts");
				break;
			case 3:
				strcpy_s(Deck[CardCount].CardSuit, "Spades");
				break;
			}

			switch (nameofcard) {
			case 0:
				strcpy_s(Deck[CardCount].CardName, "Ace");
				Deck[CardCount].CardValue = 11;
				break;
			case 1:
				strcpy_s(Deck[CardCount].CardName, "2");
				Deck[CardCount].CardValue = 2;
				break;
			case 2:
				strcpy_s(Deck[CardCount].CardName, "3");
				Deck[CardCount].CardValue = 3;
				break;
			case 3:
				strcpy_s(Deck[CardCount].CardName, "4");
				Deck[CardCount].CardValue = 4;
				break;
			case 4:
				strcpy_s(Deck[CardCount].CardName, "5");
				Deck[CardCount].CardValue = 5;
				break;
			case 5:
				strcpy_s(Deck[CardCount].CardName, "6");
				Deck[CardCount].CardValue = 6;
				break;
			case 6:
				strcpy_s(Deck[CardCount].CardName, "7");
				Deck[CardCount].CardValue = 7;
				break;
			case 7:
				strcpy_s(Deck[CardCount].CardName, "8");
				Deck[CardCount].CardValue = 8;
				break;
			case 8:
				strcpy_s(Deck[CardCount].CardName, "9");
				Deck[CardCount].CardValue = 9;
				break;
			case 9:
				strcpy_s(Deck[CardCount].CardName, "10");
				Deck[CardCount].CardValue = 10;
				break;
			case 10:
				strcpy_s(Deck[CardCount].CardName, "Jack");
				Deck[CardCount].CardValue = 10;
				break;
			case 11:
				strcpy_s(Deck[CardCount].CardName, "Queen");
				Deck[CardCount].CardValue = 10;
				break;
			case 12:
				strcpy_s(Deck[CardCount].CardName, "King");
				Deck[CardCount].CardValue = 10;
				break;
			}

			CardCount++;
		}
	}

	/*Check to see if deck is created
	for (int a = 0; a < 52; a++) {
	std::cout << Deck[a].CardName << " of " << Deck[a].CardSuit << " Value: " << Deck[a].CardValue << "\n";
	}
	std::cin.get();
	*/

}

//Function used to shuffle and randomize the position of each card in the deck.
void ShuffleTheDeck(CardType Deck[]) {

	bool NumbersUsed[52] = { false };
	CardType TempDeck[52];
	int cardCountsofar = 0;

	//Loops through each card in the deck and places it in a random position in a temporary deck.
	do {

		bool nextCard = false;

		do {

			int randomNum = (rand() % 52);

			if (NumbersUsed[randomNum] == false) {
				nextCard = true;
				NumbersUsed[randomNum] = true;
				TempDeck[randomNum] = Deck[cardCountsofar];
				cardCountsofar++;
			}

		} while (nextCard == false);

	} while (cardCountsofar < 52);

	//Temporary deck is duplicated into the original deck.
	for (int a = 0; a < 52; a++) {

		Deck[a] = TempDeck[a];

	}

	/* Check to see if deck is shuffled
	for (int a = 0; a < 52; a++) {
		std::cout << Deck[a].CardName << " of " << Deck[a].CardSuit << " Value: " << Deck[a].CardValue << "\n";
	}
	std::cin.get();
	*/
}

//Function used to ask the player how much money they want to bet and validates their input.
int PlayerBet(int TotalPlayerMoney) {

	bool check;
	int CurrentBet = 0;
	
	//Loops the question until the input is valid.
	do {

		check  = true;
		
		std::cout << "Total Player Pot: " << TotalPlayerMoney << "\n";
		std::cout << "Dealer: Please place your initial bet\n";
		std::cin >> CurrentBet;

		//Validation for if the player inputs something other than 1 or 2.
		if ( (std::cin.fail()) || (CurrentBet < 1) ) {

			check = false;
			std::cout << "Invalid input!";
			Sleep(1500);
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			system("CLS");

		}
		else if (CurrentBet > TotalPlayerMoney) {

			check = false;
			std::cout << "Select an amount between 1 and " << TotalPlayerMoney << "!";
			Sleep(1500);
			system("CLS");

		}

	} while (check == false);

	return CurrentBet;

}

//Function used to ask the player if they want to hit or stand during a round and validates their input.
int PlayerMove() {

	int PlayerTurnChoice;
	bool check;

	do {

		PlayerTurnChoice = 0;
		check = true;

		std::cout << "Dealer: Would you like to hit or keep?\n";
		std::cout << "1|Hit\n";
		std::cout << "2|Stand\n";
		std::cin >> PlayerTurnChoice;

		//Validation for if the player inputs something other than 1 or 2.
		if ((std::cin.fail()) || (PlayerTurnChoice < 1)) {

			check = false;
			std::cout << "Invalid input!\n";
			Sleep(1500);
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		}
		else if (PlayerTurnChoice > 2) {

			check = false;
			std::cout << "Select 1 or 2!\n";
			Sleep(1500);

		}

	} while (check == false);

	return PlayerTurnChoice;

}

//Function used to show the cards in the player's hand and the hand value.
void ShowPlayerCards(CardType PlayerHand[], int numPlayerCards) {

	std::cout << "Your Cards\n";

	for (int a = 0; a < numPlayerCards; a++) {

		std::cout << PlayerHand[a].CardName << " of " << PlayerHand[a].CardSuit << "\n";

	}

	std::cout << "\n";

	std::cout << "Card Value: " << CalculateHandValue(PlayerHand,numPlayerCards) << "\n";

	std::cout << "\n";

}

//Function used to show the cards in the dealer's hand and the hand value.
void ShowDealerCards(CardType DealerHand[], int numDealerCards) {

	std::cout << "Dealer Cards\n";

	for (int a = 0; a < numDealerCards; a++) {

		std::cout << DealerHand[a].CardName << " of " << DealerHand[a].CardSuit << "\n";

	}

	std::cout << "\n";

	std::cout << "Dealer Card Value: " << CalculateHandValue(DealerHand, numDealerCards) << "\n";

	std::cout << "\n";

}

//Function used to calculate the value of any player's hand. Done in a function so that in the future it can be used repeatedly if there are more than one player versus the dealer.
int CalculateHandValue(CardType Hand[], int HandCardCount) {

	int totalValue = 0;
	bool isAce = false;
	//if more than one ace then minus 10 multiple

	for (int a = 0; a < HandCardCount; a++) {

		totalValue += Hand[a].CardValue;
		
		if (Hand[a].CardValue == 11) {

			isAce = true;

		}

	}

	if ((totalValue > 21) && (isAce)) {

			totalValue -= 10;

	}

	return totalValue;

}

//Function used to add one to the deck card pointer and shuffle a new deck if the deck has ran out of cards.
void CheckDeckCardCount(CardType Deck[], int& DeckCardCount) {

	DeckCardCount++;

	if ((DeckCardCount) > 51) {

		DeckCardCount = 0;
		ShuffleTheDeck(Deck);

	}

}

//Function used to ask the player if they want to play another game and validates the input.
int NextGameCheck() {

	int PlayerTurnChoice = 0;
	bool check;

	do {

		check = true;

		std::cout << "Do you want to play another game?\n";
		std::cout << "1|Yes\n";
		std::cout << "2|No\n";
		std::cin >> PlayerTurnChoice;

		//Validation so that the player does not input something that is not 1 or 2.
		if ((std::cin.fail()) || (PlayerTurnChoice < 1)) {

			check = false;
			std::cout << "Invalid input!";
			Sleep(1500);
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			system("CLS");

		}
		else if (PlayerTurnChoice > 2) {

			check = false;
			std::cout << "Select 1 or 2!";
			Sleep(1500);
			system("CLS");

		}

	} while (check == false);

	return PlayerTurnChoice;
}