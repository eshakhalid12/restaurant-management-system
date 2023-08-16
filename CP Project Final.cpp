//header files
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

//global declaration of some variables to be used
int bill=0;
string orderDet;
int cartSize=0;
string cart[10];

//function declaration
void customer();
void appetizers();
void mainCourse();
void dessert();
void menuFile();
void orderIntoFile(string custName, string tableNum, string orderDet, int bill);
void readOrder();
void menuIntoFile();


int main(){
	
	//checking if it is the admin or a customer
	
	char id;
	cout<<"press 'A' for admin "<<endl<<"press 'C' for customer: "<<endl;
	cin>>id;
	
	//if it is admin, confirming their identity
	
	if(id=='a'|| id=='A'){
		string pswd="admin123";
		string pswd2;
		cout<<"enter password to confirm authority:"<<endl;
		cin>>pswd2;
		
		if(pswd.compare(pswd2)==0){
		readOrder();
		}
		else{
			cout<<"invalid access restart the program";
		}
	}
	
	//if it is the customer 
	else if(id=='c'||id=='C'){
		
		menuFile();   //funtion calling to view the menu from file
		cout<<endl<<"!!! YOU CAN ORDER ONLY 10 ITEMS AT A TIME !!!"<<endl;
		customer();   //function callin to take orders
		
		//cart viewing
		cout<<endl<<"Would you like to view your cart? If yes, press 'y' else press 'n': ";
		char viewCart;
		cin>>viewCart;

		if(viewCart=='y') {
    	cout<<"Items in your cart:"<<endl;
    	for(int i=0;i<cartSize;i++){
        cout<<"Item "<<i+1<<": "<<cart[i]<<endl;
    	}
    	
		}
		
		cout<<"your order has been placed successfully, kindly wait while we prepare your order";
	}
	
	else{
		cout<<"invalid id";
	}
	
	return 0;
	
}

///function for saving menu into file
void menuFile(){
	
	ofstream rMenu;
	rMenu.open("rMenu.txt",ios::out);
	if(!rMenu){
		cout<<"error! file not found ";
	}
	
	//menu input into the file
	else{
		rMenu<<endl<<":::::::::MENU::::::::::"<<endl;
		rMenu<<endl<<"::::::Appetizers:::::::"<<endl;
		rMenu<<"garlic bread   PKR 200/-"<<endl;
		rMenu<<"corn soup   PKR 300/-"<<endl;
		rMenu<<"hot wings   PKR 500/-"<<endl;
		rMenu<<endl<<":::::Main Course::::::"<<endl;
		rMenu<<"biryani   PKR 400/-"<<endl;
		rMenu<<"chowmein   PKR 400/-"<<endl;
		rMenu<<"singaporean rice   PKR 500/-"<<endl;
		rMenu<<endl<<"::::::Desserts::::::"<<endl;
		rMenu<<"lava cake   PKR 700/-"<<endl;
	    rMenu<<"ice cream   PKR 300/-"<<endl;
	    rMenu<<"sundae   PKR 500/-"<<endl;
	    
	    rMenu.close();
	}
	
	//menu printing 
	ifstream displayMenu("rMenu.txt");
	string x;
	while(getline(displayMenu,x)){
		cout<<x<<endl;
	}
	displayMenu.close();
}

//function to save order into the file for admin to view
void orderIntoFile(string custName, string tableNum, string orderDetails, int bill) {
    
	ofstream orderFile("orderFile.txt", ios::app);
    
    if (!orderFile) {
        cout << "Error opening the file or file not found." << endl;
    }
    else {
        orderFile<<"Customer Name: "<<custName<<endl;
        orderFile<<"Table Number: "<<tableNum<<endl;
        orderFile<<"Order Summary:\n"<<orderDet<<endl;
        orderFile<<"Total Bill: PKR "<<bill<<"/-"<<endl;
        orderFile<<"--------------------------------------"<<endl;

        orderFile.close();
    }
}

