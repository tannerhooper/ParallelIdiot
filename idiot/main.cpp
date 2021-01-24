#include <iostream>
#include <mpi.h>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>

#define MCW MPI_COMM_WORLD

using namespace std;

struct card{
  int value;
  int suit;
};

void myShuffle(vector<struct card > &myDeck){
    //shuffles deck
    srand(time(0));
    for (int i = 0; i < myDeck.size()-1; i++){
        int j = i + rand() % (myDeck.size()-i);
        swap(myDeck[i], myDeck[j]);
    }
}

bool compareByValue(const card &a, const card &b){
    return a.value < b.value;
}

void sortHand(vector<struct card > &myHand){
    //sorting magic
    std::sort(myHand.begin(),myHand.end(),compareByValue);
}

vector<int> findLowestCard(vector<struct card > &cards, struct card compare){
    //finds the card that is greater than the card of the table and how many.
    vector<int> playMe;
    for (int i = 0; i < cards.size(); i++){
        if (playMe.size() == 0){
            if (cards[i].value >= compare.value){
                playMe.push_back(i);
            }
        }
        else {
            if (cards[playMe.back()].value == cards[i].value){
                playMe.push_back(i);
            }
            else {
                return playMe;
            }
        }
    }
    if (playMe.size() == 0) { playMe.push_back(-1); }
    return playMe;
}

int findLowestCardBool(struct card &singlecard, struct card &compare){
    //for face down
    if(singlecard.value >= compare.value){
        return 1;
    }else{
        return -1;
    }
}

int inaRow(vector<struct card> hand){
    int count = 1;
    for(int i = 0; i < hand.size()-1; i++){
        if(hand[i].value == hand[i+1].value){
            count++;
        }else{
            count = 1;
        }
        if(count >= 4){
            return 1;
        }
    }
    return 0;
}

void cardDisp(struct card &card){
    for(int i = 0; i < 10; i ++){
        if(i == 5){
            if(card.suit == 3){
                cout << "|   diamonds   |";
            }else if(card.suit == 2){
                cout << "|    hearts    |";
            }else if(card.suit == 1){
                cout << "|    spades    |";
            }else{
                cout << "|    clubs     |";
            }
        }else if(i == 4){
            cout << "|      of      |";
        }else if(i == 3){
            if(card.value == 10){
                cout << "|     Jack     |";
            }else if(card.value == 11){
                cout << "|     Queen    |";
            }else if(card.value == 12){
                cout << "|     King     |";
            }else if(card.value == 13){
                cout << "|     Ace      |";
            }else if(card.value == 14){
                cout << "|       2      |";
            }else if(card.value == 15){
                cout << "|      10      |";
            }else{
                cout << "|       "  << card.value << "      |";
            }
        }else{
            for(int j = 0; j < 16; j++){
                if(i == 0 || i == 9){
                    cout << "-";
                }else{
                    if(j == 0 || j == 15){
                        cout << "|";
                    }else{
                        cout << " ";
                    }
                }
            }
        }
        cout << endl;
    }
    cout << endl;
}

void handDisp(vector<struct card> hand){
    //Display up to 12 cards correctly
    for(int i = 0; i < 10; i ++){
        if(i == 5){
            for(int k = 0; k < hand.size(); k++){
                if(hand[k].suit == 3){
                    cout << "|   diamonds   |  ";
                }else if(hand[k].suit == 2){
                    cout << "|    hearts    |  ";
                }else if(hand[k].suit == 1){
                    cout << "|    spades    |  ";
                }else{
                    cout << "|    clubs     |  ";
                }
            }
        }else if(i == 4){
            for(int k = 0; k < hand.size(); k++){
                cout << "|      of      |  ";
            }
        }else if(i == 3){
            for(int k = 0; k < hand.size(); k++){
                if(hand[k].value == 10){
                    cout << "|     Jack     |  ";
                }else if(hand[k].value == 11){
                    cout << "|     Queen    |  ";
                }else if(hand[k].value == 12){
                    cout << "|     King     |  ";
                }else if(hand[k].value == 13){
                    cout << "|     Ace      |  ";
                }else if(hand[k].value == 14){
                    cout << "|       2      |  ";
                }else if(hand[k].value == 15){
                    cout << "|      10      |  ";
                }else{
                    cout << "|       "  << hand[k].value << "      |  ";
                }
            }
        }else{
            for(int k = 0; k < hand.size(); k++){
                if(k > 0){
                    cout << "  ";
                }
                for(int j = 0; j < 16; j++){
                    if(i == 0 || i == 9){
                        cout << "-";
                    }else{
                        if(j == 0 || j == 15){
                            cout << "|";
                        }else{
                            cout << " ";
                        }
                    }
                }
            }
        }
        cout << endl;
    }
}

