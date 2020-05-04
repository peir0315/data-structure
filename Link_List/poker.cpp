#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

// 0 for no repeat, vice versa
int card_code_all[53] = {0}; //1-52, 0 redundent

class LinkedList;
class ListNode{
private:
public:
    int data;           // card number
    char shape;         // card shape
    int card_code;      // card code
    ListNode *next;

    ListNode():data(0),next(0){};
    ListNode(int a):data(a),next(0){};
    ListNode(int a, char b):data(a),shape(b),next(0){};
    ListNode(int a, char b,int c):data(a),shape(b),card_code(c),next(0){};

    friend class LinkedList;
};

class LinkedList{
private:
public:
    int size;                   // size是用來記錄Linked list的長度(非必要)
    ListNode *first;            // list的第一個node

    LinkedList():first(0){};
    void PrintList();                                   // 印出list的所有資料
    void Push_front(int data, char shape, int code);    // 在list的開頭新增node
    void Push_back(int data, char shape, int code);     // 在list的尾巴新增node
    void Delete(int data_in, char shape, int code);     // 刪除list中的data_in
    void Clear();                                       // 把整串list刪除
    void Reverse();                                     // 將list反轉: 7->3->14 => 14->3->7
};

void LinkedList::PrintList(){

    if(first ==0){
        printf("List is empty!\n");
        return;
    }
    ListNode *temp=first;             // 用pointer *current在list中移動
    while (temp != 0) {                 // Traversal
        cout << temp->shape<<temp->data<<"("<<temp->card_code<<")"<<endl;/*這句不太會用*/
        temp = temp->next;
    }
}

void LinkedList::Push_front(int data, char shape, int code){

    ListNode *newNode=new ListNode(data, shape, code);   /*可以直接 list node嗎=new ListNode(data, shape, code)*/
    newNode->next=first;                 /*j為什麼fist可以這樣放(不是沒傳進去嗎?)*/
    first=newNode;
}

void LinkedList::Push_back(int data, char shape, int code){

    ListNode *newNode = new ListNode(data, shape, code);   // 配置新的記憶體

    if (first == 0) {                      // 若list沒有node, 令newNode為first
        first = newNode;
        return;
    }

    ListNode *current=first;
    while(current->next!=0){
        current=current->next;
    }
    current->next = newNode;               // 將newNode接在list的尾巴
}

void LinkedList::Delete(int data_in, char shape, int code){
    
    ListNode *current = first,
    *previous = 0;
    while (1) {
        while (current != 0 && current->data != data_in) {  // Traversal
            previous = current;
            current = current->next;
        }
        if (current == 0) {
               cout <<"No corresponsed card!"<<endl;
            return;
        }
        if (current->shape==shape) {
            //cout<<current->shape<<"   "<<shape<<endl;
            break;
        }else {
            previous = current;
            current = current->next;
        }
    }
    
    if (current == first) {
        first = current->next;
        delete current;
        current = 0;
        // return;
    }
    else {
        previous->next=current->next;
        delete current;
        current = 0;
        // return;
    }
}

void LinkedList::Clear(){
    
    while (first != 0) {            // Traversal
        ListNode *current=first;
        first=first->next;
        delete current;
        current=0;
    }
}

void LinkedList::Reverse(){
    
    if (first == 0 || first->next == 0) {
        // list is empty or list has only one node
        return;
    }
    
    ListNode *previous = 0,
    *current = first,
    *preceding = first->next;
    
    while (preceding != 0) {
        current->next = previous;
        previous = current;            // previous往後挪
        current = preceding;           // current往後挪
        preceding = preceding->next;
    }
    
    current->next = previous;
    first = current;                   // 更新first為current
}

ListNode random_get() {
    // 亂數範圍定義
    char card_shape_all[4]={'S','H','D','C'};
    int min;
    int max;
    while (1) {
        // 產生1-13亂數
        min = 1;
        max = 13;
        int card_num = rand() % (max - min + 1) + min;
        // 產生花色亂數
        min = 0;
        max = 3;
        int card_shape_random_num = rand() % (max - min + 1) + min;
        char card_shape = card_shape_all[ card_shape_random_num ];
        // 計算card_code
        int cardcode = card_shape_random_num*13 + card_num;
        if (card_code_all[cardcode]==0) {
            card_code_all[cardcode]=1;
            ListNode card = ListNode(card_num,card_shape,cardcode);
            return card;
        }
    }
}

