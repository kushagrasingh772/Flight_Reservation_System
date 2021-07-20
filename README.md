# Flight_Reservation_System
The project involves making use of Dijkstra's algorithm to develop a reservation system of the flights operating in the United States.

This was a group project made for the purpose of submission of Data Structure Lab Project given to me in my 3rd semester.

TOOLS AND TECHNOLOGY USED:
 
•	Language Used: C++ , Python
•	Standard Template Library
•	Graph Theory Concepts
•	Dijkstra Algorithm
•	CSV reader
•	Python for data preprocessing               

DATASET-
USA AIRPORT DATABASE

Original Dataset Link: https://www.kaggle.com/flashgordon/usa-airport-dataset
DESCRIPTION:
This dataset is a record of 3.5 Million+ US Domestic Flights from 1990 to 2009. It has been taken from OpenFlights website which has a huge database of different travelling mediums across the globe.
Original Dataset contains:
Here is some info about the attributes present in the dataset:
1.	Origin_airport: Three letter airport code of the origin airport
2.	Destination_airport: Three letter airport code of the destination airport
3.	Origin_city: Origin city name
4.	Destination_city: Destination city name
5.	Passengers: Number of passengers transported from origin to destination
6.	Seats: Number of seats available on flights from origin to destination
7.	Flights: Number of flights between origin and destination (multiple records for one month, many with flights > 1)
8.	Distance: Distance (to nearest mile) flown between origin and destination
9.	Fly_date: The date (yyyymm) of flight
10.	Origin_population: Origin city's population as reported by US Census
11.	Destination_population: Destination city's population as reported by US Census
 
Processed Data set:

For the purpose of this project, I have toned down the dataset to 2500 rows and 7 columns using pandas and numpy library. The data has been cleaned and processed using the above said libraries in python to be made more useful and more just for the purpose of this project.

The processed dataset contains 7 columns which are:

1.ORIGIN_AIRPORT
2.DESTINATION_AIRPORT
3.PASSENGERS
4.SEATS
5.DISTANCE
6.DESTINATION_CITY
7.ORIGIN_CITY

