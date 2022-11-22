/*
Tên tệp: XO.cpp
3x3 tic tac toe

-------------
|   |   |   |
-------------
|   |   |   |
-------------
|   |   |   |
-------------

Phiên bản 1
1. AI engine
-Trạng thái: vector<vector<char>> (3x3)
-Màn hình
-Kiểm tra tính kết thúc trò chơi
-Tính điểm các trạng thái
	+Điểm trạng thái cuối cùng
	+Không phải điểm trạng thái cuối cùng
- Nước đi hợp lí
	+ Phát hiện nước đi hiện tại
	+ Tính toán các nước đi hợp lí
-Tính toán nước đi tốt nhất

2. Giao diện người dùng
-Chọn x hoặc o
-Đầu vào tọa độ di chuyển bắt đầu từ 0
-Báo cáo nếu di chuyển bất hợp lí (sai)
-Kết quả khi trò chơi kết thúc
-Xuất ra các bước đi hiện tại
-Xuất ra di chuyển của máy
*/
#include<bits/stdc++.h>
using namespace std;
// 1. AI engine
// Trạng thái: vector<vector<char>> (3x3)
typedef vector<vector<char>> State;

// Màn hình
// input: board
// output: in ra màn hình
/*
-------------
|   |   |   |
-------------
|   |   |   |
-------------
|   |   |   |
-------------
*/
void printBoard(State board)
{
	cout<<" -------------"<<endl;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			cout<<" | "<<board[i][j];
		}
		cout<<" |"<<endl<<" -------------"<<endl;
	}
}

// Kiểm tra tính kết thúc nước đi của trò chơi
char NextPlayer(State choose)
{
	int countX=0,countO=0;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(choose[i][j]=='x') countX++;
			else if(choose[i][j]=='o') countO++;
		}
	}
	if(countX==countO) return 'x';
	else return 'o';
}

State play(State choose,int i,int j,char player)
{
	State NewState=State(3,vector<char>(3,' '));
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			NewState[i][j]=choose[i][j];
		}
	}
	NewState[i][j]=player;
	return NewState;
}

vector<State>NextState(State choose)
{
	char nextPlayer=NextPlayer(choose);
	vector<State> state;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(choose[i][j]==' '){
				State nextState=play(choose,i,j,nextPlayer);
				state.push_back(nextState);
			}
		}
	}
	return state;
}

// Tính điểm các trạng thái
	// Điểm trạng thái cuối cùng
	// Không phải điểm trạng thái cuối cùng
bool CheckRow(State choose)
{	
	// Kiểm tra hàng
	for(int i=0;i<3;i++)
		if(choose[i][0]==choose[i][1] && choose[i][0]==choose[i][2] && choose[i][0]!=' ') return true;
	// Kiểm tra cột
	for(int i=0;i<3;i++)
		if(choose[0][i]==choose[1][i] && choose[0][i]==choose[2][i] && choose[0][i]!=' ') return true;
	// Kiểm tra đường chéo
	if(choose[0][0]==choose[1][1] && choose[0][0]==choose[2][2] && choose[0][0]!=' ') return true;
	if(choose[0][2]==choose[1][1] && choose[0][2]==choose[2][0] && choose[0][2]!=' ') return true;
	// Kiểm tra tất cả các ô
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(choose[i][j]==' ') return false;
		}
	}
	return true;
}
int ScoreRow(State choose)
{
	// Kiểm tra hàng
	for(int i=0;i<3;i++)
		if(choose[i][0]==choose[i][1] && choose[i][0]==choose[i][2] && choose[i][0]!=' ')
			return choose[i][0]=='x' ? 1:-1;
	// Kiểm tra cột
	for(int i=0;i<3;i++)
		if(choose[0][i]==choose[1][i] && choose[0][i]==choose[2][i] && choose[0][i]!=' ')
			return choose[0][i]=='x' ? 1:-1;
	// Kiểm tra đường chéo
	if(choose[0][0]==choose[1][1] && choose[0][0]==choose[2][2] && choose[0][0]!=' ')
		return choose[0][0]=='x' ? 1:-1;
	if(choose[0][2]==choose[1][1] && choose[0][2]==choose[2][0] && choose[0][2]!=' ')
		return choose[0][2]=='x' ? 1:-1;
	return 0;
}

// Nước đi hợp lí
	// Phát hiện nước đi hiện tại
	// Tính toán các nước đi hợp lí
pair<int, State> Score(State choose)
{
	if(CheckRow(choose)){
		return make_pair(ScoreRow(choose), choose);
	}
	char player=NextPlayer(choose);
	vector<State> state=NextState(choose);
	int bestScore=-10;
	State bestState;
	for(State x: state){
		pair<int,State> y=Score(x);
		int score=y.first;
		if(player=='x'){
			if(bestScore<score||bestScore==-10){
				bestScore=score;
				bestState=x;
			}
		}else{
			if(bestScore>score||bestScore==-10){
				bestScore=score;
				bestState=x;
			}
		}
	}
	return make_pair(bestScore,bestState);
}

// Tính toán nước đi tốt nhất
pair<int,int> ComputerPlay(State choose)
{
	pair<int,State>y=Score(choose);
	int score=y.first;
	State newState=y.second;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(newState[i][j]!=choose[i][j]) return make_pair(i,j);
		}
	}
	return make_pair(-1,-1);
}

// 2. Giao diện người dùng
int main()
{
	State choose = State(3,vector<char>(3, ' '));
	char Player='.',NowPlayer='x';
	// Chọn x hoặc o
	cout<<"Chon nguoi choi cua ban (x or o): ";
	cin>>Player;
	cout<<"Ban chon "<<Player<<endl;

	printBoard(choose);
	while(true){
		int i=-1,j=-1;
		// In ra màn hình các bước đi hiện tại
		// In ra màn hình các bước di chuyển của máy
		if(Player==NowPlayer){
			// Đầu vào tọa độ di chuyển bắt đầu từ 0
			// Báo cáo nếu di chuyển bất hợp lí (sai)
			cout<<"Nhap nuoc di cua ban:";
			cin>>i>>j;
			cout<<"Ban chon ("<<i<<", "<<j<<")"<<endl;
			if(i<0||j<0||i>2||j>2) cout<<"Nhap sai!!!"<<endl;
		}else{
			pair<int,int>move=ComputerPlay(choose);
			i=move.first;
			j=move.second;
			cout<<"May tinh chon ("<<i<<", "<<j<<")"<<endl;
		}
		choose=play(choose,i,j,NowPlayer);
		printBoard(choose);
		// Kết quả khi trò chơi kết thúc
		// Phát hiện người chiến thắng hoặc hòa
		NowPlayer=NowPlayer=='x'?'o':'x';
		if(CheckRow(choose)){
			int score=ScoreRow(choose);
			if(score>0){
				cout<<"x won - o lost"<<endl;
			}else if(score<0){
				cout<<"x lost - o won"<<endl;
			}else{
				cout<<"A draw"<<endl;
			}
			break;
		}
	}
	return 0;
}
