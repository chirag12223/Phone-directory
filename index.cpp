#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class TrieNode {
    public:
    char data;
    TrieNode *children[26];
    bool isTerminal;
    TrieNode(char ch){
        data=ch;
        for(int i=0;i<26;i++){
            children[i]=NULL;
        }isTerminal=false;
    }
     
};
class  Trie{
    public:
    TrieNode*root;

    Trie(){
        root=new TrieNode('\0');
    }
    void insert(TrieNode*root,string word){
        if(word.length()==0){
            root->isTerminal=true;
            return;
        }char ch=word[0];
        TrieNode*child;
        int c=ch-'a';
        if(root->children[c]!=NULL){
            child=root->children[c];
        }else{
            child=new TrieNode(ch);
            root->children[c]=child;
        }int n=word.length();
        insert(child,word.substr(1));
    }
    bool search(TrieNode*root,string word){
        if(word.length()==0 ){
            if(root->isTerminal==true){
                return true;
            }return false;
        }
        int c=word[0]-'a';
        if(root->children[c]==NULL){
            return false;
        }else{
            return search(root->children[c],word.substr(1));
        }
    }
    void del(TrieNode*root,string word){
        if(word.length()==0 ){
            root->isTerminal=false;
        }
        int c=word[0]-'a';
        del(root->children[c],word.substr(1));
    }
    void in(string word){
        return insert(root,word);
    }bool sear(string word){
        return search(root,word);
    }void de(string word){
        return del(root,word);
    }
};

int main(){
    Trie*t=new Trie();
    cout<<"HI, WELCOME TO MY PHONE DIRECTORY";
    cout<<"1->Insert"<<endl<<"2->delete"<<endl<<"3->search"<<"4->update"<<endl;
    int n;
    cin>>n;
    map<string,string>mp;
    while(1){
        if(n==-1){
            break;
        }if(n==1){
            string word;
            cin>>word;
            string number;
            cin>>number;
            mp[word]=number;
            t->in(word);
            cout<<t->sear(word);
        }if(n==2){
            string word;
            cin>>word;
            if(t->sear(word)){
                mp.erase(mp.find(word));
                t->de(word);
            }
        }if(n==3){
            string word;
            cin>>word;
            if(mp.find(word)!=mp.end()){
                cout<<mp[word];
            }
        }if(n==4){
            string word;
            cin>>word;
            if(t->sear(word)){
                mp.erase(mp.find(word));
                t->de(word);
            }string w1;
            cin>>w1;
            string number;
            cin>>number;
            mp[w1]=number;
            t->in(w1);
        }cin>>n;
        
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
