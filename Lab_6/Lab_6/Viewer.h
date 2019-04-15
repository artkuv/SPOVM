#ifndef VIEWER_H
#define VIEWER_H

#include "ENUM.h"
#include "Controller.h"
#include <iostream>
#include <sstream>
#include <conio.h>
#include <cstdlib>

/// <summary>
/// MVC model in this project is pretty bad, because it was written for about 2 and a half hours,
/// so i recommend rewriting the GUI, if you intend to use this memory model
/// </summary>
class Viewer
{
public:
	void Run();

private:
	Viewer(const Viewer&) = delete;
	Viewer& operator=(const Viewer&) = delete;

	void AddNewObject();
	void AddNewReference();
	void RemoveOldReference();
	void AllocateMemoryToExisting();
	void FreeAllocatedMemory();
	void InitiazlieAllocated();

private:
	int SelectIndex();
	ENUM SelectType();
	void ShowMenuOptions();
	void ShowModelData();

public:
	Viewer();
	explicit Viewer(Controller* controller);
	~Viewer();

private:
	Controller * controller_;
};

#endif