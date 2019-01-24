#include <GL/glew.h>
#include "Renderer.h"

namespace xe {



void Renderer::addCommand(IRenderCommand * command) {}

void Renderer::render() {
	// Uncomment this once everything is rendered by new renderer

	cleanRenderCommand();
}

void Renderer::clearGL() {
	// Enable Depth mask to make sure glClear the depth buffer correctly
	glDepthMask(true);
	glClearColor(clearColor.R, clearColor.G, clearColor.B, clearColor.A);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDepthMask(false);
}

void Renderer::cleanRenderCommand() {}

}