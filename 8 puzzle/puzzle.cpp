#include<bits/stdc++.h>
using namespace std;

int goal[3][3] = {0,1,2,3,4,5,6,7,8};

bool valid(int i,int j) {
    if((i>=0 && i<3) && (j>=0 && j<3)) return true;
    else return false;
}

class board {

public:
    int brd[3][3];
    double hrstic;
    int x,y;
    board() {
        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                brd[i][j]=0;
            }
        }
        hrstic = 0;
    }
    void set_board() {
        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                cin>>brd[i][j];
            }
        }
    }

};

class puzzle {
public:
    board b;
    board neighbors[4];
    int neighbor_size;
    puzzle *parent;
    double distance_cost;
    double Cost;
    puzzle() {
        board *a=&b;
        a=NULL;
        neighbor_size=0;
        distance_cost=0;
        Cost=0;
        parent=NULL;
        for(int i=0;i<4;i++) {
            board *t=&neighbors[i];
            t=NULL;
        }
    }

    puzzle(board bb) {
        int x0,y0;
        neighbor_size=0;
        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                b.brd[i][j]=bb.brd[i][j];
                neighbors[0].brd[i][j]=b.brd[i][j];
                neighbors[1].brd[i][j]=b.brd[i][j];
                neighbors[2].brd[i][j]=b.brd[i][j];
                neighbors[3].brd[i][j]=b.brd[i][j];
                if(b.brd[i][j]==0) {
                    x0=i;
                    y0=j;
                }

            }
        }

        int temp;

        if(valid(x0-1,y0)) {
            temp=neighbors[neighbor_size].brd[x0-1][y0];
            neighbors[neighbor_size].brd[x0-1][y0]=0;
            neighbors[neighbor_size].brd[x0][y0]=temp;
            neighbor_size++;
        }

        if(valid(x0+1,y0)) {
            temp=neighbors[neighbor_size].brd[x0+1][y0];
            neighbors[neighbor_size].brd[x0+1][y0]=0;
            neighbors[neighbor_size].brd[x0][y0]=temp;
            neighbor_size++;
        }

        if(valid(x0,y0-1)) {
            temp=neighbors[neighbor_size].brd[x0][y0-1];
            neighbors[neighbor_size].brd[x0][y0-1]=0;
            neighbors[neighbor_size].brd[x0][y0]=temp;
            neighbor_size++;
        }

        if(valid(x0,y0+1)) {
            temp=neighbors[neighbor_size].brd[x0][y0+1];
            neighbors[neighbor_size].brd[x0][y0+1]=0;
            neighbors[neighbor_size].brd[x0][y0]=temp;
            neighbor_size++;
        }

        parent=NULL;
        distance_cost=0;
        Cost=0;
    }

    bool operator <(const puzzle &o) const {
        return this->Cost>o.Cost;
    }
};

double h1_misplaced(board b) {
    int c=0;
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(b.brd[i][j]!=goal[i][j] && b.brd[i][j]!=0) c++;
        }
    }

    return c;
}

double h2_eucledian(board b) {
    double dis = 0.0,ech;
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(b.brd[i][j]==1) ech = sqrt(pow((i-0),2)+pow((j-1),2));
            else if(b.brd[i][j]==2) ech = sqrt(pow((i-0),2)+pow((j-2),2));
            else if(b.brd[i][j]==3) ech = sqrt(pow((i-1),2)+pow((j-0),2));
            else if(b.brd[i][j]==4) ech = sqrt(pow((i-1),2)+pow((j-1),2));
            else if(b.brd[i][j]==5) ech = sqrt(pow((i-1),2)+pow((j-2),2));
            else if(b.brd[i][j]==6) ech = sqrt(pow((i-2),2)+pow((j-0),2));
            else if(b.brd[i][j]==7) ech = sqrt(pow((i-2),2)+pow((j-1),2));
            else if(b.brd[i][j]==8) ech = sqrt(pow((i-2),2)+pow((j-2),2));
//            else if(b.brd[i][j]==9) ech = sqrt(pow((i-2),2)+pow((j-1),2));
//            else if(b.brd[i][j]==10) ech = sqrt(pow((i-2),2)+pow((j-2),2));
//            else if(b.brd[i][j]==11) ech = sqrt(pow((i-2),2)+pow((j-3),2));
//            else if(b.brd[i][j]==12) ech = sqrt(pow((i-3),2)+pow((j-0),2));
//            else if(b.brd[i][j]==13) ech = sqrt(pow((i-3),2)+pow((j-1),2));
//            else if(b.brd[i][j]==14) ech = sqrt(pow((i-3),2)+pow((j-2),2));
//            else if(b.brd[i][j]==15) ech = sqrt(pow((i-3),2)+pow((j-3),2));
            else ech = 0.0;
            dis = dis+ech;
            //cout<<dis<<endl;
        }
    }

    return dis;

}

