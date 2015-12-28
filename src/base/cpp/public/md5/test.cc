#include <iostream>
#include "md5_digest.h"

using namespace std;

int main( int argc, char * argv[] ) {

  if ( argc < 2 ) {
    cerr << "Incomplete command line, usage <bin> <input string>" << endl;
    exit( 1 );
  }
  unsigned char * input = reinterpret_cast< unsigned char * >( argv[ 1 ] );
  unsigned char digest[ 16 ];
  md5_digest( input, digest );

  for ( size_t i = 0; i < 16; ++i ) {
    cout << std::hex << int( digest[ i ] ) << endl;
  }
  return 0;
}
