#include<bits/stdc++.h>
using namespace std;

class tile{
public:
    int row;
    int col;
    tile(){
    }
    tile(int r,int c) {
        row=r;
        col=c;
    }
};

bool valid_move(int r,int c) {
    if((r>=0 && r<3) && (c>=0 && c<3)) return true;
    else return false;
}

bool possible_move(char board[3][3]) {
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(board[i][j]==(char)95) return true;
        }
    }
    return false;
}

int grab(char board[3][3],int r,int c) {
    if(board[r][c]=='x') return 2;
    else if(board[r][c]=='o') return -2;
}

void show_board(char board[3][3]) {
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            cout<<setw(4)<<board[i][j];
        }
        cout<<endl<<endl;
    }
    cout<<endl<<endl;
}

int winner(char board[3][3],int cnt) {

    if(cnt==9) {
        return 50;
    }

    //Row_Match
    for(int i=0;i<3;i++) {
        if((board[i][0]==board[i][1]) && (board[i][1]==board[i][2])&& board[i][0]!=(char)95) {// && (board[i][2]==board[i][3])) {
            //cout<<"Win by row match"<<endl;
            if(board[i][0]=='X') return 100;
            else if(board[i][0]=='O') return -100;
        }
    }

     //Column_Match
    for(int i=0;i<3;i++) {
        if((board[0][i]==board[1][i]) && (board[1][i]==board[2][i])&& board[0][i]!=(char)95) {// && (board[2][i]==board[3][i])) {
            //cout<<"Win by column match"<<endl;
            if(board[0][i]=='X') return 100;
            else if(board[0][i]=='O') return -100;
        }
    }

    //Left_diagonal
    if ((board[0][0]==board[1][1]) && (board[1][1]==board[2][2]) && board[0][0]!=(char)95) {// && (board[2][2]==board[3][3])) {
        //cout<<"Win by diagonal match"<<endl;
        if(board[0][0]=='X') return 100;
        else if(board[0][0]=='O') return -100;
    }

    if ((board[0][2]==board[1][1]) && (board[1][1]==board[2][0])&& board[0][2]!=(char)95) {// && (board[2][1]==board[3][0])) {
        //cout<<"Win by d match"<<endl;
        if(board[0][0]=='X') return 100;
        else if(board[0][3]=='O') return -100;
    }

    return 0;
}

int minimax(char board[3][3],int depth,bool turn,int cnt) {
    //cout<<"hello"<<endl;
    int w=winner(board,cnt);
    //cout<<"w:"<<w<<endl;
    if(w==100) return w;
    if(w==-100) return w;
    if(possible_move(board)==false) return 0;
    if(turn) {
        //cout<<"O"<<endl;
        int best=-1000;
        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                if(board[i][j]==(char)95) {
                    board[i][j]='X';
                    best=max(best,minimax(board,depth+1,!turn,cnt));
                    //cout<<best<<endl;
                    board[i][j]=95;
                }
            }
        }
        //cout<<"oka"<<endl;
        return best;
    }

    else {
        //cout<<"X"<<endl;
        int best=1000;
        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                if(board[i][j]==(char)95) {
                    board[i][j]='X';
                    best=min(best,minimax(board,depth+1,!turn,cnt));
                    //cout<<"b:"<<best<<endl;
                    board[i][j]=95;
                }
            }
        }
        //cout<<"oka2"<<endl;
        return best;
    }

}

tile bestmove(char board[3][3],int cnt) {
    //cout<<"asi"<<endl;
    int best=-INT_MAX;
    tile t=tile(-1,-1);

    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(board[i][j]==(char)95) {
                board[i][j]='O';
                //cout<<"asi2"<<endl;
                int mov=minimax(board,0,false,cnt);
                //cout<<"asi3"<<endl;
                board[i][j]=95;
                if(mov>best) {
                    best=mov;
                    t.row=i;
                    t.col=j;
                }
            }
        }
    }
    return t;
}


int main() {

    char board[3][3];
    int r,c;
    //cout<<possible_move(board)<<endl;
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            board[i][j]=95;
        }
    }

    show_board(board);
    int cnt=0;

    //cout<<possible_move(board);
    while(1) {

        int w=winner(board,cnt);
        if(w==100) {
            cout<<"You WIN!"<<endl;
            break;
        }
        else if(w==-100) {
            cout<<"Computer WINS!"<<endl;
            break;
        }
        else if(w==50) {
            cout<<"Match DRAWN!"<<endl;
            break;
        }
        else {
            cnt++;
            while(1) {
                cout<<"Grab your position"<<endl;
                cout<<"Row:";
                cin>>r;
                cout<<"Col:";
                cin>>c;
                if(valid_move(r,c)) {
                    int g=grab(board,r,c);
                    if(g==2) {
                        cout<<"Already you picked the position"<<endl;
                        continue;
                    }
                    else if(g==-2) {
                         cout<<"Already computer picked the position"<<endl;
                        continue;
                    }
                    else {
                        board[r][c]='X';
                        break;
                    }
                }
                else {
                    cout<<"Please enter valid position"<<endl;
                    continue;
                }

            }
            show_board(board);
            cout<<"Computer's Turn"<<endl;

            tile t=bestmove(board,cnt);
            cout<<"row:"<<t.row<<"  col:"<<t.col<<endl;
            board[t.row][t.col]='O';
            show_board(board);
        }
    }

}
