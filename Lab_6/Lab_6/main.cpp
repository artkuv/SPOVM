#include "MyPointer.h"
#include "Manager.h"
#include "Controller.h"
#include "Model.h"
#include "Viewer.h"
#include <iostream>

using namespace std;

int main()
{
	Manager memmory_manager;

	Model* model = new Model;
	model->memory_manager_ = dynamic_cast<ManagerInterface*>(&memmory_manager);
	Controller* controller = new Controller(model);
	Viewer* viewer = new Viewer(controller);

	viewer->Run();

	delete viewer;
	delete controller;
	delete model;
}