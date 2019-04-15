#ifndef MODEL_H
#define MODEL_H

#include "ManagerInterface.h"
#include "MyPointer.h"
#include <vector>

/// <summary>
/// MVC model in this project is pretty bad, because it was written for about 2 and a half hours,
/// so i recommend rewriting the GUI, if you intend to use this memory model
/// </summary>
struct Model
{
private:
	Model(const Model&) = delete;
	Model& operator=(const Model&) = delete;

public:
	Model();
	~Model();

public:
	std::vector<MyPointer<char>> char_vector_;
	std::vector<MyPointer<int>> int_vector_;
	std::vector<MyPointer<float>> float_vector_;
	std::vector<MyPointer<double>> double_vector_;

	manager::ManagerInterface* memory_manager_;
};

#endif