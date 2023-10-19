#include "Tasks.h"
#include <cctype>

Tasks::Tasks() : taskName("Default Task"), taskPriority("Default"), isDone(false) {}
Tasks::Tasks(std::string& name, std::string prio) : taskName(name), taskPriority(prio), isDone(false) {}

std::string Tasks::get_taskName() const{ return taskName; }
void Tasks::set_taskName(const std::string &taskName_){ taskName = taskName_; }

std::string Tasks::get_taskPriority() const { return taskPriority; }
void Tasks::set_taskPriority(const std::string &taskPriority_) { taskPriority = taskPriority_; }

bool Tasks::get_isDone() const { return isDone; }
void Tasks::set_isDone(const bool& isDone_) { isDone = isDone_; }

std::ostream& operator<<(std::ostream& os, const Tasks& task){
  os <<"\tTask Name: " <<  task.get_taskName() <<std::endl;
  os <<"\tTask Priority: "<< task.get_taskPriority() <<std::endl;
  os <<"\tCompleted: "<< std::boolalpha << task.get_isDone() <<std::endl;
  return os;
}

Tasks createTask(){
  std::string name, prio;
  std::cout <<"Task Name: ";
  std::getline(std::cin >> std::ws, name);
  bool validInput = false;
  while(!validInput){
    std::cout <<"Task Priority(High/Medium/Low): ";
    std::getline(std::cin, prio);
    for(char& c : prio){
      if(std::isalpha(c)){
        c = std::toupper(c);
      }
    }
    if(prio == "HIGH" || prio == "MEDIUM" || prio == "LOW"){
      //std::cout<< "INVALID PRIORITY INPUT\n";
      validInput = true;
    }
    else{
      std::cout<< "INVALID PRIORITY INPUT\n";
      //validInput = true;
    }
  }
  Tasks newTask(name,prio);
  return newTask;
}

void saveTask(const std::string& filename, const std::vector<Tasks>& data){
  std::ofstream outputFile(filename);
  if(outputFile.is_open()){
    for(const Tasks& value : data){
      outputFile << value.get_taskName() << "\n";
      outputFile << value.get_taskPriority() << "\n";
      outputFile << value.get_isDone() << "\n";
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
        newTask.set_taskName(line);  
      }
      else if(count % 3 == 2){
        newTask.set_taskPriority(line);
      }
      else if(count % 3 == 0){
        newTask.set_isDone(std::stoi(line));
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

void updateTasks(const int& index, std::vector<Tasks>& data){
  if(index <= 0 && index < data.size()) std::cout << "Invalid Task Index\n";
  else{
    data.at(index-1).set_isDone(true);
    std::cout <<"Updating Task: " << index;
  }
}

bool deleteTasks(const int& index, std::vector<Tasks>& data){
  if(index < data.size() && index <= 0) return false;
  else{
    data.erase(data.begin() + (index-1));
    return true;
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
    <<"\t3) Update Completion Status     \n"
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
