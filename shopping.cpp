#include<iostream>
#include<fstream>
using namespace std;

class shopping{
    private:
        int pcode;
        float price;
        float discount;
        string pname;
    
    public:
        void menu();
        void administrator();
        void buyer();
        void add();
        void edit();
        void remove();
        void list();
        void receipt();

};

void shopping :: menu(){
    int choice;
    string email;
    string password;

    cout<<"\t\t\t\t_________________________________________________________\n";
    cout<<"\t\t\t\t                                                         \n";
    cout<<"\t\t\t\t                    Supermarket                          \n";
    cout<<"\t\t\t\t                                                         \n";
    cout<<"\t\t\t\t_________________________________________________________\n";
    cout<<"\t\t\t\t                                                         \n";
    m:
        cout<<"\t\t\t\t|       1] Administrator        |\n";
        cout<<"\t\t\t\t|                               |\n";
        cout<<"\t\t\t\t|       2]Buyer                 |\n";
        cout<<"\t\t\t\t|                               |\n";
        cout<<"\t\t\t\t|       3]Exit                  |\n";
        cout<<"\t\t\t\t|                               |\n";
        cout<<"\t\t\t\t Please enter your choice: ";
        cin>>choice;

        switch(choice){
            case 1:
                again:
                    cout<<"\t\t\t\t Please login: \n";
                    cout<<"\t\t\t\t Enter email: ";
                    cin>>email;
                    cout<<"\t\t\t\t Enter password: ";
                    cin>>password;

                    if(email=="robby@gmail.com" && password=="robby@123"){
                        administrator();
                    }
                    else{
                        cout<<"\t\t\t\t Invalid username or password\n";
                        goto again;
                    }
                    break;
            case 2:
                buyer();
                break;
            case 3:
                exit(0);
            default:
                cout<<"\t\t\t\t Please select from the given options\n";
                goto m;

    }
}

void shopping::administrator(){
    s:
        int choice;

        cout<<"\n\n\n\t\t Administrator Menu        ";
        cout<<"\t\t\t\t|___________1] Add the product_________________|\n";
        cout<<"\t\t\t\t|                                              |\n";
        cout<<"\t\t\t\t|___________2] Modify the product______________|\n";
        cout<<"\t\t\t\t|                                              |\n";
        cout<<"\t\t\t\t|___________3] Delete the product______________|\n";
        cout<<"\t\t\t\t|                                              |\n";
        cout<<"\t\t\t\t|___________4] Back to the main menu___________|\n";

        cout<<"\t\t Please enter your choice: ";
        cout<<choice;

        switch(choice){
            case 1:
                add();
                break;
            case 2:
                edit();
                break;
            case 3:
                remove();
                break;
            case 4:
                menu();
                break;
            default:
                cout<<"\t\t Please enter correct choice\n";
                goto s;
        }

}

void shopping::buyer(){
    m:
        int choice;
        cout<<"\n\n";
        cout<<"\t\t\t\t_______Buyer_______\n";
        cout<<"\t\t\t\t                   \n";
        cout<<"\t\t\t\t|       1]Buy a product        |\n";
        cout<<"\t\t\t\t|                              |\n";
        cout<<"\t\t\t\t|       2]Go back              |\n";
        cout<<"\t\t\t\t|                              |\n";

        cout<<"\t\t\t\t Please enter your choice: ";
        cin>>choice;

        switch(choice){
            case 1:
                receipt();
                break;
            case 2:
                menu();
                break;
            default:
                cout<<"Please enter correct option\n";
                goto m;
        }

}

void shopping::add(){
    m:
        fstream data;
        int c;
        int token=0;
        float p;
        float d;
        string n;

        cout<<"\n\n\t\t Add new product \n";
        cout<<"\t\t\t Product code of the product: ";
        cin>>pcode;
        cout<<"\n\t\t\t Name of the product: ";
        cin>>pname;
        cout<<"\n\t\t\t Price of the product: ";
        cin>>price;
        cout<<"\n\t\t\t Discount on the product: ";
        cin>>discount;

        data.open("database.txt", ios::in);
        if(!data){
            data.open("database.txt", ios::app|ios::out);
            data<<" "<<pcode<<" "<<pname<<" "<<price<<" "<<discount<<"\n";
            data.close();
        }
        else{
            data>>c>>n>>p>>d;

            while(!data.eof()){
                if(c==pcode){
                    token++;
                }
                data>>c>>n>>p>>d;
            }
            data.close();

            if(token==1){
                goto m;
            }
            else{

                data.open("database.txt", ios::app|ios::out);
                data<<" "<<pcode<<" "<<pname<<" "<<price<<" "<<discount<<"\n";
                data.close();
            }
        }
        cout<<"Record inserted"<<endl;
}

