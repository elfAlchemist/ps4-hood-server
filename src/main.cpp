#include <stdio.h>
#include <sstream>
#include <iostream>
#include "util.h"

#include "mongoose.h" // To build, run: cc main.c mongoose.c

// HTTP server event handler function
struct Route
{
	const char *uri;
	void (*handler)(struct mg_connection *, struct mg_http_message *);
};

struct kinfo_proc
{
	char junk0[0x48];
	pid_t pid;
	pid_t ppid;
	pid_t pgid;
	pid_t tpgid;
	pid_t sid;
	char junk1[0x163];
	char name[19];
};

void handle_time_get(struct mg_connection *c, struct mg_http_message *hm)
{
	mg_http_reply(c, 200, "", "{%m:%lu}\n", MG_ESC("time"), time(NULL));
}

void handle_packages(struct mg_connection *c, struct mg_http_message *hm)
{
	mg_http_reply(c, 200, "Content-Type: application/json\r\n", "{\"packages\":[]}\n");
}

void handle_unsupported(struct mg_connection *c, struct mg_http_message *hm)
{
	mg_http_reply(c, 500, "", "{%m:%m}\n", MG_ESC("error"), MG_ESC("Unsupported URI"));
}

void handle_browse(struct mg_connection *c, struct mg_http_message *hm)
{
	struct mg_http_serve_opts opts = {.root_dir = "/"};
	mg_http_serve_dir(c, hm, &opts);
}

Route routes[] = {
	{"/api/time/get", handle_time_get},
	{"/api/packages", handle_packages},
	// Add more routes here
};

void ev_handler(struct mg_connection *c, int ev, void *ev_data)
{
	if (ev == MG_EV_HTTP_MSG)
	{
		struct mg_http_message *hm = (struct mg_http_message *)ev_data;
		bool matched = false;
		for (auto &route : routes)
		{
			if (mg_match(hm->uri, mg_str(route.uri), NULL))
			{
				route.handler(c, hm);
				matched = true;
				break;
			}
		}
		if (!matched)
			handle_browse(c, hm);
	}
}

int main(void)
{
	int sleepSeconds = 2;

	// No buffering
	setvbuf(stdout, NULL, _IONBF, 0);

	// TODO: escape sandbox

	Notify("Hello Onion");

	// Code Here

	// sceAppInstUtilInitialize();

	struct mg_mgr mgr;											   // Declare event manager
	mg_mgr_init(&mgr);											   // Initialise event manager
	mg_http_listen(&mgr, "http://0.0.0.0:8000", ev_handler, NULL); // Setup listener
	for (;;)
	{ // Run an infinite event loop
		mg_mgr_poll(&mgr, 1000);
	}

	// End Code Here

	for (;;)
	{
	}
}
