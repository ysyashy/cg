#include "CommandPrimitive.h"
#include "IRenderCommand.h"

namespace xe {

CommandPrimitive::CommandPrimitive() {
	commandType = IRenderCommand::Type::PRIMITIVE_COMMAND;
}

}