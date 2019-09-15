#include<iostream>
#include<conio.h>
#include<string.h>
#include<cctype>
#include<iomanip>
#include<Windows.h>
#include<fstream>

using namespace std;

class Admin
{
    public:
    void create_event()
    {
        ofstream ofs;
          string price,host,date,time,name;
      cout<<"Enter Event Organizer"<<endl;
      cin>>host;
      cout<<"Enter the event date(dd/mm/yyyy) and time(24hr System)"<<endl;
      cin>>date>>time;
      cout<<"Enter the name of the event"<<endl;
      cin>>name;
      cout<<"Enter the price per ticket"<<endl;
      cin>>price;
	 ofs.open("Events.txt", ios::out | ios::app);

                            ofs<<host<<"\t\t"<<date<<"\t"<<time<<"\t\t"<<name<<"\t"<<price<<endl;

                    ofs.close();
                    cout<<"Event Created"<<endl;
    }
};

class Host
    {
    char username[20],mail[30],eventname[30],start[20],enddate[20],venue[20],description[500],coupon[20],message[500],timing[20];
    char ch;
    int choice,pay,tktno,pass1,pass2,pass3;
    float price;
    double pno;
    public:
    Host() //constructor called
    {
       eventname;
       mail;
       pno;
       start;
       enddate;
       venue;
       description;
       coupon;
       message;
       timing;
       choice=0;
       tktno=0;
       price=0.00;

    }

    void register1()//Registration for host
    {
        int flag = 0;
        cout<<"Enter your name:"<<endl;
        cin>>username;
        mail1:
        cout<<"Enter your email id:"<<endl;
        cin>>mail;
        for(int f=0;f<sizeof(mail);f++)
            {
                if(mail[f]=='@' || mail[f]=='.')
                {
                    flag+=1;
                }
            }
                if(flag>1)
                {
                    goto phone;
                }
                else if(flag< 2)
                {
                    cout<<"Please enter a valid email address"<<endl;
                    goto mail1;
                }
        phone:
        cout<<"Enter your phone no:"<<endl;
        cin>>pno;
        if(7000000000<=pno && pno<=9999999999)
            {
                goto Password;
            }
        else
        {
            cout<<"Please enter a valid phone number!"<<endl;
            goto phone;
        }
        do
        {
            Password:
        cout<<"Enter password:\n(Password should be a four digit number)"<<endl;
         cin>>pass1;
         if(pass1>=1000 && pass1<=9999)
         {
        cout<<"\nConfirm password:"<<endl;
        cin>>pass2;
         }
         else
            {
                cout<<"Your password must be a four digit number!"<<endl;
                goto Password;
            }

        }
        while(pass1!=pass2);
    }

    void write_account()//store data
    {
	Host h1;
	ofstream outFile;
	outFile.open("Account.txt",ios::app|ios::binary);
	h1.register1();
	outFile.write(reinterpret_cast<char *> (&h1), sizeof(Host));
	outFile.close();
    }

    int returnpassword() const
    {
        return pass1;
    }

    void login()
    {
        int n;
        char name[50];
        cout<<"Enter your name:"<<endl;
        cin>>name;
        repeat1:
        cout<<"Enter your password:"<<endl;
        cin>>n;
        Host h1;
        bool flag=false;
        ifstream inFile;
        inFile.open("Account.txt",ios::binary);
        if(!inFile)
        {
		cout<<"Account could not be open !! Press any Key...";
		return;
	}
        while(inFile.read(reinterpret_cast<char *> (&h1), sizeof(Host)))
	{
		if(h1.returnpassword()==n)
		{
		    flag=true;
			h1.show_account();

		}
	}
	inFile.close();
	if(flag==false)
    {
		cout<<"Incorrect password\n";
		goto repeat1;
    }
}

    void show_account()
    {
	cout<<"\nLogin Successful"<<endl;
	//create_event();
    }

    void create_event()//Event Detail Form filled by host for guests
    {

        //char eventname[20];
        Guestpassword:
        cout<<"Enter the password for guests\n(Password must be a four digit number)"<<endl;
        cin>>pass3;
        if(pass3>=1000 && pass3<=9999)
        {
          goto hey;
        }
        else
            {
                cout<<"Your password must be a four digit number!"<<endl;
                goto Guestpassword;
            }

        hey:
        cout<<"Note:Donot use spaces between words!!\nUse '_' or '-' instead"<<endl;
        cout<<"Enter event name:"<<endl;
        cin>>eventname;
        cout<<"Event Visibility\n1.Public\n2.Private"<<endl;
        cin>>choice;
        cout<<"Event Start Date:"<<endl;
        cin>>start;
        cout<<"Event End Date:"<<endl;
        cin>>enddate;
        cout<<"Enter the timing:"<<endl;
        cin>>timing;
        cout<<"Enter the venue:"<<endl;
        cin>>venue;
        //cout<<"Enter event description:"<<endl;
        //cin>>description;
        cout<<"Is the event paid?\n1.Yes\n2.No"<<endl;
        cin>>pay;
        if(pay==1)
        {
            cout<<"Enter your ticket/coupon name"<<endl;
            cin>>coupon;
            cout<<"Enter the maximum qty of tickets/coupons available:"<<endl;
            cin>>tktno;
            cout<<"Enter the price per ticket"<<endl;
            cin>>price;
        }
            cout<<"Message to attendee"<<endl;
            cin>>message;
        }
        void write_Event()//store Event Details
    {
	Host h1;
	ofstream Event;
	Event.open("Event Details.txt",ios::app|ios::binary);
	h1.create_event();
	Event.write(reinterpret_cast<char *> (&h1), sizeof(Host));
	Event.close();
    }
    void show_eventdetails()
        {
            cout<<"Event name:"<<eventname<<endl;
            cout<<"Event Start Date:"<<start<<endl;
            cout<<"Event End Date:"<<enddate<<endl;
            cout<<"Timing:"<<timing<<endl;
            cout<<"Venue:"<<venue<<endl;
            //cout<<"Event description:"<<description<<endl;
            cout<<"Price per ticket:"<<price<<endl;
            cout<<"Message to attendee:"<<message<<endl;
        }
    int returnpasswordguest()
    {
	return pass3;
    }
    void display_eventdetails(int p)
    {
    repeat:
    cout<<"Enter the 4 digit password given by the host:"<<endl;
    cin>>p;
    Host h1;
    bool flag=false;
    ifstream inputFile;
    inputFile.open("Event Details.txt",ios::binary);
    if(!inputFile)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }

        while(inputFile.read(reinterpret_cast<char *> (&h1), sizeof(Host)))
    {
        if(h1.returnpasswordguest()==p)
        {
            cout<<"\n EVENT DETAILS\n";
            flag=true;
            h1.show_eventdetails();
        }
    }
    inputFile.close();
    if(flag==false)
    {
        cout<<"\nEvent does not exist\n";
        goto repeat;
    }

}

   void view_events()
    {
        string flights;
        ifstream File;
        int u=0;
        cout<<"EventNo Organiser        Date           Time            Event Name     Price(in Rupees)"<<endl;
         ifstream myfile ("Events.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,flights) )
    {
        u++;
      cout <<u<<"\t"<< flights<< '\n';
    }
    myfile.close();
  }
  else
    cout << "Unable to open file";
    }

    void book_tickets()
    {
        ifstream file;
        ofstream ofs;
        int a;
        start1:
        cout<<"Enter the event number"<<endl;
        cin>>a;
        int u=0;
        int available[100];
        file.open("Available.txt");
            while(!file.eof())
            {
                file>>available[u];
                u++;
            }
            file.close();

            switch(a)
            {
                case 1: {
                        int number;
                        cout<<" Available tickets:"<<available[0];
                        cout<<"Enter the no of tickets you want to purchase"<<endl;
                        cin>>number;
                        int a;
                        a=available[0];
                        a=a-number;
                        if (a<0)
                        {
                            cout<<"Tickets sold Out!";
                            goto start1;
                        }
                        else
                        {
                            available[0]=a;
                            ofs.open("Available.txt", ios::out | ios::trunc);
                                for(int k = 0 ; k < 100 ; k++){
                                        ofs<<available[k]<<endl;
                                            }
                                    ofs.close();
                        }
                        cout<<"Booking Ticket............."<<endl;
                        Sleep(500);
                        cout<<"\nTicket Booked!"<<endl;
                        }
                        break;
                        case 2: {
                        int number;
                        cout<<" Available tickets:"<<available[1];
                        cout<<"Enter the no of tickets you want to purchase"<<endl;
                        cin>>number;
                        int a;
                        a=available[1];
                        a=a-number;
                        if (a<0)
                        {
                            cout<<"Tickets sold Out!"<<endl;
                            goto start1;
                        }
                        else
                        {
                            available[1]=a;
                            ofs.open("Available.txt", ios::out | ios::trunc);
                                for(int k = 0 ; k < 100 ; k++){
                                        ofs<<available[k]<<endl;
                                            }
                                    ofs.close();
                        }
                        cout<<"Booking Ticket............."<<endl;
                        Sleep(500);
                        cout<<"\nTicket Booked!"<<endl;
                        }
                        break;
                        case 3: {
                        int number;
                        cout<<" Available tickets:"<<available[2];
                        cout<<"Enter the no of tickets you want to purchase"<<endl;
                        cin>>number;
                        int a;
                        a=available[2];
                        a=a-number;
                        if (a<0)
                        {
                            cout<<"Tickets sold Out!";
                            goto start1;
                        }
                        else
                        {
                            available[2]=a;
                            ofs.open("Available.txt", ios::out | ios::trunc);
                                for(int k = 0 ; k < 100 ; k++){
                                        ofs<<available[k]<<endl;
                                            }
                                    ofs.close();
                        }
                        cout<<"Booking Ticket............."<<endl;
                        Sleep(500);
                        cout<<"\nTicket Booked!"<<endl;
                        }
                        break;
                        case 4: {
                        int number;
                        cout<<" Available tickets:"<<available[3];
                        cout<<"Enter the no of tickets you want to purchase"<<endl;
                        cin>>number;
                        int a;
                        a=available[3];
                        a=a-number;
                        if (a<0)
                        {
                            cout<<"Tickets sold Out!";
                            goto start1;
                        }
                        else
                        {
                            available[3]=a;
                            ofs.open("Available.txt", ios::out | ios::trunc);
                                for(int k = 0 ; k < 100 ; k++){
                                        ofs<<available[k]<<endl;
                                            }
                                    ofs.close();
                        }
                        cout<<"Booking Ticket............."<<endl;
                        Sleep(500);
                        cout<<"\nTicket Booked!"<<endl;
                        }
                        break;
                        case 5: {
                        int number;
                        cout<<" Available tickets:"<<available[4];
                        cout<<"Enter the no of tickets you want to purchase"<<endl;
                        cin>>number;
                        int a;
                        a=available[4];
                        a=a-number;
                        if (a<0)
                        {
                            cout<<"Tickets sold Out!";
                            goto start1;
                        }
                        else
                        {
                            available[4]=a;
                            ofs.open("Available.txt", ios::out | ios::trunc);
                                for(int k = 0 ; k < 100 ; k++){
                                        ofs<<available[k]<<endl;
                                            }
                                    ofs.close();
                        }
                        cout<<"Booking Ticket............."<<endl;
                        Sleep(500);
                        cout<<"\nTicket Booked!"<<endl;
                        }
                        break;
                        case 6: {
                        int number;
                        cout<<" Available tickets:"<<available[5];
                        cout<<"Enter the no of tickets you want to purchase"<<endl;
                        cin>>number;
                        int a;
                        a=available[5];
                        a=a-number;
                        if (a<0)
                        {
                            cout<<"Tickets sold Out!";
                            goto start1;
                        }
                        else
                        {
                            available[5]=a;
                            ofs.open("Available.txt", ios::out | ios::trunc);
                                for(int k = 0 ; k < 100 ; k++){
                                        ofs<<available[k]<<endl;
                                            }
                                    ofs.close();
                        }
                        cout<<"Booking Ticket............."<<endl;
                        Sleep(500);
                        cout<<"\nTicket Booked!"<<endl;
                        }
                        break;
                        case 7: {
                        int number;
                        cout<<" Available tickets:"<<available[6];
                        cout<<"Enter the no of tickets you want to purchase"<<endl;
                        cin>>number;
                        int a;
                        a=available[6];
                        a=a-number;
                        if (a<0)
                        {
                            cout<<"Tickets sold Out!";
                            goto start1;
                        }
                        else
                        {
                            available[6]=a;
                            ofs.open("Available.txt", ios::out | ios::trunc);
                                for(int k = 0 ; k < 100 ; k++){
                                        ofs<<available[k]<<endl;
                                            }
                                    ofs.close();
                        }
                        cout<<"Booking Ticket............."<<endl;
                        Sleep(500);
                        cout<<"\nTicket Booked!"<<endl;
                        }
                        break;
                        case 8: {
                        int number;
                        cout<<" Available tickets:"<<available[7];
                        cout<<"Enter the no of tickets you want to purchase"<<endl;
                        cin>>number;
                        int a;
                        a=available[7];
                        a=a-number;
                        if (a<0)
                        {
                            cout<<"Tickets sold Out!";
                            goto start1;
                        }
                        else
                        {
                            available[7]=a;
                            ofs.open("Available.txt", ios::out | ios::trunc);
                                for(int k = 0 ; k < 100 ; k++){
                                        ofs<<available[k]<<endl;
                                            }
                                    ofs.close();
                        }
                        cout<<"Booking Ticket............."<<endl;
                        Sleep(500);
                        cout<<"\nTicket Booked!"<<endl;
                        }
                        break;
                        case 9: {
                        int number;
                        cout<<" Available tickets:"<<available[8];
                        cout<<"Enter the no of tickets you want to purchase"<<endl;
                        cin>>number;
                        int a;
                        a=available[8];
                        a=a-number;
                        if (a<0)
                        {
                            cout<<"Tickets sold Out!";
                            goto start1;
                        }
                        else
                        {
                            available[8]=a;
                            ofs.open("Available.txt", ios::out | ios::trunc);
                                for(int k = 0 ; k < 100 ; k++){
                                        ofs<<available[k]<<endl;
                                            }
                                    ofs.close();
                        }
                        cout<<"Booking Ticket............."<<endl;
                        Sleep(500);
                        cout<<"\nTicket Booked!"<<endl;
                        }
                        break;
                        case 10: {
                        int number;
                        cout<<" Available tickets:"<<available[9];
                        cout<<"Enter the no of tickets you want to purchase"<<endl;
                        cin>>number;
                        int a;
                        a=available[9];
                        a=a-number;
                        if (a<0)
                        {
                            cout<<"Tickets sold Out!";
                            goto start1;
                        }
                        else
                        {
                            available[9]=a;
                            ofs.open("Available.txt", ios::out | ios::trunc);
                                for(int k = 0 ; k < 100 ; k++){
                                        ofs<<available[k]<<endl;
                                            }
                                    ofs.close();
                        }
                        cout<<"Booking Ticket............."<<endl;
                        Sleep(500);
                        cout<<"\nTicket Booked!"<<endl;
                        }
                        break;

            }
    }
};

