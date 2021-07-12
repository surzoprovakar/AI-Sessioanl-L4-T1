#include<bits/stdc++.h>
using namespace std;

class Puzzle_8{
public:
    int block[4][4];
    double distance;
    int neighbour[4][4][4];
    Puzzle_8 *parent;
    int costSoFar;
    int neighbourNumber;
    //bool isCreated;

    Puzzle_8(){
        parent=NULL;
    }

    Puzzle_8(int ara[4][4]){
        int zero_X,zero_Y;
        neighbourNumber=0;
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                block[i][j]=ara[i][j];
                neighbour[0][i][j]=block[i][j];
                neighbour[1][i][j]=block[i][j];
                neighbour[2][i][j]=block[i][j];
                neighbour[3][i][j]=block[i][j];
                if(block[i][j]==0){
                    zero_X=i;
                    zero_Y=j;
                }
            }
        }

        int temp;
        if((zero_X-1)!=-1){
            temp=neighbour[neighbourNumber][zero_X-1][zero_Y];
            neighbour[neighbourNumber][zero_X-1][zero_Y]=0;
            neighbour[neighbourNumber][zero_X][zero_Y]=temp;
            neighbourNumber++;
        }

        if((zero_X+1)!=4){
            temp=neighbour[neighbourNumber][zero_X+1][zero_Y];
            neighbour[neighbourNumber][zero_X+1][zero_Y]=0;
            neighbour[neighbourNumber][zero_X][zero_Y]=temp;
            neighbourNumber++;
        }

        if((zero_Y-1)!=-1){
            temp=neighbour[neighbourNumber][zero_X][zero_Y-1];
            neighbour[neighbourNumber][zero_X][zero_Y-1]=0;
            neighbour[neighbourNumber][zero_X][zero_Y]=temp;
            neighbourNumber++;
        }

        if((zero_Y+1)!=4){
            temp=neighbour[neighbourNumber][zero_X][zero_Y+1];
            neighbour[neighbourNumber][zero_X][zero_Y+1]=0;
            neighbour[neighbourNumber][zero_X][zero_Y]=temp;
            neighbourNumber++;
        }


        distance=0;
        parent=NULL;
        costSoFar=0;
        //isCreated=true;
    }

    bool operator<(const Puzzle_8 &o) const
    {
        return this->distance > o.distance;
    }
};

string convert2Dto1D(int block[4][4]){
    string oneDimension="";

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            string Result;
            ostringstream convert;
            convert << block[i][j];
            Result = convert.str();
            oneDimension=oneDimension+Result;
        }
    }

    return oneDimension;
}

double Heuristic1(int ara[4][4]){
    int LookingFor,LookingX=0,LookingY=0;
    double distance=0;
    int foundX,foundY;
    for(LookingFor=1;LookingFor<16;LookingFor++){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(ara[i][j]==LookingFor){
                    foundX=i;
                    foundY=j;
                }
            }
        }
        double dis=abs(LookingX-foundX)+abs(LookingY-foundY);
        distance=distance+dis;
        LookingY++;
        if(LookingY==4){
            LookingX++;
            LookingY=0;
        }
    }
    return distance;
}
double Heuristic2(int ara[4][4]){
    int LookingFor,LookingX=0,LookingY=0;
    double distance=0;
    int foundX,foundY;
    for(LookingFor=1;LookingFor<16;LookingFor++){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(ara[i][j]==LookingFor){
                    foundX=i;
                    foundY=j;
                }
            }
        }
        double dis=sqrt(pow((LookingX-foundX),2)+pow((LookingY-foundY),2));
        distance=distance+dis;
        LookingY++;
        if(LookingY==4){
            LookingX++;
            LookingY=0;
        }
    }
    return distance;

}
double Heuristic3(int ara[4][4]){
    int LookingFor=1;
    double mispalce=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(i==3 && j==3)break;
            if(ara[i][j]!=LookingFor){
                mispalce++;
            }
            LookingFor++;
        }
    }
    return mispalce;

}
double Heuristic4(int ara[4][4]){
    int LookingFor,LookingX=0,LookingY=0;
    double rowMisplace=15, columnMisplace=15;
    for(LookingFor=1;LookingFor<16;LookingFor++){
        for(int i=0;i<4;i++){
            if(ara[LookingX][i]==LookingFor)rowMisplace--;
        }
        for(int i=0;i<4;i++){
            if(ara[i][LookingY]==LookingFor)columnMisplace--;
        }
        LookingY++;
        if(LookingY==4){
            LookingX++;
            LookingY=0;
        }

    }
    return columnMisplace+rowMisplace;
}
double Heuristic5(int ara[4][4]){
    int P[16];
    int B[16];

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(ara[i][j]==0){
                P[i*4+j]=16;
                B[15]=i*4+j+1;
            }
            else {
                P[i*4+j]=ara[i][j];
                B[ara[i][j]-1]=i*4+j+1;
            }
        }
    }



    int flag=1;
    int temp,temp1;
    double distance=0;
    while(1){
        for(int i=0;i<16;i++){
            if(P[i]!=i+1)flag=0;
        }
        if(flag==1){
            break;
        }
        flag=1;
        temp=P[B[15]-1];
        P[B[15]-1]=P[B[B[15]-1]-1];
        P[B[B[15]-1]-1]=temp;
        temp=B[15];
        temp1=B[B[15]-1];
        B[B[15]-1]=temp;
        B[15]=temp1;
        distance++;

    }
    return distance;
}
double Heuristic6(int ara[4][4]){
    int P[16];
    int B[16];

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(ara[i][j]==0){
                P[i*4+j]=16;
                B[15]=i*4+j+1;
            }
            else {
                P[i*4+j]=ara[i][j];
                B[ara[i][j]-1]=i*4+j+1;
            }
        }
    }
    /*for(int x=0;x<9;x++){
        cout<<P[x];
    }
    cout<<"  ";
    for(int x=0;x<9;x++){
        cout<<B[x];
    }
    cout<<endl;*/
    int flag=1,currentPosition=0;
    int temp,temp1,temp2,temp3;
    double distance=0;
    while(1){
        for(int i=0;i<16;i++){
            if(P[i]!=i+1)flag=0;
        }
        if(flag==1){
            break;
        }
        flag=1;
        if(B[currentPosition]==currentPosition+1)
        {
            currentPosition++;
            continue;
        }
        distance++;
        temp=P[B[currentPosition]-1];
        temp1=P[currentPosition];
        P[B[currentPosition]-1]=temp1;
        P[currentPosition]=temp;
        temp2=B[temp-1];
        temp3=B[temp1-1];
        B[temp-1]=temp3;
        B[temp1-1]=temp2;
        currentPosition++;

        /*for(int x=0;x<9;x++){
            cout<<P[x];
        }
        cout<<"  ";
        for(int x=0;x<9;x++){
            cout<<B[x];
        }
        cout<<endl;*/
    }
    return distance;

}

