#include "funclib.h"
#include "testLib.h"

#include <cstdio>

void setupTest3_onePair_1(Card* const wDeck)
{
	wDeck[0].id = 5; //Three of Diamonds
	wDeck[1].id = 8; //Four of Clubs
	wDeck[2].id = 7; //Three of Spades
}

void setupTest3_onePair_2(Card* const wDeck)
{
	wDeck[0].id = 8; //Four of Clubs
	wDeck[1].id = 4; //  Three of Clubs
	wDeck[2].id = 12; //  Five of Clubs
}


void setupTest3_onePair_3(Card* const wDeck)
{
	wDeck[0].id = 4; // Three of Clubs
	wDeck[1].id = 6; // Four of Hearts
	wDeck[2].id = 5; //Three of Spades
}


void setupTest5_fourOfAKind_1(Card* const wDeck)
{
	wDeck[0].id = 1;
	wDeck[1].id = 0;
	wDeck[2].id = 3;
	wDeck[3].id = 4;
	wDeck[4].id = 5;
}


void setupTest5_fourOfAKind_2(Card* const wDeck)
{
	wDeck[0].id = 0;
	wDeck[1].id = 8;
	wDeck[2].id = 4;
	wDeck[3].id = 12;
	wDeck[4].id = 16;
}


void setupTest5_fourOfAKind_3(Card* const wDeck)
{
	wDeck[0].id = 0;
	wDeck[1].id = 28;
	wDeck[2].id = 34;
	wDeck[3].id = 29;
	wDeck[4].id = 33;
}

void testF(Card* const deck)
{
	shuffle(deck);
	test3(deck);
	sort(deck, 3);//設定測試牌型一對(3張)
	determine(deck, 3); //決定牌型一對(3張): return true

	setupTest3_onePair_2(deck);   //設定測試牌型一對(3張)
	sort(deck, 3);
	determine(deck, 3); //決定牌型一對(3張): return true

	setupTest3_onePair_3(deck);   //設定測試牌型不是一對(3張)
	sort(deck, 3);
	determine(deck, 3); //決定牌型一對(3張): return false

	setupTest5_fourOfAKind_1(deck);		//設定測試牌型四條
	sort(deck, 5);
	determine(deck, 5);		//決定牌型四條 (5張): return true


	setupTest5_fourOfAKind_2(deck);	//設定測試牌型四條
	sort(deck, 5);
	determine(deck, 5);		//決定牌型四條 (5張): return true


	setupTest5_fourOfAKind_3(deck);	//設定測試牌型不是四條
	sort(deck, 5);
	determine(deck, 5);		//決定牌型四條 (5張): return false

	
}

void test3(Card* const wDeck)
{
	//sort(wDeck, 3);
	wDeck[0].id = 5; //Three of Diamonds
	wDeck[1].id = 8; //Four of Clubs
	wDeck[2].id = 7; //Three of Spades	 //設定測試牌型一對(3張)
}