void venue2()
    {

            int o;
            cout<<"enter your choice:"<<endl;
            cout<<"1.Open Air venues\n2.Restaurants with private dining rooms"<<endl;
            cin>>o;
            switch(o)
                {
                    case 1:
                        {
                            string line;
                            ifstream myfile("OpenAirVenue.txt");
                            if(myfile.is_open())
                            {
                            while(getline(myfile,line))
                            {
                                cout<<line<<'\n';
                            }
                                myfile.close();
                            }

                        }
                        break;
                      case 2:
                        {
                            string line;
                            ifstream myfile("Restaurants.txt");
                            if(myfile.is_open())
                                {
                                    while(getline(myfile,line))
                                        {
                                            cout<<line<<'\n';
                                        }
                            myfile.close();
                                }
                        }
                        break;
                      default:
                        cout<<"ERROR!"<<endl;
                        break;
                }

    }

    void venue()
    {
        int s;
        int k;
        do
        {
        cout<<"\n"<<endl;
        cout<<"How would you like to search for venue?"<<endl;
        cout<<"1.Search by area \n2.Search by no. of people\n3.Search by type of venue"<<endl;
        cin>>k;
        switch(k)
        {
        case 1:
            {
                int l;
                cout<<"Choose your area:\n1.Andheri\n2.Bandra\n3.Colaba\n4.Dadar\n5.Juhu\n6.Malad\n7.Navi Mumbai\n8.Thane\n9.Powai\n10.Vashi"<<endl;
                cin>>l;
                switch(l)
                {
                    case 1:
                    {
                        string line;
                        ifstream myfile("andheri.txt");
                        if(myfile.is_open())
                            {
                                while(getline(myfile,line))
                                {
                                    cout<<line<<'\n';
                                }
                        myfile.close();
                            }
                    }
                    break;
                    case 2:
                    {
                        string line;
                        ifstream myfile("bandra.txt");
                        if(myfile.is_open())
                        {
                        while(getline(myfile,line))
                        {
                            cout<<line<<'\n';
                        }
                        myfile.close();
                        }
                    }
                    break;
                    case 3:
                    {
                        string line;
                        ifstream myfile("colaba.txt");
                        if(myfile.is_open())
                        {
                        while(getline(myfile,line))
                        {
                            cout<<line<<'\n';
                        }
                        myfile.close();
                        }
                    }
                    break;
                    case 4:
                    {
                        string line;
                        ifstream myfile("dadar.txt");
                        if(myfile.is_open())
                        {
                        while(getline(myfile,line))
                        {
                            cout<<line<<'\n';
                        }
                        myfile.close();
                        }
                    }
                    break;
                    case 5:
                    {
                        string line;
                        ifstream myfile("juhu.txt");
                        if(myfile.is_open())
                        {
                        while(getline(myfile,line))
                        {
                            cout<<line<<'\n';
                        }
                        myfile.close();
                        }

                    }
                    break;
                    case 6:
                    {
                        string line;
                        ifstream myfile("malad.txt");
                        if(myfile.is_open())
                        {
                        while(getline(myfile,line))
                        {
                            cout<<line<<'\n';
                        }
                        myfile.close();
                        }
                    }
                    break;
                    case 7:
                    {
                        string line;
                        ifstream myfile("navi mumbai.txt");
                        if(myfile.is_open())
                        {
                        while(getline(myfile,line))
                        {
                            cout<<line<<'\n';
                        }
                        myfile.close();
                        }
                    }
                    break;
                    case 8:
                    {
                    string line;
                    ifstream myfile("thane.txt");
                    if(myfile.is_open())
                    {
                        while(getline(myfile,line))
                        {
                            cout<<line<<'\n';
                        }
                    myfile.close();
                    }
                    }
                    break;
                    case 9:
                    {
                    string line;
                    ifstream myfile("powai.txt");
                    if(myfile.is_open())
                    {
                        while(getline(myfile,line))
                        {
                            cout<<line<<'\n';
                        }
                    myfile.close();
                    }
                    }
                    break;
                    case 10:
                    {
                    string line;
                    ifstream myfile("vashi.txt");
                    if(myfile.is_open())
                    {
                        while(getline(myfile,line))
                        {
                            cout<<line<<'\n';
                        }
                    myfile.close();
                    }
                    }
                    break;
                    default:
                        cout<<"ERROR!"<<endl;
                        break;
        }
        break;
    }
    case 2:
               {

                   int m;
                   cout<<"Select the number of people attending the event:"<<endl;
                   cout<<"1.Upto 500\n2.500-1000\n3.1000+"<<endl;
                   cin>>m;
                   switch(m)
                   {
                   case 1:
                    {
                        string line;
                        ifstream myfile("VenueUpto500.txt");
                        if(myfile.is_open())
                        {
                            while(getline(myfile,line))
                            {
                                cout<<line<<'\n';
                            }
                        myfile.close();
                        }

                   }
                   break;
                   case 2:
                    {
                       string line;
                       ifstream myfile("Venue500-1000.txt");
                        if(myfile.is_open())
                        {
                            while(getline(myfile,line))
                            {
                                cout<<line<<'\n';
                            }
                        myfile.close();
                        }
                    }
                    break;
                   case 3:
                    {
                        string line;
                        ifstream myfile("Venue1000+.txt");
                        if(myfile.is_open())
                        {
                        while(getline(myfile,line))
                        {
                            cout<<line<<'\n';
                        }
                        myfile.close();
                        }
                   }
                   break;
                   default:
                    cout<<"ERROR!"<<endl;
                    break;
                   }
               }
              break;
              case 3:
                    venue2();
                    break;
              default:
                cout<<"ERROR!"<<endl;
                break;

    }
        cout<<"\n";
        cout<<"What would you like to do?"<<endl;
        cout<<"1.Continue looking for other venues\n2.Exit"<<endl;
        cin>>s;
    }
    while(s!=2);
    }

