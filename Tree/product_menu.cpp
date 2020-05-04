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

int GetKey(){return key;}              // main()要能夠檢視node是否正確
string GetElement(){return element;}   // 讀取data
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
    TreeNode *current = root;               // 將curent指向root作為traversal起點
    while (current != NULL && KEY != current->key) {  // 跳出迴圈：1.沒找到 2.有找到
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
    while (x != NULL) {                // 在while中, 以如同Search()的方式尋找適當的位置
        y = x;
        if (insert_node->key < x->key){
            x = x->leftchild;
        }
        else{
            x = x->rightchild;
        }
    }                                  // 跳出迴圈後, x即為NULL
                                       // y即為insert_node的parent
    insert_node->parent = y;           // 將insert_node的parent pointer指向y

    if (y == NULL){                    // 下面一組if-else, 把insert_node接上BST
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
    q.push(this->root);                     // 把root作為level-order traversal之起點 推進queue中
    while (!q.empty()){                     // 若queue不是空的, 表示還有node沒有visiting
        TreeNode *current = q.front();      // 取出先進入queue的node
        q.pop();
        printf("%03d",current->key);
        cout  << " "<< current->element << endl;

        if (current->leftchild != NULL){    // 若leftchild有資料, 推進queue
            q.push(current->leftchild);
        }
        if (current->rightchild != NULL){   // 若rightchild有資料, 推進queue
            q.push(current->rightchild);
        }
    }
}

void BST::DeleteBST(int KEY){
    TreeNode *delete_node = Search(KEY);    // 先確認BST中是否有具有KEY的node
    if (delete_node == NULL) {
        std::cout << "data not found.\n";
        return;
    }
    TreeNode *y = 0;      // 真正要被刪除並釋放記憶體的node
    TreeNode *x = 0;      // 要被刪除的node的"child"

    if (delete_node->leftchild == NULL || delete_node->rightchild == NULL){
        y = delete_node;
    }
    else{
        y = Successor(delete_node);        // 將y設成delete_node的Successor
    }                                      // 經過這組if-else, y調整成至多只有一個child
    if (y->leftchild != NULL){
        x = y->leftchild;                  // 將x設成y的child, 可能是有效記憶體,
    }                                      // 也有可能是NULL
    else{
        x = y->rightchild;
    }
    if (x != NULL){                        // 在y被刪除之前, 這個步驟把x接回BST
        x->parent = y->parent;
    }
    if (y->parent == NULL){                // 若刪除的是原先的root, 就把x當成新的root
        this->root = x;
    }
    else if (y == y->parent->leftchild){    // 若y原本是其parent之left child
        y->parent->leftchild = x;           // 便把x皆在y的parent的left child, 取代y
    }
    else{                                   // 若y原本是其parent之right child
        y->parent->rightchild = x;          // 便把x皆在y的parent的right child, 取代y
    }

    if (y != delete_node) {                 // 若y是delete_node的替身, 最後要再將y的資料
        delete_node->key = y->key;          // 放回delete_node的記憶體位置, 並將y的記憶體位置釋放
        delete_node->element = y->element;
    }
    if(delete_node->key!=0)
    delete y;                               // 將y的記憶體位置釋放
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
    fp.open(filename, ios::in);//開啟檔案
    if(!fp){//如果開啟檔案失敗，fp為0；成功，fp為非0
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
    fp.close();//關閉檔案

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
                T.DeleteBST(num);       // 刪除龜仙人, 確認比克(513)會成為新root
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
