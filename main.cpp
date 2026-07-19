#include<bits/stdc++.h>

// using std::string;
// string init = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0";

// class position {
//     string s;
// };

enum piece { p, P, n, N, b, B, r, R, q, Q, k, K, E };
enum cell {
    a8, b8, c8, d8, e8, f8, g8, h8, 
    a7, b7, c7, d7, e7, f7, g7, h7, 
    a6, b6, c6, d6, e6, f6, g6, h6,     
    a5, b5, c5, d5, e5, f5, g5, h5, 
    a4, b4, c4, d4, e4, f4, g4, h4, 
    a3, b3, c3, d3, e3, f3, g3, h3, 
    a2, b2, c2, d2, e2, f2, g2, h2, 
    a1, b1, c1, d1, e1, f1, g1, h1
};
const piece pos_classic[64] = {
    r, n, b, q, k, b, n, r,
    p, p, p, p, p, p, p, p,
    E, E, E, E, E, E, E, E,
    E, E, E, E, E, E, E, E,
    E, E, E, E, E, E, E, E,
    E, E, E, E, E, E, E, E,
    P, P, P, P, P, P, P, P,
    R, N, B, Q, K, B, N, R
};

struct board {
    std::set<int_fast64_t> hash_history;
    piece pos[64];
    int_fast32_t clock_halfmove = 0;
    // int_fast32_t clock_fullmove = 0;
    short enPass = -1;
    short castle = 15;
    board() {
        for (int i = 0; i < 64; ++i) {
            pos[i] = E;
        }
    }
    void init_classic() {
        std::copy(pos_classic, pos_classic + 64, pos);
    }
    // bool valid() {
    //     return true;
    // }
    // bool is_under_check() {
    //     return true;
    // }
    bool move(short c1, short c2) {
        if (!(c1 >= 1 && c1 <= 64) 
           &&(c2 >= 1 && c2 <= 65)) return false;
        if (pos[c1] == E) return false;
        short delta = c2 - c1;
        short h = delta % 8;
        short v = delta / 8;
        switch (pos[c1]) {
            case p:
            case P:
                if (v == 0) return false;
                if (clock_halfmove % 2 == 0 && v > 0) return false;
                if (clock_halfmove % 2 == 1 && v < 0) return false;
                if (abs(v) > 2) return false;
                if (h != 0) {
                    if (enPass == -1) return false;
                    if (h != 1) return false;
                    if (v != 1) return false;
                } else {
                    if (pos[c2] != E) return false;
                }     
                break;
            case n:
            case N:
                break;
            case b:
            case B:
                break;
            case q:
            case Q:
                break;
            case k:
            case K:
                break;
            default:
                return false;
        }
        pos[c2] = pos[c1];
        pos[c1] = E;
        clock_halfmove += 1;
        // clock_fullmove += 1;
        return true;

    }
    // short parse(cell c1) {
    //     short pieceAsInt = 

    // }
    // bool move(cell c1, cell c2) {
    //     return move(static_cast<short>(c1);)
    // }
    void print_piece(piece pc) {
        // A string containing the names matching your enum order.
        // Index 12 corresponds to 'E' (Empty), which we print as a dot '.'
        const std::string pieceNames = "pPnNbBrRqQkK.";
    
        std::cout << pieceNames[pc];
    }
    bool print() {
        for (int i = 0; i < 64; ++i) {
            print_piece(pos[i]);
            if (i % 8 == 7) std::cout << '\n';
        }
        return true;
    }
};
int main() {
    using std::cout;
    board game;
    game.init_classic();
    game.print();
    // cout << " FLAG 1\n";
    game.move(e2, e4);
    
    // cout << " FLAG 2\n";
    game.print();
    
}