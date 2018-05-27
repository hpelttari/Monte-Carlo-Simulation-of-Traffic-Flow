#include <iostream>
#include <random>
#include <vector>

using namespace std;


//function prototypes
vector<bool> createInitialConfiguration(int, int);
void printTraffic(vector<bool>);
vector<int> createListOfJumpRates(vector<bool>);
vector<int> updateJumpRates(vector<int>,vector<bool>,int);
vector<bool> moveCarOnRoad(int,vector<bool>);
int findIndexOfPreviousCar(vector<bool>, int);
int findIndexOfNextCar(vector<bool>, int);
int findLastCar(vector<bool>);
int findFirstCar(vector<bool>);
vector<double> R(vector<int>,int);
int findEventToCarryOut(vector<double>, mt19937&);
double updateTime(int, double, mt19937&);


int main(){
  int N=100;
  vector<bool> road =createInitialConfiguration(N, 200);
  int firstCar=findFirstCar(road);
  int lastCar=findLastCar(road);
  vector<int> jumpRates=createListOfJumpRates(road);
  /*printTraffic(road);
    for(int i=0;i<jumpRates.size();i++){
    cout<<jumpRates[i];//<<endl;
  }
  cout<<endl;
  road=moveCarOnRoad(1,road);
  //firstCar=2;
  cout<<"\n";
  printTraffic(road);
  jumpRates=updateJumpRates(jumpRates,road,2);
  for(int i=0;i<jumpRates.size();i++){
    cout<<jumpRates[i];//<<endl;
  }
  cout<<endl;
  cout<<"\n";
  road=moveCarOnRoad(5, road);
  jumpRates=updateJumpRates(jumpRates,road,6);
  printTraffic(road);
  for(int i=0;i<jumpRates.size();i++){
    cout<<jumpRates[i];
  }
  cout<<endl;*/


  //Main KMC loop
  double t=0;
  double MaxTime=1000000;
  double carMoved=1;
  vector<double> cumFunc(jumpRates.size());
  mt19937 mt_rand(123);
  for(int i=0;i<4000000;i++){
    jumpRates=updateJumpRates(jumpRates,road,carMoved);
    cumFunc=R(jumpRates,N);
    carMoved=findEventToCarryOut(cumFunc,mt_rand);
    //cout<<cumFunc[cumFunc.size()-1]<<endl;
    road=moveCarOnRoad(carMoved,road);
    t=updateTime(cumFunc[cumFunc.size()-1],t,mt_rand);
    if(carMoved==road.size()-1){
      carMoved=0;
    }else{
      carMoved++;
    }
    printTraffic(road);
    printTraffic(road);
    printTraffic(road);
    printTraffic(road);
    printTraffic(road);
    printTraffic(road);
    printTraffic(road);
    printTraffic(road);
        printTraffic(road);
    printTraffic(road);
    printTraffic(road);
    printTraffic(road);
    printTraffic(road);
    printTraffic(road);
    printTraffic(road);
    printTraffic(road);
        printTraffic(road);
    printTraffic(road);
    printTraffic(road);
    printTraffic(road);
    printTraffic(road);
    printTraffic(road);
    printTraffic(road);
    printTraffic(road);
        printTraffic(road);
    printTraffic(road);
    printTraffic(road);
    printTraffic(road);
    printTraffic(road);
    printTraffic(road);
    printTraffic(road);
    printTraffic(road);
        printTraffic(road);
    printTraffic(road);
    printTraffic(road);
    printTraffic(road);
    printTraffic(road);
    printTraffic(road);
    printTraffic(road);
    printTraffic(road);
    
  }

  
  return 0;
}

vector<bool> createInitialConfiguration(int N, int L){
  double density = (double)N/L;
  cout<<"density="<<density<<" inverse="<<1/density<<endl;
  vector<bool> road(L);
  int counter=1;
  for(int i=0;i<L;i++){
    if(counter==1/density){
      counter=0;
      road[i]=1;
    } else{
      road[i]=0;
    }
    counter++;
  }
  return road;
}

int findFirstCar(vector<bool> road){
  int firstCar=0;
  while(true){
    if(road[firstCar]==true){
      break;
    }
    firstCar++;
  }

  return firstCar;
}

