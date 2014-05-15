#include <iostream>
#include <time.h>
using namespace std;

// precondition: the deck (val and suit arrays) have been initialized
// postcondition: the deck (val and suit arrays) are shuffled 
void shuffle(char suit[], int val[]);

// precondition: player and computer has enough money to play
// postcondition: amt is subtracted from the amount of the player (player) and the
//                computer (computer)
void ante (int &player, int &comp, int amt);  

// precondition: a player has been dealt a hand and the deck has been shuffled
// postcondition: the player is prompted to exchange 0-5 of his/her cards
//                the player's hand (hand_val and hand_suit) are updated 
//                and next_card is changed to the index of the next card in 
//		  the deck
void exchange(int val[], char suit[], int hand_val[], char hand_suit[], int &next_card);

// precondition: the computer has been dealt a hand and the deck has been shuffled
// postcondition: this function is a stub that does not do anything; currently, the computer
// 			never exchanges any cards 
void exchange_computer(){;}

// precondition:  the deck has been initializes
// postcondition: 5 cards are dealt to the player and the computer
//                the index of the next_card in the deck is updated 
void deal(int deck_val[], char deck_suit[], int pval[], char psuit[], int cval[], char csuit[], int &next_card);

// precondition: the deck or hand have been initialized
// postcondition: the first 'num' cards are output 
void output (int val[], char suit[], int num);

// precondition: money has been give to the player and computer
// postcondition: the amount of money is displayed
void output_money(int p, int c) {
  cout << "Player has: $" << p << endl;
  cout << "Computer has: $" << c << endl;
}

// postcondition: displays a welcome message
void welcome() {
    cout << "----------------------------------------\n";
    cout << "Welcome to the CSC-210 Poker Table!\n";
    cout << "----------------------------------------\n";
  }

/*************************************************
* The functions below are used to determine the
* poker hand
*************************************************/

// precondition: the hand is ready to be evaluated
// postcondition: outputs the type of hand (e.g., TWO PAIRS) and
// 		  returns the score, with better hands having higher scores
int calc_score (int val[], char suit[]);

// precondition: an array with at least 'size' elements has been initialized
// postcondition: returns the index of the first or last positive value of array x
int firstpos (int x[], int size);
int lasttpos (int x[], int size);

// precondition: an array with at least 'num' elements has been initialized
// postcondition: returns the max_count of the first 'num' elements of the array 'x' and
//			sets 'w' equal to the value of the largest element; if multiple max_countima
//			exist, then 'w' is set equal to the largest value (2-A have values 2-14) 
int max_count (int x[], int num, int &w);

// precondition: a hand is ready to be evaluated
// postcondition: returns true if flush (if all characters in x are H,D,C, or S; or false otherwise 
bool is_flush(char x[], int size);

// returns the number of elements in 'x' that are equal to 'val' 
// precondition: a hand is ready to be evaluated
// postcondition: returns the number of elements in 'x' that are equal to 'val'
int num_vals(int x[], int val, int size);

//precondition: cards are being shuffled, first and second card suits are known
//postcondition: suit of first and second card are swapped
void swap(char& suit1, char& suit2);

//precondition: cards are being shuffled, first and second card values are known
//postcondition: value of first and second card are swapped
void swap(int& val1, int& val2);

//precondition: player and computer scores have been calculated
//postcondition: outputs the winner of round and pot is added to winners score
void findWinner(int player_score, int computer_score, int& player_money, int& comp_money, int pot);

//precondition: player has 5 cards in their hand
//postcondition: returns the point value of the highest card
int highest_card(int handVal[], int size);

//precondition: both players money values have been initialized, check if both players have >10$ for the ante
//postcondition: returns true (and then ends the game) if either player has <10$
bool isOver(int pMoney, int cMoney);

//precondition: user is asked how much to bet
//postcondition: a bet is placed if both players have sufficient funds
void placeBet(int& pMoney, int& cMoney, int& bet);

