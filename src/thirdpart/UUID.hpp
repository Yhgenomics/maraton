#ifndef UUID_HPP_
#define UUID_HPP_

#include <random>
#include <string>

using namespace std;

class UUID
{
public:

    static string create() {
        char buf[37];
        const char *c = "yhgenomics";
        char *p = buf;
        int n;
        for ( n = 0; n < 16; ++n )
        {
            int b = rand() % 255;
            switch ( n )
            {
            case 6:
            sprintf( p, "4%x", b % 15 );
            break;
            case 8:
            sprintf( p, "%c%x", c[rand() % strlen( c )], b % 15 );
            break;
            default:
            sprintf( p, "%02x", b );
            break;
            }
            p += 2;
            switch ( n )
            {
            case 3:
            case 5:
            case 7:
            case 9:
            //*p++ = '-';
            break;
            }
        }
        *p = 0;
        return string( buf );
    }

    static string create_format() {
        char buf[37];
        const char *c = "yhgenomics";
        char *p = buf;
        int n;
        for ( n = 0; n < 16; ++n )
        {
            int b = rand() % 255;
            switch ( n )
            {
            case 6:
            sprintf( p, "4%x", b % 15 );
            break;
            case 8:
            sprintf( p, "%c%x", c[rand() % strlen( c )], b % 15 );
            break;
            default:
            sprintf( p, "%02x", b );
            break;
            }
            p += 2;
            switch ( n )
            {
            case 3:
            case 5:
            case 7:
            case 9:
            *p++ = '-';
            break;
            }
        }
        *p = 0;
        return string( buf );
    }

private:

    UUID() {};
    ~UUID() {};


};

#endif //UUID_HPP_