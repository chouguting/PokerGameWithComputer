#include <cstdio>

#include "funclib.h"

/*
 main idea:���⭫�n���P���handCardTemp��,�����n�����ŵ�(�Ҧp�|���������|�i�@�˪��O���n��,�ѤU���i�����n)
		   ���Ҧ����n�����P����A��ѤU�P��JTEMP,�̫�A�ƻs�^�h��P
 */

void sortByComPlayer(Card* handCard, int size)
{
	int hasFilled[13] = {0}; //�x�sTemp�P�襤�Ӧ�m���S����J��
	Card handCardTemp[13]; //�Ȧs�Τ�P(��T�w���P����i�h)
	int sortIndex = size - 1; //�o��index�|�s�U�@�����Ӷ�Ȫ���m

	int currentRound = 0; //�ĴX��
	int i, j;

	int sortedIdIndex = 120; //�w�g��z�L���PID�|�ȮɳQ�令100�h�A�o��sort�ɥL�̴N�|�b�᭱

	int currentSize = size; //�ثe����z�ϰ쪺�j�p


	//�T�ӵP��
	for (currentRound = 0; currentRound < 3; currentRound++)
	{
		if (currentRound > 0)
		{
			sort(handCard, size); //����z�P(�Ĥ@ROUND����)
		}

		//printf("\n\n");


		int hasStrightFlush = 0; //���S���P�ᶶ
		int hasStright = 0; //���S����
		int hasFlush = 0; //���S���P��
		int straightFlushCardIndex[5]; //�P�ᶶ��mINDEX
		int straightCardIndex[5]; //����m INDEX
		int flushCardIndex[5]; //�P���m INDEX

		int fourOfaKindIndex = 0; //�|������m
		int hasFourOfaKind = 0; //���S���|��

		int threeOfaKindIndex = 0; //�T������m
		int hasThreeOfaKind = 0; //���S���T��

		int hasPair = 0; //���S����l
		int pairIndex = 0; //��l����m
		int hasSecondPair = 0; //���S���ĤG�ӹ�l
		int secondPairIndex = 0; //�ĤG�ӹ�l����m


		//�o�䳣�O5�i�P�~�|�X�{���P��
		if (currentRound < 2)
		{
			//�P�ɧ� �P�ᶶ,��,�P�� ����m(�p�G��)
			for (i = currentSize - 1; i >= 4; i--)
			{
				/*�Q��indexCurrent=4��J��쪺�P�ᶶ,��or�P�᪺��m
				�C���@�i�ŦX���PindexCurrent�N��@
				�p�GindexCurrent<0���ܡA�N��H�g��줭�i�F(�N����)*/
				int straightFlushIndexCurrent = 4;
				int straightIndexCurrent = 4;
				int flushIndexCurrent = 4;

				//�P�ᶶ����̤j�A���N���ΦA�䶶or�P��F
				straightFlushCardIndex[straightFlushIndexCurrent] = i;
				straightFlushIndexCurrent--;

				if (hasStright == 0) //�w�g��춶�N���ΦA�䶶�F
				{
					straightCardIndex[straightIndexCurrent] = i;
					straightIndexCurrent--;
				}

				if (hasFlush == 0) //�w�g���P��N���ΦA��P��F
				{
					flushCardIndex[flushIndexCurrent] = i;
					flushIndexCurrent--;
				}

				int lastFaceByStraightFlush = (handCard[i].id) / 4; //�Ʀr
				int lastFace = (handCard[i].id) / 4; //�Ʀr
				int lastSuit = (handCard[i].id + 1) % 4; //���

				for (j = i - 1; j >= 0; j--) //�q��P���ݶ}�l��,�o�˧�쪺�N�O�̤j��
				{
					//��P�ᶶ
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


					//�䶶
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


					//��P��
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


			//��|��
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


		//��@�ӤT��
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


		//���ӹ�l(�Ĥ@�Ө��p���ĤG�Ө��j��)
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


		//�w�g�䧹�F �}�l��JCardTemp
		if (currentRound < 2)
		{
			//����1: �P�ᶶ
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

			//����2: �K��
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
				sortIndex--; //���Ť@��
				continue;
			}


			//����3: ��Ī
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


			//����4: �P��
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


			//����5: ���l
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


		//����6: �T��
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
			sortIndex = sortIndex - 2; //���Ũ��
			continue;
		}


		//����7: ���
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
				sortIndex = sortIndex - 1; //���Ť@��
			}
			currentSize = currentSize - 4;
			sortIndex = sortIndex - 1;
			continue;
		}

		//����8: ��l
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
			sortIndex = sortIndex - 3; //���ŤT��
			continue;
		}

		//����9: ���P
		handCardTemp[sortIndex] = handCard[currentSize - 1];
		hasFilled[sortIndex] = 1;
		handCard[currentSize - 1].id = sortedIdIndex;
		sortIndex = sortIndex - 1;
		sortedIdIndex = sortedIdIndex - 1;
		currentSize = currentSize - 1;
		sortIndex = sortIndex - 4; //���ť|��
	}


	//���٨S��J���P��iTEMP���Ŧ��
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

	//��TEMP���ƻs�^��P
	for (i = 0; i < 13; i++)
	{
		handCard[i] = handCardTemp[i];
	}
}
