#include<bits/stdc++.h>
using namespace std;

class tile{
public:
    int row;
    int col;
    tile() {
        row=0;
        col=0;
    }
    tile(int r,int c) {
        row=r;
        col=c;
    }

};

class tile_info{
public:
    double hrs;
    tile t;
    tile_info() {
        hrs=0;
        tile *tt=&t;
        tt=NULL;
    }

    tile_info(double d,tile tat) {
        hrs=d;
        t=tat;
    }
    bool operator <(const tile_info &o) const {
        return this->hrs>o.hrs;
    }
};

class cell{
public:
    int x;
    int y;
    int parent_x;
    int parent_y;
    double f;
    double g;
    double h;
    cell() {
        x=0;
        y=0;
        parent_x=0;
        parent_y=0;
        f=0;
        g=0;
        h=0;
    }
};
bool valid(int r,int c) {
    if((r>=0 && r<25) && (c>=0 && c<25)) return true;
    else return false;
}

bool un_block(char grid[25][25],int r,int c) {
    if(grid[r][c]!=char(178)) return true;
    else return false;
}

bool destination(int r,int c,tile des) {
    if(r==des.row && c==des.col) return true;
    else return false;
}

double h1_eucledian(int r,int c,tile des) {
    return sqrt(pow((r-des.row),2)+pow((c-des.col),2));
}

double h2_manhattan(int r,int c,tile des) {
    return (abs(r-des.row)+abs(c-des.col));
}

double h3_diagonal(int r,int c,tile des) {
    return max(abs(r-des.row),abs(c-des.col));
}

void path(cell grid[25][25],char g[25][25],tile des) {
    cout<<"path"<<endl;
    int totalmove=0;
    int r=des.row;
    int c=des.col;
    tile tt;
    g[r][c]=220;
    stack<tile> path;

    while(!(grid[r][c].parent_x==30 && grid[r][c].parent_y==30)) {
        path.push(tile(r,c));
        int temp_r=grid[r][c].parent_x;
        int temp_c=grid[r][c].parent_y;
        r=temp_r;
        c=temp_c;
        g[r][c]=220;
        totalmove++;
    }

    tt=tile(r,c);
    path.push(tt);

    cout<<"Total Move "<<totalmove<<endl;
    while(!path.empty()) {
        tile t=path.top();
        path.pop();
        cout<<" -> "<<t.row<<" "<<t.col;
    }
    cout<<endl<<"------------------"<<endl<<endl;

    cout<<"    ";
    for(int i=0;i<25;i++) {
        cout<<setw(2)<<i<<" ";
    }
    cout<<endl;
    cout<<"    ";
    for(int i=0;i<25;i++) {
        cout<<setw(2)<<'v'<<" ";
    }
    cout<<endl;
    for(int i=0;i<25;i++) {
        cout<<setw(2)<<i<<">  ";
        for(int j=0;j<25;j++) {
            //grid[i][j]=rand()%2;
            cout<<g[i][j]<<"  ";
        }
        cout<<endl;
    }
}

