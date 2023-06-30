#include <stdio.h>
#include <unistd.h>

#include <event2/event.h>
#include <event2/util.h>

int main(int argc, char *argv[])
{
    printf("Libevent's version is %s\n", event_get_version());

    printf("Libevent's I/O mutiplexing are:\n");

    const char **method = event_get_supported_methods();
    int i = 0;
    for (i = 0; method[i] != NULL; i++)
    {
        printf("%s\t", method[i]);
    }
    putchar(10);

    struct event_base *base = NULL;
    struct event_config *cfg = NULL;

    cfg = event_config_new();
    if (!cfg) 
    {
        return 0;
    }
    event_config_avoid_method(cfg, "epoll");
    event_config_avoid_method(cfg, "poll");

    base = event_base_new_with_config(cfg);
    if (!base) 
    {
        event_config_free(cfg);
        return 0;
    }


    printf("Default cfg is %s\n", event_base_get_method(base));

    event_base_free(base);
    event_config_free(cfg);

    return 0;
}
