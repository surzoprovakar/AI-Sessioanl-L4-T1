#include<bits/stdc++.h>
using namespace std;

class Puzzle_8{
public:
    int block[3][3];
    double distance;
    int oneDimension;
    int neighbour[4][3][3];
    Puzzle_8 *parent;
    int costSoFar;
    int neighbourNumber;
    bool isCreated;

    Puzzle_8(){
        parent=NULL;
    }

    Puzzle_8(int ara[3][3]){
        oneDimension=0;
        int zero_X,zero_Y;
        neighbourNumber=0;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                block[i][j]=ara[i][j];
                oneDimension=oneDimension+block[i][j];
                neighbour[0][i][j]=block[i][j];
                neighbour[1][i][j]=block[i][j];
                neighbour[2][i][j]=block[i][j];
                neighbour[3][i][j]=block[i][j];
                if(i==2 && j==2){}
                else {oneDimension=oneDimension*10;}
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

        if((zero_X+1)!=3){
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

        if((zero_Y+1)!=3){
            temp=neighbour[neighbourNumber][zero_X][zero_Y+1];
            neighbour[neighbourNumber][zero_X][zero_Y+1]=0;
            neighbour[neighbourNumber][zero_X][zero_Y]=temp;
            neighbourNumber++;
        }


        distance=0;
        parent=NULL;
        costSoFar=0;
        isCreated=true;
    }

    bool operator<(const Puzzle_8 &o) const
    {
        return this->distance > o.distance;
    }
};

int convert2Dto1D(int block[3][3]){
    int oneDimension=0;

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            oneDimension=oneDimension+block[i][j];
            if(i==2 && j==2){}
            else {oneDimension=oneDimension*10;}

        }
    }

    return oneDimension;

}

double Heuristic1(int ara[3][3]){
    int LookingFor,LookingX=0,LookingY=0;
    double distance=0;
    int foundX,foundY;
    for(LookingFor=1;LookingFor<9;LookingFor++){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(ara[i][j]==LookingFor){
                    foundX=i;
                    foundY=j;
                }
            }
        }
        double dis=abs(LookingX-foundX)+abs(LookingY-foundY);
        distance=distance+dis;
        LookingY++;
        if(LookingY==3){
            LookingX++;
            LookingY=0;
        }
    }
    return distance;
}
double Heuristic2(int ara[3][3]){
    int LookingFor,LookingX=0,LookingY=0;
    double distance=0;
    int foundX,foundY;
    for(LookingFor=1;LookingFor<9;LookingFor++){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(ara[i][j]==LookingFor){
                    foundX=i;
                    foundY=j;
                }
            }
        }
        double dis=sqrt(pow((LookingX-foundX),2)+pow((LookingY-foundY),2));
        distance=distance+dis;
        LookingY++;
        if(LookingY==3){
            LookingX++;
            LookingY=0;
        }
    }
    return distance;

}
double Heuristic3(int ara[3][3]){
    int LookingFor=1;
    double mispalce=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(i==2 && j==2)break;
            if(ara[i][j]!=LookingFor){
                mispalce++;
            }
            LookingFor++;
        }
    }
    return mispalce;

}
double Heuristic4(int ara[3][3]){
    int LookingFor,LookingX=0,LookingY=0;
    double rowMisplace=8, columnMisplace=8;
    for(LookingFor=1;LookingFor<9;LookingFor++){
        for(int i=0;i<3;i++){
            if(ara[LookingX][i]==LookingFor)rowMisplace--;
        }
        for(int i=0;i<3;i++){
            if(ara[i][LookingY]==LookingFor)columnMisplace--;
        }
        LookingY++;
        if(LookingY==3){
            LookingX++;
            LookingY=0;
        }

    }
    return columnMisplace+rowMisplace;
}
double Heuristic5(int ara[3][3]){
    int P[9];
    int B[9];

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(ara[i][j]==0){
                P[i*3+j]=9;
                B[8]=i*3+j+1;
            }
            else {
                P[i*3+j]=ara[i][j];
                B[ara[i][j]-1]=i*3+j+1;
            }
        }
    }



    int flag=1;
    int temp,temp1;
    double distance=0;
    while(1){
        for(int i=0;i<9;i++){
            if(P[i]!=i+1)flag=0;
        }
        if(flag==1){
            break;
        }
        flag=1;
        temp=P[B[8]-1];
        P[B[8]-1]=P[B[B[8]-1]-1];
        P[B[B[8]-1]-1]=temp;
        temp=B[8];
        temp1=B[B[8]-1];
        B[B[8]-1]=temp;
        B[8]=temp1;
        distance++;

    }
    return distance;
}
double Heuristic6(int ara[3][3]){
    int P[9];
    int B[9];

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(ara[i][j]==0){
                P[i*3+j]=9;
                B[8]=i*3+j+1;
            }
            else {
                P[i*3+j]=ara[i][j];
                B[ara[i][j]-1]=i*3+j+1;
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
        for(int i=0;i<9;i++){
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

void print2D(int ara[3][3])
{
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout<<ara[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"---------"<<endl;
    cout<<endl;
}

map<int,Puzzle_8*> mymap;
map<int,int> visited;
map<int,int> costSoFar;

int main(){
    priority_queue<Puzzle_8> frontier;
    int totalCurrent=0;

    int start[3][3];
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf("Enter element in position(%d, %d): ",i,j);
            scanf("%d",&start[i][j]);
        }
    }
    /*cout<<Heuristic6(start);
    return 0;*/


    Puzzle_8 startState(start);


    frontier.push(startState);
    mymap[startState.oneDimension]=&startState;
    //visited[startState.oneDimension]=1;
    costSoFar[startState.oneDimension]=1;


    map<int,Puzzle_8> current;
    int curIndex=0;
    while(!frontier.empty()){


        current[curIndex]=frontier.top();
        //printf("current= %d\n", current[curIndex].oneDimension);
        frontier.pop();
        visited[current[curIndex].oneDimension]=1;

        if(current[curIndex].oneDimension==123456780){

            break;

        }

        for(int i=0;i<current[curIndex].neighbourNumber;i++){
            int native=convert2Dto1D(current[curIndex].neighbour[i]);


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
                //double priority=newCost+Heuristic5(current[curIndex].neighbour[i]);
                double priority=newCost+Heuristic6(current[curIndex].neighbour[i]);
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
