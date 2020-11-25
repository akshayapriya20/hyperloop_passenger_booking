# hyperloop_passenger_booking
This project is created for Zoho placement
This is README file for implementation of hyperloop passenger booking project using C programming.

This project required three packages and they can be imported as follows
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

In this project, I used singly linked list to store passenger details.
I also used adjacent matrix to create a graph data structure to store all the routes.

I have created three functions in this poject
1. add_passenger() to add a passenger into linked list
2. start_pod() to make pod to pickup old man in the queue
3. print_queue() to print the count and names of remaining members in the queue

My Approach:-
1. All the routes are stored in graph data structure.
   So that shortest path between source and destination can be easily found by using BFS(Breadth First Search).

2. All the passengers details were stored in linked list.
   So that any number of new passenger can be added easily.

3. Oldest passenger in the queue can also be found easily by traversing the linked list and using linear search algorithm.
   So that oldest passenger can be deleted from linked list easily and 
   printing the shortest path from starting station to desired destination of oldest passenger while the START_POD command recieved.
