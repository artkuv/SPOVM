#include "Controller.h"

using namespace std;

void Controller::PushNewObject(ENUM type, int size)
{
	switch (type)
	{
	case CHAR:
	{
		this->model_->char_vector_.push_back(MyPointer<char>(this->model_->memory_manager_));
		this->model_->char_vector_.back().allocateMemory(size);
		break;
	}
	case INT:
	{
		this->model_->int_vector_.push_back(MyPointer<int>(this->model_->memory_manager_));
		this->model_->int_vector_.back().allocateMemory(size);
		break;
	}
	case FLOAT:
	{
		this->model_->float_vector_.push_back(MyPointer<float>(this->model_->memory_manager_));
		this->model_->float_vector_.back().allocateMemory(size);
		break;
	}
	case DOUBLE:
	{
		this->model_->double_vector_.push_back(MyPointer<double>(this->model_->memory_manager_));
		this->model_->double_vector_.back().allocateMemory(size);
		break;
	}
	}
}

void Controller::AddReference(ENUM type, int index)
{
	switch (type)
	{
	case CHAR:
	{
		if (index >= this->model_->char_vector_.size())
			return;

		this->model_->char_vector_.push_back(MyPointer<char>(this->model_->memory_manager_));
		this->model_->char_vector_.back() = this->model_->char_vector_[index];
		break;
	}
	case INT:
	{
		if (index >= this->model_->int_vector_.size())
			return;

		this->model_->int_vector_.push_back(MyPointer<int>(this->model_->memory_manager_));
		this->model_->int_vector_.back() = this->model_->int_vector_[index];
		break;
	}
	case FLOAT:
	{
		if (index >= this->model_->float_vector_.size())
			return;

		this->model_->float_vector_.push_back(MyPointer<float>(this->model_->memory_manager_));
		this->model_->float_vector_.back() = this->model_->float_vector_[index];
		break;
	}
	case DOUBLE:
	{
		if (index >= this->model_->double_vector_.size())
			return;

		this->model_->double_vector_.push_back(MyPointer<double>(this->model_->memory_manager_));
		this->model_->double_vector_.back() = this->model_->double_vector_[index];
		break;
	}
	}
}

void Controller::RemoveReference(ENUM type, int index)
{
	switch (type)
	{
	case CHAR:
	{
		if (index >= this->model_->char_vector_.size())
			return;

		std::vector<MyPointer<char>>::iterator iterator = this->model_->char_vector_.begin();
		std::advance(iterator, index);
		this->model_->char_vector_.erase(iterator);

		break;
	}
	case INT:
	{
		if (index >= this->model_->int_vector_.size())
			return;

		std::vector<MyPointer<int>>::iterator iterator = this->model_->int_vector_.begin();
		std::advance(iterator, index);
		this->model_->int_vector_.erase(iterator);

		break;
	}
	case FLOAT:
	{
		if (index >= this->model_->float_vector_.size())
			return;

		std::vector<MyPointer<float>>::iterator iterator = this->model_->float_vector_.begin();
		std::advance(iterator, index);
		this->model_->float_vector_.erase(iterator);

		break;
	}
	case DOUBLE:
	{
		if (index >= this->model_->double_vector_.size())
			return;

		std::vector<MyPointer<double>>::iterator iterator = this->model_->double_vector_.begin();
		std::advance(iterator, index);
		this->model_->double_vector_.erase(iterator);

		break;
	}
	}
}

void Controller::AllocateTo(ENUM type, int index, size_t size)
{
	switch (type)
	{
	case CHAR:
	{
		if (index >= this->model_->char_vector_.size())
			return;

		this->model_->char_vector_[index].allocateMemory(size);

		break;
	}
	case INT:
	{
		if (index >= this->model_->int_vector_.size())
			return;

		this->model_->int_vector_[index].allocateMemory(size);

		break;
	}
	case FLOAT:
	{
		if (index >= this->model_->float_vector_.size())
			return;

		this->model_->float_vector_[index].allocateMemory(size);

		break;
	}
	case DOUBLE:
	{
		if (index >= this->model_->double_vector_.size())
			return;

		this->model_->double_vector_[index].allocateMemory(size);

		break;
	}
	}
}

void Controller::FreeFrom(ENUM type, int index)
{
	switch (type)
	{
	case CHAR:
	{
		if (index >= this->model_->char_vector_.size())
			return;

		this->model_->char_vector_[index].freeMemory();

		break;
	}
	case INT:
	{
		if (index >= this->model_->int_vector_.size())
			return;

		this->model_->int_vector_[index].freeMemory();

		break;
	}
	case FLOAT:
	{
		if (index >= this->model_->float_vector_.size())
			return;

		this->model_->float_vector_[index].freeMemory();

		break;
	}
	case DOUBLE:
	{
		if (index >= this->model_->double_vector_.size())
			return;

		this->model_->double_vector_[index].freeMemory();

		break;
	}
	}
}

void Controller::InitializeAt(ENUM type, int index, std::string str)
{
	switch (type)
	{
	case CHAR:
	{
		if (index >= this->model_->char_vector_.size())
			return;

		this->model_->char_vector_[index].copyData(const_cast<char*>(str.c_str()), str.size());

		break;
	}
	case INT:
	{
		if (index >= this->model_->int_vector_.size())
			return;

		int temp = 0;
		vector<int> values;
		stringstream stream(str);
		while (stream >> temp)
		{
			values.push_back(temp);
		}

		this->model_->int_vector_[index].copyData(values.data(), values.size());

		break;
	}
	case FLOAT:
	{
		if (index >= this->model_->float_vector_.size())
			return;

		float temp = 0;
		vector<float> values;
		stringstream stream(str);
		while (stream >> temp)
		{
			values.push_back(temp);
		}

		this->model_->float_vector_[index].copyData(values.data(), values.size());

		break;
	}
	case DOUBLE:
	{
		if (index >= this->model_->double_vector_.size())
			return;

		double temp = 0;
		vector<double> values;
		stringstream stream(str);
		while (stream >> temp)
		{
			values.push_back(temp);
		}

		this->model_->double_vector_[index].copyData(values.data(), values.size());

		break;
	}
	}
}

Model* Controller::GetModel()
{
	return this->model_;
}

Controller::Controller()
{
}

Controller::Controller(Model* model) : model_(model)
{
}

Controller::~Controller()
{
}