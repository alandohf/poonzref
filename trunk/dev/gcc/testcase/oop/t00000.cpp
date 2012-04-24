#include <iostream>

class C{

};

	enum emtype {X,Y,Z=9};
	emtype id = Z;
	//~ int i = 0;	
int main(int argc, char *argv[]) {
	//~ C c;
	switch ( id ) {
			case X:
				std::cout<<Z<<std::endl;
			break;
			case Y:
				std::cout<<Y<<std::endl;
			break;
			case Z:
				std::cout<<X<<std::endl;
			break;
			default:
				;
	}
}