//funtion to print the order stored into the previous file
void readOrder(){
	
	string order;
	ifstream orderFile;
	orderFile.open("orderFile.txt",ios::in);
	if(!orderFile){
		cout<<"file not found";
	}
	else{
		getline(orderFile,order);
		while(getline(orderFile,order)){
			cout<<order<<endl;
		}
		orderFile.close();
	}
	
}

//function to take order from appetizers
void appetizers() {
	
	//checking if the cart has space
	if(cartSize<10){
			
	char more ='y'; //choice variable
	while (more == 'y') {
		int order,price=0;
		cout<<"press 1 for garlic bread"<<endl<<"2 for corn soup"<<endl<<"3 for hot wings"; //choices
		cin>>order;
		switch(order){     
			case 1:
				price+=200;     //calculating and updating the bill
				orderDet+="Garlic bread  PKR 200/-";cout<<endl;   //saving the order details
				cart[cartSize]="Garlic bread  PKR 200/-";      //adding to the cart
				cartSize++;	   //updating the cart vacancy
				break;
			case 2:
			    price+=300;
			    orderDet+="Corn soup  PKR 300/-";cout<<endl;
			    cart[cartSize]="Corn soup  PKR 300/-";
			    cartSize++;
				break;
			case 3:
			    price+=500;
			    orderDet+="Hot wings  PKR 500/-";cout<<endl;
			    cart[cartSize]="Hot wings  PKR 500/-";
			    cartSize++;
				break;			
		}
		bill+=price;
		cout<<"the total is: "<<bill<<endl;
        cout<<"you can order "<<10-cartSize<<" more items"<<endl;
		cout<<"Do you want more from appetizers? Press 'y' to continue and 'n' to stop "<<endl;
		cin>>more;
		
	}
	//this part asks the user if they want to order anything else or checkout
	char choice2;
	cout<<"Would you like to order something from main course and desserts? press 'y' to continue 'n' to finalize your order "<<endl;
	cin>>choice2;
	if (choice2=='y'){
		customer();
	}
	else if (choice2=='n'){
		string custName,tableNum;
		
		//taking information for the order to be delivered correctly without any mistakes
		cout<<"Enter your name without spaces: ";
		cin>>custName;
		cout<<"Enter your table number: ";
		cin>>tableNum;
		
		orderIntoFile(custName,tableNum,orderDet,bill); //function calling to pass the customer details taken above
	
		cout<<"Your total bill is PKR "<<bill<<" kindly prepare in advance to avoid inconvenience";
		
	}
	
	}
	else if(cartSize>=10){
		cout<<"your cart is full, please proceed to place your order to order more "<<endl;
		string custName,tableNum;
		
		cout<<"Enter your name without spaces: ";
		cin>>custName;
		cout<<"Enter your table number: ";
		cin>>tableNum;
		
		orderIntoFile(custName,tableNum,orderDet,bill);
	
		cout<<"your total bill is PKR "<<bill<<" kindly prepare it on time"<<endl;
	}
	}
