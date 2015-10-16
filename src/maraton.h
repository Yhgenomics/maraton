#define SAFE_DELETE(__X__) if( __X__ != nullptr ) { delete __X__; __X__ = nullptr; }
#define SAFE_DELETE_ARRAY(__X__) if( __X__ != nullptr ) { delete __X__[]; __X__ = nullptr; }

#include "utils/Logger.h"
#include "utils/Singleton.h"
#include "thirdpart/HTTPParser.hpp"
#include "thirdpart/json.hpp"
#include "thirdpart/UUID.hpp"