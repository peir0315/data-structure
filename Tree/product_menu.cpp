#include <iostream>
#include <string>
#include <queue>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <fstream>
#include <cstdlib>

using namespace std;

class BST;
class TreeNode{
//private:
public:
    TreeNode *leftchild;
    TreeNode *rightchild;
    TreeNode *parent;

    int key;
    string element;
    int price;
    int amount;

    TreeNode():leftchild(0),rightchild(0),parent(0),key(0),element(""),price(0),amount(0){};
    TreeNode(int a,string b, int c,int d):leftchild(0),rightchild(0),parent(0),key(a),element(b),price(c),amount(d){};

int GetKey(){return key;}              // main()�n����˵�node�O�_���T
string GetElement(){return element;}   // Ū��data
int GetPrice(){return price;}
int GetAmount(){return amount;}
    friend class BST;
};

class BST{
private:
    TreeNode* Leftmost(TreeNode *current);
    //TreeNode* Rightmost(TreeNode *current);
    //TreeNode* Predecessor(TreeNode *current);
public:
    BST():root(0){};

    TreeNode *root;
    TreeNode* Successor(TreeNode *current);
    TreeNode* Search(int KEY);
    void InsertBST(int key,string element, int price, int amount);
    void InorderPrint();
    void Levelorder();
    void DeleteBST(int key);
};

TreeNode* BST::Search(int KEY){
    TreeNode *current = root;               // �Ncurent���Vroot�@��traversal�_�I
    while (current != NULL && KEY != current->key) {  // ���X�j��G1.�S��� 2.�����
        if (KEY < current->key){
            current = current->leftchild;
        }
        else {
            current = current->rightchild;
        }
    }
    return current;
}

void BST::InsertBST(int key, string element,int price, int amount){

    TreeNode *y = 0;
    TreeNode *x = 0;
    TreeNode *insert_node = new TreeNode(key, element,price ,amount );

    x = root;
    while (x != NULL) {                // �bwhile��, �H�p�PSearch()���覡�M��A����m
        y = x;
        if (insert_node->key < x->key){
            x = x->leftchild;
        }
        else{
            x = x->rightchild;
        }
    }                                  // ���X�j���, x�Y��NULL
                                       // y�Y��insert_node��parent
    insert_node->parent = y;           // �Ninsert_node��parent pointer���Vy

    if (y == NULL){                    // �U���@��if-else, ��insert_node���WBST
        this->root = insert_node;
    }
    else if (insert_node->key < y->key){
        y->leftchild = insert_node;
    }
    else if(insert_node->key == y->key){
        cout<< "The product has been exited."<<endl;
        delete insert_node;
    }
    else{
        y->rightchild = insert_node;
    }
}
/*TreeNode* BST::Rightmost(TreeNode *current){

    while (current->rightchild != NULL){
        current = current->rightchild;
    }
    return current;
}*/
/*TreeNode* BST::Predecessor(TreeNode *current){
    if (current->leftchild != NULL){
        return Rightmost(current->leftchild);
    }

    TreeNode *new_node = current->parent;

    while (new_node != NULL && current == new_node->leftchild) {
        current = new_node;
        new_node = new_node->parent;
    }
    return new_node;
}*/
TreeNode* BST::Leftmost(TreeNode *current){

    while (current->leftchild != NULL){
        current = current->leftchild;
    }
    return current;
}
TreeNode* BST::Successor(TreeNode *current){

    if (current->rightchild != NULL){
        return Leftmost(current->rightchild);
    }

    TreeNode *new_node = current->parent;

    while (new_node != NULL && current == new_node->rightchild) {
        current = new_node;
        new_node = new_node->parent;
    }

    return new_node;
}
void BST::InorderPrint(){
    TreeNode *current = new TreeNode;
    current = Leftmost(root);
    while(current){
        printf("%03d",current->key);
        cout  << " "<< current->element << endl;
        current = Successor(current);
    }
}

void BST::Levelorder(){

    std::queue<TreeNode*> q;
    q.push(this->root);                     // ��root�@��level-order traversal���_�I ���iqueue��
    while (!q.empty()){                     // �Yqueue���O�Ū�, ����٦�node�S��visiting
        TreeNode *current = q.front();      // ���X���i�Jqueue��node
        q.pop();
        printf("%03d",current->key);
        cout  << " "<< current->element << endl;

        if (current->leftchild != NULL){    // �Yleftchild�����, ���iqueue
            q.push(current->leftchild);
        }
        if (current->rightchild != NULL){   // �Yrightchild�����, ���iqueue
            q.push(current->rightchild);
        }
    }
}

