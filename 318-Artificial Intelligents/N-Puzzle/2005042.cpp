#include<bits/stdc++.h>
#include "../../dbg.h"
using namespace std;
int expanded=0,explored=0;
int inversionCount(vector<vector<int>> &block){
    int n=block.size();
    int inversion_count=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(!block[i][j]) continue;
            int k,l;
            if(j==n-1){
                k=i+1;
                l=0;
            }
            else{
                k=i;
                l=j+1;
            }
            for(;k<n;k++){
                for(;l<n;l++){
                    //dbg(block[i][j],block[k][l]);
                    //dbg(block);
                    
                    if(block[k][l] && block[i][j]>block[k][l])
                        inversion_count++;
                    //dbg(inversion_count);
                }
                l=0;
            }
        }
    }
    return inversion_count;
}
bool solvable(vector<vector<int>> &block){
    int n = block.size();
    int inversion_count=inversionCount(block);
    //dbg(inversion_count);
    if(n%2!=0){
        
        return inversion_count%2==0;
    }
    else{
        int k=0,l=0,flag=0;
        //dbg(block);
        for(;k<n;k++){
            for(;l<n;l++){
                if(!block[k][l]){
                    //dbg(k,l);
                    flag=1;
                    break;
                }
            }
            l=0;
            //dbg(k,l);
            if(flag) break;
        }
        //dbg(k,l);
        if((inversion_count+(n-k-1))%2==0) return true;
        return false;
    }
}
int manhattan_dist(vector<vector<int>> &block){
    //dbg(block);
    int dist=0,n=block.size();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(block[i][j]){
                int row_shd_be=(block[i][j]-1)/n;
                int col_shd_be=((block[i][j]-1)%n);
                //dbg(i,j,row_shd_be,col_shd_be);
                dist+=abs(i-row_shd_be)+abs(j-col_shd_be);
            }
        }
    }
    //dbg(dist);
    return dist;
}
int hamming_dist(vector<vector<int>> &block){
    int dist=0,n=block.size();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(block[i][j] && block[i][j]!=i*n+j+1) dist++;
        }
    }
    return dist;
}
void print_block(vector<vector<int>> &block){
    int n=block.size();
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(block[i][j])
                cout << block[i][j] << " ";
            else cout<<"* ";
        }
        cout << endl;
    }
}
class Node{
    public:
    Node* parent;
    int dist;
    int move;
    vector<vector<int>> block;
    pair<int,int> co_ordinate;
    function<int (vector<vector<int>> &)> heuristicDist;
    Node(vector<vector<int>> &block,function<int (vector<vector<int>> &)> hd,Node *p=NULL){
        this->block=block;
        this->parent=p;
        this->heuristicDist=hd;
        dist=heuristicDist(block);
        move= parent==NULL? 0 : parent->move+1;
        if(parent==NULL){
            for(int i=0;i<block.size();i++){
                for(int j=0;j<block.size();j++){
                    if(!block[i][j]){
                        co_ordinate.first=i;
                        co_ordinate.second=j;
                    }
                }
            }
        }
    }
    int cost(){
        return dist+move;
    }
};
Node* makeMove(Node* node,int dir){
    //dir 0 = up ,1=right, 2 = down, 3=left
    int n=node->block.size();
    int x=node->co_ordinate.first;
    int y=node->co_ordinate.second;
    Node* temp;
    //dbg(x,y,dir);
    if((x==0 && dir==0 )|| (x ==n-1 && dir == 2) || (y==0 && dir ==3) || (y==n-1 && dir ==1)){
        //dbg(x,n,y);
        return NULL;
    }
    else{
        vector<vector<int>> new_block(n,vector<int>(n,0));
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                new_block[i][j]=node->block[i][j];
            }
        }
        if(dir==0){
            new_block[x][y]=new_block[x-1][y];
            new_block[x-1][y]=0;
            temp=new Node(new_block,node->heuristicDist,node);
            temp->co_ordinate.first=x-1;
            temp->co_ordinate.second=y;
        }
        else if(dir==1){
            new_block[x][y]=new_block[x][y+1];
            new_block[x][y+1]=0;
            temp=new Node(new_block,node->heuristicDist,node);
            temp->co_ordinate.first=x;
            temp->co_ordinate.second=y+1;
        }
        else if(dir==2){
            new_block[x][y]=new_block[x+1][y];
            new_block[x+1][y]=0;
            temp=new Node(new_block,node->heuristicDist,node);
            temp->co_ordinate.first=x+1;
            temp->co_ordinate.second=y;
        }
        else if(dir==3){
            new_block[x][y]=new_block[x][y-1];
            new_block[x][y-1]=0;
            temp=new Node(new_block,node->heuristicDist,node);
            temp->co_ordinate.first=x;
            temp->co_ordinate.second=y-1;
        }
        //dbg(temp->block);
        return temp;
    }
}
void printTree(Node *node){
    if(node==NULL){
        return;
    }
    printTree(node->parent);
    print_block(node->block);
    cout<<endl;
}
void solve(vector<vector<int>> &block,function<int (vector<vector<int>> &)> heuristicDist){
    
    priority_queue<pair<int, Node*>,vector<std::pair<int, Node*>>,greater<pair<int, Node*>>> pq;
    Node* head=new Node(block,heuristicDist);
    //dbg(head->block);
    //dbg(head->cost());
    pair<int,Node*> base(head->cost(),head);
    set<vector<vector<int>>> visited;
    Node* result;
    pq.push(base);
    while (true)
    {
        pair<int,Node*> top=pq.top();
        pq.pop();
        if(top.second->dist==0){
            cout<<"Total move required : "<<top.second->cost()<<endl;
            result=top.second;
            break;
        }
        expanded++;
        for(int i=0;i<4;i++){
            Node *temp;
            //dbg(i);
            temp=makeMove(top.second,i);
            //assert(temp!=NULL);
            if(temp!=NULL){
                if(visited.find(temp->block)==visited.end()){
                    //dbg(i,temp->block,temp->cost(),temp->dist);
                    pair<int,Node*> new_pair(temp->cost(),temp);
                    pq.push(new_pair);
                    explored++;
                    visited.insert(temp->block);
                }
            }
        }
        //break;
    }
    printTree(result);
    cout<<"Expanded Nodes : "<<expanded<<'\n';
    cout<<"Explored Nodes : "<<explored<<'\n';
}

int main(){
    int n;
    cin >> n;
    vector<vector<int>> block(n,vector<int> (n,0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            string a;
            cin>>a;
            if(a=="*")
                block[i][j]=0;
            else
                block[i][j]=stoi(a);
        }
    }
    if(!solvable(block)){
        cout << "Not Solvable" << endl;
        return 0;
    }
    cout<<"1 for Manhattan 2 for Hamming distance\n";
    int choice;
    function<int (vector<vector<int>> &)> heuristicDist;
    cin>>choice;
    if(choice == 1){
        heuristicDist = manhattan_dist;
    }
    else if(choice == 2){
        heuristicDist = hamming_dist;
    }
    solve(block,heuristicDist);
    return 0;
}