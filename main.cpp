#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>
#include <unistd.h>

struct Tasks {
  std::string taskName;
  std::string taskDetails;
  bool isDone = false;

};

std:: ostream& operator<<(std::ostream& os, const Tasks& task){
  os <<"\tTask Name: "<< task.taskName << std::endl;
  os <<"\tTaks Priority: " << task.taskDetails << std::endl;
  os <<"\tCompleted: " << std::boolalpha << task.isDone << std::endl;
  return os;
}

Tasks createTask(){
  Tasks newTask;
  std::cout <<"Task Name: ";
  std::getline(std::cin >> std::ws,newTask.taskName); 
  std::cout <<"Task Priority(High/Medium/Low): ";
  std::getline(std::cin,newTask.taskDetails);
//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return newTask; 
}

void saveTask(const std::string& filename, const std::vector<Tasks>& data){
  std::ofstream outputFile(filename);
  if(outputFile.is_open()){
    for(const Tasks& value : data){
      outputFile << value.taskName << "\n";
      outputFile << value.taskDetails << "\n";
      outputFile << value.isDone << "\n";
      outputFile << '\n';
    }
    outputFile.close();
  }
  else{
    std::cerr << "Failed to save data to the file: " << filename << std::endl;
  }
}

void loadTasks(const std::string& filename, std::vector<Tasks>& data){
  Tasks newTask;
  std::string line;
  std::ifstream inputFile(filename);
  if(inputFile.is_open()){
    int count = 1;
    while(std::getline(inputFile,line)&& !(inputFile.eof())){
        if(count % 3 == 1){
          newTask.taskName = line;
        }
        else if(count % 3 == 2){
          newTask.taskDetails = line;
        }
        else if(count % 3 == 3){
          newTask.isDone = std::stoi(line);
          data.push_back(newTask);
        }
      count++;
    }
    inputFile.close();
  }
  else{
    std::cerr << "Failed to open file." << std::endl;
  }
}

void printMenu(){
  std::cout <<"---------------------------------\n"
    <<"            MAIN MENU            \n"
    <<"                                 \n"
    <<"SELECT AN OPTION                 \n"
    <<"                                 \n"
    <<"\t1) View Tasks List               \n"
    <<"\t2) Add New Task                  \n"
    <<"\t3) Update a Task                 \n"
    <<"\t4) Delete a Task                 \n"
    <<"\t5) Exit Program                 \n"
    <<"                                 \n"
    <<"---------------------------------\n";
}
void printList(std::vector<Tasks>& list){
  std::cout<<"===================\n"
           <<"\tTo Do List\n"
           <<"===================\n";
  for(int i = 0; i < list.size(); i++){
      std::cout << i+1 <<")" << list.at(i);
      std::cout << std::endl;
  }

}
void taskOptions(int option, std::vector<Tasks>& list){

}
int main(){
  std::vector<Tasks> toDoList;
  std::string filename = "data.txt";
  loadTasks(filename,toDoList);
  bool continueLoop = true;
  while(true){
    system("clear");
    printMenu();
    int option = 0;
    std::cin >> option;
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
    if(option == 2){
      toDoList.push_back(createTask());
    //  saveTask(filename, toDoList);
    }
    if(option == 5){
      std::cout <<"Exiting Program" << std::endl;
      sleep(2);
      saveTask(filename, toDoList);
      exit(0);
    }
    saveTask(filename, toDoList);
  }
}
