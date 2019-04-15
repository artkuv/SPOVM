#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ENUM.h"
#include "Model.h"
#include <sstream>

/// <summary>
/// MVC model in this project is pretty bad, because it was written for about 2 and a half hours,
/// so i recommend rewriting the GUI, if you intend to use this memory model
/// </summary>
class Controller
{
private:
	Controller(const Controller&) = delete;
	Controller& operator=(const Controller&) = delete;

public:
	Model* GetModel();
	void PushNewObject(ENUM type, int size);
	void AddReference(ENUM type, int index);
	void RemoveReference(ENUM type, int index);
	void AllocateTo(ENUM type, int index, size_t size);
	void FreeFrom(ENUM type, int index);
	void InitializeAt(ENUM type, int index, std::string str);

public:
	Controller();
	explicit Controller(Model* model);
	~Controller();

private:
	Model* model_;
};

#endif