void handNoDisp(vector<struct card> hand){
    for(int i = 0; i < 10; i ++){
        if(i == 5){
            for(int k = 0; k < hand.size(); k++){
                if(hand[k].suit == 3){
                    cout << "|   ********   |  ";
                }else if(hand[k].suit == 2){
                    cout << "|    ******    |  ";
                }else if(hand[k].suit == 1){
                    cout << "|    ******    |  ";
                }else{
                    cout << "|    *****     |  ";
                }
            }
        }else if(i == 4){
            for(int k = 0; k < hand.size(); k++){
                cout << "|      **      |  ";
            }
        }else if(i == 3){
            for(int k = 0; k < hand.size(); k++){
                if(hand[k].value == 10){
                    cout << "|     ****     |  ";
                }else if(hand[k].value == 11){
                    cout << "|     *****    |  ";
                }else if(hand[k].value == 12){
                    cout << "|     ****     |  ";
                }else if(hand[k].value == 13){
                    cout << "|     ***      |  ";
                }else if(hand[k].value == 14){
                    cout << "|       *      |  ";
                }else if(hand[k].value == 15){
                    cout << "|      **      |  ";
                }else{
                    cout << "|       *      |  ";
                }
            }
        }else{
            for(int k = 0; k < 5; k++){
                if(k > 0){
                    cout << "  ";
                }
                for(int j = 0; j < 16; j++){
                    if(i == 0 || i == 9){
                        cout << "-";
                    }else{
                        if(j == 0 || j == 15){
                            cout << "|";
                        }else{
                            cout << " ";
                        }
                    }
                }
            }
        }
        cout << endl;
    }
}


int main(int argc, char **argv){
    //init values and MPI
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);
    int deckNum = 3;
    vector<struct card > deck;
    vector<struct card > down;
    vector<struct card > up;
    vector<struct card > hand;
    vector<struct card > table;
    struct card current;
    current.value = 0;
    current.suit = 0;
    bool idiot = false;
    int yourTurn = 0;
    srand(rank*time(0));
    int cantPlay = -1;
    bool first = false;
    int shouldDeal = false;

//  suits
//  0: club
//  1: spade
//  2: heart
//  3: diamond

//  dealt hands
//  0-4: face down
//  5-9: face up
//  10-14: hand

//  card values
//  3-9: 3-9
//  10; J
//  11: Q
//  12: K
//  13: A
//  14: 2
//  15: 10