void shopping::edit(){
    fstream data,data1;
    int pkey;
    int token=0;
    int c;
    float p;
    float d;
    string n;

    cout<<"\n\t\t\t Modify the record";
    cout<<"\n\t\t\t Product code: ";
    cin>>pkey;

    data.open("database.txt",ios::in);
    if(!data){
        cout<<"\n\nFile does not exist! ";
    }
    else{
        data1.open("database1.txt",ios::app|ios::out);

        data>>pcode>>pname>>price>>discount;
        while(!data.eof()){
            if(pkey==pcode){
                cout<<"\n\t\t Product new code: ";
                cin>>c;
                cout<<"\n\t\t Name of the product: ";
                cin>>n;
                cout<<"\n\t\t Price: ";
                cin>>p;
                cout<<"\n\t\t Discount: ";
                cin>>d;
                data1<<" "<<c<<" "<<n<<" "<<p<<" "<<" "<<d<<"\n";
                cout<<"Record edited ";
                token++;
            }
            else{
                data1<<" "<<pcode<<" "<<pname<<" "<<price<<" "<<discount<<"\n";
            }
            data>>pcode>>pname>>price>>discount;

        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt","database.txt");

        if(token==0){
            cout<<"\n\n Record not found. Sorry!";
        }
    }
}

void shopping::remove(){
    fstream data,data1;
    int pkey;
    int token=0;
    cout<<"\n\t\t Delete the product";
    cout<<"\n\t\t Product code: ";
    cin>>pkey;
    data.open("database.txt",ios::in);
    if(!data){
        cout<<"File does not exist";
    }
    else{
        data1.open("databse1.txt",ios::app|ios::out);
        data>>pcode>>pname>>price>>discount;
        while(!data.eof()){
            if(pcode==pkey){
                cout<<"\n\t\t Product deleted successfully!";
                token++;
            }
            else{
                data1<<" "<<pcode<<" "<<pname<<" "<<price<<" "<<" "<<discount<<"\n";
            }
            data>>pcode>>pname>>price>>dis;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("databse1.txt","databse.txt");

        if(token==0){
            cout<<"\n\t\t Record not found. Sorry!";
        }
    }
}

void shopping::list(){
    fstream data;
    data.open("database.txt",ios::in);
    cout<<"\n|____________________________________________________________________|\n";
    cout<<"ProNo\t\tName\t\tPrice\n";
    cout<<"\n|____________________________________________________________________|\n";
    data>>pcode>>pname>>price>>discount;
    while(!data.eof()){
        cout<<pcode<<"\t"<<pname<<"\t"<<price<<"\n";
        data>>pcode>>pname>>price>>discount;
    }
    data.close();
}

void shopping::receipt(){
    m:
        fstream data;

        int arrc[100];
        int arrq[100];
        char choice;
        int c=0;
        float amount=0;
        float discount=0;
        float total=0;

        cout<<"\n\t\t\t RECEIPT ";
        data.open("databse.txt",ios::in);
        if(!data){
            cout<<"\n\t Empty database";
        }
        else{
            data.close();
            list();
            cout<<"\n__________________________________________________\n";
            cout<<"\n                                                  \n";
            cout<<"\n              Please place the order              \n";
            cout<<"\n                                                  \n";
            cout<<"\n__________________________________________________\n";

            
            do{
                cout<<"\n\t Enter the product code: ";
                cin>>arrc[c];
                cout<<"\n\t Enter the product quantity: ";
                cin>>arrq[c];
                for(int i=0;i<c;i++){
                    if(arr[c]==arr[i]){
                        cout<<"\n\t Duplicate product code.Please try again.";
                        goto m;
                    }
                }
                c++;
                cout<<"\n\t Do you want to buy another product? If yes type Y else type N";
                cin>>>choice;
            }
            while(choice=='Y');

            cout<<"\n\t\t\t\t______________________________RECEIPT__________________________________\n";
            cout<<"\nProduct no\t Product name\t Product quantity\t Price\t Amount with discount\n";
            for(int i-0;i<c;i++){
                data.open("database.txt",ios::in);
                data>>pcode>>pname>>price>>discount;
                while(!data.eof()){
                    if(pcode==arrc[i]){
                        amount=price*arrq[i];
                        discount=amount-(amount*discount/100);
                        total=total+discount;
                        cout<<"\n"<<pcode<<"\t"<<pname<<"\t"<<arrq[i]<<"\t"<<price<<"\t"<<amount<<"\t"<<discount;
                    }
                    data>>pcode>>pname>>price>>discount;
                }
            }
            data.close();
        }
        cout<<"\n\t\t________________________________________________\n";
        cout<<"\t\t Total Amount: "<<amount;
}

int main(){
    shopping s;
    s.menu();
}