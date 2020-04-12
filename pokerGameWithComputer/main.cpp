#include <cstdlib>
#include <stdio.h>
#include <time.h>

#include "funclib.h"

#include "computerPlayerBehavior.h"


void gameInit(); //遊戲初始化(選擇人數，制定換牌規則)
Card* handCard[4]; //四副手牌
int changeWithWhom[4]; //各個玩家要跟誰換牌
int playerCount; //儲存有幾個玩家(支援2或4人)
Card deck[52]; //牌堆

//牌面(數字)
const char* face[] = {
	"Deuce", "Three",
	"Four", "Five",
	"Six", "Seven", "Eight",
	"Nine", "Ten",
	"Jack", "Queen", "King", "Ace"
};

//牌面(花色)
const char* suit[] = {"Clubs", "Diamonds", "Hearts", "Spades"};

//這個陣列是牌型(順序配合Determine)
const char* cardType[] = {"散牌", "對子", "二對", "三條", "順子", "同花", "葫蘆", "四條", "同花順"};


int main()
{
	////////
	srand(time(nullptr));
	int i, j;

	playerCount = 4;

	printf("歡迎來到神奇的撲克遊戲 這次是跟電腦玩喔!!\n");


	gameInit(); //初始化

	int operation = 0; //存玩家的操作
	fillDeckFaceFirst(deck, face, suit); //填入牌


	int score[4] = {0}; //每個人的分數先歸零


	system("cls");
	while (true)
	{
		printf("目前分數:");
		printf("玩家: %d  ", score[0]);

		for (i = 1; i < playerCount; i++)
		{
			printf("電腦P%d:%d  ", i, score[i]);
		}

		printf("\n動作選項:\n\t(1)重新開始(重設開始積分)\n\t(2) 繼續下一回\n\t(3) 不玩了\n");
		printf("Input your operation(1~3):");
		scanf_s("%d", &operation, 10);
		if (operation == 1) //遊戲重置
		{
			system("cls");
			for (i = 0; i < 4; i++)
			{
				score[i] = 0; //歸零每個玩家的分數
			}
			printf("遊戲重制\n");
			gameInit(); //重新初始化
			system("cls");
			printf("遊戲已重制\n");
			system("pause");
			system("cls");
		}
		else if (operation == 2) //繼續遊戲
		{
			shuffle(deck);


			int scoreThisRoundTemp[4][3]; //暫存分數 4個玩家 前中後3個墩

			int currentPlayer; //現在的動作是針對哪位玩家


			//排列牌組，順便計算手牌分數
			for (currentPlayer = 0; currentPlayer < playerCount; currentPlayer++)
			{
				Card handCardTemp[13]; //暫存手牌
				int indexTemp; //暫存玩家輸入的牌的編號
				printf("\t現在輪到第%d位玩家\n", currentPlayer + 1);
				printf("\n以下是您的牌\n");
				sort(handCard[currentPlayer], 13); //先整理
				deal(handCard[currentPlayer], 13); //再印出牌

				//如果是人類玩家
				if (currentPlayer == 0)
				{
					//先把玩家輸入的排序存到handCardTemp中,再複製回handCard				

					//暫存後墩五張
					printf("請輸入後墩五張:");
					for (i = 8; i < 13; i++)
					{
						scanf_s("%d", &indexTemp, 10);
						handCardTemp[i] = handCard[currentPlayer][indexTemp - 1];
					}

					//暫存中墩五張
					printf("請輸入中墩五張:");
					for (i = 3; i < 8; i++)
					{
						scanf_s("%d", &indexTemp, 10);
						handCardTemp[i] = handCard[currentPlayer][indexTemp - 1];
					}

					//暫存前墩三張
					printf("請輸入前墩三張:");
					for (i = 0; i < 3; i++)
					{
						scanf_s("%d", &indexTemp, 10);
						handCardTemp[i] = handCard[currentPlayer][indexTemp - 1];
					}

					//把handCardTemp再複製回handCard
					for (i = 0; i < 13; i++)
					{
						handCard[currentPlayer][i] = handCardTemp[i];
					}

					sort(handCard[currentPlayer], 3); //排序前墩
					sort(handCard[currentPlayer] + 3, 5); //排序中墩
					sort(handCard[currentPlayer] + 8, 5); //排序後墩
				}
				else //如果是電腦玩家
				{
					sortByComPlayer(handCard[currentPlayer], 13);
				}

				printf("\n換牌後:\n");
				deal(handCard[currentPlayer], 13);

				//計算手牌的分數
				if (isStraight(handCard[currentPlayer], 13) == 1) //特例:如果是一條龍就讓她贏了
				{
					printf("你的牌是一條龍!!");
					for (i = 0; i < 3; i++)
					{
						scoreThisRoundTemp[currentPlayer][i] = 100000;
					}
				}
				else //正常狀況下存入分數
				{
					//利用determine印出牌型,利用giveScore手牌的分數
					printf("\n前墩: %s  分數:%d\n", cardType[determine(handCard[currentPlayer], 3)],
					       giveScore(handCard[currentPlayer], 3));
					printf("中墩: %s 分數:%d\n", cardType[determine(handCard[currentPlayer] + 3, 5)],
					       giveScore(handCard[currentPlayer] + 3, 5));
					printf("後墩: %s 分數:%d\n", cardType[determine(handCard[currentPlayer] + 8, 5)],
					       giveScore(handCard[currentPlayer] + 8, 5));

					//把各玩家的三墩分數暫存起來
					scoreThisRoundTemp[currentPlayer][0] = giveScore(handCard[currentPlayer], 3);
					scoreThisRoundTemp[currentPlayer][1] = giveScore(handCard[currentPlayer] + 3, 5);
					scoreThisRoundTemp[currentPlayer][2] = giveScore(handCard[currentPlayer] + 8, 5);


					//規則判斷: 後墩必須大於等於中墩，中墩必須大於等於前墩，否則視為三墩全輸
					if (scoreThisRoundTemp[currentPlayer][0] >= scoreThisRoundTemp[currentPlayer][1] ||
						scoreThisRoundTemp[currentPlayer][1] >= scoreThisRoundTemp[currentPlayer][2])
					{
						printf("\n但你違反了規則要你的排序方式,所以全部零分");
						printf("(後墩必須大於等於中墩，中墩必須大於等於前墩，否則視為三墩全輸)\n\n");
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

			//計算比較各墩後的最終分數
			for (currentPlayer = 0; currentPlayer < playerCount; currentPlayer++)
			{
				printf("現在結算 第%d位玩家這輪的分數:\n", currentPlayer + 1);
				printf("\n\t前墩\t中墩\t後墩\n");
				printf("我自己\t%d\t%d\t%d\n", scoreThisRoundTemp[currentPlayer][0], scoreThisRoundTemp[currentPlayer][1],
				       scoreThisRoundTemp[currentPlayer][2]);
				printf("\n");
				int homerunCount = 0; //計算全贏的場數
				for (i = 0; i < playerCount; i++)
				{
					if (i != currentPlayer)
					{
						printf("第%d位\t%d\t%d\t%d\n", i + 1, scoreThisRoundTemp[i][0], scoreThisRoundTemp[i][1],
						       scoreThisRoundTemp[i][2]);
					}
				} //印出和其他玩家的對照
				printf("\n\n\n");

				for (i = 0; i < playerCount; i++)
				{
					int winTimesWithOtherPlayer = 0; //儲存和另一個玩家比較 贏的場次
					int tieTimesWithOtherPlayer = 0; //儲存和另一個玩家比較 平手的場次
					if (i != currentPlayer) //不用和自己比
					{
						for (j = 0; j < 3; j++)
						{
							if (scoreThisRoundTemp[currentPlayer][j] > scoreThisRoundTemp[i][j])
							{
								winTimesWithOtherPlayer++;
							}
							if (scoreThisRoundTemp[currentPlayer][j] == scoreThisRoundTemp[i][j])
							{
								tieTimesWithOtherPlayer++;
							}
						}
						int totalPlus = 0; //暫存總分要加的分
						if (tieTimesWithOtherPlayer == 3) //全部平手 加0分
						{
							totalPlus = 0;
						}
						else if (winTimesWithOtherPlayer == 3) //全贏 加6分
						{
							score[currentPlayer] = score[currentPlayer] + 6;
							totalPlus = 6;
							homerunCount++;
						}
						else if (winTimesWithOtherPlayer == 2) //輸一場 加2分
						{
							score[currentPlayer] = score[currentPlayer] + 2;
							totalPlus = 2;
						}
						else if (winTimesWithOtherPlayer == 1) //贏一場 減1分
						{
							score[currentPlayer] = score[currentPlayer] - 1;
							totalPlus = -1;
						}
						else if (winTimesWithOtherPlayer == 0) //全輸 減6分
						{
							score[currentPlayer] = score[currentPlayer] - 6;
							totalPlus = -6;
						}


						printf("第%d位玩家 對第%d位玩家 總分加%d\n", currentPlayer + 1, i + 1, totalPlus);
					}
				}
				if (homerunCount >= 3 && playerCount == 4) //如果對其他玩家都是全贏,就HOMERUN
				{
					printf("恭喜你紅不讓了!!! 總分再加18分\n");
					score[currentPlayer] = score[currentPlayer] + 18;
				}

				printf("結果: 第%d位玩家總分:%d\n\n\n", currentPlayer + 1, score[currentPlayer]);
			}

			system("pause");
			system("cls");
		}
		else if (operation == 3)
		{
			break;
		}
	}

	system("cls");
	printf("感謝遊玩");
	system("pause");
	return 0;
}


void gameInit()
{
	int i;
	int playHandCardIndex; //玩家選第幾副牌

	printf("請問你要選擇第幾副牌做為您的手牌(第一到四副):");
	scanf_s("%d", &playHandCardIndex, 10);

	playHandCardIndex = playHandCardIndex - 1; //實際INDEX要再減一

	//四副手牌
	for (i = 0; i < 4; i++)
	{
		handCard[i] = deck + 13 * i;
	}

	//把玩家選擇的那副牌換到第一個位置
	Card* chagetemp = handCard[0];
	handCard[0] = handCard[playHandCardIndex];
	handCard[playHandCardIndex] = chagetemp;
}
