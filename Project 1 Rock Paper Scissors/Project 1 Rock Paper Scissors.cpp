
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;


enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice Player1Choice;
	enGameChoice computerChoice;
	enWinner Winner;
	string WinnerName;
};
struct stGameResults
{
	int GameRounds;
	short Player1WinTimes, ComputerWinTimes, DrawTimes;

	enWinner GameWinner;
	string WinnerName;

};
int ReadRandomNumber(int From, int To)

{
	int randNum = rand() % (To - From + 1) + From;
	return randNum;


}

enGameChoice ReadPlayer1Choice()
{
	short choice;
	do
	{
		cout << "\n Your choice [1]:Stone ,[2]:Paper,[3]:Scissors ?\n";
		cin >> choice;





	} while (choice > 3 || choice < 1);

	return enGameChoice(choice);


}
enGameChoice GetComputerChoice()
{


	return enGameChoice(ReadRandomNumber(1, 3));


}
enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1Choice == RoundInfo.computerChoice)
	{
		return enWinner::Draw;
	}

	switch (RoundInfo.Player1Choice)
	{
	case enGameChoice::Stone:
		if (RoundInfo.computerChoice == enGameChoice::Paper)
		{
			return enWinner::Computer;
		}
		break;

	case enGameChoice::Paper:
		if (RoundInfo.computerChoice == enGameChoice::Scissors)
		{
			return enWinner::Computer;
		}
		break;

	case enGameChoice::Scissors:
		if (RoundInfo.computerChoice == enGameChoice::Stone)
		{
			return enWinner::Computer;
		}
		break;
	}

	return enWinner::Player1;
}
string PrintWinnerName(enWinner Winner)
{

	string arrWinnerName[3] = { "Player1","Computer","No Winner" };
	return  arrWinnerName[Winner - 1];


}
string ChoiceName(enGameChoice Choice)
{

	string arrameChoices[3] = { "Stone","Paper","Scissors" };
	return  arrameChoices[Choice - 1];


}

void PrintRoundResults(stRoundInfo RoundInfo)
{


	cout << "\n\n_________________" << "Round[" << RoundInfo.RoundNumber << "]____________\n\n";

	cout << "Player 1 choice:" << ChoiceName(RoundInfo.Player1Choice) << endl;
	cout << "Computer choice:" << ChoiceName(RoundInfo.computerChoice) << endl;
	cout << "Round Winner:" << RoundInfo.WinnerName << endl;
	cout << "______________________________________\n\n";

}

enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
	if (Player1WinTimes > ComputerWinTimes)
		return enWinner::Player1;
	else if (ComputerWinTimes > Player1WinTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;



}
stGameResults FillGameResult(int GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResults GameResults;

	GameResults.GameRounds = GameRounds;
	GameResults.Player1WinTimes = Player1WinTimes;
	GameResults.ComputerWinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
	GameResults.WinnerName = PrintWinnerName(GameResults.GameWinner);



	return GameResults;
}

stGameResults PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;

	short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{

		cout << "\nRound [" << GameRound << "] " << "  begins\n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choice = ReadPlayer1Choice();
		RoundInfo.computerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = PrintWinnerName(RoundInfo.Winner);


		if (RoundInfo.Winner == enWinner::Player1)
			Player1WinTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinTimes++;
		else DrawTimes++;

		PrintRoundResults(RoundInfo);
	}



	return FillGameResult(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);


}
string Tabs(short  NumberOfTabs)
{
	string t = "";

	for (int i = 1; i < NumberOfTabs; i++)
	{
		t = t + "\t";
		cout << t;

	}

	return t;



}
void ShowGameOverScreen()
{
	cout << Tabs(2) << "___________________________________________________\n\n";
	cout << Tabs(2) << "         +++ " << "G a m e O v e r ""+++\n";
	cout << Tabs(2) << "___________________________________________________\n\n";



}
void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player1:
		system("color 2F");
		break;

	case enWinner::Computer:
		system("color 4F");
		cout << "\a";
		break;

	case enWinner::Draw:
		system("color 6F");
		break;

	}




}
void ShowFinalGameResult(stGameResults GameResults)
{

	cout << Tabs(2) << "_________________[Game Result]____________________\n\n";
	cout << Tabs(2) << "Game Rounds       :" << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Player1 won times :" << GameResults.Player1WinTimes << endl;
	cout << Tabs(2) << "Computer won times:" << GameResults.ComputerWinTimes << endl;
	cout << Tabs(2) << "Draw times        :" << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "Final winner      :" << GameResults.WinnerName << endl;
	cout << Tabs(2) << "___________________________________________________\n\n";

	SetWinnerScreenColor(GameResults.GameWinner);

}
short HowManyRounds()
{

	short GameRounds;
	do
	{
		cout << "\n How many rounds ?\n";
		cin >> GameRounds;





	} while (GameRounds > 3 || GameRounds < 1);

	return GameRounds;
}
void ResetScreen()
{
	system("cls");
	system("color 0F");




}

void StartGame()
{

	char   PlayAgain = 'Y';

	do {

		ResetScreen();
		stGameResults GameResults = PlayGame(HowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResult(GameResults);


		cout << endl << Tabs(2) << "Do you want to Play again ? Y/N? \n ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');

}


int main()
{

	srand((unsigned)time(NULL));



	StartGame();




	return 0;
}

