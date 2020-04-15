#include <cstdio>

#include "funclib.h"

/*
 main idea:先把重要的牌填到handCardTemp中,不重要的先空著(例如四條中的那四張一樣的是重要的,剩下那張不重要)
		   等所有重要的都牌完後再把剩下牌填入TEMP,最後再複製回去手牌
 */

void sortByComPlayer(Card* handCard, int size)
{
	int hasFilled[13] = {0}; //儲存Temp牌堆中該位置有沒有填入值
	Card handCardTemp[13]; //暫存用手牌(把確定的牌先填進去)
	int sortIndex = size - 1; //這個index會存下一個應該填值的位置

	int currentRound = 0; //第幾輪
	int i, j;

	int sortedIdIndex = 120; //已經整理過的牌ID會暫時被改成100多，這樣sort時他們就會在後面

	int currentSize = size; //目前未整理區域的大小


	//三個牌敦
	for (currentRound = 0; currentRound < 3; currentRound++)
	{
		if (currentRound > 0)
		{
			sort(handCard, size); //先整理牌(第一ROUND不用)
		}

		//printf("\n\n");


		int hasStrightFlush = 0; //有沒有同花順
		int hasStright = 0; //有沒有順
		int hasFlush = 0; //有沒有同花
		int straightFlushCardIndex[5]; //同花順位置INDEX
		int straightCardIndex[5]; //順位置 INDEX
		int flushCardIndex[5]; //同花位置 INDEX

		int fourOfaKindIndex = 0; //四條的位置
		int hasFourOfaKind = 0; //有沒有四條

		int threeOfaKindIndex = 0; //三條的位置
		int hasThreeOfaKind = 0; //有沒有三條

		int hasPair = 0; //有沒有對子
		int pairIndex = 0; //對子的位置
		int hasSecondPair = 0; //有沒有第二個對子
		int secondPairIndex = 0; //第二個對子的位置


		//這邊都是5張牌才會出現的牌型
		if (currentRound < 2)
		{
			//同時抓 同花順,順,同花 的位置(如果有)
			for (i = currentSize - 1; i >= 4; i--)
			{
				/*利用indexCurrent=4填入找到的同花順,順or同花的位置
				每找到一張符合的牌indexCurrent就減一
				如果indexCurrent<0的話，代表以經找到五張了(代表成立)*/
				int straightFlushIndexCurrent = 4;
				int straightIndexCurrent = 4;
				int flushIndexCurrent = 4;

				//同花順順位最大，找到就不用再找順or同花了
				straightFlushCardIndex[straightFlushIndexCurrent] = i;
				straightFlushIndexCurrent--;

				if (hasStright == 0) //已經找到順就不用再找順了
				{
					straightCardIndex[straightIndexCurrent] = i;
					straightIndexCurrent--;
				}

				if (hasFlush == 0) //已經找到同花就不用再找同花了
				{
					flushCardIndex[flushIndexCurrent] = i;
					flushIndexCurrent--;
				}

				int lastFaceByStraightFlush = (handCard[i].id) / 4; //數字
				int lastFace = (handCard[i].id) / 4; //數字
				int lastSuit = (handCard[i].id + 1) % 4; //花色

				for (j = i - 1; j >= 0; j--) //從手牌尾端開始找,這樣找到的就是最大的
				{
					//找同花順
					if (lastFaceByStraightFlush - 1 == (handCard[j].id) / 4 && lastSuit == (handCard[j].id + 1) % 4 &&
						hasStrightFlush == 0)
					{
						straightFlushCardIndex[straightFlushIndexCurrent] = j;
						straightFlushIndexCurrent--;
						lastFaceByStraightFlush = (handCard[j].id) / 4;
					}
					if (straightFlushIndexCurrent < 0)
					{
						hasStrightFlush = 1;
						break;
					}


					//找順
					if (lastFace - 1 == (handCard[j].id) / 4 && hasStright == 0)
					{
						straightCardIndex[straightIndexCurrent] = j;
						straightIndexCurrent--;
						lastFace = (handCard[j].id) / 4;
					}
					if (straightIndexCurrent < 0)
					{
						hasStright = 1;
					}


					//找同花
					if (lastSuit == (handCard[j].id + 1) % 4 && hasFlush == 0)
					{
						flushCardIndex[flushIndexCurrent] = j;
						flushIndexCurrent--;
					}


					if (flushIndexCurrent < 0)
					{
						hasFlush = 1;
					}
				}

				if (hasStrightFlush == 1)
				{
					break;
				}
			}


			//抓四條
			for (i = currentSize - 4; i >= 0; i--)
			{
				if (howManyOfaKind(4, handCard + i, 4) == 1)
				{
					hasFourOfaKind = 1;
					fourOfaKindIndex = i;
					break;
				}
			}
		}


		//抓一個三條
		for (i = currentSize - 3; i >= 0; i--)
		{
			if (howManyOfaKind(3, handCard + i, 3) == 1 && howManyOfaKind(3, handCard + i + 1, 3) == 0 && i > 0)
			{
				hasThreeOfaKind = 1;
				threeOfaKindIndex = i;
				break;
			}
			if (howManyOfaKind(3, handCard + i, 3) == 1 && i == 0)
			{
				hasThreeOfaKind = 1;
				threeOfaKindIndex = i;
				break;
			}
		}
		//if (hasThreeOfaKind == 1)printf("ThreeOfaKind Index:%d\n", threeOfaKindIndex);


		//抓兩個對子(第一個取小的第二個取大的)
		for (i = currentSize; i >= 1; i--)
		{
			if (hasSecondPair == 0 && hasPair == 1 && whereIsHowManyOfaKind(2, handCard, i) != -1)
			{
				if (whereIsHowManyOfaKind(3, handCard, i) != whereIsHowManyOfaKind(2, handCard, i))
				{
					hasSecondPair = 1;
					secondPairIndex = pairIndex;
				}
			}
			if (whereIsHowManyOfaKind(2, handCard, i) != -1)
			{
				if (hasThreeOfaKind == 1 && threeOfaKindIndex == whereIsHowManyOfaKind(2, handCard, i))
				{
				}
				else
				{
					hasPair = 1;
					pairIndex = whereIsHowManyOfaKind(2, handCard, i);
				}
			}
		}
		if (pairIndex == secondPairIndex)hasSecondPair = 0;

		//if (hasPair == 1)printf("pair Index:%d\n", pairIndex);
		//if (hasSecondPair == 1)printf("SECOND pair Index:%d\n", secondPairIndex);


		//已經找完了 開始填入CardTemp
		if (currentRound < 2)
		{
			//順位1: 同花順
			if (hasStrightFlush == 1)
			{
				for (i = 0; i < 5; i++)
				{
					handCardTemp[sortIndex] = handCard[straightFlushCardIndex[i]];
					hasFilled[sortIndex] = 1;
					handCard[straightFlushCardIndex[i]].id = sortedIdIndex;
					sortedIdIndex = sortedIdIndex - 1;

					sortIndex = sortIndex - 1;
				}
				currentSize = currentSize - 5;
				continue;
			}

			//順位2: 鐵支
			if (hasFourOfaKind == 1)
			{
				for (i = 0; i < 4; i++)
				{
					handCardTemp[sortIndex] = handCard[fourOfaKindIndex + i];
					hasFilled[sortIndex] = 1;
					handCard[fourOfaKindIndex + i].id = sortedIdIndex;
					sortedIdIndex = sortedIdIndex - 1;
					sortIndex = sortIndex - 1;
				}
				currentSize = currentSize - 4;
				sortIndex--; //先空一格
				continue;
			}


			//順位3: 葫蘆
			if (hasThreeOfaKind == 1 && hasPair == 1)
			{
				for (i = 0; i < 3; i++)
				{
					handCardTemp[sortIndex] = handCard[threeOfaKindIndex + i];
					hasFilled[sortIndex] = 1;
					handCard[threeOfaKindIndex + i].id = sortedIdIndex;
					sortedIdIndex = sortedIdIndex - 1;
					sortIndex = sortIndex - 1;
				}
				for (i = 0; i < 2; i++)
				{
					handCardTemp[sortIndex] = handCard[pairIndex + i];
					hasFilled[sortIndex] = 1;
					handCard[pairIndex + i].id = sortedIdIndex;
					sortedIdIndex = sortedIdIndex - 1;
					sortIndex = sortIndex - 1;
				}
				currentSize = currentSize - 5;
				continue;
			}


			//順位4: 同花
			if (hasFlush == 1)
			{
				for (i = 0; i < 5; i++)
				{
					handCardTemp[sortIndex] = handCard[flushCardIndex[i]];
					hasFilled[sortIndex] = 1;
					handCard[flushCardIndex[i]].id = sortedIdIndex;
					sortedIdIndex = sortedIdIndex - 1;
					sortIndex = sortIndex - 1;
				}
				currentSize = currentSize - 5;
				continue;
			}


			//順位5: 順子
			if (hasStright == 1)
			{
				for (i = 0; i < 5; i++)
				{
					handCardTemp[sortIndex] = handCard[straightCardIndex[i]];
					hasFilled[sortIndex] = 1;
					handCard[straightCardIndex[i]].id = sortedIdIndex;
					sortedIdIndex = sortedIdIndex - 1;
					sortIndex = sortIndex - 1;
				}
				currentSize = currentSize - 5;
				continue;
			}
		}


		//順位6: 三條
		if (hasThreeOfaKind == 1)
		{
			for (i = 0; i < 3; i++)
			{
				handCardTemp[sortIndex] = handCard[threeOfaKindIndex + i];
				hasFilled[sortIndex] = 1;
				handCard[threeOfaKindIndex + i].id = sortedIdIndex;
				sortedIdIndex = sortedIdIndex - 1;
				sortIndex = sortIndex - 1;
			}
			currentSize = currentSize - 3;
			sortIndex = sortIndex - 2; //先空兩格
			continue;
		}


		//順位7: 兩對
		if (hasPair == 1 && hasSecondPair == 1)
		{
			for (i = 0; i < 2; i++)
			{
				handCardTemp[sortIndex] = handCard[pairIndex + i];
				hasFilled[sortIndex] = 1;
				handCard[pairIndex + i].id = sortedIdIndex;
				sortedIdIndex = sortedIdIndex - 1;
				sortIndex = sortIndex - 1;
			}
			for (i = 0; i < 2; i++)
			{
				handCardTemp[sortIndex] = handCard[secondPairIndex + i];
				hasFilled[sortIndex] = 1;
				handCard[secondPairIndex + i].id = sortedIdIndex;
				sortedIdIndex = sortedIdIndex - 1;
				sortIndex = sortIndex - 1; //先空一格
			}
			currentSize = currentSize - 4;
			sortIndex = sortIndex - 1;
			continue;
		}

		//順位8: 對子
		if (hasPair == 1)
		{
			if (hasSecondPair == 1)
			{
				pairIndex = secondPairIndex;
			}
			for (i = 0; i < 2; i++)
			{
				handCardTemp[sortIndex] = handCard[pairIndex + i];
				hasFilled[sortIndex] = 1;
				handCard[pairIndex + i].id = sortedIdIndex;
				sortedIdIndex = sortedIdIndex - 1;
				sortIndex = sortIndex - 1;
			}
			currentSize = currentSize - 2;
			sortIndex = sortIndex - 3; //先空三格
			continue;
		}

		//順位9: 散牌
		handCardTemp[sortIndex] = handCard[currentSize - 1];
		hasFilled[sortIndex] = 1;
		handCard[currentSize - 1].id = sortedIdIndex;
		sortIndex = sortIndex - 1;
		sortedIdIndex = sortedIdIndex - 1;
		currentSize = currentSize - 1;
		sortIndex = sortIndex - 4; //先空四格
	}


	//把還沒填入的牌填進TEMP的空位裡
	for (i = 0; i < 13; i++)
	{
		for (j = 0; j < 13; j++)
		{
			if (hasFilled[i] == 0 && handCard[j].id < 100)
			{
				handCardTemp[i] = handCard[j];
				hasFilled[i] = 1;
				handCard[j].id = sortedIdIndex;
				sortedIdIndex = sortedIdIndex - 1;
			}
		}
	}

	//把TEMP的複製回手牌
	for (i = 0; i < 13; i++)
	{
		handCard[i] = handCardTemp[i];
	}
}
