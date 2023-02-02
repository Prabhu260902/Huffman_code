#include<bits/stdc++.h>
using namespace std;

struct node{
	char data;
	int freq;
	node* left;
	node* right;
	node(char ch,int f){
		data=ch;
		freq=f;
		left=right=NULL;
	}
};

//encode function
map<char,string>ans;
void encode(node* root,string t){
	if(root==NULL) return ;
	if(root->data!='$') ans[root->data]=t;
	encode(root->left,t+"0");
	encode(root->right,t+"1");
	return ;
}

//decoding function
string orginal;
void decode(node* temp,node* root,vector<bool>st,int ind){
	if(ind>=st.size()) {
		orginal+=temp->data;
		return ;
	}
	if(temp->left==NULL and temp->right==NULL){
		orginal+=temp->data;
		if(st[ind]) decode(root,root,st,ind);
		else decode(root,root,st,ind);
	}
	else{
	if(st[ind]) decode(temp->right,root,st,ind+1);
	else decode(temp->left,root,st,ind+1);
	}
	
}


int main(){
	map<char,int>mm;
	string s; 
	getline(cin, s);
	for(auto i:s) mm[i]++;
	priority_queue<pair<int,node*>,vector<pair<int,node*>>,greater<pair<int,node*>>>mp;
	for(auto i:mm){
		node* temp=new node(i.first,i.second);
		mp.push({i.second,temp});
	}
	while(mp.size()>1){
		node* temp1=mp.top().second;
		mp.pop();
		node* temp2=mp.top().second;
		mp.pop();
		node* root=new node('$',temp1->freq+temp2->freq);
		root->left=temp1;
		root->right=temp2;
		mp.push({temp1->freq+temp2->freq,root});
	}

	encode(mp.top().second,"");  //encode function

	string st="";
	for(auto i:s){
		st+=ans[i];
	}
	int a=st.size();
	vector<bool>v(a);
	for (int i = 0; i < a; ++i) {
	  v[i] = (st[i] == '1');
	}
	cout<<st<<endl;



	orginal="";
	decode(mp.top().second,mp.top().second,v,0);
	cout<<orginal<<endl;
}