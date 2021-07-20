	#include <bits/stdc++.h>
	#include <string>
	#include<time.h>
	using namespace std;
	typedef tuple<int,int,int> ftuple;
	typedef pair<int, int> fpair;


	class Flight
	{

		public:
		  string OACode,DACode,OCity,Dcity;
		  int passengers,seats,flightnumer,distance,seats_reserved;

	};

	map<string, int> flightMap;
	vector< ftuple > flightGraph[500];

	bool installed=false;


	Flight flight[2501];
	bool check_key( string key)
	{
		// Key is not present
		if (flightMap.find(key) == flightMap.end())
			return false;

		return true;
	}

	bool checkCityExists(string city)
	{
		if(check_key(city))return true;
		return false;

	}

	void notInstalledError()
	{

		cout<<"Critical Error : Flight Data Not Installed"<<endl;
		return;
	}


	string trimalpha(string s)
	{
		for(string::iterator i = s.begin(); i != s.end(); i++)
		{
			if(!isalpha(s.at(i - s.begin())))
			{
				s.erase(i);
				i--;
			}
		}
		return s;
	}

	void read_record()
	{

		ifstream fp;

		fp.open("out.csv");
		int i=0;

		string oac,dac,pa,sea,dist,dc,oc;
		getline(fp,oac,',');
		getline(fp,dac,',');
		getline(fp,pa,',');
		getline(fp,sea,',');
		getline(fp,dist,',');
		getline(fp,dc,',');
		getline(fp,oc,'\n');

		int ind=1;

		while(fp.good())
		{

			getline(fp,oac,',');
			getline(fp,dac,',');
			getline(fp,pa,',');
			getline(fp,sea,',');
			getline(fp,dist,',');
			getline(fp,dc,',');
			getline(fp,oc,'\n');

			oc=trimalpha(oc);

			dc=trimalpha(dc);
			flight[i].OACode=oac;
			flight[i].DACode=dac;
			flight[i].passengers=stoi(pa);
			flight[i].seats=stoi(sea);
			flight[i].distance=stoi(dist);
			flight[i].Dcity=dc;
			flight[i].OCity=oc;
			flight[i].flightnumer=i;
			flight[i].seats_reserved=stoi(pa);

			if(!check_key(oc))
			{
				flightMap[oc]=ind++;


			}

			if(!check_key(dc))
			{
				flightMap[dc]=ind++;

			}


			cout<<i<<" Reading Data : "<<endl;

			cout<<"Origin City Code: "<<oac<<" ";
			cout<<"Destination City Code: "<<dac<<" ";
			cout<<"Number of Passengers: "<<pa<<" ";
			cout<<"Number of seats: "<<sea<<" ";
			cout<<"Destination City: "<<dc<<" ";
			cout<<"Origin City: "<<oc<<"\n";
			i++;


		}


	}


	vector<int> Dijkstra(int source,int destination)
	{
		priority_queue<fpair,vector<fpair>,greater<fpair>> pq;
		vector<int> dist;
		vector<bool> vis;

		int n=flightMap.size();
		dist.resize(n+1,1e7);
		vis.resize(n+1,false);

		vector<int> parent;
		vector<int> path;

		parent.resize(n+5,-1);
		path.resize(n+5,-1);

		dist[source]=0;
		pq.push({0,source});

		while(pq.size()>0)
		{
			auto[currw,currv]=pq.top();
			pq.pop();

			if(vis[currv])continue;
			vis[currv]=true;

			//if(dist[cv]<cw)continue;

			for(auto[nextw,nextv,nextfin]:flightGraph[currv])
			{

				if(vis[nextv])continue;

				int newWeight=currw+nextw;

				if(newWeight<dist[nextv])
				{

					dist[nextv]=newWeight;
					parent[nextv]=currv;
					path[nextv]=nextfin;

					pq.push({newWeight,nextv});

				}

			}

		}

		vector<int> pathTaken;

		if(dist[destination]==1e7)return pathTaken;


		for(int i=destination;i!=source;i=parent[i])
		{
			pathTaken.push_back(path[i]);

		}
		reverse(pathTaken.begin(), pathTaken.end());


		return pathTaken;


	}

	void buildGraph()
	{
		for(int i=0;i<=2500;i++)
		{
			int originIndex=flightMap[flight[i].OCity];
			int destinationIndex=flightMap[flight[i].Dcity];

			flightGraph[originIndex].push_back(make_tuple(flight[i].distance,destinationIndex,flight[i].flightnumer));

			//making the graph directed by commenting the code below
			//flightGraph[destinationIndex].push_back(make_tuple(flight[i].distance,originIndex,flight[i].flightnumer));



		}




	}

	int calculateCost(int distance)
	{

		int baseFair=50;
		int totalFair=(distance+1)/2+baseFair;

		return totalFair;

	}



	void install()
	{
		if(installed)
		{
			cout<<"Flight Data Already Installed"<<endl;
			return;
		}

		installed=true;

		cout<<"Installing Flight Data...."<<endl;
		read_record();
		cout<<"Read Data Successfully! "<<endl;
		buildGraph();
	}



	class Booking{

		public:

			string booked_under;
			int booking_id;
			int num_seats;
			int distance;
			int cost;
			vector<int> flightsTaken;
			string password;
			string bookingTimeAndDate;


	};

	vector<Booking> bookings;

	string generatepassword()
	{
		char alphanum[] = "0123456789!@#$%^&*abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		int l=sizeof(alphanum)-1;
		string p="";
		for(int i=0;i<8;i++)
		{
			p+=(alphanum[rand() % l]);
		}
		return p;


	}




	void reseveSeats()

	{

	  if(!installed)
	  {
		 notInstalledError();
		 return;
	  }

	  string originCity;
	  string destinationCity;

	  cout <<"Enter Origin City: "<<endl;
	  cin>>originCity;
	  for (auto & c: originCity) c = toupper(c);
	  if(!checkCityExists(originCity))
	  {
		  cout<<"Entered City doesn't exist!!"<<endl;
		  cout << "Enter 1 to retry booking  or any other key to  Exit";
		  int cho;
		  cin>>cho;
		  if(cho==1)reseveSeats();
		  else
		  {
			return;
		  }


	  }

	  cout <<"Enter Destination City: "<<endl;
	  cin>>destinationCity;
	   for (auto & c: destinationCity) c = toupper(c);
	  if(!checkCityExists(destinationCity))
	  {
		  cout<<"Entered Destination City doesn't exist!!"<<endl;
		  cout << "Enter 1 to retry booking  or any other key to  Exit";
		  int cho;
		  cin>>cho;
		  if(cho==1)reseveSeats();
		  else
		  {
			return;
		  }


	  }


	  vector<int> path;
	  path= Dijkstra(flightMap[originCity],flightMap[destinationCity]);

	  if(path.size()==0)
	  {
		  cout<<"Sorry there is no flight connecting "<<originCity<<" and "<<destinationCity<<endl;
		  cout << "Enter 1 to retry booking seats or any other key to  Exit";
		  int cho;
		  cin>>cho;
		  if(cho==1)reseveSeats();
		  else
		  {
			return;
		  }
	  }

	  cout<<"You will have to take "<<path.size()<<" flight(s) to reach your destination : "<<endl;

	  int totalDistance=0;

	  for(int i : path)
	  {
		  cout<<"From "<<flight[i].OCity<<" to "<<flight[i].Dcity<<endl;
		  totalDistance+=flight[i].distance;
		  cout<<"then "<<endl;
	  }

	  cout<<"You will reach your destination"<<endl;
	  int costFlight=calculateCost(totalDistance);
	  cout<<"The total sum you will have to pay is "<<costFlight<<" $ "<<endl;

	  cout<<"You will have travelled "<<totalDistance<<" miles"<<endl;



		cout<<"Enter number of Required Seats\n";
		int reqseats;
		cin>>reqseats;
		int counter=0;


		for(int i: path)
		{
			if(reqseats>flight[i].seats-flight[i].seats_reserved)
			{
				cout<<" Sorry The  Flight "<<flight[i].OCity<<" to "<<flight[i].Dcity<<" has Only "<<(flight[i].seats-flight[i].seats_reserved)<<" seats available"<<endl;
				counter=1;
			}
		}



		if (counter==1)
		{
		    cout << "Enter 1 to retry or any other key to  Exit";
			int cho;
		  	cin>>cho;
		  	if(cho==1)reseveSeats();
		  	else
		  	{
				return;
		  	}
		}


		for(int i : path)
		{
			flight[i].seats_reserved+=reqseats;
		}




		Booking book;
		cout<<"Enter Booking Name: ";
		string nam;
		for(int i : path)
		{
			flight[i].seats_reserved+=reqseats;
			book.flightsTaken.push_back(i);
		}

		cin>>nam;
		book.booked_under=nam;
		int b_id=bookings.size();
		book.booking_id=b_id;
		book.num_seats=reqseats;
		book.distance= totalDistance;

		string pword=generatepassword();
		book.cost=costFlight;
		book.password=pword;

		time_t my_time = time(NULL);
		string time=ctime(&my_time);

		cout<<"Resrvation time:"<<time;

		book.bookingTimeAndDate=time;
		bookings.push_back(book);

		cout<<"Booking Successfull!!"<<endl;

		cout<<"Your booking id is: "<<b_id<<endl;
		cout<<"Your password is: "<<pword<<endl;

		cout<<"Please remember these for future reference"<<endl;
	}


	int authenticate()
	{
		int option=0;
		cout<<"Enter your booking id : ";
		int bookid;
		cin>>bookid;

		cout<<"Enter your password : ";
		string passwd;
		cin>>passwd;

		if (bookid>=(int)bookings.size())
		{
			option=1;
			cout<<"Your Booking ID is incorrect!!"<<endl;
			return -1;
		}

		if(passwd!=bookings[bookid].password)
		{
			option=1;
			cout<<"Your Password is incorrect!!"<<endl;
		}

		else
		{
			cout<<"Succesfully Logged in!!!!"<<endl;
		}

		if(option==1)
		{
			return -1;
		}

		else
		{
			return bookid;
		}

	}

	void cancellation()
	{

		int authKey=authenticate();
		if(authKey!=-1)
		{
			cout<<"Press 1 to confirm your cancellation ";
			int choiced;
			cin>>choiced;
			if (choiced==1)
			{
				cout<<"Your ticket has been cancelled and your money "<<bookings[authKey].cost-100
				<<" has been added to your account after deducting cancellation amount"<<endl;
				for(int i : bookings[authKey].flightsTaken)
				{
					flight[i].seats_reserved-=bookings[authKey].num_seats;

				}


			}
		}


		else
		{
			cout<<"Failed authentication!"<<endl;
		}


	}

	void showBooking()
	{

		 if(!installed)
		  {
			 notInstalledError();
			 return;
		  }
		int authKey=authenticate();
		if(authKey!=-1)
		{

			cout<<"Your Booking Id is:";
			cout<<authKey<<endl;

			cout<<"Your journey is booked under the name: "<<bookings[authKey].booked_under<<endl;


			cout<<"The number of seats you have reserved are: "<<bookings[authKey].num_seats<<endl;

			cout<<"The number of flights you will be taking is "<<bookings[authKey].flightsTaken.size()<<" namely:"<<endl;

			for(int i : bookings[authKey].flightsTaken)
			{
				cout<<"From "<<flight[i].OCity<<" to "<<flight[i].Dcity<<endl;

				cout<<"then "<<endl;
			}

			cout<<"You will reach your destination"<<endl;

			cout<<"Your Journey will be of "<<bookings[authKey].distance<<" miles"<<endl;

			cout<<"The total money you have paid is "<<bookings[authKey].cost<<" USD"<<endl;

			cout<<"Your booking was made on "<<bookings[authKey].bookingTimeAndDate<<endl;

		}

	}

	void seeConnectivity()
	{

	  if(!installed)
	  {
		 notInstalledError();
		 return;
	  }

	  string originCity;
	  string destinationCity;

	  cout <<"Enter Origin City: "<<endl;
	  cin>>originCity;
	  for (auto & c: originCity) c = toupper(c);

	  cout <<"Enter Destination City: "<<endl;
	  cin>>destinationCity;
	  for (auto & c: destinationCity) c = toupper(c);

	  vector<int> path;
	  path= Dijkstra(flightMap[originCity],flightMap[destinationCity]);

	  if(path.size()==0)
	  {

			cout<<"Entered Cities arent connected by any flights";
			return;

	  }

	  cout<<"The entered cities are conneccted with flights:"<<endl;

	  int d=0;
	  int min_=INT_MAX;

	  for(int i : path)
	  {
		  cout<<"From "<<flight[i].OCity<<" to "<<flight[i].Dcity<<endl;
		  d+=flight[i].distance;
		  min_=min(min_,(flight[i].seats-flight[i].seats_reserved));

	  }
	  cout<<"number of seats available: "<<min_<<endl;

	  cout<<"The ditance thus is "<<d<<" miles"<<endl;



	}



	int main()

	{

	  system("clear");

		int w;
		srand(time(0));
	  while (1)

	  {

		cout<<"\n";
		time_t my_time = time(NULL);
		printf("%s", ctime(&my_time));
		//system("cls");

		cout << "\n\n\n\n\n";

		cout << "\t\t\t1.Install\n\t\t\t"

			 << "2.Reservation\n\t\t\t"

			 << "3.Show Booking\n\t\t\t"

			 << "4.Cancellation. \n\t\t\t"

			 << "5.See Connectivity between two cities \n\t\t\t"

			 << "6.Exit";

		cout << "\n\t\t\tEnter your choice:-> ";

		cin >> w;

		switch (w)

		{

		case 1:
		  install();

		  break;

		case 2:
		  reseveSeats();

		  break;

		case 3:
		  showBooking();

		  break;

		case 4:

		  cancellation();

		  break;

		case 5:
		  seeConnectivity();
		  break;

		case 6:
		  exit(0);
		}
	  }

	  return 0;

	}
