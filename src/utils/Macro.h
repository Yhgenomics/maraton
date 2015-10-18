#ifndef MACRO_H_
#define MACRO_H_

#define SAFE_DELETE(__X__) if( __X__ != nullptr ) { delete __X__; __X__ = nullptr; }
#define SAFE_DELETE_ARRAY(__X__) if( __X__ != nullptr ) { delete __X__[]; __X__ = nullptr; }

const int CIRCLE_BUFFER_SIZE = 5120;
const int SESSION_BUFFER_SIZE = 5120;
const int HTTP_RESPONSE_CONTENT_SIZE = 1024 * 1024;


#endif // !MACRO_H_
