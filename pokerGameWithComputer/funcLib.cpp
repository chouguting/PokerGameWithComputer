#include <cstdio>
#include <cstdlib>

#include "funclib.h"


int cardTypeScore[] = {0, 60, 120, 200, 280, 360, 500, 800, 1000};

void fillDeckFaceFirst(Card* const wDeck, const char* wFace[],
                       const char* wSuit[])
{
	int i = 0;
	int j;
	for (j = 0; j < 13; j++)
	{
		int k;
		for (k = 0; k < 4; k++)
		{
			wDeck[i].face = wFace[j];
			wDeck[i].suit = wSuit[k];
			wDeck[i].id = i;
			i++;
		}
	}
}

void fillDeck(Card* const wDeck, const char* wFace[],
              const char* wSuit[])
{
	int i;

	for (i = 0; i <= 51; i++)
	{
		wDeck[i].face = wFace[i % 13];
		wDeck[i].suit = wSuit[i / 13];
	}
}

void shuffle(Card* const wDeck)
{
	int i, j;
	Card temp;

	for (i = 0; i <= 51; i++)
	{
		j = rand() % 52;
		temp = wDeck[i];
		wDeck[i] = wDeck[j];
		wDeck[j] = temp;
	}
}

void deal(const Card* const wDeck, int quantity)
{
	int i;

	for (i = 0; i < quantity; i++)
		printf("\t第%d張牌 \t %5s of %-8s \t%d%c", i + 1, wDeck[i].face,
		       wDeck[i].suit, wDeck[i].id, '\n');
}


void dealManyPlayer(int playerCount, const Card* const wDeck)
{
	int i;
	int max = 13 * playerCount - 1;
	int currentCardNum = 1;

	for (i = 0; i <= max; i++)
	{
		printf("\t第%d張牌 \t%d \t %5s of %-8s   %d%c   ", currentCardNum, i + 1, wDeck[i].face,
		       wDeck[i].suit, wDeck[i].id, '\n');
		currentCardNum++;
		if ((i + 1) % 13 == 0)
		{
			printf("\n\n");
			currentCardNum = 1;
		}
	}
}


//判斷同花
int isFlush(Card wDeck[], int size)
{
	int isflush = 1;
	int i;
	int lastSuit = (wDeck[0].id + 1) % 4;
	for (i = 0; i < size; i++)
	{
		if ((wDeck[i].id + 1) % 4 != lastSuit)
		{
			isflush = 0;
		}
		lastSuit = (wDeck[i].id + 1) % 4;
	}

	return isflush;
}

//判斷順
int isStraight(Card wDeck[], int size)
{
	int isstraight = 1;
	int i;

	int lastFace = (wDeck[0].id) / 4;
	for (i = 1; i < size; i++)
	{
		//printf("FACE: %d LAST:%d\n", (wDeck[i].id) / 4,lastFace);
		if ((wDeck[i].id) / 4 != lastFace + 1)
		{
			isstraight = 0;
		}
		lastFace = (wDeck[i].id) / 4;
	}
	return isstraight;
}


//判斷A2345的順 (特殊的)
int isSpecialStraight(Card wDeck[], int size)
{
	int isspecialstraightraight = 1;
	int i;

	if (wDeck[0].id / 4 != 0)
	{
		isspecialstraightraight = 0;
	}

	int lastFace = (wDeck[0].id) / 4;
	for (i = 1; i < size - 1; i++)
	{
		//printf("FACE: %d LAST:%d\n", (wDeck[i].id) / 4,lastFace);
		if ((wDeck[i].id) / 4 != lastFace + 1)
		{
			isspecialstraightraight = 0;
		}
		lastFace = (wDeck[i].id) / 4;
	}
	if (wDeck[size - 1].id / 4 != 12)
	{
		isspecialstraightraight = 0;
	}
	return isspecialstraightraight;
}


//判斷給定值數量的牌出現幾次
int howManyOfaKind(int multipleKind, Card wDeck[], int size)
{
	int howMany = 0;
	int i = 0;
	while (i <= size - multipleKind)
	{
		int hasCorrectNumber = 1;
		int currentFace = (wDeck[i].id) / 4;
		int sameCount = 0;
		int j = 0;

		while (currentFace == (wDeck[i + j].id) / 4 && j + i < size)
		{
			sameCount++;
			j++;
		}
		if (sameCount == multipleKind)
		{
			i = i + multipleKind;
			howMany++;
		}
		else
		{
			i = i + sameCount;
		}
	}
	return howMany;
}


