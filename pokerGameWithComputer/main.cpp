#include <cstdlib>
#include <stdio.h>
#include <time.h>

#include "funclib.h"
#include "oldLib.h"
#include "testLib.h"
#include "computerPlayerBehavior.h"


void gameInit();

Card* handCard[4];
int changeWithWhom[4], playerCount;



Card deck[52];
const char* face[] = { "Deuce", "Three",
                       "Four", "Five",
                       "Six", "Seven", "Eight",
                       "Nine", "Ten",
                       "Jack", "Queen", "King" ,"Ace" };

const char* suit[] = { "Clubs","Diamonds","Hearts","Spades" };

const char* cardType[] = { "���P","��l","�G��","�T��" ,"���l" ,"�P��" ,"��Ī" ,"�|��" ,"�P�ᶶ" };




int main()
{
    		////////
    srand(time(NULL));
    int i,j;
    playerCount = 4;
	
    printf("�w��Ө쯫�_�����J�C�� �o���O��q������!!\n");


    
	
    gameInit();

    fillDeckFaceFirst(deck, face, suit);
    int operation=0;
    

    int score[4] = {0};

    
	
    system("cls");
	while(1)
	{
        printf("�ثe����:");
        printf("���a: %d  ",score[0]);
		
		for(i=1;i<playerCount;i++)
		{	
            printf("�q��P%d:%d  ",i, score[i]);
		}
		
        printf("\n�ʧ@�ﶵ:\n\t(1)���s�}�l(���]�}�l�n��)\n\t(2) �~��U�@�^\n\t(3) �����F\n");
        printf("Input your operation(1~3):");
        scanf_s("%d", &operation, 10);
		if(operation==1)
		{
            system("cls");
            for(i=0;i<4;i++)
            {
                score[i] = 0;
            }
            printf("�C������\n");
            gameInit();
            system("cls");
            printf("�C���w����\n");
            system("pause");
            system("cls");
		}else if(operation==2)
		{
            shuffle(deck);
            //dealManyPlayer(playerCount, deck);
			
           
            int changeCardIndexBuffer[4][3]; //�Ȧs�n�����P�O����

            int scoreThisRoundTemp[4][3]; //�Ȧs���� 4�Ӫ��a �e����3�Ӽ[
			
            int currentPlayer;

			

			

			//���a�ƦC�P�աA���K�p���P����
			for(currentPlayer=0;currentPlayer<playerCount;currentPlayer++)
			{
				
                Card handCardTemp[13];
				int indexTemp; //�Ȧs�Ʀn���P
                printf("\t�{�b�����%d�쪱�a\n", currentPlayer + 1);
                printf("\n�H�U�O�z���P\n");
                //system("pause");
                sort(handCard[currentPlayer], 13);
                deal(handCard[currentPlayer], 13);
                i = 0;

				if(currentPlayer==0)
				{
                    //�e�[�T�i
                    printf("�п�J�e�[�T�i:");
                    for (i = 0; i < 3; i++)
                    {
                        scanf_s("%d", &indexTemp, 10);
                        handCardTemp[i] = handCard[currentPlayer][indexTemp - 1];
                    }

                    //���[���i
                    printf("�п�J���[���i:");
                    for (; i < 8; i++)
                    {
                        scanf_s("%d", &indexTemp, 10);
                        handCardTemp[i] = handCard[currentPlayer][indexTemp - 1];
                    }
                    //��[���i
                    printf("�п�J��[���i:");
                    for (; i < 13; i++)
                    {
                        scanf_s("%d", &indexTemp, 10);
                        handCardTemp[i] = handCard[currentPlayer][indexTemp - 1];
                    }

                    for (i = 0; i < 13; i++)
                    {
                        handCard[currentPlayer][i] = handCardTemp[i];
                    }

                    sort(handCard[currentPlayer], 3);
                    sort(handCard[currentPlayer] + 3, 5);
                    sort(handCard[currentPlayer] + 8, 5);

				}else
				{
                    sortByComPlayer(handCard[currentPlayer], 13);
				}
				
                printf("\n���P��:\n");
                deal(handCard[currentPlayer], 13);

                //�p���P������
				if(isStraight(handCard[currentPlayer],13)==1) //�p�G�O�@���s�N���oĹ�F
				{
                    printf("�A���P�O�@���s!!");
                    for (i = 0; i < 3; i++)
                    {
                        scoreThisRoundTemp[currentPlayer][i] = 100000;
                    }
				}else//�s�J����
				{
                    printf("\n�e�[: %s  ����:%d\n", cardType[determine(handCard[currentPlayer], 3)], giveScore(handCard[currentPlayer], 3));
                    printf("���[: %s ����:%d\n", cardType[determine(handCard[currentPlayer] + 3, 5)], giveScore(handCard[currentPlayer] + 3, 5));
                    printf("��[: %s ����:%d\n", cardType[determine(handCard[currentPlayer] + 8, 5)], giveScore(handCard[currentPlayer] + 8, 5));

                    scoreThisRoundTemp[currentPlayer][0] = giveScore(handCard[currentPlayer], 3);
                    scoreThisRoundTemp[currentPlayer][1] = giveScore(handCard[currentPlayer] + 3, 5);
                    scoreThisRoundTemp[currentPlayer][2] = giveScore(handCard[currentPlayer] + 8, 5);

                    if (scoreThisRoundTemp[currentPlayer][0] >= scoreThisRoundTemp[currentPlayer][1] || scoreThisRoundTemp[currentPlayer][1] >= scoreThisRoundTemp[currentPlayer][2])
                    {
                        printf("\n���A�H�ϤF�W�h�n�A���ƧǤ覡,�ҥH�����s��");
                        printf("(��[�����j�󵥩󤤼[�A���[�����j�󵥩�e�[�A�_�h�����T�[����)\n\n");
                        for (i = 0; i < 3; i++)
                        {
                            scoreThisRoundTemp[currentPlayer][i] = 0;
                        }
                    }
				}

                
				
                system("pause");
                system("cls");
			}
			

            system("cls");
            //�p�����U�[�᪺�̲פ���
            for (currentPlayer = 0; currentPlayer < playerCount; currentPlayer++)
            {
                printf("�{�b���� ��%d�쪱�a�o��������:\n", currentPlayer + 1);
                printf("\n\t�e�[\t���[\t��[\n");
                printf("�ڦۤv\t%d\t%d\t%d\n", scoreThisRoundTemp[currentPlayer][0], scoreThisRoundTemp[currentPlayer][1], scoreThisRoundTemp[currentPlayer][2]);
                printf("\n");
                int homerunCount = 0;
            	for(i=0;i<playerCount;i++)
            	{
            		if(i!=currentPlayer)
            		{
                        printf("��%d��\t%d\t%d\t%d\n", i + 1, scoreThisRoundTemp[i][0], scoreThisRoundTemp[i][1], scoreThisRoundTemp[i][2]);
            		}
            		
            	}
                printf("\n\n\n");
            	
                for (i = 0; i < playerCount; i++)
                {
                    int winTimesWithOtherPlayer = 0;
                    int tieTimesWithOtherPlayer = 0;
                    if (i != currentPlayer)
                    {
                    	for (j = 0; j < 3; j++)
                        {
                            if(scoreThisRoundTemp[currentPlayer][j]>scoreThisRoundTemp[i][j])
                            {
                                winTimesWithOtherPlayer++;
                            }
                            if (scoreThisRoundTemp[currentPlayer][j] == scoreThisRoundTemp[i][j])
                            {
                                tieTimesWithOtherPlayer++;
                            }
                        }
                        int totalPlus = 0;
                        if (tieTimesWithOtherPlayer == 3)
                        {
                            totalPlus = 0;
                        }
                        else if (winTimesWithOtherPlayer == 3 )
                        {
                            score[currentPlayer] = score[currentPlayer] + 6;
                            totalPlus = 6;
                            homerunCount++;
                        }
                        else if (winTimesWithOtherPlayer == 2 )
                        {
                            score[currentPlayer] = score[currentPlayer] + 2;
                            totalPlus = 2;
                        }
                        else if (winTimesWithOtherPlayer == 1 )
                        {
                            score[currentPlayer] = score[currentPlayer] - 1;
                            totalPlus = -1;
                        }
                        else if (winTimesWithOtherPlayer == 0 )
                        {
                            score[currentPlayer] = score[currentPlayer] - 6;
                            totalPlus = -6;
                        }
                        
                    	
                        printf("��%d�쪱�a ���%d�쪱�a �`���[%d\n", currentPlayer + 1, i + 1, totalPlus);
                    }
	
                }
            	if(homerunCount>=3 && playerCount == 4)
            	{
                    printf("���ߧA�������F!!! �`���A�[18��\n");
                    score[currentPlayer] = score[currentPlayer] + 18;
            	}

                printf("���G: ��%d�쪱�a�`��:%d\n\n\n",currentPlayer+1,score[currentPlayer]);
            }
            
            system("pause");
            system("cls");
			
		}else if(operation==3)
		{
            break;
		}
		
	}

    system("cls");																				// �~�P
    printf("�P�¹C��");

    system("pause");
    return 0;
}


void gameInit()
{
    int i;
    int playHandCardIndex;//���a��ĴX�ƵP
    
    printf("�аݧA�n��ܲĴX�ƵP�����z����P(�Ĥ@��|��):");
    scanf_s("%d", &playHandCardIndex, 10);

    playHandCardIndex = playHandCardIndex - 1;//���INDEX�n�A��@

	//�|�Ƥ�P
    for (i = 0; i < 4; i++)
    {
        handCard[i] = deck + 13 * i;
    }
	
    Card* chagetemp = handCard[0];//
    handCard[0] = handCard[playHandCardIndex];
    handCard[playHandCardIndex] = chagetemp;
	
    
    
}