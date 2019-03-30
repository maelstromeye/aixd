#include <iostream>
using namespace std;
template <typename Key, typename Data> class List
{
	private:
		struct Node
		{
			public:
				Node* next;
				Key key;
				Data data;
				Node(){key=0; data=0; next=NULL;}
				Node(Key nkey, Data ndata){key=nkey; data=ndata; next=NULL;}
				void print(){cout<<key<<endl<<data<<endl;}	
		};
		Node* head;
		Node* gethead(){return head;}
	public:
		List() {head=NULL;}
		List(Key arrkey[], Data arrdata[], int i)
		{
			if(i<=0)
			{
				head=NULL;
				return;
			}
			if(!arrkey||!arrdata)
			{
				head=NULL;
				return;
			}
			int a=0;
			Node* nodeptr;
			head=new Node(arrkey[0], arrdata[0]);
			nodeptr=head;
			for(a=1; a<i; a++)
			{
				nodeptr->next=new Node(arrkey[a], arrdata[a]);
				nodeptr=nodeptr->next;
			}
		}
		List(List<Key, Data> &list)
		{
			Node* nodeptr=list.gethead(), *builder;
			if(!nodeptr)
			{
				this->head=NULL;
				return;
			}
			builder=new Node(nodeptr->key, nodeptr->data);
			head=builder;
			nodeptr=nodeptr->next;
			for(;nodeptr!=NULL;nodeptr=nodeptr->next)
			{
				builder->next=new Node(nodeptr->key, nodeptr->data);
				builder=builder->next;
			}			
		}
		~List(){destroy();}
		template<typename K, typename D>
		List<K, D> operator=(List<K, D> &list)
		{
			
		}
		Data operator[](int i)
		{
			int s=size();
			if(i>=s) return 0;
			Node* nodeptr=head;
			for(int c=0;c<i; c++, nodeptr=nodeptr->next);
			return nodeptr->data;
		}
		int size()
		{
			Node* nodeptr=head;
			int i=0;
			for(;nodeptr!=NULL; nodeptr=nodeptr->next, i++);
			return i;
		}
		void print()
		{
			if(!head) return;
			int i=0;
			Node* nodeptr=head;
			for(;nodeptr!=NULL; nodeptr=nodeptr->next)
			{
				cout<<endl<<nodeptr->key<<endl<<nodeptr->data<<endl;
			}
		}
		void putFront(Key k, Data d)
		{
			Node* nodeptr=head;
			head=new Node(k, d);
			head->next=nodeptr;
		}
		void putBack(Key k, Data d)
		{
			if (!head)
			{
				head=new Node(k, d);
				return;
			}
			Node* nodeptr=head;
			for(;nodeptr->next!=NULL; nodeptr=nodeptr->next);
			nodeptr->next=new Node(k, d);
		}
		void remove(Key k, Node* &nodeptr)
		{
			if(!nodeptr) return;
			Node* copy;
			bool flag=false;
			if(nodeptr->key==k)
			{
				copy=nodeptr;
				nodeptr=nodeptr->next;
				delete copy;
				flag=true;
			}
			if(flag) remove(k, nodeptr);
			else remove(k, nodeptr->next);
		}
		void destroy()
		{
			Node* nodeptr=head, *helper;
			while(nodeptr!=NULL)
			{
				helper=nodeptr->next;
				delete nodeptr;
				nodeptr=helper;
			}
			head=NULL;
		}
		void insert(int i, Key k, Data d)
		{
			int s=size();
			if(i>=s) return;
			Node*
		}
		Data back()
		{
			if(!head) return 0;
			Node* nodeptr=head;
			for(;nodeptr->next!=NULL; nodeptr=nodeptr->next);
			return nodeptr->data;	
		}
		Data front() {return head->data;}
		void remove(Key k){remove(k, head);}
		bool isempty(){if (!head) return true;return false;}
};
template<typename Key, typename Data> void stresstest(List<Key, Data> &list);
int main()
{
	int i=1;
	int arr1[]={7, 6, 1, 3, 1, 1, 232, 344, 1, 4};
	int arr2[]={2, 4, 5, 1 ,1, 0, 2, 33, 4 ,5 , 5, 5};
	List <int, int> list0(arr1, arr2, 10);
	stresstest(list0);
	List <int, int> list1(NULL, NULL, 1);
	stresstest(list1);
}
template<typename Key, typename Data> void stresstest(List<Key, Data> &list)
{
	List<Key, Data> copy(list);
	cout<<"empty: "<<list.isempty()<<endl<<"size: "<<list.size()<<endl;
	list.print();
	cout<<"---------------"<<endl;
	copy.print();
	cout<<"--------------------"<<endl;
	list.remove(6);
	list.remove(1);
	list.print();
	cout<<"-------------------"<<endl;
	list.putBack(800,2800);
	list.putFront(800,2890);
	list.print();
	cout<<"-------------------"<<endl;
	copy().print();
	cout<<"--------------"<<endl;
	cout<<list.front()<<endl<<list.back()<<endl;
}

