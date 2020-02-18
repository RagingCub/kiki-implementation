#include <stdio.h>
#include <kiki_api.h>

void show_status(kiki_handle_t *dev) {
    struct kiki_status status;
    int r = kiki_device_get_status(dev, &status);
    printf("status return: %d\n", r);
    if (r == 0) printf("\tstatus_no: %d; status_msg: %s\n", status.status_no, status.status_msg);
}

int main() {
    kiki_handle_t *dev = NULL;
    int r = kiki_device_init(&dev);
    printf("init return: %d\n", r);
    printf("\tfileno: %d\n", kiki_device_fileno(dev));

    show_status(dev);

    r = kiki_device_clear_buffers(dev);
    printf("clear_buffers return: %d\n", r);

    size_t amount;
    r = kiki_count_buffers(dev, &amount);
    printf("count_buffers return: %d\n", r);
    if (r == 0) printf("\tbuffers count: %zu\n", amount);

    show_status(dev);

    kiki_device_deinit(dev);
    return 0;
}
