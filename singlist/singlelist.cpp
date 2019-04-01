#include <iostream>
using namespace std;
template <typename Key, typename Data> class List	//singly linked list
{
	private:
		struct Node	//list's node
		{
			Node* next;
			Key key;
			Data data;
			Node(){key=0; data=0; next=NULL;}
			Node(Key nkey, Data ndata){key=nkey; data=ndata; next=NULL;}	//constructors
		};
		Node* head;	//start of list
		Node* gethead(){return head;}
	public:
		List() {head=NULL;}
		List(Key arrkey[], Data arrdata[], int i)	//constructor from arrays (i is the number of elements)
		{
			if(i<=0)
			{
				head=NULL;
				return;
			}
			if(!arrkey||!arrdata)	//if either is NULL, return
			{
				head=NULL;
				return;
			}
			int a=0;
			Node* nodeptr;
			head=new Node(arrkey[0], arrdata[0]);	//first node
			nodeptr=head;
			for(a=1; a<i; a++)
			{
				nodeptr->next=new Node(arrkey[a], arrdata[a]);
				nodeptr=nodeptr->next;
			}
		}
		template<typename K, typename D>
		List(List<K, D> &list)	//copy constructor
		{
			Node* nodeptr=list.gethead(), *builder;
			if(!nodeptr)	//if 2nd list is empty, return
			{
				this->head=NULL;
				return;
			}
			builder=new Node(nodeptr->key, nodeptr->data);	//first node
			head=builder;
			nodeptr=nodeptr->next;
			for(;nodeptr!=NULL;nodeptr=nodeptr->next)	//build the list
			{
				builder->next=new Node(nodeptr->key, nodeptr->data);
				builder=builder->next;
			}			
		}
		~List(){destroy();}	//destructor
		template<typename K, typename D>
		List<K, D> operator=(List<K, D> &list)	//assignment operator
		{
			Node* nodeptr=list.gethead(), *builder;
			if(!nodeptr)	//if the 2nd list is empty, return
			{
				this->head=NULL;
				return *this;
			}
			builder=new Node(nodeptr->key, nodeptr->data);	//first node
			head=builder;
			nodeptr=nodeptr->next;
			for(;nodeptr!=NULL;nodeptr=nodeptr->next)	//build the list
			{
				builder->next=new Node(nodeptr->key, nodeptr->data);
				builder=builder->next;
			}	
			return *this;
		}
		List<Key, Data> operator+=(List<Key, Data> &list)	//concatenation with assignment
		{
			Node* nodeptr=list.gethead();
			for(;nodeptr!=NULL; nodeptr=nodeptr->next)	//iterate through list
			{
				this->putBack(nodeptr->key, nodeptr->data);	//add things at the end
			}
			return *this;
		}
		
		List<Key, Data> operator+(List<Key, Data> &list)	//concatenation
		{
			List<Key, Data> blank;	//what we're returning
			Node* nodeptr=head;
			for(;nodeptr!=NULL; nodeptr=nodeptr->next)	//add 1st list's elements
			{
				blank.putBack(nodeptr->key, nodeptr->data);
			}
			for(nodeptr=list.gethead(); nodeptr!=NULL; nodeptr=nodeptr->next)	//add 2nd list's elements
			{
				blank.putBack(nodeptr->key, nodeptr->data);
			}
			return blank;	//return new list
		}
		Data operator[](int i) const	//access data at index
		{
			int s=size();
			if(i<0||i>s) return 0;	//if argument is wrong
			Node* nodeptr=head;
			for(int c=0;c<i; c++, nodeptr=nodeptr->next);	//find the right node
			return nodeptr->data;
		}
		Key getkey(int i) const	//access key at index
		{
			int s=size();
			if(i<0||i>s) return 0;	//if argument is wrong
			Node* nodeptr=head;
			for(int c=0;c<i; c++, nodeptr=nodeptr->next);	//find the right node
			return nodeptr->key;
		}
		int size() const	//return number of elements
		{
			Node* nodeptr=head;
			int i=0;
			for(;nodeptr!=NULL; nodeptr=nodeptr->next, i++);	//find the last element, count as you go up
			return i;
		}
		void print()	//print the list to cout
		{
			if(!head) return;
			int i=0;
			Node* nodeptr=head;
			for(;nodeptr!=NULL; nodeptr=nodeptr->next)
			{
				std::cout<<endl<<nodeptr->key<<endl<<nodeptr->data<<endl;
			}
		}
		bool print(Key k)	//print elements with key==k to cout
		{
			Node* nodeptr=head;
			bool flag=false;
			for(;nodeptr!=NULL; nodeptr=nodeptr->next)	//iterate
			{
				if(nodeptr->key==k) 
				{
					std::cout<<nodeptr->data<<endl;
					flag=true;
				}
			}
			return flag;	//if any found return true
		}
		void putFront(Key k, Data d)	//insert element at front
		{
			Node* nodeptr=head;
			head=new Node(k, d);
			head->next=nodeptr;
		}
		void putBack(Key k, Data d)	//insert element at back
		{
			if (!head)
			{
				head=new Node(k, d);
				return;
			}
			Node* nodeptr=head;
			for(;nodeptr->next!=NULL; nodeptr=nodeptr->next);	//iterate until the end
			nodeptr->next=new Node(k, d);
		}
		void remove(Key k, Node* &nodeptr)	//remove element with key==k
		{
			if(!nodeptr) return;	//anchor
			Node* copy;
			bool flag=false;
			if(nodeptr->key==k)	//if found
			{
				copy=nodeptr;
				nodeptr=nodeptr->next;
				delete copy;	//delet
				flag=true;
			}
			if(flag) remove(k, nodeptr);	//if removed, call with the new next one
			else remove(k, nodeptr->next);	//else with the actual next one
		}
		void destroy()	//clear
		{
			Node* nodeptr=head, *helper;
			while(nodeptr!=NULL)	//free memory
			{
				helper=nodeptr->next;
				delete nodeptr;
				nodeptr=helper;
			}
			head=NULL;
		}
		void insert(int i, Key k, Data d)	//insert node with k and d at index i
		{
			int s=size();
			if(i>s||i<0) return;	//if arguments wrong, return
			Node* nodeptr=head;
			if(i==0)	//if at front
			{
				head=new Node(k, d);
				head->next=nodeptr;
				return;
			}
			Node* helper;
			for(int c=0;c<i-1; c++, nodeptr=nodeptr->next);	//iterate until index-1
			helper=nodeptr->next;
			nodeptr->next=new Node(k, d);
			nodeptr->next->next=helper;
		}
		void popFront()	//delete the first element
		{
			if(!head) return;
			Node* nodeptr=head;
			head=nodeptr->next;
			delete nodeptr;
		}
		void popBack()	//delete the last element
		{
			if(!head) return;
			if(!head->next) 
			{
				delete head;
				head=NULL;
			}
			Node* nodeptr=head;
			for(;nodeptr->next->next!=NULL;nodeptr=nodeptr->next);	//seek the end
			delete nodeptr->next;
			nodeptr->next=NULL;
		}
		Data back()	//get data from last element
		{
			if(!head) return 0;
			Node* nodeptr=head;
			for(;nodeptr->next!=NULL; nodeptr=nodeptr->next);
			return nodeptr->data;	
		}
		Data front() {if(!head) return 0; return head->data;}	//get data from first element
		void remove(Key k){remove(k, head);}	//call the recursive function to remove
		bool isempty() const{if (!head) return true; return false;}	//true if empty, else false
};
template<typename Key, typename Data> List<Key, Data>
produce(const List<Key, Data> &l1, int start1, int length1, const List<Key, Data> &l2, int start2, int length2, int limit)	//"produce" function
{
	List<Key, Data> *blank=new List<Key, Data>();	//we're returning this
	if(start1<0||length1<0||start2<0||length2<0||(!length1&&!length2)||(l1.isempty()&&l2.isempty())) return *blank;	//if arguments are wrong
	if(l2.isempty()) length2=0;	//if one of the list is empty, treat its length as 0
	if(l1.isempty()) length1=0;
	int i=0, j=0, s1=l1.size(), s2=l2.size();	//i - # of elements added from first list, j - # of elements addded from 2nd list, s1, s2 - sizes of lists
	for(i=0;i+j<limit;)
	{
		if((i+j)%(length1+length2)>=length1)	//whether the next element of new list comes from 2nd or 1st list
		{
			blank->putBack(l2.getkey((start2+j)%s2), l2[(start2+j)%s2]);
			j++;
		}
		else
		{
			blank->putBack(l1.getkey((start1+i)%s1), l1[(start1+i)%s1]);
			i++;
		}
	}
	return *blank;
}
void key()	//"Press enter to continue"
{
    cout<<"Press enter to continue"<<endl;
    cin.get();
    fseek(stdin,0,SEEK_END);
    return;
}
template<typename Key, typename Data>
void stresstest(List<Key, Data> &list, Key r1, Key r2, Key r3, int rem1, int rem2, int rem3, Key k, Data d, int start1, int l1, int start2, int l2, int limit)	//this function tests all the methods
{																					//r1, r2, r3 - keys to be removed, rem1, rem2, rem3 - indeces that are going to be tested, k, d - such nodes will be inserted, rest are arguments of "produce"
	cout<<"empty: "<<list.isempty()<<endl<<"size: "<<list.size()<<endl;
	cout<<"List:"<<endl;
	list.print();
	cout<<"Removed elements with key: "<<r1<<" "<<r2<<" "<<r3<<endl;
	list.remove(r1);
	list.remove(r2);
	list.remove(r3);
	list.print();
	key();
	cout<<"Copy constructor: "<<endl;
	List<Key, Data> copy(list);
	copy.print();
	key();
	cout<<"Assignment operator:"<<endl;
	copy=list;
	copy.print();
	key();
	cout<<"Pop 3 last elements:"<<endl;
	list.popBack();
	list.popBack();
	list.popBack();
	list.print();
	key();
	cout<<"Pop 2 first elements:"<<endl;
	list.popFront();
	list.popFront();
	list.print();
	key();
	cout<<"Concatenate with + with the previous copy:"<<endl;
	(list+copy).print();
	cout<<"Concatenate with +="<<endl;
	list+=copy;
	list.print();
	key();
	cout<<"Destroy the copy:"<<endl;
	copy.destroy();
	copy.print();
	key();
	cout<<"Print data from elements with key "<<k<<endl;
	list.print(k);
	key();
	cout<<"Access data at: "<<rem1<<" "<<rem2<<" "<<rem3<<endl<<list[rem1]<<" "<<list[rem2]<<" "<<list[rem3]<<endl<<"Access key at: "<<rem1<<" "<<rem2<<" "<<rem3<<endl<<list.getkey(rem1)<<" "<<list.getkey(rem2)<<" "<<list.getkey(rem3)<<endl<<"Full list:"<<endl;
	list.print();
	cout<<"Data at front:"<<endl<<list.front()<<endl<<"Data at back:"<<endl<<list.back()<<endl<<"Creating a copy."<<endl;
	copy=list;
	key();
	cout<<"Insert elements with key "<<k<<" and data "<<d<<" at: "<<rem1<<" "<<rem2<<" "<<rem3<<" and at front and back"<<endl;
	list.insert(rem1, k, d);
	list.insert(rem2, k, d);
	list.insert(rem3, k, d);
	list.putFront(k, d);
	list.putBack(k, d);
	list.print();
	key();
	cout<<"Produce of copy and current list with parameters: "<<start1<<" "<<l1<<" "<<start2<<" "<<l2<<" "<<limit<<endl;
	produce(copy, start1, l1, list, start2, l2, limit).print();
	key();
	cout<<"End of test"<<endl;
	key();
}
int main()	//main
{
	int i=1;
	int arr1[]={7, 6, 1, 3, 1, 1, 232, 344, 1, 4};
	int arr2[]={2, 4, 5, 1 ,1, 0, 265, 353, 4 ,5};
	List <int, int> list1(arr1, arr2, 10);	//produce list from arrays
	stresstest(list1, 9, 0, 999, 1, 2, 0, 5, 420, 4, 5, 1, 1, 37);
	List <int, int> blank;	//empty list
	stresstest(blank, 7, 7, 676, 3, 2, 3, 1, 434, 3, 1, 0, 9, 15);	//test the lists
	return 0;
}

