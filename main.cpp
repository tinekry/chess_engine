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
int string_to_cell(const std::string& s) {
    if (s.length() < 2) return -1; 
    int file = s[0] - 'a';
    int rank_idx = 8 - (s[1] - '0');

    return (rank_idx * 8) + file;
}
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
void clear_screen() {
#ifdef _WIN32
    std::system("cls");   // Для Windows
#else
    std::system("clear"); // Для Linux / macOS
#endif
}
struct board {
    std::set<int_fast64_t> hash_history;
    mutable piece pos[64];
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
        bool color_of_moved_peice = (pos[c1] % 2) ^ 1;
        if (clock_halfmove % 2 == 0 && color_of_moved_peice == 1) return false;
        if (clock_halfmove % 2 == 1 && color_of_moved_peice == 0) return false;
        if (h == 0 && v == 0) return false;
        switch (pos[c1]) {
            case p:
            case P:
                if (v == 0) return false;
                if (abs(v) > 2) return false;
                if (h != 0) {
                    if (enPass == -1) return false;
                    if (h != 1) return false;
                    if (v != 1) return false;
                } else {
                    if (pos[c2] != E) return false;
                    if (abs(v) == 2 && pos[(c1 + c2) / 2] != E) {   
                        return false;
                    }
                }   
                 
                break;
            case r:
            case R:
                if (h != 0 && v != 0) return false;
                break;
            case n:
            case N:
                if (abs(h) == 1) { 
                    if (abs(v) != 2) return false;
                    break;
                } else if (abs(h) == 2) {
                    if (abs(h) != 2) return false;
                    break;
                }
                return false;
                break;
            case b:
            case B:
                if (abs(h) != abs(v)) return false;
                if (abs(h == 0)) return false;
                break;
            case q:
            case Q:
                if (!(abs(h) == abs(v) || h == 0 || v == 0)) {
                    return false;
                }
                break;
            case k:
            case K:
                if (abs(h) > 1 || abs(v) > 1) return false;
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
        using std::cout;
        cout << "   a b c d e f g h\n\n";
        for (int i = 0; i < 64; ++i) {
            if (i % 8 == 0) cout << 8 - i/8 << "  ";
            print_piece(pos[i]);
            cout << " ";
            if (i % 8 == 7) cout << '\n';
        }
        cout << "\n   a b c d e f g h\n";
        return true;
    }
};
void wrong() {
    std::cout << " You're an idiot, try again\n";
}
int main() {
    using std::cin, std::cout, std::string;
    board game;
    game.init_classic();
    cout << " Game started\n";
    cout << "move cell_1 cell_2\n";
    cout << "Ex. move e2 e4\n";
    cout << "To stop type 'EXIT' as first parametr\n";
    game.print();
    while (true)
    {
        string s, c1, c2;
        cin >> s >> c1 >> c2;
        if (s == "EXIT") break;
        if (s != "move" && s != "m") {
            wrong();
            continue;
        }
        if (game.move(string_to_cell(c1), string_to_cell(c2))) {
            clear_screen();
            game.print();
        } else {
            wrong();
            continue;
        }
    }
}