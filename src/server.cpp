#include "mongoose/mongoose.h"
#include "routes/routes.h"

void start_server()
{
	struct mg_mgr mgr;											   // Declare event manager
	mg_mgr_init(&mgr);											   // Initialise event manager
	mg_http_listen(&mgr, "http://0.0.0.0:8000", ev_handler, NULL); // Setup listener
	for (;;)
	{ // Run an infinite event loop
		mg_mgr_poll(&mgr, 1000);
	}
}
