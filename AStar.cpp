#include<bits/stdc++.h>
using namespace std;

class GridBlock{
public:
    int X;
    int Y;
    bool state;
    char content;
    GridBlock *parent;
    int neighbourNumber;
    int neighbour[4][2];
    int costSoFar;
    double distance;

    GridBlock(){parent=NULL;}

    GridBlock(int x,int y)
    {
        X=x;
        Y=y;
        state=true;
        content='A';
        parent=NULL;
        neighbourNumber=0;
        distance=0;
        costSoFar=INT_MAX;
        if(X+1<25){
            neighbour[neighbourNumber][0]=X+1;
            neighbour[neighbourNumber][1]=Y;
            neighbourNumber++;
        }
        if(X-1>0){
            neighbour[neighbourNumber][0]=X-1;
            neighbour[neighbourNumber][1]=Y;
            neighbourNumber++;
        }
        if(Y+1<25){
            neighbour[neighbourNumber][0]=X;
            neighbour[neighbourNumber][1]=Y+1;
            neighbourNumber++;
        }
        if(Y-1>0){
            neighbour[neighbourNumber][0]=X;
            neighbour[neighbourNumber][1]=Y-1;
            neighbourNumber++;
        }

    }

    bool operator<(const GridBlock &o) const
    {
        return this->distance > o.distance;
    }

};

double Heuristic1(int curX,int curY,int goalX,int goalY){
    return abs(goalX-curX)+abs(goalY-curY);
}

double Heuristic2(int curX,int curY,int goalX,int goalY){
    return sqrt(pow((goalX-curX),2)+pow((goalY-curY),2));
}

double Heuristic3(int curX,int curY,int goalX,int goalY){
    return max((goalX-curX),(goalY-curY));
}




//map<int,GridBlock*> mymap;
map<int,int> visited;
//map<int,int> costSoFar;
int main()
{

    GridBlock Grid[25][25];
    //map<int ,GridBlock*> Ob;
    //int Obindex=0;
    double probability;
    srand (time(NULL));
    for(int i=0;i<25;i++){
        for(int j=0;j<25;j++){
            GridBlock obj(i,j);
            //Ob[Obindex]=&obj;
            Grid[i][j]=obj;
            probability=(rand()%10 +1);

            //cout<<probability<<" ";
            if(probability<3){
                Grid[i][j].state=false;
                Grid[i][j].content='B';
            }

        }
        //cout<<endl;
    }

    for(int i=0;i<25;i++){
        for(int j=0;j<25;j++){
            if(Grid[i][j].content=='B'){
                printf("%c ",177);
            }
            else if(Grid[i][j].content=='A'){
                printf("%c ",88);
            }
        }
        cout<<endl;
    }

    priority_queue<GridBlock> frontier;
    int startX,startY,goalX,goalY;

    cout<<"Enter Starting X Co-Ordinate: ";
    cin>>startX;
    cout<<"Enter Starting Y Co-Ordinate: ";
    cin>>startY;
    cout<<"Enter Goal X Co-Ordinate: ";
    cin>>goalX;
    cout<<"Enter Goal Y Co-Ordinate: ";
    cin>>goalY;

    if(!Grid[startX][startY].state){
        cout<<"not a valid starting Co-ordinate"<<endl;
        return 0;
    }
    if(!Grid[goalX][goalY].state){
        cout<<"not a valid goal Co-ordinate"<<endl;
        return 0;
    }

    Grid[startX][startY].costSoFar=0;

    frontier.push(Grid[startX][startY]);

    GridBlock current;
    int totalCurrent=0;
    int flag=0;

    while(!frontier.empty()){
        current=frontier.top();
        frontier.pop();
        //cout<<current.X<<","<<current.Y<<endl;

        visited[current.X*100+current.Y]=1;


        if(current.X==goalX && current.Y==goalY){
            flag=1;

            break;

        }

        for(int i=0;i<current.neighbourNumber;i++){
            if(!Grid[current.neighbour[i][0]][current.neighbour[i][1]].state)continue;
            int x=current.neighbour[i][0];
            int y=current.neighbour[i][1];
            int native=x*100+y;

            int newCost=current.costSoFar+1;
            if(visited[native]!=1 && newCost<Grid[x][y].costSoFar){
                Grid[x][y].costSoFar=newCost;
                //double priority=newCost;
                double priority=newCost/2+Heuristic1(x,y,goalX,goalY);
                //double priority=newCost/2+Heuristic2(x,y,goalX,goalY);
                //double priority=newCost/2+Heuristic3(x,y,goalX,goalY);
                //mymap[native]->parent=&current[curIndex];
                Grid[x][y].parent=&Grid[current.X][current.Y];
                Grid[x][y].distance=priority;

                frontier.push(Grid[x][y]);
            }


        }
        totalCurrent++;
    }
    cout<<"Total Current: "<<totalCurrent<<endl;

    cout<<"----------------------------"<<endl;

    if(flag==0){
        cout<<"No path found"<<endl;
    }

    for(int i=0;i<25;i++){
        for(int j=0;j<25;j++){
            if(visited[i*100+j]==1){
                Grid[i][j].content='V';
            }
        }
    }
    if(flag==1){
        GridBlock *head;
        head=new GridBlock();
        head=&current;
        int TotalMove=0;
        Grid[current.X][current.Y].content='F';
        while(1){
            if(head->parent==NULL){
                head->content='S';
                break;
            }
            if(head->parent->X<head->X)head->content='D';
            else if(head->parent->X>head->X)head->content='U';
            else if(head->parent->Y<head->Y)head->content='R';
            else if(head->parent->Y>head->Y)head->content='L';
            head=head->parent;
            TotalMove++;

        }
        cout<<"TotalMove: "<<TotalMove<<endl;
    }

    for(int i=0;i<25;i++){
        for(int j=0;j<25;j++){
            if(Grid[i][j].content=='B'){
                printf("%c ",177);
            }
            else if(Grid[i][j].content=='V'){
                printf("%c ",35);
            }
            else if(Grid[i][j].content=='A'){
                printf("%c ",88);
            }
            else if(Grid[i][j].content=='U'){
                printf("%c ",94);
            }
            else if(Grid[i][j].content=='D'){
                 printf("%c ",118);
            }
            else if(Grid[i][j].content=='R'){
                 printf("%c ",62);
            }
            else if(Grid[i][j].content=='L'){
                 printf("%c ",60);
            }
            else if(Grid[i][j].content=='S'){
                 printf("%c ",36);
            }
            else if(Grid[i][j].content=='F'){
                 printf("%c ",36);
            }
        }
        cout<<endl;
    }


}
