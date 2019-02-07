#include "Renderer.h"
#include "RenderCommand.h"
#include "GLProgram.h"

namespace xe {

Renderer::Renderer() {
	commands.reserve(2048);
}

void Renderer::addCommand(RenderCommand * command) {
	commands.push_back(command);
}

void Renderer::renderer() {
	glClearColor(0.2f, 0.2f, 0.2f, 0.4f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	Matrix PV = Matrix::identify;
	for (RenderCommand *cmd : commands) {
		cmd->glProgram->setMat4("PVM", PV*cmd->modelView);
		cmd->execute();
	}
}

void Renderer::clear() {
	commands.clear();
}

}