void a_star_search(char grid[25][25],tile src,tile des) {

    tile t;
    tile_info tin;

    if(destination(src.row,src.col,des)) {
        cout<<"Already reached destination"<<endl;
        return;
    }
    if(un_block(grid,src.row,src.col)==false) {
        cout<<"Source cell is blocked"<<endl;
        return;
    }

    if(un_block(grid,des.row,des.col)==false) {
        cout<<"Destination cell is blocked"<<endl;
        return;
    }

    bool closedList[25][25];
    memset(closedList,false,sizeof(closedList));
    cell board[25][25];

    for(int i=0;i<25;i++) {
        for(int j=0;j<25;j++) {
            board[i][j].f=FLT_MAX;
            board[i][j].g=FLT_MAX;
            board[i][j].h=FLT_MAX;
            board[i][j].parent_x=-1;
            board[i][j].parent_y=-1;
        }
    }

    int init_x=src.row;
    int init_y=src.col;
    board[init_x][init_y].f=0;
    board[init_x][init_y].g=0;
    board[init_x][init_y].h=0;
    board[init_x][init_y].parent_x=30;
    board[init_x][init_y].parent_y=30;

    t=tile(init_x,init_y);
    tin=tile_info(0.0,t);
    //cout<<tin.hrs<<" "<<tin.t.row<<" "<<tin.t.col<<endl;

    priority_queue<tile_info> OpenList;
    OpenList.push(tin);

    bool isDestination=false;

    while(!OpenList.empty()) {
        //cout<<"hello"<<endl;
        tile_info tmid=OpenList.top();
        OpenList.pop();

        int r=tmid.t.row;
        int c=tmid.t.col;
        closedList[r][c]=true;

        double fnew,gnew,hnew;

        //Uper cell
        if(valid(r-1,c)==true) {
            //cout<<"uper"<<endl;
            if(destination(r-1,c,des)==true) {
                board[r-1][c].parent_x=r;
                board[r-1][c].parent_y=c;
                cout<<"Destination has reached"<<endl;
                path(board,grid,des);
                isDestination=true;
                return;
            }
            else if(closedList[r-1][c]==false && un_block(grid,r-1,c)==true) {
                gnew=board[r][c].g+1;
                hnew=h1_eucledian(r-1,c,des);
                //hnew=h2_manhattan(r-1,c,des);
                //hnew=h3_diagonal(r-1,c,des);
                fnew=gnew+hnew;

                if(board[r-1][c].f==FLT_MAX || board[r-1][c].f>fnew) {
                    t=tile(r-1,c);
                    tin=tile_info(fnew,t);
                    OpenList.push(tin);
                    board[r-1][c].g=gnew;
                    board[r-1][c].h=hnew;
                    board[r-1][c].f=fnew;
                    board[r-1][c].parent_x=r;
                    board[r-1][c].parent_y=c;
//                    cout<<"up"<<endl;
//                    cout<<"fnew "<<fnew<<endl;
//                    cout<<tin.hrs<<" "<<tin.t.row<<" "<<tin.t.col<<endl;

                }
            }
        }


         //Lower cell
        if(valid(r+1,c)) {
            //cout<<"lower"<<endl;
            if(destination(r+1,c,des)) {
                board[r+1][c].parent_x=r;
                board[r+1][c].parent_y=c;
                cout<<"Destination has reached"<<endl;
                path(board,grid,des);
                isDestination=true;
                return;
            }
            else if(closedList[r+1][c]==false && un_block(grid,r+1,c)==true) {
                gnew=board[r][c].g+1;
                hnew=h1_eucledian(r+1,c,des);
                //hnew=h2_manhattan(r+1,c,des);
                //hnew=h3_diagonal(r+1,c,des);
                fnew=gnew+hnew;

                if(board[r+1][c].f==FLT_MAX || board[r+1][c].f>fnew) {
                    t=tile(r+1,c);
                    tin=tile_info(fnew,t);
                    OpenList.push(tin);
                    board[r+1][c].g=gnew;
                    board[r+1][c].h=hnew;
                    board[r+1][c].f=fnew;
                    board[r+1][c].parent_x=r;
                    board[r+1][c].parent_y=c;
//                    cout<<"low"<<endl;
//                    cout<<"fnew "<<fnew<<endl;
//                    cout<<tin.hrs<<" "<<tin.t.row<<" "<<tin.t.col<<endl;

                }
            }
        }

         //Left cell
        if(valid(r,c-1)) {
            //cout<<"left"<<endl;
            if(destination(r,c-1,des)) {
                board[r][c-1].parent_x=r;
                board[r][c-1].parent_y=c;
                cout<<"Destination has reached"<<endl;
                path(board,grid,des);
                isDestination=true;
                return;
            }
            else if(closedList[r][c-1]==false && un_block(grid,r,c-1)==true) {
                gnew=board[r][c].g+1;
                hnew=h1_eucledian(r,c-1,des);
                //hnew=h2_manhattan(r,c-1,des);
                //hnew=h3_diagonal(r,c-1,des);
                fnew=gnew+hnew;

                if(board[r][c-1].f==FLT_MAX || board[r][c-1].f>fnew) {
                    t=tile(r,c-1);
                    tin=tile_info(fnew,t);
                    OpenList.push(tin);
                    board[r][c-1].g=gnew;
                    board[r][c-1].h=hnew;
                    board[r][c-1].f=fnew;
                    board[r][c-1].parent_x=r;
                    board[r][c-1].parent_y=c;
//                    cout<<"left"<<endl;
//                    cout<<"fnew "<<fnew<<endl;
//                    cout<<tin.hrs<<" "<<tin.t.row<<" "<<tin.t.col<<endl;

                }
            }
        }

         //Right cell
        if(valid(r,c+1)) {
            //cout<<"right"<<endl;
            if(destination(r,c+1,des)) {
                board[r][c+1].parent_x=r;
                board[r][c+1].parent_y=c;
                cout<<"Destination has reached"<<endl;
                path(board,grid,des);
                isDestination=true;
                return;
            }
            else if(closedList[r][c+1]==false && un_block(grid,r,c+1)==true) {
                gnew=board[r][c].g+1;
                hnew=h1_eucledian(r,c+1,des);
                //hnew=h2_manhattan(r,c+1,des);
                //hnew=h3_diagonal(r,c+1,des);
                fnew=gnew+hnew;

                if(board[r][c+1].f==FLT_MAX || board[r][c+1].f>fnew) {
                    t=tile(r,c+1);
                    tin=tile_info(fnew,t);
                    OpenList.push(tin);
                    board[r][c+1].g=gnew;
                    board[r][c+1].h=hnew;
                    board[r][c+1].f=fnew;
                    board[r][c+1].parent_x=r;
                    board[r][c+1].parent_y=c;
//                    cout<<"right"<<endl;
//                    cout<<"fnew "<<fnew<<endl;
//                    cout<<tin.hrs<<" "<<tin.t.row<<" "<<tin.t.col<<endl;

                }
            }
        }
    }

    if(isDestination==false) {
        cout<<"Destination is not reachable"<<endl;
        return;
    }



}



int main() {

    srand(time(NULL));
    char grid[25][25];
    cout<<"    ";
    for(int i=0;i<25;i++) {
        cout<<setw(2)<<i<<" ";
    }
    cout<<endl;
    cout<<"    ";
    for(int i=0;i<25;i++) {
        cout<<setw(2)<<'v'<<" ";
    }
    cout<<endl;
    for(int i=0;i<25;i++) {
        cout<<setw(2)<<i<<">  ";
        for(int j=0;j<25;j++) {
            int ran=rand()%2;
            if(ran==0 && (i+j)%2==0) grid[i][j]=178;
            else grid[i][j]=233;
            cout<<grid[i][j]<<"  ";
        }
        cout<<endl;
    }

    tile src;
    tile des;
    cout<<"Enter Source X co-ordinate"<<endl;
    cin>>src.row;
    cout<<"Enter Source Y co-ordinate"<<endl;
    cin>>src.col;



    cout<<"Enter Destination X co-ordinate"<<endl;
    cin>>des.row;
    cout<<"Enter Destination Y co-ordinate"<<endl;
    cin>>des.col;

    a_star_search(grid,src,des);


    return 0;
}
