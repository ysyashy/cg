#include "xeTypes.h"

namespace xe {

const BlendFunc BlendFunc::DISABLE = { GL_ONE, GL_ZERO };
const BlendFunc BlendFunc::ALPHA_PREMULTIPLIED = { GL_ONE, GL_ONE_MINUS_SRC_ALPHA };
const BlendFunc BlendFunc::ALPHA_NON_PREMULTIPLIED = { GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA };
const BlendFunc BlendFunc::ADDITIVE = { GL_SRC_ALPHA, GL_ONE };

}