void BST::DeleteBST(int KEY){
    TreeNode *delete_node = Search(KEY);    // ���T�{BST���O�_���㦳KEY��node
    if (delete_node == NULL) {
        std::cout << "data not found.\n";
        return;
    }
    TreeNode *y = 0;      // �u���n�Q�R��������O���骺node
    TreeNode *x = 0;      // �n�Q�R����node��"child"

    if (delete_node->leftchild == NULL || delete_node->rightchild == NULL){
        y = delete_node;
    }
    else{
        y = Successor(delete_node);        // �Ny�]��delete_node��Successor
    }                                      // �g�L�o��if-else, y�վ㦨�ܦh�u���@��child
    if (y->leftchild != NULL){
        x = y->leftchild;                  // �Nx�]��y��child, �i��O���İO����,
    }                                      // �]���i��ONULL
    else{
        x = y->rightchild;
    }
    if (x != NULL){                        // �by�Q�R�����e, �o�ӨB�J��x���^BST
        x->parent = y->parent;
    }
    if (y->parent == NULL){                // �Y�R�����O�����root, �N��x���s��root
        this->root = x;
    }
    else if (y == y->parent->leftchild){    // �Yy�쥻�O��parent��left child
        y->parent->leftchild = x;           // �K��x�Ҧby��parent��left child, ���Ny
    }
    else{                                   // �Yy�쥻�O��parent��right child
        y->parent->rightchild = x;          // �K��x�Ҧby��parent��right child, ���Ny
    }

    if (y != delete_node) {                 // �Yy�Odelete_node������, �̫�n�A�Ny�����
        delete_node->key = y->key;          // ��^delete_node���O�����m, �ñNy���O�����m����
        delete_node->element = y->element;
    }
    if(delete_node->key!=0)
    delete y;                               // �Ny���O�����m����
    y = 0;
}

