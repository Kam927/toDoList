#include "Tasks.h"
#include <cstdlib>
#include <unistd.h>
#include <limits>

int main(){
  std::vector<Tasks> toDoList;
  std::string filename = "data.txt";
  loadTasks(filename,toDoList);
  bool continueLoop = true;
  while(true){
    system("clear");
    printMenu();
    int option = 0;
    int index = 0;
    std::cin >> option;
    if(!std::cin && option != 1 && option != 2 && option != 3 && option !=4 && option != 5){
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    else{
      if(option == 1){
        while(continueLoop){
          system("clear");
          char userInput;
          printList(toDoList);
          std::cout <<"Press 'q' to return to main menu"<< std::endl;
          std::cin >> userInput;
          if(toupper(userInput) == 'Q'){
            continueLoop = false;
          }
        }
        continueLoop = true;
      } 
      else if(option == 2){
        toDoList.push_back(createTask());
        //  saveTask(filename, toDoList);
      }
      else if(option == 3){
        system("clear");
        printList(toDoList);
        std::cout <<"Which task to update: ";
        std::cin >> index;
        updateTasks(index,toDoList);
      }
      else if(option == 4){
        system("clear");
        printList(toDoList);
        std::cout << "Which task to delete: ";
        std::cin >> index;
        bool deletion = deleteTasks(index,toDoList);
        if(deletion){
          std::cout <<"Deleting Task: " << index;
        }
        else{
          std::cout <<"Invalid option!\n";
        }
        sleep(1);
      } 
      else if(option == 5){
        std::cout <<"Saving Program...\n"; 
        sleep(1);
        std::cout <<"Exiting Program" << std::endl;
        sleep(1);
        saveTask(filename, toDoList);
        exit(0);
      }
      saveTask(filename, toDoList);
    }
  }
}
