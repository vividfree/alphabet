#ifndef __MD5_DIGEST_H__
#define __MD5_DIGEST_H__

#include <string>

#ifdef __cplusplus
extern "C" 
{
#endif

void md5_digest( const unsigned char *instr, unsigned char digest[16] );

#ifdef __cplusplus
}
#endif

void md5_digest_readable( const std::string& instr, std::string& digest );
#endif //__MD5_DIGEST_H__
