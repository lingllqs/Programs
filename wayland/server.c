#include <stdio.h>
#include <wayland-server.h>


int main(int argc, char *argv[])
{
    // 创建显示服务
    struct wl_display *display = wl_display_create();

    if (!display)
    {
        fprintf(stderr, "Unable to create wayland display\n");
        return 1;
    }

    // 创建通信套接字
    const char *socket = wl_display_add_socket_auto(display);
    if (!socket)
    {
        fprintf(stderr, "Unable to add socket to wayland display\n");
        return 1;
    }

    // 运行显示服务
    fprintf(stderr, "Running wayland display on %s\n", socket);
    wl_display_run(display);

    // 销毁
    wl_display_destroy(display);

    return 0;
}