void meal()
{
    int w;
    do
    {
    cout<<"\n";
    cout<<"\n";
    int x,y,z;
    cout<<"How would you like to browse the caterers for your event?"<<endl;
    cout<<"1.Search by number of people\n2.Search by price per plate"<<endl;
    cin>>z;
    switch(z)
    {
    case 1:
        {
        cout<<"How many people would be attending the event?"<<endl;
        cout<<"1.1-100\n2.100-1000\n3.More than 1000"<<endl;
        cin>>y;
        switch(y)
        {
        case 1:
            {
             string line;
             ifstream myfile("Caterers100.txt");
                if(myfile.is_open())
                {
                while(getline(myfile,line))
                {
                  cout<<line<<'\n';
                }
              myfile.close();
                }
            }
        break;
        case 2:
            {
             string line;
             ifstream myfile("Caterers100-500.txt");
             if(myfile.is_open())
             {
                while(getline(myfile,line))
                {
                  cout<<line<<'\n';
                }
              myfile.close();
             }
            }
        break;
        case 3:
        {
             string line;
             ifstream myfile("Caterers1000+.txt");
             if(myfile.is_open())
             {
                while(getline(myfile,line))
                {
                  cout<<line<<'\n';
                }
              myfile.close();
             }
        }
        break;
        default:
            cout<<"ERROR!"<<endl;
        }
        break;
    }
    case 2:
        {
        cout<<"What is the range of price(per plate)you're looking for?"<<endl;
        cout<<"1.Upto Rs 400\n2.Upto Rs 700\n3.Above Rs 700"<<endl;
        cin>>x;
        switch(x)
        {
        case 1:
            {
             string line;
             ifstream myfile("CaterersUptoRs400.txt");
             if(myfile.is_open())
             {
                while(getline(myfile,line))
                {
                  cout<<line<<'\n';
                }
              myfile.close();
             }
            }
        break;
        case 2:
            {
             string line;
             ifstream myfile("CaterersUptoRs700.txt");
             if(myfile.is_open())
             {
                while(getline(myfile,line))
                {
                  cout<<line<<'\n';
                }
              myfile.close();
             }
            }
        break;
        case 3:
            {
             string line;
             ifstream myfile("CaterersAboveRs700.txt");
             if(myfile.is_open())
             {
                while(getline(myfile,line))
                {
                  cout<<line<<'\n';
                }
              myfile.close();
             }
            }
        break;
        default:
            cout<<"ERROR!";
        }
        break;
    }
        default:
            cout<<"ERROR!";
            break;
    }
            cout<<"\n";
            cout<<"What would you like to do?"<<endl;
            cout<<"1.Continue looking for other caterers\n2.Exit"<<endl;
            cin>>w;
    }
    while(w!=2);

}

