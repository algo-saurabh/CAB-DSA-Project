#include<bits/stdc++.h>
#include<fstream>

using namespace std;

class Node
{
    public:
    string name,dob,religion,country;
    Node *next;
    Node *prev;
};

vector<string> all_name,all_data,all_dob,all_country,all_religion;

void input(){
    ifstream thefile("data3.csv");
	int x =0;
	string s;
	while(thefile.good()){
            getline(thefile,s);
            s = s.substr(0,s.length()-5);
            all_data.push_back(s);
            int l = s.length();
            string s1 = "";
            for(int i=0;i<l;i++) {
                if(s[i]==','){
                    break;
                }
                s1 = s1 + s[i];
            }
            all_name.push_back(s1);
            s1 = "";
            for(int i=s.length();i>=0;i--) {
                if(s[i]==',')break;
                s1 = s1 + s[i];
            }
            reverse(s1.begin(),s1.end());
            all_religion.push_back(s1);
            s1 = "";
            int y=0;
            for(int i = s.length();i>=0;i--) {
                if(s[i]==','){
                    y= y+1;
                }
                 if(y==2) {
                    break;
                }
                if(y==1 && s[i]!=',') {
                    s1 = s1+s[i];
                }
            }
            reverse(s1.begin(),s1.end());
            all_country.push_back(s1);
            s1 = "";
            y=0;
            for(int i = 0;i<l;i++) {
                if(s[i]==','){
                    y= y+1;
                }
                 if(y==2) {
                    break;
                }
                if(y==1 && s[i]!=',') {
                    s1 = s1+s[i];
                }
            }
            all_dob.push_back(s1);
            x++;
            if(x==161) break;
	}
	all_name.erase(all_name.begin());
    all_country.erase(all_country.begin());
    all_religion.erase(all_religion.begin());
    all_dob.erase(all_dob.begin());

}
/* A utility function to swap two elements */
void swap ( string* a, string* b )
{
    string t = *a;
    *a = *b;
    *b = t;
}

// A utility function to find
// last node of linked list
Node *lastNode(Node *root)
{
    while (root && root->next)
        root = root->next;
    return root;
}

/* Considers last element as pivot,places the pivot element at its correct position in sorted array,
and places all smaller (smaller than pivot) to left of pivot and all greater elements to right of pivot */

Node* partition(Node *l, Node *h){
    // set pivot as h element
    string x = h->name;

    // similar to i = l-1 for array implementation
    Node *i = l->prev;

    // Similar to "for (int j = l; j <= h- 1; j++)"
    for (Node *j = l; j != h; j = j->next)
    {
        if (j->name >= x)
        {
            // Similar to i++ for array
            i = (i == NULL)? l : i->next;

            swap(&(i->name), &(j->name));
            swap(&(i->dob), &(j->dob));
            swap(&(i->country), &(j->country));
            swap(&(i->religion), &(j->religion));
        }
    }
    i = (i == NULL)? l : i->next; // Similar to i++
    swap(&(i->name), &(h->name));
    swap(&(i->dob), &(h->dob));
    swap(&(i->religion), &(h->religion));
    swap(&(i->country), &(h->country));

    return i;
}


void _quickSort(Node* l, Node *h){
    if (h != NULL && l != h && l != h->next)
    {
        Node *p = partition(l, h);
        _quickSort(l, p->prev);
        _quickSort(p->next, h);
    }
}


void quickSort(Node *head){
    // Find last node
    Node *h = lastNode(head);

    // Call the recursive QuickSort
    _quickSort(head, h);
}


void printList(Node *head){
    while (head)
    {
        cout << head->name << "  "<<head->dob<<"  "<<head->religion<<"  "<<head->country<<endl;
        head = head->next;
    }
    cout << endl;
}


void push(Node** head_ref, string name, string dob, string religion, string country){
    Node* new_node = new Node; /* allocate node */
    new_node->name = name;
    new_node->dob = dob;
    new_node->religion = religion;
    new_node->country = country;

    /* since we are adding at the
    beginning, prev is always NULL */
    new_node->prev = NULL;

    /* link the old list off the new node */
    new_node->next = (*head_ref);

    /* change prev of head node to new node */
    if ((*head_ref) != NULL) (*head_ref)->prev = new_node ;

    /* move the head to point to the new node */
    (*head_ref) = new_node;
}

void search_name(string name){
    int pos = -1;
    for(int i=0;i<all_name.size();i++){
        string s = all_name[i];
        if(name[0]==s[0]&&name[1]==s[1]&&name[2]==s[2]){
            pos = i;
            break;
        }
    }
    if(pos!=-1){
        cout<<"NAME: "<<all_name[pos]<<endl;
        cout<<"DOB: "<<all_dob[pos]<<endl;
        cout<<"Religion: "<<all_religion[pos]<<endl;
        cout<<"Country: "<<all_country[pos]<<endl;
    }
    else{
        cout<<"Sorry No entry found in DATABASE"<<endl;
    }
}



int main(){

    input();

    cout<<"<-------------------------------------->"<<endl<<endl;
    cout<<"  Welcome to the CAB Project  "<<endl<<endl;
    cout<<"  In this project the DATASTRUCTURE used is DOUBLE LINKED LIST"<<endl;
    cout<<"  Algorithm used are QUICK SORT to sort the DATABASE"<<endl;
    cout<<"  And LINEAR SEARCH to search in the DATABASE"<<endl<<endl;
    cout<<"<-------------------------------------->"<<endl<<endl;

    cout<<"  Choose:"<<endl;
    cout<<"  1. Sort the DATABASE"<<endl;
    cout<<"  2. Search in the DATABASE"<<endl;
    cout<<"  3. EXIT the Program"<<endl<<endl;
    cout<<"Enter your choice: ";
    int ch;
    cin>>ch;
    if(ch==1){
            // creating double linked list for storing names
        Node *a = NULL;
        for(int i=0;i<all_name.size();i++) {
            push(&a,all_name[i],all_dob[i],all_religion[i],all_country[i]);
        }
        quickSort(a);
        cout<<endl<<endl<<endl;
        cout<<"  The Result after sorting the DATABASE................"<<endl<<endl;
        printList(a);

    }
    else if(ch==2){
        cout<<endl<<"Enter the First Name...";
        string name_to_search;
        cin>>name_to_search;
        cout<<endl;
        search_name(name_to_search);
    }
	return 0;
}