int main() {
    srand( (unsigned)time( NULL ) );    //  random seed
    LinkedList hand_field;
    LinkedList range_field;             // temp:用來排列順序顯示
    ListNode *current;
    int n=0;                            // temp:card number added
    char s;
    int mode=0;
    int num,tagg=14;                             // temp:shape of the card choosed
    cout<<"Mode input"<<endl<<"(1 for functions demo mode; 2 for game mode): ";
    cin>>mode;
    if (mode==1) {
        while (1) {
            cout<<"-----------------------------------------------------------------------------------------------"<<endl;
            cout<<"Function choosing section:"<<endl;
            cout<<"1 for plusing n cards to list"<<endl;
            cout<<"2 for choosing a shape & listing in original order"<<endl;
            cout<<"3 for choosing a shape & listing in oppsite order"<<endl;
            cout<<"4 for choosing a shape & listing in value from smaller to bigger"<<endl;
            cout<<"5 for choosing a card & delete the minimum card among those bigger than the card you choose"<<endl;
            cout<<"others input for Exit"<<endl;
            cout<<"----------------------------------------------------------------------------------------------"<<endl;
            cout<<"you choose: ";
            int function=0;
            cin>>function;
            switch (function) {
                case 1:
                    cout<<"The number of the card: ";
                    cin>>n;
                    if (n>52||n<1) {
                        cout<<"NOT ALLOW NUMBER"<<endl;
                        break;
                    }
                    // randomly get n cards & link them
                    for (int i=0;i<n;i++) {
                        ListNode rand_card = random_get();
                        hand_field.Push_back(rand_card.data, rand_card.shape, rand_card.card_code);
                        //cout <<"random card is "<<rand_card.data<<" "<<rand_card.shape<<" "<<rand_card.card_code<<"\n";
                    }
                    cout<<"Licensing......"<<endl;
                    hand_field.PrintList();
                    //for (int i=0;i<53;i++) cout<<card_code_all[i];
                    //cout<<"\n";
                    cout<<"Licensed!"<<endl;
                    break;
                case 2:
                    cout<<"The shape of the card: ";
                    cin>>s;
                    if (hand_field.first == 0) {
                        cout << "List is empty.\n";
                        break;
                    }
                    if(isdigit(s)||(s!='S'&&s!='H'&&s!='D'&&s!='C')){
                        cout << "Wrong input!\n";
                        break;
                    }
                    current = hand_field.first;
                    while (current != 0) {                  // Traversal
                        if (current->shape==s) cout << current->shape<<current->data<<"("<<current->card_code<<")"<<endl;
                        current = current->next;
                    }
                    break;
                case 3:
                    cout<<"The shape of the card: ";
                    cin>>s;
                    if (hand_field.first == 0) {
                        cout << "List is empty.\n";
                        break;
                    }
                    if(isdigit(s)||(s!='S'&&s!='H'&&s!='D'&&s!='C')){
                        cout << "Wrong input!\n";
                        break;
                    }
                    hand_field.Reverse();
                    current = hand_field.first;
                    while (current != 0) {                  // Traversal
                        if (current->shape==s) cout << current->shape<<current->data<<"("<<current->card_code<<")"<<endl;
                        current = current->next;
                    }
                    hand_field.Reverse();
                    break;
                case 4:
                    cout<<"The shape of the card: ";
                    cin>>s;
                    if (hand_field.first == 0) {
                        cout << "List is empty.\n";
                        break;
                    }
                    if(isdigit(s)||(s!='S'&&s!='H'&&s!='D'&&s!='C')){
                        cout << "Wrong input!\n";
                        break;
                    }
                    for(int i=2;i<14;i++){
                        current=hand_field.first;
                        while(current!=0){
                            if(current->shape==s && current->data==i){
                                cout << current->shape<<current->data<<"("<<current->card_code<<")"<<endl;
                            }
                            current=current->next;}
                    }
                    current=hand_field.first;
                    while(current!=0){
                        if(current->shape==s && current->data==1){
                            cout << current->shape<<current->data<<"("<<current->card_code<<")"<<endl;
                        }
                        current=current->next;
                        
                    }
                    
                    break;
                case 5:
                    cout<<"The shape of the card: ";
                    cin>>s;
                    if(isdigit(s)||(s!='S'&&s!='H'&&s!='D'&&s!='C')){
                        cout << "Wrong input!\n";
                        break;
                    }
                    cout<<"The number of the card: ";
                    cin>>num;
                    if (hand_field.first == 0) {            // 如果first node指向NULL, 表示list沒有資料
                        cout << "List is empty.\n";
                        break;
                    }
                    current=hand_field.first;
                    while(current!=0){
                        if(current->shape==s && current->data>num && current->data<tagg){
                            tagg=current->data;
                        }
                        current=current->next;
                    }
                    if (tagg==14 && num>1) {
                        hand_field.Delete(1, s, 0);
                        break;
                    } else if (tagg==14||num==1) {
                        cout<<"No corresponsed card!"<<endl;
                        break;
                    }
                    current=hand_field.first;
                    while(current!=0){
                        if(current->shape==s && current->data==tagg){
                            cout<<"delete: "<<s<<tagg<<endl;
                            hand_field.Delete(tagg,s,current->card_code);
                        }
                        current=current->next;
                    }
                    tagg=14;
                    break;
                default:
                    return 0;
            }

        }
    }else if (mode==2) {
        LinkedList playerA;
        LinkedList playerB;
        int section_switch=0;
        while (section_switch==0) {
        cout<<"playerA function section: "<<endl;
        cout<<"-----------------------------------------------------------------------------------------------"<<endl;
        cout<<"Function choosing section:"<<endl;
        cout<<"1 for plusing n cards to list"<<endl;
        cout<<"2 for choosing a shape & listing in original order"<<endl;
        cout<<"3 for choosing a shape & listing in oppsite order"<<endl;
        cout<<"4 for choosing a shape & listing in value from smaller to bigger"<<endl;
        cout<<"5 for choosing a card & delete the minimum card among those bigger than the card you choose"<<endl;
        cout<<"6 for turn ending and switch to next section"<<endl;
        cout<<"others input for Exit"<<endl;
        cout<<"----------------------------------------------------------------------------------------------"<<endl;
        cout<<"you choose: ";
        int function=0;
        cin>>function;
        switch (function) {
            case 1:
                cout<<"The number of the card: ";
                cin>>n;
                if (n>52||n<1) {
                    cout<<"NOT ALLOW NUMBER"<<endl;
                    break;
                }
                // randomly get n cards & link them
                for (int i=0;i<n;i++) {
                    ListNode rand_card = random_get();
                    playerA.Push_back(rand_card.data, rand_card.shape, rand_card.card_code);
                    //cout <<"random card is "<<rand_card.data<<" "<<rand_card.shape<<" "<<rand_card.card_code<<"\n";
                }
                cout<<"Licensing......"<<endl;
                playerA.PrintList();
                //for (int i=0;i<53;i++) cout<<card_code_all[i];
                //cout<<"\n";
                cout<<"Licensed!"<<endl;
                break;
            case 2:
                cout<<"The shape of the card: ";
                cin>>s;
                if (playerA.first == 0) {            // 如果first node指向NULL, 表示list沒有資料
                    cout << "List is empty.\n";
                    break;
                }
                if(isdigit(s)||(s!='S'&&s!='H'&&s!='D'&&s!='C')){
                    cout << "Wrong input!\n";
                    break;
                }
                current = playerA.first;             // 用pointer *current在list中移動
                while (current != 0) {                  // Traversal
                    if (current->shape==s) cout << current->shape<<current->data<<"("<<current->card_code<<")"<<endl;
                    current = current->next;
                }
                break;
            case 3:
                cout<<"The shape of the card: ";
                cin>>s;
                if (playerA.first == 0) {            // 如果first node指向NULL, 表示list沒有資料
                    cout << "List is empty.\n";
                    break;
                }
                if(isdigit(s)||(s!='S'&&s!='H'&&s!='D'&&s!='C')){
                    cout << "Wrong input!\n";
                    break;
                }
                playerA.Reverse();
                current = playerA.first;             // 用pointer *current在list中移動
                while (current != 0) {                  // Traversal
                    if (current->shape==s) cout << current->shape<<current->data<<"("<<current->card_code<<")"<<endl;
                    current = current->next;
                }
                playerA.Reverse();
                break;
            case 4:
                cout<<"The shape of the card: ";
                cin>>s;
                if (playerA.first == 0) {            // 如果first node指向NULL, 表示list沒有資料
                    cout << "List is empty.\n";
                    break;
                }
                if(isdigit(s)||(s!='S'&&s!='H'&&s!='D'&&s!='C')){
                    cout << "Wrong input!\n";
                    break;
                }
                for(int i=2;i<14;i++){
                    current=playerA.first;
                    while(current!=0){
                        if(current->shape==s && current->data==i){
                            cout << current->shape<<current->data<<"("<<current->card_code<<")"<<endl;
                        }
                        current=current->next;}
                }
                current=playerA.first;
                while(current!=0){
                    if(current->shape==s && current->data==1){
                        cout << current->shape<<current->data<<"("<<current->card_code<<")"<<endl;
                    }
                    current=current->next;}
                break;
            case 5:
                cout<<"The shape of the card: ";
                cin>>s;
                if(isdigit(s)||(s!='S'&&s!='H'&&s!='D'&&s!='C')){
                    cout << "Wrong input!\n";
                    break;
                }
                cout<<"The number of the card: ";
                cin>>num;
                if (playerA.first == 0) {            // 如果first node指向NULL, 表示list沒有資料
                    cout << "List is empty.\n";
                    break;
                }
                
                current=playerA.first;
                while(current!=0){
                    if(current->shape==s && current->data>num&&current->data<tagg){
                        tagg=current->data;
                    }
                    current=current->next;
                }
                if (tagg==14 && num>1) {
                    cout<<"delete: "<<s<<1<<endl;
                    playerA.Delete(1, s, 0);
                    break;
                } else if (tagg==14||num==1) {
                    cout<<"No corresponsed card!"<<endl;
                    break;
                }
                current=playerA.first;
                while(current!=0){
                    if(current->shape==s && current->data==tagg){
                        cout<<"delete: "<<s<<tagg<<endl;
                        playerA.Delete(tagg,s,(s-'0')*13+tagg);
                    }
                    current=current->next;
                }
                tagg=14;
                break;
            case 6:
                cout<<"change to next section!"<<endl;
                section_switch=1;
                break;
            default:
                return 0;
        }
        }
        while (section_switch==1) {
            cout<<"playerB function section: "<<endl;
            cout<<"-----------------------------------------------------------------------------------------------"<<endl;
            cout<<"Function choosing section:"<<endl;
            cout<<"1 for plusing n cards to list"<<endl;
            cout<<"2 for choosing a shape & listing in original order"<<endl;
            cout<<"3 for choosing a shape & listing in oppsite order"<<endl;
            cout<<"4 for choosing a shape & listing in value from smaller to bigger"<<endl;
            cout<<"5 for choosing a card & delete the minimum card among those bigger than the card you choose"<<endl;
            cout<<"6 for turn ending and switch to next section"<<endl;
            cout<<"others input for Exit"<<endl;
            cout<<"----------------------------------------------------------------------------------------------"<<endl;
            cout<<"you choose: ";
            int function=0;
            cin>>function;
            switch (function) {
                case 1:
                    cout<<"The number of the card: ";
                    cin>>n;
                    if (n>52||n<1) {
                        cout<<"NOT ALLOW NUMBER"<<endl;
                        break;
                    }
                    // randomly get n cards & link them
                    for (int i=0;i<n;i++) {
                        ListNode rand_card = random_get();
                        playerB.Push_back(rand_card.data, rand_card.shape, rand_card.card_code);
                        //cout <<"random card is "<<rand_card.data<<" "<<rand_card.shape<<" "<<rand_card.card_code<<"\n";
                    }
                    cout<<"Licensing......"<<endl;
                    playerB.PrintList();
                    //for (int i=0;i<53;i++) cout<<card_code_all[i];
                    //cout<<"\n";
                    cout<<"Licensed!"<<endl;
                    break;
                case 2:
                    cout<<"The shape of the card: ";
                    cin>>s;
                    if (playerB.first == 0) {            // 如果first node指向NULL, 表示list沒有資料
                        cout << "List is empty.\n";
                        break;
                    }
                    if(isdigit(s)||(s!='S'&&s!='H'&&s!='D'&&s!='C')){
                        cout << "Wrong input!\n";
                        break;
                    }
                    current = playerB.first;             // 用pointer *current在list中移動
                    while (current != 0) {                  // Traversal
                        if (current->shape==s) cout << current->shape<<current->data<<"("<<current->card_code<<")"<<endl;
                        current = current->next;
                    }
                    break;
                case 3:
                    cout<<"The shape of the card: ";
                    cin>>s;
                    if (playerB.first == 0) {            // 如果first node指向NULL, 表示list沒有資料
                        cout << "List is empty.\n";
                        break;
                    }
                    if(isdigit(s)||(s!='S'&&s!='H'&&s!='D'&&s!='C')){
                        cout << "Wrong input!\n";
                        break;
                    }
                    playerB.Reverse();
                    current = playerB.first;             // 用pointer *current在list中移動
                    while (current != 0) {                  // Traversal
                        if (current->shape==s) cout << current->shape<<current->data<<"("<<current->card_code<<")"<<endl;
                        current = current->next;
                    }
                    playerB.Reverse();
                    break;
                case 4:
                    cout<<"The shape of the card: ";
                    cin>>s;
                    if (playerB.first == 0) {            // 如果first node指向NULL, 表示list沒有資料
                        cout << "List is empty.\n";
                        break;
                    }
                    if(isdigit(s)||(s!='S'&&s!='H'&&s!='D'&&s!='C')){
                        cout << "Wrong input!\n";
                        break;
                    }
                    for(int i=2;i<14;i++){
                        current=playerB.first;
                        while(current!=0){
                            if(current->shape==s && current->data==i){
                                cout << current->shape<<current->data<<"("<<current->card_code<<")"<<endl;
                            }
                            current=current->next;}
                    }
                    current=playerB.first;
                    while(current!=0){
                        if(current->shape==s && current->data==1){
                            cout << current->shape<<current->data<<"("<<current->card_code<<")"<<endl;
                        }
                        current=current->next;}
                    break;
                case 5:
                    cout<<"The shape of the card: ";
                    cin>>s;
                    if(isdigit(s)||(s!='S'&&s!='H'&&s!='D'&&s!='C')){
                        cout << "Wrong input!\n";
                        break;
                    }
                    cout<<"The number of the card: ";
                    cin>>num;
                    if (playerB.first == 0) {            // 如果first node指向NULL, 表示list沒有資料
                        cout << "List is empty.\n";
                        break;
                    }
                    
                    current=playerB.first;
                    while(current!=0){
                        if(current->shape==s && current->data>num&&current->data<tagg){
                            tagg=current->data;
                        }
                        current=current->next;
                    }
                    if (tagg==14 && num>1) {
                        //cout<<tagg<<" "<<num<<endl;
                        cout<<"delete: "<<s<<1<<endl;
                        hand_field.Delete(1, s, 0);
                        break;
                    } else if (tagg==14||num==1) {
                        cout<<"No corresponsed card!"<<endl;
                        break;
                    }
                    current=playerB.first;
                    while(current!=0){
                        if(current->shape==s && current->data==tagg){
                            cout<<"delete: "<<s<<tagg<<endl;
                            playerB.Delete(tagg,s,(s-'0')*13+tagg);
                        }
                        current=current->next;
                    }
                    tagg=14;
                    break;
                case 6:
                    cout<<"change to next section!"<<endl;
                    section_switch=2;
                    break;
                default:
                    return 0;
            }
        }
        cout<<"playerA cards:"<<endl;
        playerA.PrintList();
        cout<<"playerB cards:"<<endl;
        playerB.PrintList();
        cout<<"battle: "<<endl;
        tagg=14;
        while(1) {
            break;
        }
        
    }else {
        cout<<"Wrong input!"<<endl;
        return 0;
    }
    
    return 0;
}