void print2D(int ara[4][4])
{
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            cout<<setw(4)<<ara[i][j];
        }
        cout<<endl;
    }
    cout<<"  ---------------"<<endl;
    cout<<endl;
}

map<string,Puzzle_8*> mymap;
map<string,int> visited;
map<string,int> costSoFar;

int main(){
    priority_queue<Puzzle_8> frontier;
    int totalCurrent=0;

    int start[4][4];
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            printf("Enter element in position(%d, %d): ",i,j);
            scanf("%d",&start[i][j]);
        }
    }
    /*cout<<Heuristic6(start);
    return 0;*/

    Puzzle_8 startState(start);

    frontier.push(startState);
    mymap[convert2Dto1D(startState.block)]=&startState;
    costSoFar[convert2Dto1D(startState.block)]=1;

    map<int,Puzzle_8> current;
    int curIndex=0;
    while(!frontier.empty()){
        current[curIndex]=frontier.top();
        //printf("current= %d\n", current[curIndex].oneDimension);
        frontier.pop();
        visited[convert2Dto1D(current[curIndex].block)]=1;

        if(convert2Dto1D(current[curIndex].block)=="1234567891011121314150"){
            break;
        }
        for(int i=0;i<current[curIndex].neighbourNumber;i++){
            string native=convert2Dto1D(current[curIndex].neighbour[i]);


            if(costSoFar[native]==0)costSoFar[native]=INT_MAX;


            if(mymap[native]==NULL){
                Puzzle_8 newCreated(current[curIndex].neighbour[i]);
                mymap[native]=&newCreated;
            }

            int newCost=current[curIndex].costSoFar+1;
            if(visited[convert2Dto1D(current[curIndex].neighbour[i])]!=1 && newCost<costSoFar[native]){
                costSoFar[native]=newCost;
                //double priority=newCost;
                //double priority=newCost+Heuristic1(current[curIndex].neighbour[i]);
                //double priority=newCost+Heuristic2(current[curIndex].neighbour[i]);
                //double priority=newCost+Heuristic3(current[curIndex].neighbour[i]);
                //double priority=newCost+Heuristic4(current[curIndex].neighbour[i]);
                double priority=newCost+Heuristic5(current[curIndex].neighbour[i]);
                //double priority=newCost+Heuristic6(current[curIndex].neighbour[i]);
                mymap[native]->parent=&current[curIndex];

                mymap[native]->distance=priority;
                mymap[native]->costSoFar=newCost;
                frontier.push(*mymap[native]);
            }
        }
        curIndex++;
        totalCurrent++;
    }
    cout<<"Total Current: "<<totalCurrent<<endl;
    cout<<"--------------------------"<<endl;




    Puzzle_8 *head;
    head=new Puzzle_8();
    head=&current[curIndex];
    print2D(head->block);
    int TotalMove=0;

    while(1){
        if(head->parent==NULL){
            break;
        }

        //cout<<head->parent->oneDimension<<endl;
        print2D(head->parent->block);
        head=head->parent;
        TotalMove++;

    }
    cout<<"TotalMove: "<<TotalMove<<endl;



}
