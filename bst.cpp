#include<iostream>
using namespace std;

class treenode
{
	public:
		int val;
		treenode *left;
		treenode *right;
};

class bst 
{

	public:
		treenode *root;
		bst()
		{
			root=NULL;
		}

		void create_bst();
		void insert_node(treenode *temp);
		void recursive_inorder(treenode *root);
		void recursive_preorder(treenode *root);
		void recursive_postorder(treenode *root);
		void non_recursive_inorder();
		void non_recursive_preorder();
		void non_recursive_postorder();
		void delete_node_from_bst();
		void level_wise_printing();
		
	


};



class queuenode
{
public:
    treenode *addr;
    queuenode *next;
};

class myqueue
{
private:
    queuenode *frnt;
    queuenode *rear;
public:
    myqueue()
    {
        frnt = NULL;
        rear = NULL;
    }

    void add_queue(treenode *t1);
    queuenode *delete_queue();
};




void myqueue::add_queue(treenode *t1)
{
    queuenode *temp;
    if(rear == NULL)
    {
        rear = new queuenode();
        rear->addr = t1;
        rear->next = NULL;
        frnt = rear;
    }
    else
    {
        temp = new queuenode();
        temp->addr = t1;
        temp->next = NULL;
        rear->next = temp;
        rear = rear->next;
    }
}



queuenode *myqueue::delete_queue()
{
    queuenode *temp;
    temp = frnt;
    queuenode *temp1;
    temp1 = frnt;
    frnt = frnt->next;
    delete(temp1);
    return temp;
}




class stacknode
{
	public:
		treenode *addr;
		stacknode *next;
};

class stack
{
	private:
		stacknode *top;

	public:
		stack()
		{
			top =NULL;
		}

		void push(treenode *addr);
		treenode *pop();
		int stack_empty();

};

void stack :: push(treenode *addr)
{
		if( top	==NULL)
		{
			top = new stacknode();
			top->addr =addr;
			top->next=NULL;

		}
		else 
		{
			stacknode *temp;
			temp= new stacknode();
			temp->addr =addr;
			temp->next= top;
			top =temp;
		}

}


treenode * stack :: pop()
{
	if(top ==NULL)
	{
		return NULL;
	}
	else
	{
		stacknode *temp =top;
		top =top->next;
		return temp->addr;
	} 
}