int main () {


	welcome();
  // declare variables
	char playAgain;
	int player_money = 1000, comp_money = 1000, pot = 0;

  output_money(player_money, comp_money);
  do{
	  if (isOver(player_money, comp_money)){
		  cout << "The game is over; either player or computer has insufficient funds for the ante.\n";
		  break;
	  }
  int deck_val[52], player_val[5], comp_val[5];
  char deck_suit[52], player_suit[5], comp_suit[5];   
  int next_card = 0; 
  int pscore, cscore;
  
  srand(time(NULL));  // for random number generation
 
  // initialize the deck
  for (int i = 0; i < 52; i++) {
	deck_val[i] = i%13 + 1;
        if (i < 13) deck_suit[i] = 'H';
        else if (i < 26) deck_suit[i] = 'S';
 	else if (i < 39) deck_suit[i] = 'C';
	else deck_suit[i] = 'D'; 	
  }


  // output the deck
  /*
  for (int i = 0; i < 52; i++) {
	cout << deck_val[i] << deck_suit[i] << ' ';
	if ( (i +1) % 13 == 0) cout << endl;
  }*/
  /***************************************************************
   Poker Algorithm: repeat while user wants to keep playing and 
	players have enough money to play
   	1. shuffle cards
   	2. players ante up (need to pay to play)
   	3. deal cards
   	4. exchange cards
   	5. evaluate hands and find winner, allocate winnings 
  ***************************************************************/

 
  shuffle(deck_suit, deck_val);

  //cout << "Player's ante up...\n\n";
  //ante(player_money, comp_money, 10);
  //output_money(player_money, comp_money);

  placeBet(player_money, comp_money, pot);

  deal(deck_val, deck_suit, player_val, player_suit, comp_val, comp_suit, next_card);  
  cout << "Player's hand: ";
  output(player_val, player_suit, 5);
  cout << endl;

  exchange(deck_val, deck_suit, player_val, player_suit, next_card);

  exchange_computer();
 
  cout << "Player's hand: "; 
  output(player_val, player_suit,5);
  
  cout << "Computer's hand: "; 
  output(comp_val, comp_suit,5);
  
  cout << "\nPlayer has: ";
  pscore = calc_score(player_val, player_suit);
  cout << "Computer has: ";
  cscore = calc_score(comp_val, comp_suit);

  cout << "Player's highest card value: " << highest_card(player_val, 5) << endl;
  cout << "Computer's highest card value: " << highest_card(comp_val, 5) << endl;

  findWinner(pscore, cscore, player_money, comp_money, pot); //finds winner and pays out

  output_money(player_money, comp_money);


  cout << "Play again? (Y/N): ";
  cin >> playAgain;
  if (toupper(playAgain) == 'Y')
	  cout << "\nNext round\n";
  }while(toupper(playAgain)=='Y');
}


/*************************
* user-defined functions
*************************/

bool isOver(int pMoney, int cMoney){
	if (pMoney < 10 || cMoney < 10)
		return true;
	return false;
}

// this function subtracts the amt from the player's and computer's money
void ante(int &player, int &comp, int amt) {
	player-= amt;
        comp-= amt;
}

// deals 5 cards from the deck to the player (pval, psuit) and the computer (cval, csuit)
void deal(int deck_val[], char deck_suit[], int pval[], char psuit[], int cval[], char csuit[], int &next_card) {
  for (int i = 0; i < 5; i++) {
	pval[i] = deck_val[next_card];
	psuit[i] = deck_suit[next_card];
	next_card++;
	cval[i] = deck_val[next_card];
	csuit[i] = deck_suit[next_card];
	next_card++;
  }
}

// outputs the the first 'num' cards in a hand
void output (int val[], char suit[], int num) {
	for (int i = 0; i < num; i++) {
		cout << val[i] << suit[i] << ' ';
	}	
	cout << endl;
}



// finds the largest value of the first 'num' elements of array 'x'
// and sets w equal to the value of the max_count index (J,Q,K,A = 11-14)
int max_count (int x[], int num, int &w) {
  int m = x[0];
  w = 14;
  for (int i = 1; i < num; i++) {
	if (x[i] >= m) {
		m = x[i];
		w = i+1; 
	}
  }
  return m;
}

// returns the index of the 1st positive element in x, or -1 if no elements are positive
int firstpos (int x[], int size) {
	for (int i = 0; i < size; i++) {
		if (x[i] > 0) return i;
	}
	return -1;
}	

// returns the index of the last positive element in x, or -1 if no elements are positive 
int lastpos (int x[], int size) {
	for (int i = size-1; i >= 0; i--) {
		if (x[i] > 0) return i;
	}
	return -1;
}

// returns the number of elements in 'x' that are equal to 'val' 
int num_vals(int x[], int val, int size) {
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (x[i] == val) count++;
	}
	return count;
}

