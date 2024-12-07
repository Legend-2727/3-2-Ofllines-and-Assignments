#include <bits/stdc++.h>
// #include "../../dbg.h"
using namespace std;
bool doPrint = 0;
const int INF = 2e8;
const int MAX_DEPTH = 8```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

const int INF = 2e8;
const int MAX_DEPTH = 8;
const int W1 = 10, W2 = 4, W3 = 7, W4 = 6;

enum GameResult {
    PLAYER_1_WIN,
    PLAYER_2_WIN,
    TIE
};

class Mancala {
public:
    vector<int> board;
    bool is_game_over;
    int additional_moves_earned;
    int captured_stones;

    Mancala(vector<int>& b) {
        board = b;
        is_game_over = isGameOver();
        additional_moves_earned = 0;
        captured_stones = 0;
    }

    bool isGameOver() {
        bool first_half = true;
        bool second_half = true;
        for (int i = 0; i < 6; i++) {
            if (board[i]) {
                first_half = false;
                break;
            }
        }
        for (int i = 7; i < 13; i++) {
            if (board[i]) {
                second_half = false;
                break;
            }
        }
        if (first_half || second_half) {
            finishTheGame();
            return true;
        }
        return false;
    }

    void finishTheGame() {
        for (int i = 0; i < 6; i++) {
            board[6] += board[i];
            board[i] = 0;
        }
        for (int i = 7; i < 13; i++) {
            board[13] += board[i];
            board[i] = 0;
        }
    }

    vector<int> getMoves(bool p1) {
        vector<int> moves;
        int start = p1 ? 0 : 7;
        for (int i = start; i < start + 6; i++) {
            if (board[i]) {
                moves.push_back(i);
            }
        }
        random_device rd;
        mt19937 g(rd());
        shuffle(moves.begin(), moves.end(), g);
        return moves;
    }

    void printBoard() {
        cout << "   Player 2  \n ";
        for (int i = 6; i > 0; i--) {
            cout << " " << i;
        }
        cout << "\n ";
        for (int i = 1; i < 7; i++) {
            cout << " " << "-";
        }
        cout << "\n ";
        for (int i = 12; i > 6; i--) {
            cout << " " << board[i];
        }
        cout << "\n" << board[13] << "             " << board[6] << "\n ";
        for (int i = 0; i < 6; i++) {
            cout << " " << board[i];
        }
        cout << "\n ";
        for (int i = 1; i < 7; i++) {
            cout << " -";
        }
        cout << "\n ";
        for (int i = 1; i < 7; i++) {
            cout << " " << i;
        }
        cout << "\n   Player 1 \n";
        cout << "------------------------\n\n";
    }

    bool isValidMove(int i, bool p1) {
        int start = p1 ? 0 : 7;
        if (i >= 6 || i < 0) return false;
        if (board[i + start]) return true;
        return false;
    }

    bool makeMove(int i, bool p1) {
        int stones = board[i];
        board[i] = 0;
        int index = i;
        while (stones) {
            index++;
            if ((index == 6 && !p1) || (p1 && index == 13)) index++;
            if (index > 13) index = 0;
            board[index]++;
            stones--;
        }
        if (p1 && index < 6 && board[index] == 1 && board[12 - index]) {
            captured_stones += (board[12 - index] + 1);
            board[6] += (board[12 - index] + 1);
            board[index] = 0;
            board[12 - index] = 0;
        }
        else if (!p1
;
int W1 = 10, W2 = 4, W3 = 7, W4 = 6;
enum GameResult {
    PLAYER_1_WIN,
    PLAYER_2_WIN,
    TIE
    
};
class Mancala {
public:
    vector<int> board;
    bool is_game_over;
    int additional_moves_earned;
    int captured_stones;
    Mancala(vector<int>& b) {
        board = b;
        is_game_over = isGameOver();
        additional_moves_earned = 0;
        captured_stones = 0;
    }
    bool isGameOver() {
        bool first_half = true;
        bool second_half = true;
        for (int i = 0;i < 6;i++) {
            if (board[i]) {
                first_half = false;
                break;
            }
        }
        for (int i = 7;i < 13;i++) {
            if (board[i]) {
                second_half = false;
                break;
            }
        }
        if (first_half || second_half) {
            finishTheGame();
            return true;
        }
        return false;
    }
    void finishTheGame() {
        for (int i = 0;i < 6;i++) {
            board[6] += board[i];
            board[i] = 0;
        }
        for (int i = 7;i < 13;i++) {
            board[13] += board[i];
            board[i] = 0;
        }
    }
    vector<int> getMoves(bool p1) {
        vector<int> moves;
        int start = p1 ? 0 : 7;
        for (int i = start;i < start + 6;i++) {
            if (board[i]) {
                moves.push_back(i);
            }
        }
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle(moves.begin(), moves.end(), std::default_random_engine(seed));
        return moves;
    }
    void printBoard() {
        cout << "   Player 2  \n ";
        for (int i = 6;i > 0;i--) {
            cout << " " << i;
        }
        cout << "\n ";
        for (int i = 1;i < 7;i++) {
            cout << " " << "-";
        }
        cout << "\n ";
        for (int i = 12; i > 6; i--) {
            cout << " " << board[i];
        }
        cout << "\n" << board[13] << "             " << board[6] << "\n ";
        for (int i = 0; i < 6; i++) {
            cout << " " << board[i];
        }
        cout << "\n ";
        for (int i = 1;i < 7;i++) {
            cout << " -";
        }
        cout << "\n ";
        for (int i = 1;i < 7;i++) {
            cout << " " << i;
        }
        cout << "\n   Player 1 \n";
        cout << "------------------------\n\n";
    }
    bool isValidMove(int i, bool p1) {
        int start = p1 ? 0 : 7;
        if (i >= 6 || i < 0) return false;
        if (board[i + start]) return true;
        return false;
    }
    bool makeMove(int i, bool p1) {
        // int start=p1? 0:7;
        int stones = board[i];
        board[i] = 0;
        int index = i;
        while (stones) {
            index++;
            // if (doPrint) dbg(board[index], index);
            if ((index == 6 && !p1) || (p1 && index == 13)) index++;
            if (index > 13) index = 0;
            board[index]++;
            stones--;
            // if (doPrint) dbg(board[index], stones);
        }
        if (p1 && index < 6 && board[index] == 1 && board[12 - index]) {
            captured_stones += (board[12 - index] + 1);
            board[6] += (board[12 - index] + 1);
            board[index] = 0;
            board[12 - index] = 0;
        }
        else if (!p1 && index > 6 && board[index] == 1 && index < 13 && board[12 - index]) {
            captured_stones -= (board[12 - index] + 1);
            board[13] += (board[12 - index] + 1);
            board[index] = 0;
            board[12 - index] = 0;
        }
        is_game_over = isGameOver();
        if (((index == 6 && p1) || (!p1 && index == 13)) && !is_game_over) {
            additional_moves_earned += (p1 ? 1 : -1);
            return true;
        }
        return false;
    }
    int evaluate(bool p1, int heuristic_index) {
        if (is_game_over || isTheoriticallyOver()) {
            // dbg(1e6 * (board[6] - board[13]),p1);
            return 1e6 * (board[6] - board[13]);
        }
        int p1_stones = 0, p2_stones = 0, p1_storage = 0, p2_storage = 0;
        for (int i = 0;i < 6;i++) {
            p1_stones += board[i];
            p2_stones += board[12 - i];
        }
        p1_storage = board[6];
        p2_storage = board[13];
        int score = 0;
        if (heuristic_index == 1) {
            score = p1_storage - p2_storage;
        }
        else if (heuristic_index == 2) {
            score = W1 * (p1_storage - p2_storage) + W2 * (p1_stones - p2_stones);
        }
        else if (heuristic_index == 3) {
            score = W1 * (p1_storage - p2_storage) + W2 * (p1_stones - p2_stones) + W3 * (additional_moves_earned);
        }
        else {
            score = W1 * (p1_storage - p2_storage) + W2 * (p1_stones - p2_stones)
                + W3 * (additional_moves_earned)+ W4 * (captured_stones);
        }
        // dbg(score);
        // dbg(captured_stones,additional_moves_earned);
        return score;
    }
    bool isTheoriticallyOver() {
        return board[6] > 24 || board[13] > 24;
    }
    GameResult showResult() {
        if (board[6] > board[13]) {
            return PLAYER_1_WIN;
        }
        else if (board[6] < board[13]) {
            return PLAYER_2_WIN;
        }
        else {
            return TIE;
        }
    }
};

int minimax(Mancala node, int alpha, int beta, int depth, bool p1, int heuristic_index) {
    if (node.is_game_over || depth >= MAX_DEPTH || node.isTheoriticallyOver()){
        
        return node.evaluate(p1, heuristic_index);
    }
    vector<int> moves = node.getMoves(p1);
    if (p1) {
        int best_score = -INF;
        for (int i = 0;i < moves.size();i++) {
            Mancala temp = node;
            // bool turn = p1;
            bool anotherMove = temp.makeMove(moves[i], p1);
            // if (!anotherMove) turn = !turn;
            int score = minimax(temp, alpha, beta, depth + 1, anotherMove? p1 : !p1, heuristic_index);
            best_score = max(best_score, score);
            alpha = max(alpha, best_score);
            if (beta <= alpha) break;
        }
        return best_score;
    }
    else {
        int best_score = INF;
        for (int i = 0;i < moves.size();i++) {
            Mancala temp = node;
            // bool turn = p1;
            bool anotherMove = temp.makeMove(moves[i], p1);
            // if (!anotherMove) turn = !turn;
            int score = minimax(temp, alpha, beta, depth + 1,anotherMove? p1 : !p1, heuristic_index);
            best_score = min(best_score, score);
            
            beta = min(beta, best_score);
            if (beta <= alpha) break;
        }
        return best_score;
    }
}
bool makeComputerMove(Mancala &mancala,bool p1, int heuristic_index, bool print_move) {

    int best_score = p1 ? -INF : INF;
    int alpha = -INF;
    int beta = INF;
    
    vector<int> moves = mancala.getMoves(p1);
    // if(!p1){
    //     dbg(moves);
    //     exit(1);
    // }
    // dbg(moves);
    // dbg("here");
    int best_move = moves[0];
    for (int i = 0;i < moves.size();i++) {
        // dbg(alpha,beta);
        Mancala temp = mancala;
        // bool another_move=temp.makeMove(moves[i],p1);
        // temp.additional_moves_earned = 0;
        // temp.captured_stones = 0;
        bool anotherMove = temp.makeMove(moves[i], p1);
        // dbg(temp.board,mancala.board);
        // exit(1);
        int score = minimax(temp, alpha, beta, 0, anotherMove ? p1 : !p1, heuristic_index);
        if (p1) {
            if (score > best_score) {
                best_score = score;
                best_move = moves[i];
            }
            alpha=max(best_score,alpha);
        }
        else {
            if (score < best_score) {
                best_score = score;
                best_move = moves[i];
            }
            beta=min(best_score,beta);
        }

        // dbg(score,best_score);
    }
    // dbg(best_move);
    if (print_move) cout << "Computer's move : " << best_move + 1 << endl;
    return mancala.makeMove(best_move, p1);
}
void startGame_humanVsAi() {
    vector<int> initial_board(14, 4);
    initial_board[13] = 0;
    initial_board[6] = 0;
    // printBoard(initial_board);
    Mancala mancala(initial_board);
    // mancala.printBoard();
    cout << "Which side you want to play :\n";
    cout << "1 for player 1\n";
    cout << "2 for player 2\n";
    bool humanPlay = false;
    bool player1_human = false;
    int start;
    while (true) {
        int choice;
        cin >> choice;
        if (choice == 1 || choice == 2) {
            player1_human = humanPlay = choice == 1;
            // cout<<humanPlay;
            break;
        }
        cout << "wrong choice please choose again\n";
    }
    mancala.printBoard();
    while (true) {
        if (humanPlay) {
            // mancala.printBoard();
            cout << "Your turn :" << " Player ";
            if (player1_human) {
                cout << "1\n";
                start = 0;
            }
            else {
                cout << "2\n";
                start = 7;
            }
            int move;
            cin >> move;
            move--;
            // dbg(move, start);
            if (!mancala.isValidMove(move, player1_human)) {
                cout << "Invalid move please choose again\n";
                continue;
            }
            else {
                doPrint = 1;
                bool another_trun = mancala.makeMove(move + start, player1_human);
                doPrint = 0;
                if (another_trun) cout << "Again your turn\n";
                else {
                    humanPlay = !humanPlay;
                }
                mancala.printBoard();
            }
        }
        else {
            cout << "Computer's turn\n";
            bool another_turn = makeComputerMove(mancala,!player1_human, 1, true);
            if (!another_turn) humanPlay = !humanPlay;
            mancala.printBoard();
        }
        if (mancala.is_game_over) {
            mancala.printBoard();
            cout << "Game Over\n";
            GameResult temp = mancala.showResult();
            if ((temp == PLAYER_1_WIN && player1_human) || (temp == PLAYER_2_WIN && !player1_human)) {
                cout << "You Won\n";
            }
            else {
                cout << "Computer Won\n";
            }
            break;
        }
    }
}
void startGame_aiVsAi(int h1,int h2) {
    int ai_1_win = 0;
    int ai_2_win = 0;
    int draw = 0;
    // srand(time(0));
    // bool player1 = rand() % 2;
    //if 1 ai 1 plays first else ai 2;
    int totalMatches = 20;
    int tm = totalMatches;
    while (totalMatches--) {
        vector<int> initial_board(14, 4);
        initial_board[13] = 0;
        initial_board[6] = 0;
        // printBoard(initial_board);
        Mancala mancala(initial_board);
        bool turn = true;
        // if(!player1) turn = false;
        while (true) {
            if (turn) {
                // cout<<"Player 1\n";
                bool another_turn = makeComputerMove(mancala,true, h1, false);
                if (!another_turn) turn = !turn;
                // dbg(another_turn,turn);
            }
            else {
                // cout << "Player 2\n";
                bool another_turn = makeComputerMove(mancala,false, h2, false);
                if (!another_turn) turn = !turn;
            }
            // mancala.printBoard();
            if (mancala.is_game_over) {
                GameResult temp = mancala.showResult();
                if (temp == PLAYER_1_WIN) {
                    ai_1_win++;
                    cout << "AI 1 won\n";
                }
                else if (temp == TIE) {
                    draw++;
                    cout << "Draw\n";
                }
                else {
                    ai_2_win++;
                    cout << "AI 2 won\n";
                }
                break;
            }
        }
    }
    // dbg(ai_1_win, ai_2_win, draw);
    cout << "AI 1 won " << ai_1_win << " times\n";
    cout << "AI 2 won " << ai_2_win << " times\n";
    cout << "Draw " << draw << " times\n";
    cout <<"For depth :"<<MAX_DEPTH<<'\n';
    cout << "Using heuristic funtion: "<<h1<<" AI1 won :"<<(100.0*ai_1_win)/tm<<"% \n";
    cout << "Using heuristic funtion: "<<h2<<" AI2 won :"<<(100.0*ai_2_win)/tm<<"% \n";
}

int main() {
    cout << "Choose the game mode :" << endl;
    cout << "1. Human vs Computer" << endl;
    cout << "2. Computer vs Computer" << endl;
    int mode;
    cin >> mode;
    if (mode == 1) {
        startGame_humanVsAi();
    }
    else {
        cout<<"Enter heuristic for Ai 1 :";
        int h1,h2;
        cin>>h1;
        cout<<"\nEnter heuristic for Ai 2 :";
        cin>>h2;
        cout<<"\n";
        startGame_aiVsAi(h1,h2);
    }
}