int findLastCar(vector<bool> road){
  int LastCar=road.size()-1;
  while(true){
    if(road[LastCar]==true){
      break;
    }
    LastCar--;
  }

  return LastCar;
}

void printTraffic(vector<bool> road){
  for(int i=0;i<road.size();i++){
    if(road[i]==true){
      cout<<"X";
    } else{
      cout<<" ";
    }
  }
  cout<<"\n";
}
    
vector<int> createListOfJumpRates(vector<bool> road){
  vector<int> jumpRates(road.size());
  for(int car=0;car<road.size();car++){
    jumpRates[car]=0;
    //Check if the position on the road contains a car
    if(road[car]==true){
      int position=car+1;
      int rate=0;
      //add to the jump rate until a next car
      while(position<road.size()){
	if(road[position]==true){
	  break;
	}
	rate++;
	jumpRates[car]=rate;
	position++;
      }
    }
  }
  if(road[jumpRates.size()-1]==true){
      int rate=0;
      int position=0;
      while(true){
	if(road[position]==true){
	  jumpRates[jumpRates.size()-1]=rate;
	  break;
	}
	rate++;
	position++;
      }
    }
  return jumpRates;
}

vector<int> updateJumpRates(vector<int> jumpRates,vector<bool> road, int car){
  if(car>0){
  jumpRates[car-1]=0;
  } else{
    jumpRates[jumpRates.size()-1]=0;
  }
  int position=car+1;


  
  if(position==jumpRates.size()){
    position=0;
  }
  int rate=0;
  //update jump rate of the car moved
  while(true){
    if(road[position]==true){
          jumpRates[car]=rate;
	break;
      }
    rate++;
    position++;
    if(position==jumpRates.size()){
      position=0;
    }
  }
  rate=0;
  position=car-1;
  //update the jump rate of the previous car
  if(position<0){
    position=jumpRates.size()-1;
  }
  while(true){
    if(road[position]==true){
      jumpRates[position]=rate;
      break;
    }
    rate++;
    position--;
  if(position<0){
    position=jumpRates.size()-1;
  }
  }

  return jumpRates;
}

int findIndexOfPreviousCar(vector<bool> road, int car){
  int previousCar;
  int i=car-1;
  while(true){
    if(i<0){
      i=road.size()-1;
    }
    if(road[i]==1){
      previousCar=i;
      break;
    }
    i--;
  }
  return previousCar;
}

int findIndexOfNextCar(vector<bool> road, int car){
  int nextCar;
  int i=car+1;
  while(true){
    if(i>road.size()-1){
      i=0;
    }
    if(road[i]==1){
      nextCar=i;
      break;
    }
    i++;
  }
  return nextCar;
}

vector<bool> moveCarOnRoad(int car,vector<bool> road){
  if(car<road.size()-1&&road[car+1]==0){
    road[car]=0;
    road[car+1]=1;
  }/* else{
    cout<<"Can't move the car"<<endl;
    }*/
  if(car==road.size()-1&&road[0]==0){
    road[car]=0;
    road[0]=1;
  }

  return road;
}

vector<double> R(vector<int> jumpRates,int N){
  vector<double> r(jumpRates.size());
  double sum=0;
  for(int i=0;i<jumpRates.size();i++){
    sum+=jumpRates[i];
    r[i]=sum;
    //cout<<r[i];
  }
  //cout<<endl;

  return r;
}

int findEventToCarryOut(vector<double> R, mt19937& mt_rand){
  int event=0;
  double u=R[R.size()-1]*(double)mt_rand()/mt_rand.max();
  bool b;
  int j=0;
  //if(R[0]!=0&&R[1]<=u)
  
  while(R[j]==0){
  j++;
  }
  int z;
  for(int i=j;i<R.size();i++){
    z=i;
    b=(R[i]<=u);
    //cout<<" i="<<i<<" R="<<R[i]<<" u="<<u<<" true="<<b<<endl;
    if(R[i-1]<u&&u<=R[i]){
      event=i;
      break;
    }

  }
  //cout<<"z="<<z<<endl;

  //cout<<"\nevent="<<event<<endl;

  return event;
}

double updateTime(int R,double t,mt19937& mt_rand){
  double u=(double)mt_rand()/mt_rand.max();
  t+=-log(u)/R;

  return t;
}
