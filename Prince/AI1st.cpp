#include<bits/stdc++.h>
using namespace std;

int chess[10][10];
char res[10][10];
bool valid(int x,int y,int n) {
    if((x>=0 && x<n) && (y>=0 && y<n) && chess[x][y]==-1) return true;
    else return false;

}

void print(int n) {
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            cout<<res[i][j]<<" ";
            //cout<<chess[i][j]<<" ";
        }
        cout<<endl;
    }
}

void refresh(int n) {
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) chess[i][j]=-1;
    }
}

bool finished(int n) {
    int c=0;
    //int chess[n][n];
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            if(chess[i][j]==1) c++;
        }
    }
    //cout<<"cou"<<c<<endl;
    if(c==n*n) return true;
    else return false;

}

int prince(int x,int y,int n,int x_move[3],int y_move[3]) {
    //int chess[n][n];
    //cout<<"x"<<x<<" "<<y<<endl;
    int next_x,next_y;
    //cout<<"fin"<<finished()<<endl;
    chess[x][y]=1;
    if(finished(n)) {
        //print();
        return 1;
    }

    for(int i=0;i<3;i++) {
        next_x=x+x_move[i];
        next_y=y+y_move[i];
        if(valid(next_x,next_y,n)) {
            //cout<<"val"<<endl;
            //chess[next_x][next_y]=1;
            if(prince(next_x,next_y,n,x_move,y_move)==1) return 1;
            else chess[next_x][next_y]=-1;
        }

    }
    //cout<<"leave"<<endl;
    return 0;
}
void check(int n) {
    //int chess[n][n];
    //char res[n][n];

    int x_move[3]={0,1,-1};
    int y_move[3]={1,0,-1};

    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            refresh(n);
            if(prince(i,j,n,x_move,y_move)==0) {
                res[i][j]='N';
                //cout<<"not complete"<<endl;
            }

            else {
                res[i][j]='Y';
                //cout<<"complete"<<endl;
            }
        }
    }

}


int main() {
    int n;
    cin>>n;
    //cin>>n;
    check(n);
    print(n);
}