void mainCourse() {
	if(cartSize<10){
	char more = 'y';
	while (more == 'y') {
		
		int order,price=0;
		cout<<"press 1 for biryani"<<endl<<"2 for chowmein"<<endl<<"3 for singaporean rice";
		cin>>order;
		switch(order){
			case 1:
				price+=400;	
				orderDet+="biryani  PKR 400/-";cout<<endl;
				cart[cartSize]="biryani  PKR 400/-";
				cartSize++;
				break;
			case 2:
			    price+=400;
			    orderDet+="chowmein  PKR 400/-";cout<<endl;
			    cart[cartSize]="chowmein  PKR 400/-";
			    cartSize++;
				break;
			case 3:
			    price+=900;
			    orderDet+="singaporean rice  PKR 500/-";cout<<endl;
			    cart[cartSize]="singaporean rice  PKR 500/-";
			    cartSize++;
				break;			
		}
		
		bill+=price;
		cout<<"the total is: "<<bill<<endl;
		cout<<"you can order "<<10-cartSize<<" more items"<<endl;
		cout<<"Do you want more from main course? Press 'y' to continue and 'n' to stop "<<endl;
		cin>>more;
	}
	char choice2;
	cout<<"Would you like to order something from appetizers or desserts? press 'y' to continue 'n' to finalize your order "<<endl;
	cin>>choice2;
	if (choice2=='y'){
		customer();
	}
	else if (choice2=='n'){
		string custName,tableNum;
		
		cout<<"Enter your name without spaces: ";
		cin>>custName;
		cout<<"Enter your table number: ";
		cin>>tableNum;
		
		orderIntoFile(custName,tableNum,orderDet,bill);
	
		cout<<"your total bill is PKR "<<bill<<" kindly prepare it on time"<<endl;
	}
}

	
	else if(cartSize>=10){
		cout<<"your cart is full, please proceed to place your order to order more "<<endl;
		string custName,tableNum;
		
		cout<<"Enter your name without spaces: ";
		cin>>custName;
		cout<<"Enter your table number: ";
		cin>>tableNum;
		
		orderIntoFile(custName,tableNum,orderDet,bill);
	
		cout<<"your total bill is PKR "<<bill<<" kindly prepare it on time"<<endl;
	}
}

void dessert() {
	if(cartSize<10){
	char more = 'y';
	while (more == 'y') {
		
		int order,price=0;
		cout<<"press 1 for lava cake"<<endl<<"2 for ice cream"<<endl<<"3 for sundae";
		cin>>order;
		switch(order){
			case 1:
				price+=700;	
				orderDet+="lava cake  PKR 700/-";
				cart[cartSize]="lava cake  PKR 700/-";
				cartSize++;
				break;
			case 2:
			    price+=300;
			    orderDet+="ice cream  PKR 300/-";
			    cart[cartSize]="ice cream  PKR 300/-";
			    cartSize++;
				break;
			case 3:
			    price+=500;
			    orderDet+="sundae  PKR 500/-";
			    cart[cartSize]="sundae  PKR 500/-";
			    cartSize++;
				break;			
		}
		bill+=price;
		cout<<"the total is: "<<bill<<endl;
		cout<<"you can order "<<10-cartSize<<" more items"<<endl;
		cout<<"Do you want more from dessert? Press 'y' to continue and 'n' to stop"<<endl;
		cin>>more;
	}
char choice2;
	cout<<"Would you like to order something from appetizers or main course? press 'y' to continue 'n' to finalize your order "<<endl;
	cin>>choice2;
	if (choice2=='y'){
		customer();
	}
	else if (choice2=='n'){
		string custName,tableNum;
		
		cout<<"Enter your name without spaces: ";
		cin>>custName;
		cout<<"Enter your table number: ";
		cin>>tableNum;
		
		orderIntoFile(custName,tableNum,orderDet,bill);
	
		cout<<"your total bill is PKR "<<bill<<" kindly prepare it on time"<<endl;
	}
}

	
	else if(cartSize>=10){
		cout<<"your cart is full, please proceed to place your order to order more "<<endl;
		string custName,tableNum;
		
		cout<<"Enter your name without spaces: ";
		cin>>custName;
		cout<<"Enter your table number: ";
		cin>>tableNum;
		
		orderIntoFile(custName,tableNum,orderDet,bill);
	
		cout<<"your total bill is PKR "<<bill<<" kindly prepare it on time"<<endl;
	}
}

void customer(){
	char choice;
	
	cout<<"enter 'A' for appetizers"<<endl<<"enter 'M' for main course"<<endl<<"enter 'D' for desserts: "<<endl;
	cin>>choice;

	if (choice == 'a'|| choice=='A'){
		appetizers();
	} 
	else if (choice == 'm'|| choice=='M' ) {
		mainCourse();
	} 
	else if (choice == 'd' || choice=='D') {
		dessert();
	} 
	else {
		cout << "Invalid choice!"<<endl;
		customer();  //recusrion in case the user inputs wrong choice by mistake
	}
	}