// returns true if hand is a flush
bool is_flush(char x[], int size) {
	int numH = 0, numD = 0, numS = 0, numC = 0;
	for (int i = 0; i < size; i++) {
		if (x[i] == 'H') numH++;
		if (x[i] == 'D') numD++;
		if (x[i] == 'S') numS++;
		if (x[i] == 'C') numC++;
	}
		
	if (numH == size) return true;
	if (numD == size) return true;
	if (numS == size) return true;
	if (numC == size) return true;
	return false;
}
// calculuates score as follows:
// scores = base_score + appropriate high card
// base scores are 	royal flush	800
// 			straight flush	700
//			4 of a kind	600
//			full house	500
// 			flush		400
//			straight	300
//			3 of a kind	200
//			2 pair		100
//			one pair	20
//			high card
int calc_score (int val[], char suit[]) {
	int score = 0;
	int counts[13] = {0};
	// count the number of each type of card
    	for (int i = 0; i < 5; i++) {
			counts[val[i]-1]++;
		}
	int w = 0;
        int m = max_count(counts,13, w);// multiple value cards (2=pair,3=3,etc)
	int f = firstpos(counts, 13);   // value of lowest card
	int l = lastpos(counts,13);	// value of highest card

	bool flush = is_flush(suit, 5);

	if (flush) {
	  if (f == 0 && l == 12) {
		cout << "ROYAL FLUSH\n";
		score = 800;
		return score;	
	  } else if (l-f == 4) {
		cout << "STRAIGHT FLUSH\n";
		score = 700 + highest_card(val,5);
		return score;
	  }
	}

	if (m == 4) {			
		cout << "FOUR OF A KIND";
		score = 600 + w;
		return score;
	}

	if (m == 3 && num_vals(counts,2,13) ==1) {
		cout << "FULL HOUSE\n";
		score = 500 + w;  
		return score;
	}


	if (flush) {
		cout << "FLUSH\n";
		score = 400 + highest_card(val,5); 
		return score;
	}

	if (m == 1 && l-f == 4) {
		cout << "STRAIGHT\n";
		score = 300 + highest_card(val,5);
		return score; 
 	}
	
	if (m == 3) {
		cout << "THREE OF A KIND\n";	
		score = 200 + w;
		return score;
	}
		
	if (m == 2) {
		int npairs =  num_vals(counts, 2, 13);
		if (npairs > 1) {
		  cout << "TWO PAIRS\n";
		  score = 100 + w;
		  return score;
		} 
		cout << "ONE PAIR\n";
		score = 20 + w;
		return score;
	}

	score = highest_card(val,5);
	cout << "HIGH CARD\n"; 
	return score;
}
void swap(int& val1, int& val2){
	int temp = val1;
	val1=val2;
	val2=temp;
}
void swap(char& suit1, char& suit2){
	char temp = suit1;
	suit1 = suit2;
	suit2 = temp;
}
void shuffle(char arrSuit[], int arrVal[]){
	for(int i=0; i<1000; i++){
		int val1 = rand()%52;
		int val2 = rand()%52;
		swap(arrSuit[val1], arrSuit[val2]);
		swap(arrVal[val1], arrVal[val2]);
	}
}
void exchange(int val[], char suit[], int hand_val[], char hand_suit[], int &next_card){
	int userIn, card_num;
	do{
		cout << "Exchange 0-5 of your cards: ";
		cin >> userIn;
	}while(userIn>5||userIn<0);
	for (int i = 0; i<userIn; i++){
		do{
			cout << "Enter card number to exchange (1-5): ";
			cin >> card_num;
		} while (card_num>5 || card_num < 0);
		hand_val[card_num - 1] = val[next_card];
		hand_suit[card_num - 1] = suit[next_card];
		next_card++;
		cout << "New hand: ";
		output(hand_val, hand_suit, 5);
		cout << endl << endl;
	}
}
void findWinner(int player_score, int computer_score, int& player_money, int& comp_money, int pot){
	if(player_score > computer_score){
		cout << "Player wins.\n";
		player_money += pot;
	}else if(computer_score > player_score){
		cout << "Computer wins.\n";
		comp_money += pot;
	}else{
		cout << "It's a tie. Money refunded to both players.\n";
		player_money += pot / 2;
		comp_money += pot / 2;
	}
}
int highest_card(int handVal[], int size){
	int highest = handVal[0];
	for (int i = 1; i<size; i++){
		if (handVal[i] == 1){
			highest = 14;
			break;
		}else if (handVal[i]>highest){
				highest = handVal[i];
		}
	}
	return highest;
}
void placeBet(int& pMoney, int& cMoney, int& pot){
	int playerBet;
	bool tooHigh = false;
	do{
		cout << "Enter a bet: $";
		cin >> playerBet;
		if (playerBet > pMoney || playerBet > cMoney){
			tooHigh = true;
			cout << "Bet too high; place a lower bet.\n";
		}else if(pot>=0){
			tooHigh = false;
			pot = playerBet*2;
			pMoney -= playerBet;
			cMoney -= playerBet;
		}
	} while (playerBet < 0 || tooHigh);
	cout << "Player new money: $" << pMoney << endl;
	cout << "Computer new money: $" << cMoney << endl;
	cout << "Current pot: $" << pot << endl << endl;
}