//  MPI Send Receive tags
//  0: value
//  1: suit
//  2: flag/yourTurn
//  3: cantPlay
//  4: table size
//  5: deal me
//  6: deal me #
//  7: rank value
//  8: rank suit
//  9: sending #
//  10: current value mid turn
//  11: current suit mid turn
//  12: current value end turn
//  13: current suit end turn

    //deals the cards from 0
    if (!rank){
        //init deck
        for (int i = 0; i < deckNum; i++){
            for (int j = 3; j <= 15; j++){
                for (int k = 0; k < 4; k++){
                    struct card tmp;
                    tmp.value = j;
                    tmp.suit = k;
                    deck.push_back(tmp);
                }
            }
        }
        //shuffles deck
        myShuffle(deck);

        //deal to players
        for (int i = 0; i < 15*size; i++){
            MPI_Send(&deck[0].value,1,MPI_INT,i%size,0,MCW);
            MPI_Send(&deck[0].suit,1,MPI_INT,i%size,1,MCW);
            deck.erase(deck.begin());
            if (i%size == 0){
                struct card tmp2;
                MPI_Recv(&tmp2.value,1,MPI_INT,0,0,MCW,MPI_STATUS_IGNORE);
                MPI_Recv(&tmp2.suit,1,MPI_INT,0,1,MCW,MPI_STATUS_IGNORE);
                up.push_back(tmp2);
            }
        }
        yourTurn = 1;
        first = true;
    }
    //receives the cards
    else {
        //receive from dealer
        for (int i = 0; i < 15; i++){
            struct card tmp3;
            MPI_Recv(&tmp3.value,1,MPI_INT,0,0,MCW,MPI_STATUS_IGNORE);
            MPI_Recv(&tmp3.suit,1,MPI_INT,0,1,MCW,MPI_STATUS_IGNORE);
            up.push_back(tmp3);
        }
    }

    //exchange between hand and up
    for (int i = 0; i < 10; i++){
        if (i < 5){
            down.push_back(up[0]);
        }
        else {
            //if (i == 5) { sortHand(up); }
            hand.push_back(up[0]);
        }
        up.erase(up.begin());
    }
    sortHand(up);
    sortHand(hand);
    int count = 0;
    string x;
    int disp = 0;

    //displays the cards
    if(!rank){
        cout << rank << ": was dealt" << endl;
        cout << rank << ": Face Down on Table:" << endl;
        //handDisp(down);
        handNoDisp(down);
        cout << rank << ": Face Up on Table:" << endl;
        handDisp(up);
        cout << rank << ": Hand:" << endl;
        handDisp(hand);
        cout << endl;
        disp = 1;
        MPI_Send(&disp,1,MPI_INT,rank+1,0,MCW);
    }
    else{
        MPI_Recv(&disp,1,MPI_INT,MPI_ANY_SOURCE,0,MCW,MPI_STATUS_IGNORE);
        cout << rank << ": was dealt" << endl;
        cout << rank << ": Face Down on Table:" << endl;
        //handDisp(down);
        handNoDisp(down);
        cout << rank << ": Face Up on Table:" << endl;
        handDisp(up);
        cout << rank << ": Hand:" << endl;
        handDisp(hand);
        cout << endl;
        disp = 1;
        //sends the flag to display everywhere
        if(rank != size-1){
            MPI_Send(&disp,1,MPI_INT,rank+1,0,MCW);
        }
    }
    //pauses the code to allow for presentation
    if(!rank){
        cin >> x;
    }
    //allows all processors to catch up
    MPI_Barrier(MCW);
    int playAgain = 0;
    //begins the game
    while(!idiot){
        int flag0;
        int flag1;
        int flag2;
        int flag3;
        if (!rank){
            //continuous while loop to chack for probes
            while(yourTurn == 0){
                //probes for turn
                MPI_Iprobe(MPI_ANY_SOURCE,2,MCW,&flag0,MPI_STATUS_IGNORE);
                if(flag0){
                    MPI_Recv(&yourTurn,1,MPI_INT,MPI_ANY_SOURCE,2,MCW,MPI_STATUS_IGNORE);
                    MPI_Recv(&current.value,1,MPI_INT,MPI_ANY_SOURCE,10,MCW,MPI_STATUS_IGNORE);
                    MPI_Recv(&current.suit,1,MPI_INT,MPI_ANY_SOURCE,11,MCW,MPI_STATUS_IGNORE);
                    //if no more cards
                    if(hand.size() == 0 && up.size() == 0 && down.size() == 0){
                        yourTurn = -1;
                    }
                }
                //probes for other processors not being able to play
                MPI_Iprobe(MPI_ANY_SOURCE,3,MCW,&flag1,MPI_STATUS_IGNORE);
                if (flag1) {
                    vector<struct card > tabletmp = table;
                    //receives which processor can't play
                    MPI_Recv(&cantPlay, 1, MPI_INT, MPI_ANY_SOURCE, 3, MCW, MPI_STATUS_IGNORE);
                    int tSize = table.size();
                    //sends how many cards the processor will receive
                    MPI_Send(&tSize, 1, MPI_INT, cantPlay, 4, MCW);
                    while (table.size() > 0) {
                        MPI_Send(&table[0].value, 1, MPI_INT, cantPlay, 0, MCW);
                        MPI_Send(&table[0].suit, 1, MPI_INT, cantPlay, 1, MCW);
                        table.erase(table.begin());
                    }
                    cout << cantPlay << ": can not play and received " << tSize << " card(s):" << endl;
                    handDisp(tabletmp);
                    cout << endl;
                }
                //taking Card from other processors and placing on table
                MPI_Iprobe(MPI_ANY_SOURCE,5,MCW,&flag2,MPI_STATUS_IGNORE);
                if (flag2){
                    int playSize;
                    int curRank;
                    //receives which rank and how many will be playing
                    MPI_Recv(&playSize,1,MPI_INT,MPI_ANY_SOURCE,5,MCW,MPI_STATUS_IGNORE);
                    MPI_Recv(&curRank,1,MPI_INT,MPI_ANY_SOURCE,7,MCW,MPI_STATUS_IGNORE);
                    for (int i = 0; i < playSize; i++){
                        struct card tmp6;
                        cout << curRank << ": Placed Card on Table:" << endl;
                        MPI_Recv(&tmp6.value,1,MPI_INT,MPI_ANY_SOURCE,0,MCW,MPI_STATUS_IGNORE);
                        MPI_Recv(&tmp6.suit,1,MPI_INT,MPI_ANY_SOURCE,1,MCW,MPI_STATUS_IGNORE);
                        cardDisp(tmp6);
                        table.push_back(tmp6);
                    }
                    //all conditions for whether the card is special or not (i.e. 2 or 10)
                    //condition if card is 10
                    if(table.back().value == 15){
                        table.erase(table.begin(),table.end());
                        cout << "******** Table has been cleared ********\n" << endl;
                        current.value = 0;
                        current.suit = 0;
                    }
                    //condition if card is 2
                    else if(inaRow(table)){
                        table.erase(table.begin(),table.end());
                        cout << "******** Table has been cleared ********\n" << endl;
                        current.value = 0;
                        current.suit = 0;
                    }
                    //any other card
                    else{
                        if(table.back().value == 14){
                            cout << curRank << ": can play again\n" << endl;
                        }
                        current = table.back();
                    }
                    //returns current
                    MPI_Send(&current.value, 1, MPI_INT, curRank, 12, MCW);
                    MPI_Send(&current.suit, 1, MPI_INT, curRank, 13, MCW);
                }
                //sending cards to other processors
                MPI_Iprobe(MPI_ANY_SOURCE,6,MCW,&flag3,MPI_STATUS_IGNORE);
                if(flag3){
                    int curHandSize;
                    int curRank;
                    //receives how many cards the processor already has because to receive cards the hand must be < 5 and rank
                    MPI_Recv(&curHandSize,1,MPI_INT,MPI_ANY_SOURCE,6,MCW,MPI_STATUS_IGNORE);
                    MPI_Recv(&curRank,1,MPI_INT,MPI_ANY_SOURCE,7,MCW,MPI_STATUS_IGNORE);
                    if (curHandSize > 0){
                        int deckSize = deck.size();
                        //finds how many cards can be dealt or if the rest of the deck is dealt instead
                        int sendAmt = std::min((5-curHandSize), deckSize);
                        MPI_Send(&sendAmt,1,MPI_INT,curRank,9,MCW);
                        for (int i = 0; i < sendAmt; i++){
                            struct card tmp7 = deck.front();
                            //sends all of the cards
                            MPI_Send(&tmp7.value,1,MPI_INT,curRank,7,MCW);
                            MPI_Send(&tmp7.suit,1,MPI_INT,curRank,8,MCW);
                            deck.erase(deck.begin());
                        }
                    }
                }
            }
            // 0 can't play
            playAgain = 0;
        }
        //rest of the processors wait to play when it is their turn
        else{
            //only wait if it isn't still their turn i.e. card 2
            if(playAgain == 0){
                MPI_Recv(&yourTurn,1,MPI_INT,MPI_ANY_SOURCE,2,MCW,MPI_STATUS_IGNORE);
                MPI_Recv(&current.value,1,MPI_INT,MPI_ANY_SOURCE,10,MCW,MPI_STATUS_IGNORE);
                MPI_Recv(&current.suit,1,MPI_INT,MPI_ANY_SOURCE,11,MCW,MPI_STATUS_IGNORE);
            }
            //checks to see if won
            if(hand.size() == 0 && up.size() == 0 && down.size() == 0){
                yourTurn = -1;
            }
            //resets play again
            playAgain = 0;
        }
        //if it is the processors turn
        if (yourTurn == 1) {
            vector<int> playMe;
            int curFrom;
            int downplay;
            //checks to see where the cards will be played from hand, up or down table
            if (hand.size() == 0 && up.size() == 0) {
                if(down.size() == 1){
                    downplay = 0;
                }
                else{
                    downplay = rand()%(down.size()-1);
                }
                int canplay = findLowestCardBool(down[downplay],current);
                if (canplay == 1){
                    playMe.push_back(downplay);
                }
                else if (canplay == -1){
                    playMe.push_back(-1);
                }
                curFrom = 0;
            }
            else if (up.size() != 0 && hand.size() == 0) {
                playMe = findLowestCard(up, current);
                curFrom = 1;
            }
            else{
                playMe = findLowestCard(hand, current);
                curFrom = 2;
            }
            //cant play
            if (playMe.size() == 1 && playMe[0] == -1) {
                cantPlay = rank;
                //anyone but 0 can't play
                if (cantPlay != 0) {
                    //lets processor 0 know that it can't play
                    MPI_Send(&cantPlay, 1, MPI_INT, 0, 3, MCW);
                    int tSize;
                    //receives the amount of cards the processor will receive
                    MPI_Recv(&tSize, 1, MPI_INT, 0, 4, MCW, MPI_STATUS_IGNORE);
                    for (int i = 0; i < tSize; i++) {
                        struct card tmp4;
                        //places table in hand
                        MPI_Recv(&tmp4.value, 1, MPI_INT, 0, 0, MCW, MPI_STATUS_IGNORE);
                        MPI_Recv(&tmp4.suit, 1, MPI_INT, 0, 1, MCW, MPI_STATUS_IGNORE);
                        hand.push_back(tmp4);
                    }
                    //places down into hand if not played
                    sortHand(hand);
                    current.value = 0;
                    current.suit = 0;
                    MPI_Send(&yourTurn, 1, MPI_INT, (rank + 1) % size, 2, MCW);
                    MPI_Send(&current.value, 1, MPI_INT, (rank + 1) % size, 10, MCW);
                    MPI_Send(&current.suit, 1, MPI_INT, (rank + 1) % size, 11, MCW);
                    //if down can't play, placed in hand
                    if (curFrom == 0){
                        hand.push_back(down[downplay]);
                        down.erase(down.begin()+downplay);
                    }
                }
                //0 can't play
                else if(cantPlay == 0){
                    //places the table in the hand
                    while(table.size() > 0){
                        hand.push_back(table[0]);
                        table.erase(table.begin());
                        current.value = 0;
                        current.suit = 0;
                    }
                    cantPlay = -1;
                }
                //if down can't play, placed in hand
                if(curFrom == 0){
                    hand.push_back(down[downplay]);
                    down.erase(down.begin()+downplay);
                }
            }
            //can play
            else{
                vector<int> playMetmp;
                struct card tmpcurrent = current;
                //if 0 can play
                if (!rank) {
                    //plays only one card of 2 or 10
                    if((curFrom == 0 && (down[playMe[0]].value >= 14)) || (curFrom == 1 && (up[playMe[0]].value >= 14)) || (curFrom == 2 && (hand[playMe[0]].value >= 14))){
                        playMetmp.push_back(playMe[0]);
                    }
                    else{
                        playMetmp = playMe;
                    }
                    playMe = playMetmp;
                    //plays all the cards locally
                    for (int i = 0; i < playMe.size(); i++) {
                        if (curFrom == 0) {
                            tmpcurrent = down[playMe[0]];
                            table.push_back(down[playMe[0]]);
                            down.erase(down.begin() + playMe[0]);
                        }
                        else if (curFrom == 1) {
                            tmpcurrent = up[playMe[0]];
                            table.push_back(up[playMe[0]]);
                            up.erase(up.begin() + playMe[0]);
                        }
                        else if (curFrom == 2) {
                            tmpcurrent = hand[playMe[0]];
                            table.push_back(hand[playMe[0]]);
                            hand.erase(hand.begin() + playMe[0]);
                        }
                        cout << rank << ": Placed Card on Table:" << endl;
                        cardDisp(tmpcurrent);
                        if(tmpcurrent.value == 15){
                            table.erase(table.begin(),table.end());
                            cout << "********Table has been cleared********" << endl;
                            current.value = 0;
                            current.suit = 0;
                        }
                        else if(inaRow(table)){
                            table.erase(table.begin(),table.end());
                            cout << "********Table has been cleared********" << endl;
                            current.value = 0;
                            current.suit = 0;
                        }
                        else if(tmpcurrent.value == 14){
                            playAgain = 1;
                            current.value = 0;
                            current.suit = 0;
                            cout << rank << ": can play again\n" << endl;
                        }
                        else{
                            current = tmpcurrent;
                        }
                    }
                    while (hand.size() < 5 && deck.size() > 0) {
                        hand.push_back(deck.front());
                        deck.erase(deck.begin());
                    }
                }
                else {
                    //playing cards on table
                    //MPI tag 5

                    //plays only 1 card of 2 or 10
                    if((curFrom == 0 && (down[playMe[0]].value >= 14)) || (curFrom == 1 && (up[playMe[0]].value >= 14)) || (curFrom == 2 && (hand[playMe[0]].value >= 14))){
                        playMetmp.push_back(playMe[0]);
                    }
                    else{
                        playMetmp = playMe;
                    }
                    playMe = playMetmp;
                    //finds where the cards will be played from
                    int playMeSize = playMe.size();
                    MPI_Send(&playMeSize, 1, MPI_INT, 0, 5, MCW);
                    MPI_Send(&rank,1,MPI_INT,0,7,MCW);
                    for (int i = 0; i < playMeSize; i++) {
                        //played from table down
                        if (curFrom == 0) {
                            tmpcurrent = down[playMe[0]];
                            MPI_Send(&down[playMe[0]].value, 1, MPI_INT, 0, 0, MCW);
                            MPI_Send(&down[playMe[0]].suit, 1, MPI_INT, 0, 1, MCW);

                            down.erase(down.begin() + playMe[0]);
                            if(hand.size() == 0 && up.size() > 0){
                                curFrom = 1;
                            }
                            else if(hand.size() == 0 && up.size() == 0){
                                curFrom = 0;
                            }
                            else if(down.size() == 0){
                                curFrom = -1;
                            }
                        }
                        //played from table up
                        else if (curFrom == 1) {
                            tmpcurrent = up[playMe[0]];
                            MPI_Send(&up[playMe[0]].value, 1, MPI_INT, 0, 0, MCW);
                            MPI_Send(&up[playMe[0]].suit, 1, MPI_INT, 0, 1, MCW);
                            up.erase(up.begin() + playMe[0]);
                            //updates what hand should be played from
                            if(hand.size() == 0 && up.size() > 0){
                                curFrom = 1;
                            }
                            else if(hand.size() == 0 && up.size() == 0){
                                curFrom = 0;
                            }
                        }
                        else if (curFrom == 2) {
                            tmpcurrent = hand[playMe[0]];
                            MPI_Send(&hand[playMe[0]].value, 1, MPI_INT, 0, 0, MCW);
                            MPI_Send(&hand[playMe[0]].suit, 1, MPI_INT, 0, 1, MCW);

                            hand.erase(hand.begin() + playMe[0]);
                            //updates what hand should be played from
                            if(hand.size() == 0 && up.size() > 0){
                                curFrom = 1;
                            }
                            else if(hand.size() == 0 && up.size() == 0){
                                curFrom = 0;
                            }
                        }

                    }
                    //receives current from 0
                    MPI_Recv(&current.value,1,MPI_INT,MPI_ANY_SOURCE,12,MCW,MPI_STATUS_IGNORE);
                    MPI_Recv(&current.suit,1,MPI_INT,MPI_ANY_SOURCE,13,MCW,MPI_STATUS_IGNORE);
                    if(current.value == 14){
                        playAgain = 1;
                        current.value = 0;
                        current.suit = 0;
                    }

                    //receiving drawn cards from 0
                    if(curFrom == 2 && hand.size() < 5){
                        int tmpSize = hand.size();
                        int cardsNeeded;
                        //gets cards from 0 from the deck
                        MPI_Send(&tmpSize,1,MPI_INT, 0,6,MCW);
                        MPI_Send(&rank, 1, MPI_INT, 0, 7, MCW);
                        MPI_Recv(&cardsNeeded,1,MPI_INT,0,9,MCW,MPI_STATUS_IGNORE);
                        for(int i = 0; i < cardsNeeded; i++){
                            struct card tmp7;
                            MPI_Recv(&tmp7.value,1,MPI_INT,0,7,MCW,MPI_STATUS_IGNORE);
                            MPI_Recv(&tmp7.suit,1,MPI_INT,0,8,MCW,MPI_STATUS_IGNORE);
                            hand.push_back(tmp7);
                        }
                    }

                }
                //says game is finished
                if(down.size() == 0 && hand.size() == 0 && up.size() == 0){
                    cout << "*************** " << rank << " is not an idiot ***************" << endl;
                    yourTurn = -1;
                    MPI_Send(&yourTurn, 1, MPI_INT, (rank + 1) % size, 2, MCW);
                    MPI_Send(&current.value, 1, MPI_INT, (rank + 1) % size, 10, MCW);
                    MPI_Send(&current.suit, 1, MPI_INT, (rank + 1) % size, 11, MCW);
                    idiot = true;
                }
                //if played 2, then processor gets to play again
                else if(playAgain){
                    yourTurn = 1;
                }
                //next processors turn
                else{
                    MPI_Send(&yourTurn, 1, MPI_INT, (rank + 1) % size, 2, MCW);
                    MPI_Send(&current.value, 1, MPI_INT, (rank + 1) % size, 10, MCW);
                    MPI_Send(&current.suit, 1, MPI_INT, (rank + 1) % size, 11, MCW);
                    yourTurn = 0;
                }

            }
        }
        //someone has already won
        else if(yourTurn == -1){
            MPI_Send(&yourTurn, 1, MPI_INT, (rank + 1) % size, 2, MCW);
            MPI_Send(&current.value, 1, MPI_INT, (rank + 1) % size, 10, MCW);
            MPI_Send(&current.suit, 1, MPI_INT, (rank + 1) % size, 11, MCW);
            idiot = true;
        }
    }
    //so all processors catch up
    sleep(1);
    //poison pill works
    cout << rank << ": has finished with hand: " << hand.size() << " up: " << up.size() << " down: : " << down.size() << endl;
    MPI_Finalize();
    return 0;
}
