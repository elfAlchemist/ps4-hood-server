#include "../mongoose/mongoose.h"

// HTTP server event handler function
struct Route
{
	const char *uri;
	void (*handler)(struct mg_connection *, struct mg_http_message *);
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
	struct mg_http_serve_opts opts = {.root_dir = "./"};
	mg_http_serve_dir(c, hm, &opts);
}

Route routes[] = {
	{"/api/time/get", handle_time_get},
	{"/api/packages", handle_packages},
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
