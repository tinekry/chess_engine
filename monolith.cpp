#include<bits/stdc++.h>
struct vct {
    int x, y;
    vct(int x, int y) : x(x), y(y) {} 
};
struct transform {
    vct dis;
    int dir;
    bool coninous;
    transform (vct dis, int dir, bool coninous) : dis(dis), dir(dir), coninous(coninous) {}
};

struct piece {
    std::vector<transform> jump;
    char leter = '.';
    int colour;
    int down = 'a' - 'A';
    bool leap; 
};

struct rook : public piece {
    rook (int c) {
        colour = c; 
        jump = {
            transform(vct(0, 1), 15, 1),
            transform(vct(1, 0), 15, 1)
        };
        leter = 'R';
        leap = false;
    }
}; 

template <typename... Bases>
struct board : public piece, public Bases... {
    std::vector<std::unique_ptr<piece>> adj;
    std::vector<std::vector<int>> pos;
    std::map<char, int> sbl_to_ptr;
    int_fast32_t clock_halfmove = 0;
    int  h, v, enPass, castle, num_of_colours;

    bool board(int num_of_colours = 2; int h = 8; int v = 8, int enPass = -1, int castle = 15) 
: num_of_colours(num_of_colours), h(h), v(v), enPass(enPass), castle(castle) {
        if (num_of_colours != 2) {
            std::cerr << "we cannot handle the num_of_colours != 2 yet\n";
            return false;
        }
        adj.reserve(sizeof...(Bases) * num_of_colours);
        for (int i = 0; i < num_of_colours; ++i) {
            (..., adj.push_back(std::make_unique<Bases(i)>()));
        }
        for (size_t i = 0; i < adj.size(); ++i) {
            sbl_to_ptr[*adj[i].leter] = i;
        }
        pos.assign(h,std::vector<int> (v, sbl_to_ptr['.']));
    }
    bool init_classic(std::string init = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0";) {
        if (n != 8 || m != 8) {
            std::cerr << "it's not classic\n";
            return false;
        }
        if (!sbl_to_ptr.contains('R')) return false;
        if (!sbl_to_ptr.contains('r')) return false;

        if (!sbl_to_ptr.contains('N')) return false;
        if (!sbl_to_ptr.contains('n')) return false;
        if (!sbl_to_ptr.contains('B')) return false;
        if (!sbl_to_ptr.contains('b')) return false;

        if (!sbl_to_ptr.contains('Q')) return false;
        if (!sbl_to_ptr.contains('q')) return false;
        if (!sbl_to_ptr.contains('K')) return false;
        if (!sbl_to_ptr.contains('k')) return false;

        if (!sbl_to_ptr.contains('P')) return false;
        if (!sbl_to_ptr.contains('p')) return false;
        int i = 0;
        int j = 0;
        for (;i < 64;) {
            if (i < 43 && init[i] != '8' && init[i] != '/') {
                int tmp = sbl_to_ptr[init[i]];
                pos[7][0] = tmp;
            }
        }
    }
    bool move(std::string c1, std::string c2) {
        if (c1.size() != 2) return false;
        if (c2.size() != 2) return false;
        
        short dl1 = c1[0] - 'a';
        short dl2 = c2[0] - 'a';
        short dn1 = c1[1] - '0';
        short dn2 = c2[1] - '0';

        if (dn1 < 1 || dn1 > v) return false;        
        if (dl1 < 1 || dl1 > h) return false;        
        if (dn2 < 1 || dn2 > v) return false;       
        if (dl2 < 1 || dl2 > h) return false;
        
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
};

int main() {
    // Структура может наследовать 3, 4 или больше классов
    // board<A, B, C, D> obj;
    // obj.print_all(); // Выведет: 1 2 3 4 5 6 7 8
}