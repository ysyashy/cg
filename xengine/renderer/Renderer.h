#pragma once

#include <vector>

namespace xe {

class RenderCommand;

class Renderer {

public:
	Renderer();
	void addCommand(RenderCommand *command);
	void renderer();
	void clear();
private:
	std::vector<RenderCommand*> commands;

};

}
