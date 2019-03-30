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
		List<Key, Data> operator=(List<Key, Data> &list)
		{
			Node* nodeptr=list.gethead(), *builder;
			if(!nodeptr)
			{
				this->head=NULL;
				return *this;
			}
			builder=new Node(nodeptr->key, nodeptr->data);
			head=builder;
			nodeptr=nodeptr->next;
			for(;nodeptr!=NULL;nodeptr=nodeptr->next)
			{
				builder->next=new Node(nodeptr->key, nodeptr->data);
				builder=builder->next;
			}	
			return *this;
		}
		Data operator[](int i)
		{
			int s=size();
			if(i>s) i=i%s;
			if(i<0) return 0;
			Node* nodeptr=head;
			for(int c=0;c<i; c++, nodeptr=nodeptr->next);
			return nodeptr->data;
		}
		Key getkey(int i)
		{
			int s=size();
			if(i>s) i=i%s;
			if(i<0) return 0;
			Node* nodeptr=head;
			for(int c=0;c<i; c++, nodeptr=nodeptr->next);
			return nodeptr->key;
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
		void print(Key k)
		{
			Node* nodeptr=head;
			for(;nodeptr!=NULL; nodeptr=nodeptr->next)
			{
				if(nodeptr->key==k) 
				{
					cout<<nodeptr->data<<endl;
				}
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
			Node* nodeptr=head;
			int s=size();
			if(i>s||i<0) return;
			if(i==0)
			{
				nodeptr=head;
				head=new Node(k, d);
				if(s) head->next=nodeptr;
				return;
			}
			Node* helper;
			for(int c=0;c<i-1; c++, nodeptr=nodeptr->next);
			helper=nodeptr->next;
			nodeptr->next=new Node(k, d);
			nodeptr->next->next=helper;
		}
		void popfront()
		{
			if(!head) return;
			Node* nodeptr=head;
			head=nodeptr->next;
			delete nodeptr;
		}
		void popback()
		{
			if(!head) return;
			if(!head->next) 
			{
				delete head;
				head=NULL;
			}
			Node* nodeptr=head;
			for(;nodeptr->next->next!=NULL;nodeptr=nodeptr->next);
			delete nodeptr->next;
			nodeptr->next=NULL;
		}
		Data back()
		{
			if(!head) return 0;
			Node* nodeptr=head;
			for(;nodeptr->next!=NULL; nodeptr=nodeptr->next);
			return nodeptr->data;	
		}
		Data front() {if(!head) return 0; return head->data;}
		void remove(Key k){remove(k, head);}
		bool isempty(){if (!head) return true; return false;}
};
template<typename Key, typename Data> void stresstest(List<Key, Data> &list);
template<typename Key, typename Data> List<Key, Data>
produce(const List<Key, Data> &l1, int start1, int length1, const List<Key, Data> &l2, int start2, int length2, int limit) const
{
	Key karr[limit];
	Data darr[limit];
	bool flag=true;
	int i=0, j=0, k=0;
	for(i=0;i<limit;i++)
	{
		if(i%(length1+length2)>length1)
		{
			karr[i]=l2.getkey(start2+i);
			darr[i]=l2[start2+i];
		}
		else
		{
			karr[i]=l1.getkey(start1+i);
			darr[i]=l1[start1+i];
		}
	}
	List<Key, Data> list(karr, darr, limit);
	return list;
}
template<typename Key, typename Data>
void stresstest(List<Key, Data> &list)
{
	List<Key, Data> copy;
	cout<<"empty: "<<list.isempty()<<endl<<"size: "<<list.size()<<endl;
	list.print();
	cout<<"---------------"<<endl;
	copy.print();
	cout<<"--------------------"<<endl;
	list.remove(6);
	list.remove(2);
	list.print();
	cout<<"-------------------"<<endl;
	cout<<"--------------"<<endl;
	cout<<list.front()<<endl<<list.back()<<endl;
	cout<<"----------------"<<endl;
	copy=list;
	list.popback();
	list.popback();
	list.popback();
	cout<<"----------------------------"<<endl;
	copy.print();
}
int main()
{
	int i=1;
	int arr1[]={7, 6, 1, 3, 1, 1, 232, 344, 1, 4};
	int arr2[]={2, 4, 5, 1 ,1, 0, 265, 353, 4 ,5};
	int arr3[]={0, 9, 4, 2, 8, 5, 999, 169, 7, 9};
	int arr4[]={0, 9, 5, 3, 2, 3, 298, 875, 2, 3};
	List <int, int> list0(arr1, arr2, 10);
	//stresstest(list0);
	List <int, int> list1(arr3, arr4, 10);
	produce(list0, 0, 3, list1, 0, 5, 19);
	//stresstest(list1);
}
