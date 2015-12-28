#include <string.h>

#include "md5.h"
#include "md5_digest.h"

#ifdef __cplusplus
extern "C" 
{
#endif

void md5_digest(const unsigned char *instr, unsigned char digest[16])
{
    md5_state_t md5state;

    md5_init(&md5state);
    md5_append( &md5state, 
                reinterpret_cast< const md5_byte_t * >( instr ), 
                strlen( reinterpret_cast< const char * >( instr ) ) );
    md5_finish(&md5state, digest);
}
#ifdef __cplusplus
}
#endif


// Note:
//  It is assumed that the input is already inside the valid range( 0 <= num && num <= 0xf ).
//  Otherwise, no transformation will be executed.
inline char num2hex( const unsigned char num ) {
  if ( num <= 9 ) {
    return num + '0';
  } else if ( num >= 0xa && num <= 0xf ) {
    return ( num - 10 ) + 'A';
  } else {
    return num;
  }
}

using std::string;

void md5_digest_readable( const string& instr, string& digest ) {
  unsigned char ch_digest[ 16 ];
  md5_digest( reinterpret_cast< const unsigned char * > ( instr.c_str() ), ch_digest );
  digest.clear();

  for ( size_t i = 0; i < 16; ++i ) {
    unsigned char digest_char = ch_digest[ i ];
    unsigned char higher_half = ( digest_char & 0xf0 ) >> 4;
    unsigned char lower_half = digest_char & 0x0f;
    digest += num2hex( higher_half );
    digest += num2hex( lower_half );
  }
}

