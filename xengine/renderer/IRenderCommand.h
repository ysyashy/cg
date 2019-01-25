#ifndef __XE_IRenderCommand_H__
#define __XE_IRenderCommand_H__

namespace xe {

class Matrix;

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
	Type getCommandType() const;
	void init(const Matrix &modelView);
protected:
	IRenderCommand();
	virtual ~IRenderCommand();
protected:
	Type commandType;
};

}

#endif
