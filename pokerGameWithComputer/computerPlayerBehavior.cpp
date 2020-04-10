#include <cstdio>

#include "funclib.h"
void sortByComPlayer(Card* handCard,int size)
{
	int hasFilled[13] = {0};
	Card handCardTemp[13];
	int sortIndex = size-1;
	
	int currentRound = 0,i,j;

	int sortedIdIndex = 120;
	
	int currentSize = size;

	


	//三個牌敦
	for(currentRound=0;currentRound<3;currentRound++)
	{


		//printf("\nround:%d\n",currentRound);
		//printf("sortIndex:%d  currentSize:%d 本輪的牌:\n", sortIndex,currentSize);
		if (currentRound > 0)
		{
			sort(handCard, size);
		}
		//deal(handCard, 13);
		printf("\n\n");

		

		
		int hasStrightFlush = 0;  //有同花順
		int hasStright = 0;		  //有順
		int hasFlush = 0;		  //可以找同花順 順 同花
		int straightFlushCardIndex[5];//同花順INDEX
		int straightCardIndex[5];	  //順 INDEX
		int flushCardIndex[5];		  //同花 INDEX

		int fourOfaKindIndex = 0;
		int hasFourOfaKind = 0;

		int threeOfaKindIndex = 0;
		int hasThreeOfaKind = 0;

		int hasPair = 0;
		int pairIndex = 0;
		int hasSecondPair = 0;
		int secondPairIndex = 0;


		
		if (currentRound < 2)
		{
			//抓 同花順,順,同花
			for (i = currentSize - 1; i >= 4; i--)
			{
				int straightFlushIndexCurrent = 4;
				int straightIndexCurrent = 4;
				int flushIndexCurrent = 4;


				straightFlushCardIndex[straightFlushIndexCurrent] = i;
				straightFlushIndexCurrent--;

				if (hasStright == 0)
				{
					straightCardIndex[straightIndexCurrent] = i;
					straightIndexCurrent--;
				}

				if (hasFlush == 0)
				{
					flushCardIndex[flushIndexCurrent] = i;
					flushIndexCurrent--;
				}

				int lastFaceByStraightFlush = (handCard[i].id) / 4; //數字
				int lastFace = (handCard[i].id) / 4; //數字
				int lastSuit = (handCard[i].id + 1) % 4; //花色

				for (j = i - 1; j >= 0; j--)
				{
					//同花順
					if (lastFaceByStraightFlush - 1 == (handCard[j].id) / 4 && lastSuit == (handCard[j].id + 1) % 4 && hasStrightFlush == 0)
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


					
					//順
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

					
					//同花
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


			//printf("\n同花順:%d 順:%d 同花:%d\n",hasStrightFlush,hasStright,hasFlush);


			
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

			if (howManyOfaKind(3, handCard + i, 3) == 1&& howManyOfaKind(3, handCard + i+1, 3) == 0 && i > 0)
			{
				hasThreeOfaKind = 1;
				threeOfaKindIndex = i;
				break;
			}else if (howManyOfaKind(3, handCard + i, 3) == 1  && i == 0)
			{
				hasThreeOfaKind = 1;
				threeOfaKindIndex = i;
				break;
			}
		}
		if (hasThreeOfaKind == 1)printf("ThreeOfaKind Index:%d\n",threeOfaKindIndex);


	    //抓兩個對子(第一個取小的第二個取大的)
		for (i = currentSize ; i >= 1;i--)
		{
			if (hasSecondPair==0&&hasPair == 1 && whereIsHowManyOfaKind(2, handCard, i) != -1)
			{
				if (whereIsHowManyOfaKind(3, handCard, i) != whereIsHowManyOfaKind(2, handCard, i))
				{
					hasSecondPair = 1;
					secondPairIndex = pairIndex;
				}
				
			}
			if ( whereIsHowManyOfaKind(2, handCard, i)!=-1)
			{
				if(hasThreeOfaKind==1&& threeOfaKindIndex == whereIsHowManyOfaKind(2, handCard, i))
				{
					
				}else
				{
					hasPair = 1;
					pairIndex = whereIsHowManyOfaKind(2, handCard, i);
				}
			}
			
			
		}
		if (pairIndex == secondPairIndex)hasSecondPair = 0;

		if (hasPair == 1)printf("pair Index:%d\n",pairIndex);
		if (hasSecondPair == 1)printf("SECOND pair Index:%d\n", secondPairIndex);
		
		

		if (currentRound < 2) {
			//順位1: 同花順
			if (hasStrightFlush == 1)
			{
				for (i = 0; i < 5; i++)
				{
					handCardTemp[sortIndex] = handCard[straightFlushCardIndex[i]];
					hasFilled[sortIndex] = 1;
					//printf("存入SORTINDEX: %d  牌的ID:%d\n", sortIndex, handCard[straightFlushCardIndex[i]].id);
					handCard[straightFlushCardIndex[i]].id = sortedIdIndex;
					sortedIdIndex=sortedIdIndex - 1;
					
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
					//printf("存入SORTINDEX: %d  牌的ID:%d\n", sortIndex, handCard[fourOfaKindIndex + i].id);
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
					//printf("存入SORTINDEX: %d  牌的ID:%d\n", sortIndex, handCard[threeOfaKindIndex + i].id);
					handCard[threeOfaKindIndex + i].id = sortedIdIndex;
					sortedIdIndex = sortedIdIndex - 1;
					sortIndex = sortIndex - 1;

				}
				for (i = 0; i < 2; i++)
				{
					handCardTemp[sortIndex] = handCard[pairIndex + i];
					hasFilled[sortIndex] = 1;
					//printf("存入SORTINDEX: %d  牌的ID:%d\n", sortIndex, handCard[pairIndex + i].id);
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
					//printf("存入SORTINDEX: %d  牌的ID:%d\n", sortIndex, handCard[flushCardIndex[i]].id);
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
					//printf("存入SORTINDEX: %d  牌的ID:%d\n", sortIndex, handCard[straightCardIndex[i]].id);
					handCard[straightCardIndex[i]].id = sortedIdIndex;
					sortedIdIndex = sortedIdIndex - 1;
					sortIndex = sortIndex - 1;
				}
				currentSize = currentSize - 5;
				continue;
			}

		}

		
		//順位6: 三條
		if(hasThreeOfaKind==1)
		{
			for (i = 0; i < 3; i++)
			{
				handCardTemp[sortIndex] = handCard[threeOfaKindIndex + i];
				hasFilled[sortIndex] = 1;
				//printf("存入SORTINDEX: %d  牌的ID:%d\n", sortIndex, handCard[threeOfaKindIndex + i].id);
				handCard[threeOfaKindIndex + i].id = sortedIdIndex;
				sortedIdIndex = sortedIdIndex - 1;
				sortIndex = sortIndex - 1;
			}
			currentSize = currentSize - 3;
			sortIndex=sortIndex-2;
			continue;
		}

		
		//順位7: 兩對
		if (hasPair == 1 && hasSecondPair==1)
		{
			for (i = 0; i < 2; i++)
			{
				handCardTemp[sortIndex] = handCard[pairIndex + i];
				hasFilled[sortIndex] = 1;
				//printf("存入SORTINDEX: %d  牌的ID:%d\n", sortIndex, handCard[pairIndex + i].id);
				handCard[pairIndex + i].id = sortedIdIndex;
				sortedIdIndex = sortedIdIndex - 1;
				sortIndex = sortIndex - 1;
			}
			for (i = 0; i < 2; i++)
			{
				handCardTemp[sortIndex] = handCard[secondPairIndex + i];
				hasFilled[sortIndex] = 1;
				//printf("存入SORTINDEX: %d  牌的ID:%d\n", sortIndex, handCard[secondPairIndex + i].id);
				handCard[secondPairIndex + i].id = sortedIdIndex;
				sortedIdIndex = sortedIdIndex - 1;
				sortIndex = sortIndex - 1;
				
			}
			currentSize = currentSize - 4;
			sortIndex = sortIndex - 1;
			continue;
		}
		
		//順位8: 對子
		if(hasPair==1)
		{
			if(hasSecondPair==1)
			{
				pairIndex = secondPairIndex;
			}
			for (i=0;i<2;i++)
			{
				handCardTemp[sortIndex] = handCard[pairIndex + i];
				hasFilled[sortIndex] = 1;
				//printf("存入SORTINDEX: %d  牌的ID:%d\n", sortIndex, handCard[pairIndex + i].id);
				handCard[pairIndex + i].id = sortedIdIndex;
				sortedIdIndex = sortedIdIndex - 1;
				sortIndex = sortIndex - 1;
			}
			currentSize = currentSize - 2;
			sortIndex = sortIndex - 3;
			continue;
			
		}

		//順位9: 散牌
		handCardTemp[sortIndex] = handCard[currentSize-1];
		hasFilled[sortIndex] = 1;
		//printf("存入SORTINDEX: %d  牌的ID:%d\n",sortIndex, handCard[currentSize - 1].id);
		handCard[currentSize - 1].id = sortedIdIndex;
		
		sortedIdIndex = sortedIdIndex - 1;
		currentSize = currentSize - 1;
		sortIndex=sortIndex-5;



		
	}

	
	
	for(i=0;i<13;i++)
	{
		for(j=0;j<13;j++)
		{
			if(hasFilled[i]==0&&handCard[j].id<100)
			{
				handCardTemp[i] = handCard[j];
				hasFilled[i] = 1;
				handCard[j].id = sortedIdIndex;
				sortedIdIndex = sortedIdIndex - 1;
			}
		}
	}

	

	//printf("TEMP:\n");
	//deal(handCardTemp, 13);

	//printf("\HAND ORG:\n");
	//deal(handCard, 13);
	
	for (i = 0; i < 13; i++)
	{
		handCard[i] = handCardTemp[i];
	}
	
}
