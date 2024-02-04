
#include "MyFramework.h"


int main(int argc, char *argv[])
{
	//return run(new MyFramework);
	
	MyFramework* framework = new MyFramework;
	return run(framework);

	delete framework;



}


