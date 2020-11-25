/**************************

C program for implementation of hyperloop passenger booking

***************************/


//Importing neccessary packages
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Creating a Singly linked list where each node contains a passenger name, age, destination and address to next passenger block
struct Passenger { 
    char name[20];
    int age;
    char destination;
    struct Passenger* next; 
}; 


//Creating a function to add a passenger into linked list
struct Passenger* add_passenger(struct Passenger* head){
    //Allocating memory for a new passenger
    struct Passenger* new_passenger = NULL;
    new_passenger = (struct Passenger*)malloc(sizeof(struct Passenger));
    
    //Getting their details
    char name[20];
    int age;
    char destination;
    scanf("%s %d %c",&new_passenger->name, &new_passenger->age, &new_passenger->destination);
    new_passenger->next = NULL;
    
    //Make the new passenger as head node if linked list is empty
    if(head->age == 0){
        head=new_passenger;
    }
    
    //Else insert the new passenger at the end of linked list
    else{
        struct Passenger* cur = head;
        while(cur->next!=NULL){
            cur = cur->next;
        }
        cur->next = new_passenger;
    }
    
    //return the head pointer of our linked list
    return head;
}


//Creating a function to make pod to pickup old man in the queue
struct Passenger* start_pod(struct Passenger* head, char startingStation){
    //Creating pointers to find the previous node of oldest man's node
    struct Passenger* cur = head;
    struct Passenger* old_person_before_ptr = head;
    int age = head->age;
    
    //Traversing the linked list
    while(cur->next != NULL){
        if((cur->next->age)>age){
            old_person_before_ptr = cur;
            age = cur->next->age;
        }
        cur = cur->next;
    }
    
    //Deallocating the memory of oldest man's block based on it's position
    if(old_person_before_ptr->age == age){  //This condition will handle deallocation if the oldest man's block is in first position of our linked list
        if(old_person_before_ptr->next == NULL){
            struct Passenger* old_person = head;
            head->age = 0;
            printf("%s %c %c\n",old_person->name, startingStation, old_person->destination);
        }
        else{
            struct Passenger* old_person = head;
            head = head->next;
            printf("%s %c %c\n",old_person->name, startingStation, old_person->destination);
            free(old_person);
        }
    }
    else if((old_person_before_ptr->next->next)==NULL){  //This condition will handle deallocation if the oldest man's block is in last position of our linked list
        struct Passenger* old_person = old_person_before_ptr->next;
        old_person_before_ptr->next = NULL;
        printf("%s %c %c\n",old_person->name, startingStation, old_person->destination);
        free(old_person);
    }
    else{  //This condition will handle deallocation if the oldest man's block is in the middle position of our linked list
        struct Passenger* old_person = old_person_before_ptr->next;
        old_person_before_ptr->next = old_person_before_ptr->next->next;
        printf("%s %c %c\n",old_person->name, startingStation, old_person->destination);
        free(old_person);
    }
    
    //return the head pointer of our linked list
    return head;
}

//Creating a function to print the count and names of remaining members in the queue
void print_queue(struct Passenger* head){
    if(head->age == 0){  //This condition will handle if there were no members in the queue
        printf("0\nNo passengers were added\n");
    }
    else{
        //Creating pointers to traverse the linked list
        struct Passenger* cur = head;
        
        //Finding the count of remaining members in the queue
        int count = 0;
        while(cur!=NULL){
            count++;
            cur = cur->next;
        }
        printf("%d\n",count);
        
        //Printing the name of remaining members in the queue
        cur = head;
        while(cur!=NULL){
            printf("%s %d\n",cur->name,cur->age);
            cur = cur->next;
        }
    }
    
}


//This is our main method
int main(){
    //Creating a variable to receive the commands
    char command[13];
    
    //Creating an infinite loop to receive the commands
    while(1){
        
        //Receiving the command
        printf("Enter the command: ");
        scanf("%s",command);
        
        //Throw an error if the first command is not INIT
        if(strcmp(command,"INIT")!=0){
            printf("The system is not initialized. Please use INIT command to initialize the system\n");
            continue;
        }
        else{
            while(1){
                
                //initializing the system with total number of routes and starting station
                printf("initializing the system\n");
                int totalRoutes;
                char startingStation;
                scanf("%d %c",&totalRoutes, &startingStation);
                
                //Here we are using Adjacent matrix to create a graph data structure to store all the routes
                int graph[totalRoutes][totalRoutes], i, j;
                for(i=0;i<totalRoutes;i++){
                    for(j=0;j<totalRoutes;j++){
                        graph[i][j] = 0;
                    }
                }
                
                //Getting all the edges of routes one by one
                char stationA, stationB;
                for(i=0;i<totalRoutes;i++){
                    scanf(" %c %c",&stationA, &stationB);
                    graph[stationA-'A'][stationB-'A'] = 1;
                }
                
                //Allocating memory for our linked list and head pointer
                struct Passenger* head = NULL;
                head = (struct Passenger*)malloc(sizeof(struct Passenger));
                head->age = 0; // If age of head node is 0, then it means linked list is empty
                
                int count;
                while(1){
                    
                    //Receiving the command
                    printf("Enter the command: ");
                    scanf("%s",command);
                    
                    if(strcmp(command,"INIT")==0){  //This condition will handle INIT command
                        break;
                    }
                    else if(strcmp(command,"ADD_PASSENGER")==0){  //This condition will handle ADD_PASSENGER command
                        scanf("%d",&count);
                        for(i=0;i<count;i++){
                            head = add_passenger(head);  //Calling the add_passenger function
                        }
                    }
                    else if(strcmp(command,"START_POD")==0){  //This condition will handle START_POD command
                        scanf("%d",&count);
                        if(head->age == 0){  //This condition will handle if there were no members in the queue to start the pod
                            printf("Please add passengers\n");
                        }
                        else{
                            for(i=0;i<count;i++){
                                head = start_pod(head, startingStation);  //Calling the start_pod function
                            }
                        }
                    }
                    else if(strcmp(command,"PRINT_Q")==0){  //This condition will handle PRINT_Q command
                        print_queue(head);  //Calling the print_queue function
                    }
                    else{  //This condition will handle invalid commands
                        printf("Invalid command");
                    }
                }
                
            }
        }
    }
    return 0;
}
