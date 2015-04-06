#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

int card[4][13];

double check(int check_card[]); //get sum of cards point
int deal(int deal_card[], int number, int used_card[]); //give player or computer one card
void show_card(int showed_card[], int condition); //output player or computer current card
void shuffle(int shuffle_card[], int size_card); //shuffle the cards

int main(){
char choice = 'y', decision;
int player[52] = {0}, computer[52] = {0} , used_card[52] = {0};
int i, j, counter_player = 0, counter_computer = 0;
double sum_player = 0, sum_computer = 0;
bool beyond = false, first_time = true;

for (i = 0; i < 4; ++i) //initialize the 52 cards
{
    for (j = 0; j < 13; ++j)
    {
        card[i][j] = (i + 1) * 100 + j + 1 ; //the first number stands for color,other two number stands for point
    }                                        //for example 102 stands for Hearts2
}

while (1)
{
    if (first_time) ; // only second time or later will ask you continue or not
    else
    {
        cout << "Continue or not ?(y/n)";
        cin >> choice;
        choice = tolower(choice); //make sure right input
        if ((choice != 'y')&&(choice != 'n'))
        {
            cin.clear(); //clear the cin
            cin.sync();
            continue;
        }

        shuffle(player, counter_player); //initialize the parameters before new games
        shuffle(computer, counter_computer);
        shuffle(used_card, counter_computer);
        counter_computer = 0;
        counter_player = 0;
        sum_computer = 0;
        sum_player = 0;
    }

    if (choice == 'y')
    {
        first_time = false;
        cout << "Player stage" << endl;
        counter_player = deal(player, counter_player, used_card); //give two cards to player
        counter_player = deal(player, counter_player, used_card);
        sum_player = check(player);

        show_card(player, 0);

        while (1)
        {
            cout << "Want more card ?(y/n): " ;
            cin >> decision;
            decision = tolower(decision);
            if ((decision != 'y')&&(decision != 'n')) // make sure right input
            {
                cin.clear();
                cin.sync();
                continue;
            }

            if (decision == 'y')
            {
                 cout << endl;
                 counter_player = deal(player, counter_player, used_card);
                 show_card(player, 2);
                 sum_player = check(player);
                 if (sum_player > 21) //if beyond 21 points, player loss
                 {
                     cout << "Player loss" << endl;
                     break;
                 }
            }

            if (decision == 'n') break;
        }

        if (sum_player > 21) continue; //begin new games

        shuffle(used_card, counter_player); //shuffle card for computer stage
        cout << "Computer stage" << endl;
        counter_computer = deal(computer, counter_computer, used_card);
        counter_computer = deal(computer, counter_computer, used_card);
        show_card(computer, 1);
        sum_computer = check(computer);

        while ((sum_computer <= sum_player)&&(sum_computer != 21)) //computer want more card until win player or equal to 21
        {
            counter_computer = deal(computer, counter_computer, used_card);
            show_card(computer, 2);
            sum_computer = check(computer);
        }

        if ((sum_computer == 21)&&(sum_player == 21)) //player and computer all 21
        {
            if (counter_computer < counter_player) cout << "Player win" << endl;
            if (counter_computer > counter_player) cout << "Player loss" << endl;
            if (counter_computer == counter_player) cout << "Draw" << endl;
        }

        if (sum_computer > 21) cout << "Player win" << endl;
        else cout << "Player loss" << endl;
    }

    if (choice == 'n') break;
}
}

double check(int check_card[]){ //get sum of cards point
double sum = 0, point = 0;
for (int i = 0; check_card[i] != 0; ++i)
{
        point = check_card[i] % 100;
        if (point > 10) point = 0.5;
        sum += point;
}
return sum;
}

int deal(int deal_card[], int number, int used_card[]){ //give player or computer one card
bool flag;
int j = 0, choosed_card, color, mark;

srand(time(NULL));
while (1)
{
    flag = false;
    color = rand() * 4 / (RAND_MAX +1);
    mark = rand() * 13 / (RAND_MAX +1);
    choosed_card = card[color][mark];
    for (int i = 0; used_card[i] != 0 && !flag; ++i)
    {
        if (choosed_card == used_card[i]) flag = true; //only when the choosed_card don't exist in used_card can it be given to player or computer
    }
    if (!flag) break;
}

deal_card[number] = choosed_card;

while (1) //record the given card
{
    if (used_card[j] == 0)
    {
        used_card[j] = choosed_card;
        break;
    }
    ++j;
}

return (number + 1);
}

void show_card(int showed_card[], int condition){ //output player or computer current card
int color, mark;

switch (condition)
{
    case 0 : cout << "Player get card : ";break;
    case 1 : cout << "Computer get card :";break;
    case 2 : cout << "get one more card: ";
}

for (int i = 0; showed_card[i] != 0; ++i)
{
    color = showed_card[i] / 100;
    mark = showed_card[i] % 100;

    switch (color)
    {
        case 1 : cout << "Hearts";break;
        case 2 : cout << "Spade";break;
        case 3 : cout << "Diamonds";break;
        case 4 : cout << "Club";
    }

    switch (mark)
    {
        case 1: cout << "A ";break;
        case 11: cout << "J ";break;
        case 12: cout << "Q ";break;
        case 13: cout << "K ";break;
        default : cout << mark << " ";
    }
}
    cout << endl <<endl;
}

void shuffle(int shuffle_card[], int size_card){ //shuffle the cards, initialize the player or computer or used_card
for (int i = 0; i < size_card; ++i)
{
    shuffle_card[i] = 0;
}
}