void extras()
{
   int t;
   do
   {
   int u,v;
   cout<<"\n";
   cout<<"\n";
   cout<<"Would you like to search for any additional requirements?"<<endl;
   cout<<"1.Anchors\n2.Choreographers\n3.DJs\n4.Entertainers\n5.Gifting\n6.MakeUp Artist\n7.Photographer\n8.Wedding related additional requirements"<<endl;
   cin>>u;
   switch(u)
   {
   case 1:
    {
             string line;
             ifstream myfile("Anchors.txt");
             if(myfile.is_open())
             {
                while(getline(myfile,line))
                {
                  cout<<line<<'\n';
                }
              myfile.close();
             }
    }
    break;
   case 2:
    {
             string line;
             ifstream myfile("Choreographers.txt");
             if(myfile.is_open())
             {
                while(getline(myfile,line))
                {
                  cout<<line<<'\n';
                }
              myfile.close();
             }
    }
    break;
   case 3:
    {
             string line;
             ifstream myfile("DJs.txt");
             if(myfile.is_open())
             {
                while(getline(myfile,line))
                {
                  cout<<line<<'\n';
                }
              myfile.close();
             }
    }
    break;
   case 4:
    {
             string line;
             ifstream myfile("Entertainers.txt");
             if(myfile.is_open())
             {
                while(getline(myfile,line))
                {
                  cout<<line<<'\n';
                }
              myfile.close();
             }
    }
    break;
   case 5:
    {
             string line;
             ifstream myfile("Gifting.txt");
             if(myfile.is_open())
             {
                while(getline(myfile,line))
                {
                  cout<<line<<'\n';
                }
              myfile.close();
             }
    }
    break;
   case 6:
    {
             string line;
             ifstream myfile("MakeupArtists.txt");
             if(myfile.is_open())
             {
                while(getline(myfile,line))
                {
                  cout<<line<<'\n';
                }
              myfile.close();
             }
    }
    break;
   case 7:
    {
             string line;
             ifstream myfile("Photographers.txt");
             if(myfile.is_open())
             {
                while(getline(myfile,line))
                {
                  cout<<line<<'\n';
                }
              myfile.close();
             }
    }
    break;
   case 8:
    {
        cout<<"1.Mehendi Designers\n2.Pandits"<<endl;
        cin>>v;
        switch(v)
        {
        case 1:
            {
             string line;
             ifstream myfile("MehendiDesigners.txt");
             if(myfile.is_open())
             {
                while(getline(myfile,line))
                {
                  cout<<line<<'\n';
                }
              myfile.close();
             }
            }
            break;
        case 2:
            {
             string line;
             ifstream myfile("Pandits.txt");
             if(myfile.is_open())
             {
                while(getline(myfile,line))
                {
                  cout<<line<<'\n';
                }
              myfile.close();
             }
            }
            break;
            default:
            cout<<"ERROR!";
        }
        break;
    }
    default:
            cout<<"ERROR!";
   }
    cout<<"\n";
    cout<<"What would you like to do?"<<endl;
    cout<<"1.Continue looking for other additional requirements\n2.Exit"<<endl;
    cin>>t;
   }
   while(t!=2);


}

