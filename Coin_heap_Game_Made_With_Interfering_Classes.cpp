#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class Move {
public:

    Move(int sh, int sc, int th, int tc): sourceh(sh), sourcec(sc), targeth(th), targetc(tc) {}

    int getSource() const {
        return sourceh;
    }
    int getSourceCoins() const {
        return sourcec;
    }
    int getTarget() const {
        return targeth;
    }
    int getTargetCoins() const {
        return targetc;
    }

    friend ostream & operator << (ostream &out, const Move &move) ;
private:
    int sourceh;
    int sourcec;
    int targeth;
    int targetc;
};

ostream & operator << (ostream &out, const Move &move) {
    if(move.getTargetCoins()!=0) {
        out << "takes " << move.getSourceCoins() << " coins from heap " << move.getSource() << " and puts " << move.getTargetCoins() << " coins to heap "  << move.getTarget();
    }
    else {
        out << "takes " << move.getSourceCoins() << " coins from heap " << move.getSource() << " and puts nothing";
    }
    return out;
}

class State{
public:
    State(int h, const int c[], int n): heaps(h), gamers(n), current(0) {
        x=new int[heaps];
        for(int i=0; i<heaps; i++) {
            x[i]=c[i];
        }
    }
    ~State(){
        delete [] x;
        x=nullptr;
    }

    void next(const Move &move) throw(logic_error) {
        if ((move.getSource() >= getHeaps() || move.getSource() < 0) || (move.getTarget() >= getHeaps() || move.getTarget() < 0)) {
            throw logic_error("invalid heap");
        }
        else if (move.getSourceCoins()<1 || move.getSourceCoins()>getCoins(move.getSource()) || move.getTargetCoins()<0 || move.getTargetCoins()>=move.getSourceCoins()) {
            throw logic_error("invalid");
        }
        else {
            x[move.getSource()] -= move.getSourceCoins();
            x[move.getTarget()] += move.getTargetCoins();
            current++;
        }
    }

    bool winning() const {
        for(int i=0; i<heaps; i++) {
            if(x[i]!=0) {
                return false;
            }
        }
        return true;
    }

    int getHeaps() const {
        return heaps;
    }

    int getCoins(int h) const throw(logic_error) {
        if(h<0 || h>=heaps) throw logic_error("Invalid Heap");
        return x[h];
    }

    int getPlayers() const {
        return gamers;
    }

    int getPlaying() const {
        return current%gamers;
    }

    friend ostream & operator << (ostream &out, const State &state);
private:
    int heaps;
    int gamers;
    int  current;
    int * x;

};

ostream & operator << (ostream &out, const State &state) {
    for(int i=0; i<state.heaps; i++) {
        if (i != state.heaps - 1) {
            out << state.getCoins(i) << ", ";
        }
        else {
            out << state.getCoins(i) << " ";
        }
    }
    out << "with " << state.getPlaying() << "/" << state.gamers << " playing next";
    return out;
}

class Player {
public:
    Player(const string &n): Name(n) {}
    virtual ~Player() {}

    virtual const string & getType() const = 0;
    virtual Move play(const State &s) = 0;

    friend ostream & operator << (ostream &out, const Player &player);
protected:
    string Name;
};

ostream & operator << (ostream & out, const Player & player) {
    out << player.getType() << " player " << player.Name ;
    return out;
}


class SneakyPlayer: public Player {
public:

    SneakyPlayer(const string &n) : Player(n), Type("Sneaky") {}
    ~SneakyPlayer() override {}

    const string &getType() const override {
        return Type;
    }

    Move play(const State &s)  override {
        int y=0;
        while(s.getCoins(y)==0) { y++; }
        int start=s.getCoins(y);
        int k=y;
        int searching;                        //least coins ,takes all, puts none back
        for(int i=y; i<s.getHeaps(); i++) {
            searching = s.getCoins(i);
            if (searching!=0) {
                if(start >= searching) {
                    if(start!=searching) {
                        k = i;
                    }
                    start = searching;
                }
            }
        }
        Move m(k,start,0,0);
        return m;
    }
private:
    string Type;
};


class SpartanPlayer: public Player {
public:
    SpartanPlayer(const string &n) : Player(n), Type("Spartan") {}
    ~SpartanPlayer() override {}
    const string & getType() const override {
        return Type;
    }

