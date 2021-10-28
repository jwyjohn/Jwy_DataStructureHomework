#include<iostream>

using namespace std;

template <class Type>
class CircLL {

struct Node {
	Type val;
	Node* next;
	Node(Type x) : val(x), next(NULL) {};
	Node(Type x, Node* next) : val(x), next(next) {};
};
int N,M,S,K;

Node* head;

public:
	CircLL(int n, int m, int s, int k) : N(n), M(m), S(s), K(k) {
		head = new Node(-1);
		head->next = head;
		for (int i = n; i>=1; i--) {
			Node* node = new Node(i);
			node->next = head->next;
			head->next = node;
		};
		Node* tmp=head->next;
		while(tmp->next != head) tmp = tmp->next;
		tmp->next = head->next;
	};
	int showLLparm(){cout<<N<<" "<<M<<" "<<S<<" "<<K<<endl;}
	int printLL(){
		Node* cur = head;
		for (int i=0; i<=N*2; i++){
			cout<<cur->val<<", ";
			cur = cur->next;
		};
		cout<<endl;
		return 0;
	};
	int printLLS(){
                Node* cur = head->next;
                for (int i=0; i<K; i++){
                        cout<<cur->val<<" ";
                        cur = cur->next;
                };
                cout<<endl;
                return 0;
        };
	Node* accessLLnode(int k){
		Node* ret;
		int i=k;
		Node* cur = head;
                while(i>0){
			i--;
			cur = cur->next;
                };
		ret = cur;
                return ret;
	};
	int delLLnode(Node* k){
                Node* cur = head;
		Node* tmp = k;
		if (k==head->next) head->next = head->next->next;
                while(cur->next != k){
                        cur = cur->next;
                };
		cur->next = cur->next->next;
		delete tmp;
                return 0;

	};
	int runJoseph(){
		int n=N;
		int i=1,num=0;
		Node* cur = accessLLnode(S);
		Node* tmp;
		while (n>K){
			if (i==M) {
				i=1;
				num++;
				n--;
				cout<<"第"<<num<<"个死者的编号为："<<cur->val<<endl;
				delLLnode(cur);
				//printLL();
				//cout<<endl;
				cur = cur->next;
			 } else {
			 	i++;
				cur = cur->next;
			 };
		}
		return 0;
	}

};



int main(){
	//cout<<"Testing.."<<endl;
	int N,M,S,K;
	cout<<"请输入总人数N：";
	cin>>N;
	cout<<"请输入开始位置S：";
	cin>>S;
	cout<<"请输入死亡数字M：";
	cin>>M;
	cout<<"请输入剩余人数K：";
	cin>>K;
	cout<<endl;
	CircLL<int> list1(N,M,S,K);
	list1.runJoseph();
	//list1.delLLnode(list1.accessLLnode(S));
	cout<<"最后生还者为："<<endl;
	list1.printLLS();

	return 0;
}

