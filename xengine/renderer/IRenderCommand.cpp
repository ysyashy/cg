#include "IRenderCommand.h"
#include "math/XEMath.h"

namespace xe {

IRenderCommand::Type IRenderCommand::getCommandType() const {
	return commandType;
}

void IRenderCommand::init(const Matrix & modelView) {}

IRenderCommand::IRenderCommand() : commandType(IRenderCommand::Type::UNKNOW_COMMAND) {}

IRenderCommand::~IRenderCommand() {}

}