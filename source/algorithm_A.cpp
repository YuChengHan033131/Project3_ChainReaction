#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"

using namespace std;

/******************************************************
 * In your algorithm, you can just use the the funcitons
 * listed by TA to get the board information.(functions 
 * 1. ~ 4. are listed in next block)
 * 
 * The STL library functions is not allowed to use.
******************************************************/

/*************************************************************************
 * 1. int board.get_orbs_num(int row_index, int col_index)
 * 2. int board.get_capacity(int row_index, int col_index)
 * 3. char board.get_cell_color(int row_index, int col_index)
 * 4. void board.print_current_board(int row_index, int col_index, int round)
 * 
 * 1. The function that return the number of orbs in cell(row, col)
 * 2. The function that return the orb capacity of the cell(row, col)
 * 3. The function that return the color fo the cell(row, col)
 * 4. The function that print out the current board statement
*************************************************************************/
template <class T>
class queue{
    private:
        T **head;
        int _front=-1;
        int _back=-1;
        int _size;
    public:
    queue(){};
    queue(int size):_size(size){
        head = new T* [_size];
        for(int i=0;i<_size;i++){
            head[i]=NULL;
        }
    }
    void setSize(int size){
        _size=size;
        head = new T* [_size];
        for(int i=0;i<_size;i++){
            head[i]=NULL;
        }
    }
    T *front(){
        if(_front==-1){
            cout << "error! queue is empty" ;
        }
        return head[_front];
    }
    T *back(){
        if(_front==-1){
            cout << "error! queue is empty" ;
        }
        return head[_back];
    }
    void push(T *node){
        if(_front==-1){
            _front=0;
            _back=0;
        }else if((_back+1)%_size!=_front){
            _back=(_back+1)%_size;
        }else{
            increaseSize();
            _back=(_back+1)%_size;
        }
        head[_back]=node;
    }
    void increaseSize(){
        _size*=5/4+1;
        T **newHead = new T* [_size];
        for(int i=0;i<_size;i++){
            if(size()!=0){
                newHead[i]=front();
                pop();
            }else{
                _front=0;
                _back=i-1;
                break;
            }
        }
        delete(head);
        head=newHead;
    }
    void pop(){
        if(_front==-1){
            cout << "error!nothing to pop" << endl;
        }
        else if(_front==_back){
            _front=-1;
            _back=-1;
        }else{
            _front=(_front+1)%_size;
        }
    }
    void pull(){
        if(_front==-1){
            cout << "error!nothing to pull" << endl;
        }
        else if(_front==_back){
            _front=-1;
            _back=-1;
        }else{
            _back=(_back+_size-1)%_size;
        }
    }
    int size(){
        if(_front==-1){
            return 0;
        }else if(_front<=_back){
            return _back-_front+1;
        }else{
            return _back-_front+_size+1;
        }
       
    }
    void printAll(ofstream &of){
        if(_front==-1){
            cout << "error! nothing to print" << endl ;
            return ;
        }
       int temp=_front;
       while(1){
           of << head[temp]->_h() << " " << head[temp]->_w() << endl ;
           temp=(temp+1)%_size;
           if(temp==(_back+1)%_size){
               break;
           }
       }
    }
    void reset(){
        delete(head);
        _front=-1;
        _back=-1;
        delete(&_size);
    }
    void destroy(){
        while(_front!=-1){
            T *temp=head[_front];
            pop();
            delete(temp);
        }
    }
};
class Node{
    private:
        int row;
        int col;
    public:
        Node(int row,int col):row(row),col(col){}
        int _row(){
            return row;
        }
        int _col(){
            return col;
        }
        int stability(Board board){
            return board.get_capacity(row,col)-board.get_orbs_num(row,col);
        }
        int capacity(Board board){
            return board.get_capacity(row,col);
        }
        bool placeable(Board board,Player player){
            if(board.get_cell_color(row,col)==player.get_color()||
               board.get_cell_color(row,col)=='w'){
                   return true;
            }
            else{
                return false;
            }
        }
        bool invaded(Board board,Player player){
            char copColor;
            if(player.get_color()=='r'){
                copColor='b';
            }else{
                copColor='r';
            }
            Node *node=NULL;
            //up
            if(row>0){
                node = new Node(row-1,col);
                if(node->stability(board)==1&&board.get_cell_color(row-1,col)==copColor){
                    return true;
                }
            }
            //down
            if(row<ROW-1){
                node = new Node(row+1,col);
                if(node->stability(board)==1&&board.get_cell_color(row+1,col)==copColor){
                    return true;
                }
            }
            //left
            if(col>0){
                node = new Node(row,col-1);
                if(node->stability(board)==1&&board.get_cell_color(row,col-1)==copColor){
                    return true;
                }
            }
            //right
            if(col<COL-1){
                node = new Node(row,col+1);
                if(node->stability(board)==1&&board.get_cell_color(row,col+1)==copColor){
                    return true;
                }
            }
            return false;
        }
        bool invaded(Board board,char color){//detet player color!!
            Node *node=NULL;
            //up
            if(row>0){
                node = new Node(row-1,col);
                if(node->stability(board)==1&&board.get_cell_color(row-1,col)==color){
                    return true;
                }
            }
            //down
            if(row<ROW-1){
                node = new Node(row+1,col);
                if(node->stability(board)==1&&board.get_cell_color(row+1,col)==color){
                    return true;
                }
            }
            //left
            if(col>0){
                node = new Node(row,col-1);
                if(node->stability(board)==1&&board.get_cell_color(row,col-1)==color){
                    return true;
                }
            }
            //right
            if(col<COL-1){
                node = new Node(row,col+1);
                if(node->stability(board)==1&&board.get_cell_color(row,col+1)==color){
                    return true;
                }
            }
            return false;
        }
        bool CopNearby(Board board,Player player){
            char copColor;
            if(player.get_color()=='r'){
                copColor='b';
            }else{
                copColor='r';
            }
            //up
            if(row>0){
                if(board.get_cell_color(row-1,col)==copColor){
                    //cout << "up" << endl ;
                    //cout << row << "," << col << endl;
                    return true;
                }
            }
            //down
            if(row<ROW-1){
                if(board.get_cell_color(row+1,col)==copColor){
                    //cout << "down" << endl ;
                    //cout << row << "," << col << endl;
                    return true;
                }
            }
            //left
            if(col>0){
                if(board.get_cell_color(row,col-1)==copColor){
                    //cout << "left" << endl ;
                    //cout << row << "," << col << endl;
                    return true;
                }
            }
            //right
            if(col<COL-1){
                if(board.get_cell_color(row,col+1)==copColor){
                    //cout << "right" << endl ;
                    //cout << row << "," << col << endl;
                    return true;
                }
            }
            return false;
        }
        int influence(Board board,Player player){
            Board nextState=board;
            nextState.place_orb(row,col,&player);
            int boardPlayerCells=0,nextStatePlayerCells=0;
            for(int i=0;i<ROW;i++){
                for(int j=0;j<COL;j++){
                    if(board.get_cell_color(i,j)==player.get_color()){
                        boardPlayerCells+=1;
                    }
                    if(nextState.get_cell_color(i,j)==player.get_color()){
                        nextStatePlayerCells+=1;
                    }
                }
            }
            return nextStatePlayerCells-boardPlayerCells;
        }
};
void algorithm_A(Board board, Player player, int index[]){

    // cout << board.get_capacity(0, 0) << endl;
    // cout << board.get_orbs_num(0, 0) << endl;
    // cout << board.get_cell_color(0, 0) << endl;
    // board.print_current_board(0, 0, 0);
    queue <Node> q1(5),q2(5),q3(5),q4(5),q5(5),q6(5);
    
    for(int i=0;i<ROW;i++){
        for(int j=0;j<COL;j++){
            Node* node=new Node(i,j);
            if(node->stability(board)==1&&board.get_cell_color(i,j)==player.get_color()){
                if(node->invaded(board,player)){
                    q1.push(node);//repel
                    cout << "repel" << ":" << i << "," << j << endl ;

                }else if(node->CopNearby(board,player)){
                    cout << "attack" << ":" << i << "," << j << endl ;
                    q2.push(node);//attack
                }
            }else if(node->invaded(board,player)==false&&node->stability(board)!=1&&board.get_cell_color(i,j)=='w'){
                cout << "passive" << ":" << i << "," << j << endl ;
                q3.push(node);//passive
            }
            else if(board.get_cell_color(i,j)==player.get_color()&&node->invaded(board,player)==false&&node->stability(board)!=1){
                cout << "expand" << ":" << i << "," << j << endl ;
                q4.push(node);//expand
            }else if(node->invaded(board,player)&&board.get_cell_color(i,j)=='w'){
                cout << "hide" << ":" << i << "," << j << endl ;
                q5.push(node);//hide
            }else if(node->invaded(board,player)&&board.get_cell_color(i,j)==player.get_color()&&node->stability(board)!=1){
                cout << "worst" << ":" << i << "," << j << endl ;
                q6.push(node);//worst
            }
        }
    }
    //repel
    Node *bestChoice=NULL;
    if(q1.size()!=0){
        int MaxInfluence=-1;
        for(int i=0;i<q1.size();i++){
            Node *temp;
            temp=q1.front();
            q1.pop();
            q1.push(temp);
            int tempInfluence=temp->influence(board,player);
            if(tempInfluence>MaxInfluence){
                bestChoice=temp;
                MaxInfluence=tempInfluence;
            }
        }
        index[0]=bestChoice->_row();
        index[1]=bestChoice->_col();
        cout << "repel" << endl;
        return ;
    }
    
    //attack
    if(q2.size()!=0){
        cout << "attack!" ;
        int MaxInfluence=-1;
        for(int i=0;i<q2.size();i++){
            Node *temp=q2.front();
            q2.pop();
            q2.push(temp);
            int tempInfluence=temp->influence(board,player);
            cout << "tempInfluence:" <<tempInfluence << endl ;
            if(tempInfluence>MaxInfluence){
               bestChoice=temp;
                MaxInfluence=tempInfluence;
            }
        }
        index[0]=bestChoice->_row();
        index[1]=bestChoice->_col();
        cout << "attack" << endl;
        return ;
    }
    
    //passive
    if(q3.size()!=0){
        int MinCapacity=5;
        for(int i=0;i<q3.size();i++){
            Node *temp=q3.front();
            q3.pop();
            q3.push(temp);
            int tempCapacity=temp->capacity(board);
            if(tempCapacity<MinCapacity){
                bestChoice=temp;
                MinCapacity=tempCapacity;
            }  
        }
        index[0]=bestChoice->_row();
        index[1]=bestChoice->_col();
        cout << "passive" << endl;
        return ;
    }

    //expand
    if(q4.size()!=0){
        int MaxStability=0;
        int MaxInfluence=-1;
        for(int i=0;i<q4.size();i++){
            Node *temp=q4.front();
            q4.pop();
            q4.push(temp);
            int tempStability=temp->stability(board);
            if(tempStability>MaxStability){
                bestChoice=temp;
                MaxStability=tempStability;
            }else if(tempStability==1){
                int tempInfluence=temp->influence(board,player);
                if(tempInfluence>MaxInfluence){
                    bestChoice=temp;
                    MaxInfluence=tempInfluence;
                }
            }
        }
        index[0]=bestChoice->_row();
        index[1]=bestChoice->_col();
        cout << "expand" << endl;
        return ;
    }

    //hide
    if(q5.size()!=0){
        int MaxCpaacity=0;
        for(int i=0;i<q5.size();i++){
            Node *temp=q5.front();
            q5.pop();
            q5.push(temp);
            int tempCapacity=temp->capacity(board);
            if(tempCapacity>MaxCpaacity){
                bestChoice=temp;
                MaxCpaacity=tempCapacity;
            }
        }
        index[0]=bestChoice->_row();
        index[1]=bestChoice->_col();
        cout << "hide" << endl;
        return ;
    }

    //worst
    if(q6.size()!=0){
        int MaxCapacity=0;
        int MinCapacity=5;
        for(int i=0;i<q6.size();i++){
            Node *temp=q6.front();
            q6.pop();
            q6.push(temp);
            int tempStability=temp->stability(board);
            int tempCpacity=temp->capacity(board);
            if(tempStability==2&&temp->invaded(board,player.get_color())){
                if(tempCpacity<MinCapacity){
                    bestChoice=temp;
                    MinCapacity=tempCpacity;
                }
            }
            else if(MinCapacity==5&&tempCpacity>MaxCapacity){
                bestChoice=temp;
                MaxCapacity=tempCpacity;
            }
        }
        index[0]=bestChoice->_row();
        index[1]=bestChoice->_col();
        cout << "worst" << endl;
        return ;
    }
}