int stack :: stack_empty()
{
	if(top ==NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void bst::level_wise_printing()
{
    myqueue q1;
    treenode *temp = root;
    queuenode *t1;

    q1.add_queue(temp);

    treenode *temp1 = new treenode();
    temp1->val = '#';
    temp1->left = NULL;
    temp1->right = NULL;

    q1.add_queue(temp1);

    while(1)
    {
        t1 = q1.delete_queue();
        temp = t1->addr;

        if(temp->val == '#')
        {
            if(t1->next == NULL)
                break;
            else
            {
                q1.add_queue(temp1); // add # at the end
                cout<<endl;
            }
        }
        else
        {
            cout<<"     "<<temp->val;
            //check left and right if exist then add in the queue
            if(temp->left != NULL)
                q1.add_queue(temp->left);
            if(temp->right != NULL)
                q1.add_queue(temp->right);
        }
    }
}
// class BST functions starts 

void bst ::create_bst()
{
		int ch=1;
		int no;
		treenode *temp=NULL;
		treenode *t1=NULL;

	 do{
			cout<<"enter Value : ";
			cin>>no;

			temp= new(treenode);
			temp->val =no;
			temp->left=NULL;
			temp->right=NULL;
			insert_node(temp);

				cout<<" Do you Want to Continue (1 | 0):\t";
				cin>>ch;

		}while(ch!=0);
}


void bst :: insert_node(treenode *temp)
{
	treenode * t1 =NULL;

	if(root ==NULL)
	{
		root =temp;
	}
	else
	{
		t1 =root;

			while(1)
			{
					if(t1->val >temp->val)
					{
						if(t1->left !=NULL)
						{
							t1 =t1->left;
						}
						else
						{
							t1->left =temp;
							break;
						}
					}

					else
					{
						if(t1->right !=NULL)
						{
							t1 =t1->right;
						}
						else
						{
							t1->right =temp;
							break;
						}
					}					
			}
	}
}

void bst:: recursive_inorder(treenode *root)
		{		
			treenode *temp =root;
			if(temp->left !=NULL)
			{
				recursive_inorder(temp->left);
				

			}
			

			cout<<"\t"<<temp->val;

			if(temp->right !=NULL)
			{
				recursive_inorder(temp->right);

			}
		}

void bst:: recursive_preorder(treenode *root)
		{		
			treenode *temp =root;

			cout<<"\t"<<temp->val;
			if(temp->left !=NULL)
			{
				recursive_inorder(temp->left);
			}
			if(temp->right !=NULL)
			{
				recursive_inorder(temp->right);
			}
		}

void bst:: recursive_postorder(treenode *root)
		{		
			treenode *temp =root;
			
			if(temp->left !=NULL)
			{
				recursive_inorder(temp->left);
			}
			if(temp->right !=NULL)
			{
				recursive_inorder(temp->right);
			}

			cout<<"\t"<<temp->val;
		}


void bst :: non_recursive_inorder()
{
	stack s1;
	treenode * temp =root;

	while(1)
	{
		while(temp !=NULL)
		{	s1.push(temp);
			temp =temp->left;
		}
			
			if(s1.stack_empty())
			{
				break;
			}

		temp =s1.pop();
		cout<<"\t"<<temp->val;
		temp =temp->right;

	}
}

void bst :: non_recursive_preorder()
{
	stack s1;
	treenode * temp =root;

	while(1)
	{
		while(temp !=NULL)
		{	
			cout<<"\t"<<temp->val;
			s1.push(temp);
			temp =temp->left;
		}
			
			if(s1.stack_empty())
			{
				break;
			}

		temp =s1.pop();
		temp =temp->right;

	}
}

void bst :: non_recursive_postorder()
{
	stack s1;
	stack s2;
	treenode * temp =root;
	s1.push(root);
	while(1)
	{
		if(s1.stack_empty())
			break;

		temp =s1.pop();
		s2.push(temp);

		if(temp->left != NULL)
		{
			s1.push(temp->left);
		}
		if(temp-> right != NULL)
		{
			s1.push(temp->right);
		}
	}

	while(1)
	{
		if(s2.stack_empty())
			break;
		temp=s2.pop();
		cout<<"\t"<<temp->val;
	}

}

void bst::delete_node_from_bst()
{
    treenode *c, *p;
    int no;
    p = NULL;
    c = root;

    cout<<"Enter the node to be deleted: ";
    cin>>no;

    while(1)
    {
        if(c == NULL)
            break;
        else if(c->val == no)
            break;
        else if(c->val > no)
        {
            p = c;
            c = c->left;
        }
        else
        {        //case 1 : leaf node

            p = c;
            c = c->right;
        }

    }
    if(c==NULL)
    {
        cout<<"\n Node is not present in the tree";
    }
    else if(c == root)
    {
        //case 1 : leaf node
        if(c->left == NULL && c->right == NULL)
        {
            root = NULL;
            delete c;
        }
        else if(c->left != NULL && c->right == NULL)
        {
            root = c->left;
            delete c;
        }
        else if(c->left == NULL && c->right != NULL)
        {
            root = c->right;
            delete c;
        }
        else
        {
            treenode *p1, *c1;
            p1 = c;
            c1 = c->left;
            while(c1->right != NULL)
            {
                p1 = c1;
                c1 = c1->right;
            }
            // copy value of c1 to c
            if(p1==c)
            {
                p1->left = c1->left;
                delete c1;
            }
            else
            {
                c->val = c1->val;
                if(c1->left == NULL && c1->right == NULL)
                    delete c1;
                else if(c1->left != NULL && c1->right == NULL)
                {
                    p1->left = c1->left;
                    delete c1;
                }
                else
                {
                    p1->right = c1->left;
                    delete c1;
                }
            }
        }
    }
    else
    {
        //case 1 : leaf node
        if(c->left == NULL && c->right == NULL)
        {
            if(p->left == c)
            {
                p->left = NULL;
                delete c;
            }
            else
            {
                p->right = NULL;
                delete c;
            }
        }
        //case 2 only left subtree
        else if(c->left != NULL && c->right == NULL)
        {
            //if node to be deleted is connected to the left of parent
            if(p->left == c)
            {
                p->left = c->left;
                delete c;
            }
            // if node to be deleted is connected to the right of parent
            else
            {
                p->right = c->left;
                delete c;
            }
        }
        //case 3 only right subtree
        else if(c->left == NULL && c->right != NULL)
        {
            //if node to be deleted is connected to the left of parent
            if(p->left == c)
            {
                p->left = c->right;
                delete c;
            }
            // if node to be deleted is connected to the right of parent
            else
            {
                p->right = c->right;
                delete c;
            }
        }
        //case 4 : Node to be deleted has both left and right subtree.
        else
        {
            // first find inorder predecessor of node to be deleted i.e. c in our case
            // inoder predecessor of a node is
            // node with maximum value in the left subtree of the node
            treenode *p1, *c1;
            p1 = c;
            c1 = c->left;
            while(c1->right != NULL)
            {
                p1 = c1;
                c1 = c1->right;
            }

            // copy value of c1 to c
            c->val = c1->val;
            if(p1==c)
            {
                p1->left = c1->left;
                delete c1;
            }
            else
            {
                if(c1->left == NULL && c1->right == NULL)
                {
                    p1->right = NULL;
                    delete c1;
                }

                else
                {
                    p1->right = c1->left;
                    delete c1;
                }
            }
        }
        cout<<"\n Node with value "<<no<<" has been deleted";
    }
}




main()
{
	int opt,opt1,opt2;

bst T;



		do
	  {
		cout<<"\n1. Create Binary search tree \n 2. Traversal using Recursion \n3.Traversal without Recursion  \n4.Delete Node From the tree\n5.level_wise_printing (BFS).\n6 Exit"<<endl;
		cin>>opt;

		switch(opt)
		 {
			case 1: 
				cout<<"Create BST :"<<endl;
				T.create_bst();
				break;

			case 2:

				do{
					cout<<"\n\t\tTraversal With Recursion !\t";
					cout<<"\n1.Inorder Traversal \n2. Preorder Traversal \n 3. Postorder Traversal \n 4.Exit"<<endl;
					cin>>opt1;

						switch(opt1)
						{
							case 1:
								cout<<"\nInorder Traversal : "<<endl;
								T.recursive_inorder(T.root);
								break;

							case 2:
								cout<<"\nPreorder Traversal : "<<endl;
								T.recursive_preorder(T.root);
								break;

							case 3:
								cout<<"\nPostorder Traversal : "<<endl;
								T.recursive_postorder(T.root);
								break;

						}
					}while(opt1!=4);
				break;

			case 3:
				do{
					cout<<"\n\t\tTraversal Without Recursion !\t";
					cout<<"\n1.Inorder Traversal \n2. Preorder Traversal \n 3. Postorder Traversal \n 4.Exit"<<endl;
					cin>>opt2;

						switch(opt2)
						{
							case 1:
								cout<<"\nInorder Traversal : "<<endl;
								T.non_recursive_inorder();
								break;

							case 2:
								cout<<"\nPreorder Traversal : "<<endl;
								T.non_recursive_preorder();
								break;

							case 3:
								cout<<"\nPostorder Traversal : "<<endl;
								T.non_recursive_postorder();
								break;

						}
					}while(opt2!=4);
				break;


				case 4:
						cout<<"Delete Node From the tree:\n";
						T.delete_node_from_bst();
						cout<<"Here is Result after Deletion :\n";
						T.recursive_inorder(T.root);
						break;

				case 5:
					cout<<"level_wise_printing"<<endl;
					T.level_wise_printing();
					break;


		 }
	 }while(opt!=6);	

 
}
