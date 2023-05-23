#include <stdio.h>
#include <unistd.h>

#include <event2/event.h>
#include <event2/util.h>

int main(int argc, char **argv)
{
    // 打印libevent的版本信息
    printf("Libevent Version: %s\n", event_get_version());

    // 打印libevent支持的封装方法
    const char **method = event_get_supported_methods();
    int i = 0;
    for (i = 0; method[i] != NULL; ++i)
    {
        printf("%s ", method[i]);
    }
    putchar(10);

    struct event_base *base = NULL;
    struct event_config *cfg = NULL;

    cfg = event_config_new();
    if (!cfg)
    {
        return -1;
    }
    // event_config_avoid_method(cfg, "epoll");
    base = event_base_new_with_config(cfg);
    if (!base)
    {
        event_config_free(cfg);
        return -2;
    }

    // 打印默认的I/O封装方法
    printf("The default config is %s\n", event_base_get_method(base));

    event_base_free(base);
    event_config_free(cfg);

    return 0;
}