int main() {

    BST T;
    int mod;
    int sh=0;
    int pri,amou,num;
    char s;
    string number;
    string pro;
    string tem;
    int ex=0,im=0;
    char spi[128];
    char filename[10];
    cout<<"Enter the file name:"<<endl;
    cin>>filename;
    fstream fp;
    char line[128];
    fp.open(filename, ios::in);//�}���ɮ�
    if(!fp){//�p�G�}���ɮץ��ѡAfp��0�F���\�Afp���D0
        cout<<"Fail to open file: "<<filename<<endl;
    }
    //cout<<"File Descriptor: "<<fp<<endl;
    for (int i=0;i<100;i++) {
        if(num==0) break;
        fp.getline(line, sizeof(line), ' ');
        tem.assign(line);
        num=atoi (tem.c_str());
        //cout<<num<<endl;
        fp.getline(line, sizeof(line), ' ');
        tem.assign(line);
        pro=tem;
        //cout<<pro<<endl;
        fp.getline(line, sizeof(line), ' ');
        tem.assign(line);
        pri=atoi (tem.c_str());
        //cout<<pri<<endl;
        fp.getline(line, sizeof(line), '\n');
        tem.assign(line);
        amou=atoi (tem.c_str());
        //cout<<amou<<endl;
        T.InsertBST(num,pro,pri,amou);
    }
    T.DeleteBST(0);
    fp.close();//�����ɮ�

    //return 0;
    while(1){
    cout<<"--------------------------------------------------"<<endl;
    cout << "Select the function:"<<endl;
    cout << "1. Add the new product."<<endl;
    cout << "2. Search the product."<<endl;
    cout << "3. Delete the product."<<endl;
    cout << "4. Export product."<<endl;
    cout << "5. Import product."<<endl;
    cout << "6. List all product in increasing order."<<endl;
    cout << "7. List all product in level order."<<endl;
    cout << "8. Modify the product number of a product.(bonus)"<<endl;
    cout << "Others to Exit."<<endl;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"you choose: ";
        int function=0;
        cin>>function;
        TreeNode *temp;
        switch (function) {
            case 1:
                cout<<"The number of product: ";
                cin>>num;
                if(!cin){
                    cout<<"Wrong input.\nProgram Over!"<<endl;
                    return 0;
                }
                if(num>1000){
                    cout<<"Wrong input.\nPlease enter the 3-digit number."<<endl;
                    break;
                }
                temp = T.Search(num);
                if(temp!=NULL){
                cout<<"The product has exited. "<<endl;
                break;
                }
                cout<< "The name of the product:";
                cin>>pro;
                if(pro.size()>40){
                    cout<< "Wrong input! \nProduct name is too long."<<endl;
                    break;
                }
                cout<< "The price of the product:";
                cin>>pri;
                cout<< "The amount of the product:";
                cin>>amou;
                T.InsertBST(num,pro,pri,amou);
                break;
            case 2:
                cout<<"The number of product: ";
                cin>>num;
                if(!cin){
                    cin.clear();
                    cout<<"Wrong input.\nProgram Over!"<<endl;
                    return 0;
                }
                if(num>1000){
                    cout<<"Wrong input.\nPlease enter the 3-digit number."<<endl;
                    break;
                }
                temp = T.Search(num);
                if(temp!= NULL){
                    cout << "Product information:"<<endl;
                    printf("%03d",temp->GetKey());
                    cout<< " "<< temp->GetElement() << " " << temp->GetPrice() << " " << temp->GetAmount() << endl;
                }
                else {
                    cout << "Error! No product." << endl;
                }
                cout << "Next product or not:('N' for next, 'R' for over)"<<endl;
                cin>>s;
                while(s=='N'){
                    temp=T.Successor(temp);
                    printf("%03d",temp->GetKey());
                    cout<< " "<< temp->GetElement() << " " << temp->GetPrice() << " " << temp->GetAmount() << endl;
                    cout << "Next product or not:('N' for next, 'R' for over)"<<endl;
                    cin>>s;
                    if(s=='R'){
                        break;
                    }
                }
                break;
            case 3:
                cout<<"The number of product: ";
                cin>>num;
                if(!cin){
                    cin.clear();
                    cout<<"Wrong input.\nProgram Over!"<<endl;
                    return 0;
                }
                if(num>1000){
                    cout<<"Wrong input.\nPlease enter the 3-digit number."<<endl;
                    break;
                }
                temp = T.Search(num);
                if(temp!= NULL){
                    printf("%03d",temp->GetKey());
                    cout<< " "<< temp->GetElement() << " is deleted." << endl;
                }
                else {
                    cout << "Error! No product." << endl;
                }
                T.DeleteBST(num);       // �R���t�P�H, �T�{��J(513)�|�����sroot
                break;
            case 4:
                cout<<"The number of product: ";
                cin>>num;
                if(!cin){
                    cin.clear();
                    cout<<"Wrong input.\nProgram Over!"<<endl;
                    return 0;
                }
                if(num>1000){
                    cout<<"Wrong input.\nPlease enter the 3-digit number."<<endl;
                    break;
                }
                temp = T.Search(num);
                if(temp== NULL){
                    cout << "Error! No product." << endl;
                    break;
                }

                cout<<"The exported amount of product: ";
                cin>>ex;
                if(ex>temp->amount){
                    cout<<"Amount is not enough."<<endl;
                    break;
                }
                else{
                    temp->amount-=ex;
                    cout<<"Amount: "<<temp->amount<<endl;
                }
                break;
            case 5:
                cout<<"The number of product: ";
                cin>>num;
                if(!cin){
                    cin.clear();
                    cout<<"Wrong input.\nProgram Over!"<<endl;
                    return 0;
                }
                if(num>1000){
                    cout<<"Wrong input.\nPlease enter the 3-digit number."<<endl;
                    break;
                }
                temp = T.Search(num);
                if(temp== NULL){
                    cout << "Error! No product." << endl;
                    break;
                }
                cout<<"The imported amount of product: ";
                cin>>im;
                temp->amount+=im;
                cout<<"Amount: "<<temp->amount<<endl;
                break;
            case 6:
                cout << "Increase order Traversal:\n";
                T.InorderPrint();
                break;
            case 7:
                cout << "Level order Traversal:\n";
                T.Levelorder();
                break;
            case 8:
                cout<<"The number of product: ";
                cin>>num;
                if(!cin){
                    cin.clear();
                    cout<<"Wrong input.\nProgram Over!"<<endl;
                    return 0;
                }
                if(num>1000){
                    cout<<"Wrong input.\nPlease enter the 3-digit number."<<endl;
                    break;
                }
                temp = T.Search(num);
                if(temp== NULL){
                    cout << "Error! No product." << endl;
                    break;
                }
                pro=temp->element; pri=temp->price; amou=temp->amount;
                T.DeleteBST(num);
                cout<<"The number of product be changed to: ";
                cin>>num;
                if(!cin){
                    cin.clear();
                    cout<<"Wrong input.\nProgram Over!"<<endl;
                    return 0;
                }
                if(num>1000){
                    cout<<"Wrong input.\nPlease enter the 3-digit number."<<endl;
                    break;
                }
                temp = T.Search(num);
                if(temp!=NULL){
                cout<<"The product has exited. "<<endl;
                break;
                }
                T.InsertBST(num,pro,pri,amou);
                break;
            default:
                return 0;
        }
    }
}
