


#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#include <iostream>


int main( int argc, const char* argv[] ) {
	std::vector<std::string> result;

	std::ifstream st;
	std::string content;
	std::string::size_type pos;
	std::string def = "( std::vector<Variant> );";

	std::cout << "#include <map>\n"
		"#include <string>\n\n"
		"#include \"../variant/variant.h\"\n"
		"#include \"../variant/varfunc.h\"\n\n"
		"#include \"standardsymbols.h\"\n\n";

	std::string file;
	for ( int f = 1; f < argc; f++ ) {
		file = argv[f];

		st.open( file + ".h" );

		if ( st.is_open( ) ) {
			std::cout << "#include \"" << file << ".h\"" << std::endl;

			while( st ) {
				st >> content;

				if ( content == "Variant" ) {
					st >> content;

					if ( ( pos = content.find( '(' ) ) ) {
						result.push_back( content.substr( 0, pos ) );
					}
				}
			}

			st.close();
		}

	}

	std::sort( result.begin(), result.end() );

	std::cout << "\n\nnamespace gold {\n\n\n"
		"std::map<std::string, Variant> Functions = {" << std::endl;

	for ( std::vector<std::string>::const_iterator fn = result.begin();
		  fn != result.end(); ++fn ) {
		std::cout << "\t{ \"" << ( *fn ) << "\", new VarFunc( &" << ( *fn ) << " ) }";

		if ( fn + 1 != result.end() ) {
			std::cout << ',';
		}

		std::cout << std::endl;
	}

	std::cout << "};\n\n\n"
		"} // namespace gold" << std::endl;


	return 0;
}