//判斷給定值數量的牌出現幾次
int whereIsHowManyOfaKind(int multipleKind, Card wDeck[], int size)
{
	int i = size - 1;
	int theIndex;
	
	while (i >= multipleKind - 1)
	{
		int currentFace = (wDeck[i].id) / 4;
		int sameCount = 0;
		int j = 0;

		while (currentFace == (wDeck[i - j].id) / 4 && i - j >= 0)
		{
			sameCount++;
			j++;
		}
		if (sameCount == multipleKind)
		{
			theIndex=i - multipleKind+1;
			return theIndex;
		}
		else
		{
			i = i - sameCount;
		}
	}
	
	return -1;
}


//排序
void sort(Card wDeck[], int size)
{
	int i;

	for (i = 0; i < size - 1; i++)
	{
		Card min = wDeck[i];
		int minIndex = i;
		int j;
		for (j = i; j < size; j++)
		{
			if (wDeck[j].id < min.id)
			{
				min = wDeck[j];
				minIndex = j;
			}
		}
		Card cardTemp;
		cardTemp = wDeck[i];
		wDeck[i] = wDeck[minIndex];
		wDeck[minIndex] = cardTemp;
	}
}

int determine(Card wDeck[], int size)
{
	sort(wDeck, size);
	if (isFlush(wDeck, size) == 1 && (isSpecialStraight(wDeck, size) || isStraight(wDeck, size) == 1) && size > 3)
	{
		return 8; //同花順 1000分
	}
	else if (howManyOfaKind(4, wDeck, size) >= 1)
	{
		return 7; //四條 800分
	}
	else if (howManyOfaKind(3, wDeck, size) >= 1 && howManyOfaKind(2, wDeck, size) >= 1)
	{
		return 6; //葫蘆 500分
	}
	else if (isFlush(wDeck, size) == 1 && size > 3)
	{
		return 5; //同花 360分
	}
	else if ((isSpecialStraight(wDeck, size) == 1 || isStraight(wDeck, size) == 1) && size > 3)
	{
		return 4; //順子 280分
	}
	else if (howManyOfaKind(3, wDeck, size) >= 1)
	{
		return 3; //三條 200分
	}
	else if (howManyOfaKind(2, wDeck, size) == 2)
	{
		return 2; //二對 120分
	}
	else if (howManyOfaKind(2, wDeck, size) == 1)
	{
		return 1; //對子 60分
	}
	else
	{
		return 0; //散牌 0分
	}
}


Card mostImportantCard(int multipleKind, Card wDeck[], int size)
{
	int i = size - 1;
	Card veryImoprtantCard = wDeck[i];
	while (i >= multipleKind - 1)
	{
		int currentFace = (wDeck[i].id) / 4;
		int sameCount = 0;
		int j = 0;

		while (currentFace == (wDeck[i - j].id) / 4 && i - j >= 0)
		{
			sameCount++;
			j++;
		}
		if (sameCount == multipleKind)
		{
			veryImoprtantCard = wDeck[i];
			i = i - multipleKind;

			return veryImoprtantCard;
		}
		else
		{
			i = i - sameCount;
		}
	}
	return veryImoprtantCard;
}

int giveScore(Card wDeck[], int size)
{
	int type = determine(wDeck, size);
	int score = 0;
	if (isSpecialStraight(wDeck, size) == 1)
	{
		score = score + (wDeck[size - 2].id);
	}
	else if (type == 7)
	{
		score = score + mostImportantCard(4, wDeck, size).id;
	}
	else if (type == 6)
	{
		score = score + mostImportantCard(3, wDeck, size).id;
	}
	else if (type == 3)
	{
		score = score + mostImportantCard(3, wDeck, size).id;
	}
	else if (type == 2)
	{
		score = score + mostImportantCard(2, wDeck, size).id;
	}
	else if (type == 1)
	{
		score = score + mostImportantCard(2, wDeck, size).id;
	}
	else
	{
		score = score + (wDeck[size - 1].id);
	}
	score = score + cardTypeScore[type];
	return score;
}
