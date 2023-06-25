#ifndef TASKS_H
#define TASKS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


class Tasks {
  std::string taskName;
  std::string taskPriority;
  bool isDone = false;
public:
  Tasks();
  Tasks(std::string& name, std::string prio);
  //Getters & Setters;
  std::string get_taskName() const;
  void set_taskName(const std::string& taskName_);

  std::string get_taskPriority() const;
  void set_taskPriority(const std::string& taskPriority_);

  bool get_isDone() const;
  void set_isDone(const bool& isDone_);

  friend std::ostream& operator<<(std::ostream& os, const Tasks& task);

};

Tasks createTask();

void updateTasks(const int& index, std::vector<Tasks>& data);
bool deleteTasks(const int& index, std::vector<Tasks>& data);
void printMenu();
void printList(std::vector<Tasks>& list);
void saveTask(const std::string& filename, const std::vector<Tasks>& data);
void loadTasks(const std::string& filename, std::vector<Tasks>& data);

#endif