int main()
{
     cout<<"WELCOME  TO   MY   EVENT   MANAGER"<<endl;
     cout<<"************************************"<<endl;
     int choice1,choice,choice2,n,p;
     string name,guestname;
     char ch;
     Host h1;
Admin a1;
        starters:
     cout<<"Login as\n1.Host\n2.Guest\n3.Admin\n4.Exit"<<endl;
     cin>>choice;
      switch(choice)
        {
        case 1:
            start:
            cout<<"1.Sign up\n2.Login"<<endl;
            cin>>choice1;
            switch(choice1)
                {
                    case 1:
                        h1.write_account();
                        goto start;
                        break;
                    case 2:
                        h1.login();
                        Mainmenu:
                        cout<<"\nWhat would you like to do?\n1.Browse for event necessities\n2.Create invitation for Guests"<<endl;
                        cin>>choice2;
                            switch(choice2)
                            {
                                case 1:
                                {
                                    int a,q,h,i,t;
                                    string e,d;
                                    cout<<"What is your event type?"<<endl;
                                    cout<<"1.Formal\n2.Informal"<<endl;
                                    cin>>a;
                                    switch(a)
                                        {
                                            case 1:
                                            int b;
                                            cout<<"What is your event?"<<endl;
                                            cout<<"1.Seminar\n2.Workshop\n3.Conference\n4.Business dinner\n5.Press conference\n6.Trade shows\n7.Sports events\n8.Other"<<endl;
                                            cin>>b;
                                            if(b==8)
                                                {
                                                    cout<<"Enter is your event:"<<endl;
                                                    cin>>d;
                                                }
                                            break;
                                            case 2:
                                                int c;
                                                cout<<"What is your event?"<<endl;
                                                cout<<"1.Birthday\n2.Wedding\n3.Anniversary\n4.Funeral\n5.Family Gathering\n6.Baby shower\n7.Celebrations\n8.Other"<<endl;
                                                cin>>c;
                                                if(c==8)
                                                {
                                                    cout<<"Enter is your event:"<<endl;
                                                    cin>>e;
                                                }
                                            break;
                                            default:
                                            cout<<"ERROR!!!"<<endl;
                                            break;
                                        }
                                        do
                                        {
                                        cout<<"\n";
                                        cout<<"What would you like to do?"<<endl;
                                        cout<<"1.Search for Venue\n2.Search for Caterers\n3.Search for Additional Requirements\n4.Go Back to Main Menu\n"<<endl;
                                        cin>>h;
                                        switch(h)
                                        {
                                        case 1:
                                            venue();
                                            break;
                                        case 2:
                                            meal();
                                            break;
                                        case 3:
                                            extras();
                                            break;
                                        case 4: goto Mainmenu;
                                        default:
                                            cout<<"ERROR!"<<endl;
                                            break;
                                        }
                                        cout<<"\n";
                                        cout<<"What would you like to do?"<<endl;
                                        cout<<"1.Continue looking for event necessities\n2.Exit"<<endl;
                                        cin>>t;
                                        }
                                        while(t!=2);
                                        cout<<"Would you like to create the event?"<<endl;
                                        cout<<"1.Yes\n2.No"<<endl;
                                        cin>>q;
                                        switch(q)
                                        {
                                            case 1:
                                                  h1.write_Event();
                                                  break;
                                            case 2:
                                                cout<<"Come back later!"<<endl;
                                                break;
                                            default:
                                                cout<<"ERROR!"<<endl;
                                                break;
                                        }
                                    }
                                    break;
                                    case 2:
                                    h1.write_Event();
                                    break;
                                };

                                };
                            break;
                            case 2:  filter:
                                    cout<<"What would you like to do?\n1.View Public Events\n2.Login"<<endl;
                                    int x;
                                    cin>>x;
                                    if(x==1)
                                    {
                                        h1.view_events();
                                        abba:
                                        cout<<"What would you like to do?\n1.Book Tickets\n2.Back"<<endl;
                                        int a;
                                        cin>>a;
                                        if(a==1)
                                        {
                                            h1.book_tickets();
                                            goto abba;
                                        }
                                        else
                                        {
                                            goto filter;
                                        }
                                    }
                                    else
                                    {
                                cout<<"Enter your name:"<<endl;
                                cin>>guestname;
                                h1.display_eventdetails(p);
                                break;
                                    }

                            case 3:
                                string password;
                                char ch;
                cout << "Enter Admin Authentication Key\n";
                    ch = _getch();
                    while(ch != 13){//character 13 is enter
                        password.push_back(ch);
                        cout << '*';
                        ch = _getch();
                        }
                            if(password == "5977"){
                            cout << "\nAccess granted.....\n";
                             Sleep(500);
                            system("cls");
                            }
                            else    {
                               cout << "\nAccess aborted...\n";
                                    goto starters;
                                    }
                                    d:
                                    cout<<"What would you like to do?\n1.Create Events\n2.Logout"<<endl;
                                    int r;
                                    cin>>r;
                                    if (r==1)
                                    {
                                        a1.create_event();
                                        goto d;
                                    }
                                    else
                                    {
                                        goto starters;
                                    }

        }
}
