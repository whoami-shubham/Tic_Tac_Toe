#include<bits/stdc++.h>
using namespace std;

vector<pair<int,string> >valid_moves;
vector<bool>player(10,false);
vector<bool>computer(10,false);
int moves = 0;
bool play=true;
string P="O";
string C="X";
bool iWon();
void GameOver(string s);
int isWinning(vector<bool>player);
void block_winning_path(int index);
void valid_move();
void player_move();
void computer_move();
void choose_symbol();
bool isvalid_move(int n);
void print_bord();
void init_move();
int main(){
	for(int i=0;i<10;i++){
		valid_moves.push_back({i,"*"});
	}
    
    print_bord();
    char c='c';
    int chance = 0;

    do{
    	if(moves==0){
    		choose_symbol();
    	}
        if(chance){
        	computer_move();
        	print_bord();
        	chance = 0;
        	cout<<endl;
        }
        else{
        	player_move();
        	print_bord();
        	chance = 1;
        	cout<<endl;
        }
        if(!play){
        	cout<<" Do You Want to Play Again(y/n) ?";
            cin>>c;
            if(c=='y' || c=='Y'){
            	play = true;
            	moves=0;
            	chance =0;
            	init_move();
            }
        }
        moves++;
       for(int i=1;i<10;i++){
     	cout<<player[i]<<" ";
       }
      cout<<endl;

    }while(play);

}

void player_move(){
	
	if(moves==9){
		GameOver("No one Won");
	}
	int move;
	do{
	cout<<"choose A valid move from 1 2 3 4 5 6 7 8 : ";
    cin>>move;
    }while(!isvalid_move(move));
    // valid_moves[move].second = P;
    // player[move] = true;
    if(iWon()){
    	GameOver("You Won");
    }

}

void computer_move(){
	
	if(moves==9){
		GameOver("No one Won");
	}
	int index=isWinning(player);
	//cout<<"index : "<<index<<endl;
	if(index!=-1){
		block_winning_path(index);
		return;
	}
	index=isWinning(computer);
	//cout<<"index : "<<index<<endl;
	 if(index!=-1){
		computer[index] = true;
	    valid_moves[index].second = C;
	    cout<<" computer's move is "<<index<<endl;
		GameOver("You Loose !");
		return;
	}
	else{
		valid_move();
	}
}
int isWinning(vector<bool>player){
	for(int i=1;i<10;i+=3){   // left to right
		int count=0;
		for(int j=i;j<i+3;j++){
           if(player[j]){
           	count++;
           }
		}
		if(count==2){
			for(int j=i;j<i+3;j++){
		           if(!player[j] && valid_moves[j].second=="*"){
		           	  return j;
		           }
		      }
		}
	}
	for(int i=1;i<=3;i++){  // upside down
		int count=0;
		for(int j=0;j<=6;j+=3){
           if(player[i+j]){
           	count++;
           }
		}
		if(count==2){
		    
		    for(int j=0;j<=6;j+=3){
		           if((!player[i+j]) && valid_moves[j].second=="*"){
		           	  return i+j;
		           }
		      }
		}
	}
	if((player[1] + player[5] + player[9]) == 2){
       if(!player[1] && valid_moves[1].second=="*"){
       	  return 1;
       }
       else if(!player[5]  && valid_moves[5].second=="*"){
       	  return 5;
       }
       else if(!player[9] && valid_moves[9].second=="*"){
       	   return 9;
       }
	}
	if((player[3] + player[5] + player[7])==2){
		if(!player[3] && valid_moves[3].second=="*"){
       	  return 3;
       }
       else if(!player[5] && valid_moves[5].second=="*"){
       	  return 5;
       }
       else if(!player[7] && valid_moves[7].second=="*"){
       	   return 7;
       }
	}
	return -1;
}
void block_winning_path(int index){
    computer[index] = true;
    valid_moves[index].second = C;
    cout<<" computer's move is "<<index<<endl;
};
void valid_move(){
     for(int i=1;i<10;i++){
     	if(valid_moves[i].second == "*" && !player[i]){
     		computer[valid_moves[i].first] = true;
     		valid_moves[i].second = C;
     		cout<<" computer's move is "<<i<<endl;
     		break;
     	}
     }
}
void GameOver(string s){
	cout<<" GameOver "<<s<<endl;
	play = false;
}

void choose_symbol(){
	cout<<"Choose Your Symbol \'X\' or \'O\' "<<endl;
	cin>>P;
	if(P=="X" || P=="x"){
		P = "X";
		C = "O";
	}
	else{
		C = "X";
		P = "O";
	}
}
void print_bord(){
	for(int i=1;i<=9;i++){
		if(i==1){
			cout<<"--------------"<<endl;
		}
		
			
		  if(i%3==0){
				cout<<" | "<<valid_moves[i].second<<" | ";
			}
			else{
				cout<<"| "<<valid_moves[i].second<<" ";
			}
		    if(i%3==0){
		     cout<<endl;
		   }
		    if(i==9){
			cout<<"--------------"<<endl;
		}
	}
}
void init_move(){
	
    for(int i=0;i<10;i++){
    	computer[i]=false;
    	player[i] = false;
    }
    valid_moves.clear();
    for(int i=0;i<10;i++){
		valid_moves.push_back({i,"*"});
	}
}

bool isvalid_move(int n){
	if(n>0 && n<10){
		if((!computer[n]) && (valid_moves[n].second=="*")){
			valid_moves[n].second=P;
            player[n] = true;
			return true;
		}
	}
	return false;
}
bool iWon(){
	for(int i=1;i<10;i+=3){   // left to right
		int count=0;
		for(int j=i;j<i+3;j++){
           if(player[j]){
           	count++;
           }
		}
		if(count==3){
			return true;
		}
	}
	for(int i=1;i<=3;i++){  // upside down
		int count=0;
		for(int j=0;j<=9;j+=3){
           if(player[i+j]){
           	count++;
           }
		}
		if(count==3){
		    return true;
		}
	}
	if((player[1] + player[5] + player[9]) == 3){
        return true;
	}
	if((player[3] + player[5] + player[7])==3){
		return true;
	}
	return false;
}
