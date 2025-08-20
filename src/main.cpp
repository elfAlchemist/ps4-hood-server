#include <stdio.h>
#include <sstream>
#include <iostream>
#include "util.h"

#include "server.h"

int main(void)
{
	int sleepSeconds = 2;

	// No buffering
	setvbuf(stdout, NULL, _IONBF, 0);

	// TODO: escape sandbox

	Notify("Application started");

	// Start the server
	start_server();

	// End Code Here

	for (;;)
	{
	}
}
