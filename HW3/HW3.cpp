#include <iostream>
#include <vector>
#include <unordered_map> 
#include<algorithm>
using namespace std;

/********** Global Constant **********/
const int numOfASuit = 13;

/********** Global Functions **********/
// convert the suit and num of a card to int
int cardToInt(string str);
// read the num of a card
int score(int cardNum);
// the total num of remaining cards of the lose player
int scoreSum(int player);
// read the initial cards of both players from file
void start();
// store each status in a long long int
long long status(int player, int prevCard, int alpha, int beta);
// find each status through depth first search
// (from player[0]'s (Alice) perspective)
int dfs(int player, int prevCard, int alpha, int beta);

/********** Global Variables **********/
int n; // initial cards amount
vector<int> originalCard[2]; // cards of 2 players, convert from cardToInt
long long remainCard[2]; // remaining cards, 0: no, 1: yes
unordered_map<long long, int> statusMap; // key: currStatus, value: score

//========== Program Starts!!! ==========//
int main(int argc, const char * argv[]){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n;
    start();
    remainCard[0] = remainCard[1] = (1LL << n) - 1;
    int ans = dfs(0, -1, -scoreSum(0), scoreSum(1));
    cout << (ans > 0 ? "Alice\n":"Bob\n") << abs(ans) << '\n';
    
    return 0;
}

/********** Global Function Definitions **********/
int cardToInt(string str){
    int suit, num;

    if (str[0] == 'C') suit = 0; // club
    else if (str[0] == 'D') suit = 1; // diamond
    else if (str[0] == 'H') suit = 2; // heart
    else suit = 3; // spade, str[0] == 'S'

    if (str[1] == 'A') num = 1;
    else if (str[1] == 'T') num = 10;
    else if (str[1] == 'J') num = 11;
    else if (str[1] == 'Q') num = 12;
    else if (str[1] == 'K') num = 13;
    else num = str[1] - '0';
    
    return suit * numOfASuit + num - 1; // array starts at 0
}

int score(int cardNum){
    return cardNum % numOfASuit + 1;
}

int scoreSum(int player){
    int sum = 0;
    for (int i = 0; i < n; i++){
        if (remainCard[player] & (1LL << i))
            sum += score(originalCard[player][i]);
    }
    return sum;
}

void start(){
    string str;
    for (int i = 0; i < 2; i++){
        originalCard[i].resize(n);
        for (int j = 0; j < n; j++){
            cin >> str;
            originalCard[i][j] = cardToInt(str);
        }
    }     
}

long long status(int player, int prevCard, int alpha, int beta){
    // the max length of alpha and beta depend on n (n <= 17)
    // the max num of a card is 13, 
    // thus the score range is +- 17*13 = 221 = 2^8
    // 1 bit for the current player
    // 6 bits for the current card (52 different cards)
    // 9 bits for alpha, 9 bits for beta
    // 2n bits for remaining cards (n bit/player)
    return player + (prevCard << 1) + (alpha << 7) + (beta << 16)
           + (remainCard[0] << 25) + (remainCard[1] << (n + 25));
}

int dfs(int player, int prevCard, int alpha, int beta){
    long long currStatus = status(player, prevCard, alpha, beta);
    
    // if the status is the same as previous, return that score 
    // directly without calculating again
    if (statusMap.find(currStatus) != statusMap.end()){
        //cerr << "REPEAT! -> SKIP!" << '\n';
        return statusMap[currStatus];
    }

    bool pass = true;
    int nextMaxMin; // the max or min score from next card choice
    int ans;

    // reach the leaf node, the opponent wins
    if (!remainCard[!player])
        return   scoreSum(1)- scoreSum(0);

    // Depth Search First starts here!!!
    for (int i = 0; i < n; i++){
        if ((remainCard[player] & (1LL << i)) // the card still exists
            && ((prevCard == -1) // opponent pass
            ||  (prevCard / 13 == originalCard[player][i] / 13)
            ||  (prevCard % 13 == originalCard[player][i] % 13)))
        {
            //cerr << "Next: " << originalCard[player][i] << '\n';
            pass = false;
            remainCard[player] ^= (1LL << i);
            //cerr << player << " " << originalCard[player][i]; 
            //cerr << " " << alpha << " " << beta << '\n';
            //cerr << "STATUS: " << currStatus << '\n';
            nextMaxMin = dfs(!player, originalCard[player][i], alpha, beta);
            //cerr << "Score = " << nextMaxMin << '\n';;
            // after reaching the leaf, go back to another decision, 
            // thus the card exists again
            remainCard[player] ^= (1LL << i);
        
            // max layer (player == 0: Alice)
            if (!player){
                // cerr << "====================" << '\n';
                // cerr << "Last card: " << originalCard[player][i] << '\n';
                // cerr << "MAX Layer" << '\n'; 
                // ans (max) in this layer = beta min of previous layer
                alpha = ans = max(alpha, nextMaxMin);
                // cerr << "NEW alpha: " << ans << '\n';
                if (alpha >= beta)
                    break;
            }
            // min layer (player == 1: Bob)
            else{
                // cerr << "====================" << '\n';
                // cerr << "Last card: " << originalCard[player][i] << '\n';
                // cerr << "MIN Layer" << '\n';
                beta = ans = min(beta, nextMaxMin);
                // cerr << "NEW beta: " << ans << '\n';
                if (alpha >= beta)
                    break;
            }
        }
    }
    if (pass)
        ans = dfs(!player, -1, alpha, beta);    
    
    statusMap[currStatus] = ans;

    return ans;
}