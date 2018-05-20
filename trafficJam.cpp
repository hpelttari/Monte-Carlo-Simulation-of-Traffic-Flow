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

int main(){

  vector<bool> road =createInitialConfiguration(50, 100);
  vector<int> jumpRates=createListOfJumpRates(road);
  printTraffic(road);
  road=moveCarOnRoad(1,road);
  cout<<"\n";
  printTraffic(road);
  cout<<"\n";
  jumpRates=updateJumpRates(jumpRates,road,2);
  cout<<"\n";
  for(int i=0;i<jumpRates.size();i++){
    cout<<jumpRates[i]<<endl;
  }
  cout<<"\n";
  moveCarOnRoad(5, road);
  cout<<"ww"<<endl;
  jumpRates=updateJumpRates(jumpRates,road,6);
  cout<<"zz"<<endl;
  cout<<"\n";
  printTraffic(road);
  cout<<"\n";
  cout<<"kk"<<endl;
  for(int i=0;i<jumpRates.size();i++){
    cout<<jumpRates[i]<<endl;
  }
  
  return 0;
}

vector<bool> createInitialConfiguration(int N, int L){
  double density = (double)N/L;
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
  for(int i=0;i<road.size();i++){
    jumpRates[i]=0;
    if(road[i]==true){
      int j=i+1;
      int f=0;
      while(j<road.size()){
	if(road[j]==true){
	  break;
	}
	f++;
	jumpRates[i]=f;
	j++;
      }
    }
  }
  return jumpRates;
}

vector<int> updateJumpRates(vector<int> jumpRates,vector<bool> road, int car){
  jumpRates[car-1]=0;
  /*
  int f=0;
  for(int i=indexOfCarMoved+1;i<road.size();i++){
    if(road[i]==true){
      break;
    }
    f++;
  }
  jumpRates[indexOfCarMoved]=f;
  f=0;
  int carBefore;
  for(int i=indexOfCarMoved-1;i>=0;i--){
    
    if(road[i]==true){
      break;
    }
    carBefore=indexOfCarMoved-1;
    f++;
  }
  if(carBefore!=0){
  jumpRates[carBefore]=f;
   cout<<"lol"<<endl;
  } else if(road[0]==true){
    jumpRates[carBefore]=f;
  } else{
    jumpRates[carBefore]=0;
    }*/
  int nextCar=findIndexOfNextCar(road, car);
  int previousCar=findIndexOfPreviousCar(road, car);
  if(nextCar>car){
    jumpRates[car]=nextCar-car-1;
  } else{
    jumpRates[car]=(road.size()-car-1)+nextCar;
  }
  if(previousCar>car){
    jumpRates[previousCar]=car-previousCar-1;
  }else{
    jumpRates[previousCar]=(road.size()-previousCar-1)+car;
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
  } else{
    cout<<"Can't move the car"<<endl;
  }

  return road;
}
