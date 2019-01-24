#ifndef __XE_RenderCommand_H__
#define __XE_RenderCommand_H__

namespace xe {

class IRenderCommand {
public:
	/* Enum the type of render command. */
	enum class Type {
		UNKNOW_COMMAND,
		PRIMITIVE_COMMAND,
		TRIANGLES_COMMAND,
		QUAD_COMMAND,
		MESH_COMMAND,
		BATCH_COMMAND,
		GROUP_COMMAND,
		CUSTOM_COMMAND
	};
public:
	virtual Type getCommandType() = 0;
protected:
	IRenderCommand();
	virtual ~IRenderCommand();
};

}

#endif