double h3_manhattan(board b) {
    double dis = 0.0,ech;
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(b.brd[i][j]==1) ech = abs(i-0)+abs(j-1);
            else if(b.brd[i][j]==2) ech = abs(i-0)+abs(j-2);
            else if(b.brd[i][j]==3) ech = abs(i-1)+abs(j-0);
            else if(b.brd[i][j]==4) ech = abs(i-1)+abs(j-1);
            else if(b.brd[i][j]==5) ech = abs(i-1)+abs(j-2);
            else if(b.brd[i][j]==6) ech = abs(i-2)+abs(j-0);
            else if(b.brd[i][j]==7) ech = abs(i-2)+abs(j-1);
            else if(b.brd[i][j]==8) ech = abs(i-2)+abs(j-2);
//            else if(b.brd[i][j]==9) ech = abs(i-2)+abs(j-1);
//            else if(b.brd[i][j]==10) ech = abs(i-2)+abs(j-2);
//            else if(b.brd[i][j]==11) ech = abs(i-2)+abs(j-3);
//            else if(b.brd[i][j]==12) ech = abs(i-3)+abs(j-0);
//            else if(b.brd[i][j]==13) ech = abs(i-3)+abs(j-1);
//            else if(b.brd[i][j]==14) ech = abs(i-3)+abs(j-2);
//            else if(b.brd[i][j]==15) ech = abs(i-3)+abs(j-3);
            else ech = 0.0;
            dis = dis+ech;
            //cout<<dis<<endl;
        }
    }

    return dis;
}

double h4_rowcol(board b) {
    double value = 0,row=0,col=0;
    for (int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(b.brd[i][j]>=3*i && b.brd[i][j]<3*(i+1) && b.brd[i][j]!=0) row++;
        }
    }

    row = 8-row;

    for (int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(b.brd[i][j]%3==j && b.brd[i][j]!=0) col++;
        }
    }

    col = 8-col;

    return row+col;
}

double h5_NMaxSwap(board b) {
    double distance=0;
    int P[9];
    int B[9];
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            P[3*i+j]=b.brd[i][j];
        }
    }
    for(int i=0;i<9;i++) B[P[i]]=i;

    int flag=1;
    while(1) {
        //cout<<"hello"<<endl;
        for(int i=0;i<9;i++) {
            if(P[i]!=i) flag=0;
        }
        if(flag==1) break;
        flag=1;
        int tmp;
        tmp=P[B[B[8]]];
        P[B[B[8]]]=P[B[8]];
        P[B[8]]=tmp;

        //cout<<"P:";
        //for(int i=0;i<16;i++) cout<<P[i]<<" ";
        //cout<<endl;
        for(int i=0;i<9;i++) B[P[i]]=i;

        //cout<<"B:";
        //for(int i=0;i<16;i++) cout<<B[i]<<" ";
        //cout<<endl;

        distance++;
    }

    return distance;

}

string conversion(board b) {
    string result="";

    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            string temp;
            ostringstream convert;
            convert<<b.brd[i][j];
            temp=convert.str();
            result=result+temp;
        }
    }
    return result;

}

void print(board b) {
    cout<<endl;
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            cout<<setw(4)<<b.brd[i][j];
        }
        cout<<endl;
    }
    cout<<endl<<endl;
}