    Move play(const State &s) override {
        int start=s.getCoins(0);
        int k=0;
        int searching;                        //max coins ,takes one, puts none back
        for(int i=1; i<s.getHeaps(); i++) {
            searching = s.getCoins(i);
            if (start < searching) {
                start = searching;
                if(k < i) {
                    k = i;
                }
            }
        }
        Move m(k,1,0,0);
        return m;
    }
private:
    string Type;
};

class GreedyPlayer: public Player {
public:
    GreedyPlayer(const string & n) : Player(n), Type("Greedy") {}
    ~GreedyPlayer() override {}
    const string & getType() const override{
        return Type;
    }

    Move play(const State & s) override {
        int start=s.getCoins(0);
        int k=0;
        int searching;                        //max coins ,takes all, puts none back
        for(int i=1; i<s.getHeaps(); i++) {
            searching = s.getCoins(i);
            if (start < searching) {
                start = searching;
                if(k < i) {
                    k = i;
                }
            }
        }
        Move m(k,start,0,0);
        return m;
    }
private:
    string Type;
};

class RighteousPlayer: public Player {
public:
    RighteousPlayer(const string &n) : Player(n), Type("Righteous") {}

    ~RighteousPlayer() override {}


    const string &getType() const override {
        return Type;
    }

    Move play(const State &s) override {
        int start1 = s.getCoins(0);
        int k1 = 0;
        int searching1;                        //max coins ,takes half, puts half - 1 to the least coin heap
        for (int i = 1; i < s.getHeaps(); i++) {
            searching1 = s.getCoins(i);
            if (start1 < searching1) {
                start1 = searching1;
                if (k1 < i) {
                    k1 = i;
                }
            }
        }
//      int y = 0;
//      while (s.getCoins(y) == 0) { y++; }
        int start = s.getCoins(0);
        int k = 0;
        int searching;                      //max coins ,takes half, puts half - 1 to the least coin heap
        for (int i = 0; i < s.getHeaps(); i++) {
            searching = s.getCoins(i);
            if(searching!=0) {
                if (start >= searching) {
                    if (start != searching) {
                        k = i;
                    }
                    start = searching;
                }
            }
            else {
                k=i;
                break;
            }
        }
        int final;
        if (start1 % 2 == 0) {
            final = start1 / 2;
        } else {
            final = start1 / 2 + 1;
        }
        Move m(k1, final, k, final - 1);
        return m;
    }
private:
    string Type;
};

#include <vector>

class Game
{
public:
    Game(int heaps, int players): people(players), hp(heaps), size(0) {
        x = new int[hp];
    }
    ~Game() {
        delete [] x;
        x=nullptr;
    }

    void addHeap(int coins) throw(logic_error) {
        if (size != hp) {
            x[size++]=coins;
        } else {
            throw logic_error("invalid heap");
        }
    }
    void addPlayer(Player *player) throw(logic_error) {
        if(ty.size()!=people) {
            ty.emplace_back(player);
        }
        else {
            throw logic_error("invalid person");
        }
    }
    void play(ostream &out) throw(logic_error){
        if(getPlayers()<people || size<hp) {
            throw logic_error("Invalid");
        }
        State s(hp,x,people);
        while(!s.winning()) {
            out << "State: " << s << endl;
            Move m=ty[s.getPlaying()]->play(s);
            out << ty[s.getPlaying()] << endl;
            s.next(m);
        }
    }

    int getPlayers() const{
        return ty.size();
    }
    const Player *getPlayer(int p) const throw(logic_error){
        if(p>=people || p<0) throw logic_error("invalid person");
        return ty[p];
    }
private:
    int people;
    int size;
    int hp;
    int * x;
    vector <Player *> ty;
};

int main() {
    Game specker(3, 4);
    specker.addHeap(10);
    specker.addHeap(20);
    specker.addHeap(17);
    specker.addPlayer(new SneakyPlayer("Tom"));
    specker.addPlayer(new SpartanPlayer("Mary"));
    specker.addPlayer(new GreedyPlayer("Alan"));
    specker.addPlayer(new RighteousPlayer("Robin"));
    specker.play(cout);
}