//bool isgoal(board b) {
//    for(int i=0;i<4;i++) {
//        for(int j=0;j<4;j++) {
//            if(b.brd[i][i]!=goal[i][j]) return false;
//        }
//    }
//    return true;
//}
//
//int dx[4] = {1,-1,0,0}; //gap tile sorle row er je change hote pare,serially down,up,right,left
//int dy[4] = {0,0,1,-1}; //gap tile sorle column er je change hote pare,serially down,up,right,left
//
//board swap_tile(board bd,int x,int y,int a,int b) {
//    int val=bd.brd[x][y];
//    bd.brd[x][y]=bd.brd[a][b];
//    bd.brd[a][b]=val;
//    return bd;
//}
//
//puzzle neighbor_generate(puzzle p) {
//    board b = p.b;
//    int next_x,next_y;
//    int k=0;
//    for(int i=0;i<4;i++) {
//        for(int j=0;j<4;j++) {
//            if(b.brd[i][j]==0) {
//                b.x=i;
//                b.y=j;
//                break;
//            }
//        }
//    }
//    for(int i=0;i<3;i++) {
//        next_x=b.x+dx[i];
//        next_y=b.y+dy[i];
//        if(valid(next_x,next_y)) {
//            board n=swap_tile(b,b.x,b.y,next_x,next_y);
//            p.neighbors[k++]=n;
//        }
//    }
//    p.neighbor_size=k-1;
//    return p;
//}
//
//bool check_equal(board a,board b) {
//    for(int i=0;i<4;i++) {
//        for(int j=0;j<4;j++) {
//            if(a.brd[i][j]!=b.brd[i][j]) return false;
//        }
//    }
//    return true;
//}

map<string,puzzle*> mapp;
map<string,int> Visited;
map<string,int> costSoFar;

int main() {

    priority_queue<puzzle> frontier;
    //int totalcur=0;
    board bb;

    cout<<"Enter the initial puzzle"<<endl;

    bb.set_board();

    cout<<endl<<"Input Puzzle Board"<<endl<<endl;
    print(bb);

    puzzle start(bb);
    frontier.push(start);
    //cout<<"hi"<<endl;
    //print(start.b);
    //cout<<conversion(start.b)<<endl;
    mapp[conversion(start.b)]=&start;
    costSoFar[conversion(start.b)]=1;

    map<int,puzzle> current;
    int index=0;

    while(!frontier.empty()) {
        // cout<<"hello"<<endl;
        current[index]=frontier.top();
        frontier.pop();
        Visited[conversion(current[index].b)]=1;

        if(conversion(current[index].b)=="012345678") break;

        for(int i=0;i<current[index].neighbor_size;i++) {
            //cout<<"hello2"<<endl;
            string temp=conversion(current[index].neighbors[i]);

            if(costSoFar[temp]==0) costSoFar[temp]=INT_MAX;

            if(mapp[temp]==NULL) {
                puzzle newOne(current[index].neighbors[i]);
                mapp[temp]=&newOne;
            }
            int newCost=current[index].distance_cost+1;

            if(Visited[conversion(current[index].neighbors[i])]!=1 && newCost<costSoFar[temp]) {
                costSoFar[temp]=newCost;
                //double priority=newCost+h1_misplaced(current[index].neighbors[i]);
                double priority=newCost+h2_eucledian(current[index].neighbors[i]);
                //double priority=newCost+h3_manhattan(current[index].neighbors[i]);
                //double priority=newCost+h4_rowcol(current[index].neighbors[i]);
                //double priority=newCost+h5_NMaxSwap(current[index].neighbors[i]);

                mapp[temp]->parent=&current[index];
                mapp[temp]->Cost=priority;
                mapp[temp]->distance_cost=newCost;
                frontier.push(*mapp[temp]);
            }
        }
        index++;
        //totalcur++;

    }
    //cout<<endl<<"Total Current "<<totalcur<<endl;

    map<int,puzzle> List;
    //puzzle *head;
    //int c=0;
    //head=new puzzle();
    //head=&current[index];
    //cout<<totalcur<<"th shuffle"<<endl<<endl;
    //List[c]=current[0];
    int totalShuffle=0;
    for(int i=1;i<=index;i++) {
        totalShuffle++;
        cout<<totalShuffle<<"th Shuffle"<<endl;
        List[i]=current[i];
        print(List[i].b);
    }
    //cout<<"last"<<endl;
    //print(head->b);

//    while(1) {
//        //cout<<"hello3"<<endl;
//        if(head->parent==NULL) break;
//        print(head->parent->b);
//        head=head->parent;
//        totalShuffle++;
//    }


    cout<<"Total shuffle "<<totalShuffle<<endl;

    //board b;
    //b.set_board();
    //cout<<h1_misplaced(b)<<endl;
    //cout<<h2_eucledian(b)<<endl;
    //cout<<h3_manhattan(b)<<endl;
    //cout<<h4_rowcol(b)<<endl;

}
