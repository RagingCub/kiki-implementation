#include <kiki_api.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define true 1

struct kiki_handle_t {
    int fd;
};

struct kiki_buffer_handle_t {
    size_t id;
};

int kiki_device_init(kiki_handle_t **dev) {
    struct kiki_handle_t *handle = malloc(sizeof(struct kiki_handle_t));
    if (handle <= 0) {
        return -1;
    }

    int fd = open("/dev/kiki", O_RDWR);
    if (fd < 0) {
        return -1;
    }
    handle->fd = fd;

    *dev = handle;
    return 0;
}

void kiki_device_deinit(kiki_handle_t *dev) {
    close(dev->fd);
    free(dev);
}


int kiki_device_fileno(kiki_handle_t *dev) {
    return dev->fd;
}

int kiki_device_get_status(kiki_handle_t *dev, struct kiki_status *out) {
    return ioctl(dev->fd, KIKIIO_GETSTATUS, out);
}

int kiki_device_clear_buffers(kiki_handle_t *dev) {
    int r;
    while (true) {
        r = ioctl(dev->fd, KIKIIO_CLRBUFS);
        if (r == 0) return 0;
    }
    return -1;
}


int kiki_count_buffers(kiki_handle_t *dev, size_t *amount) {
    int r;
    while (true) {
        r = ioctl(dev->fd, KIKIIO_COUNTBUF, amount);
        if (r == 0) return 0;
    }
    return -1;
}

int kiki_list_buffers(kiki_handle_t *dev, kiki_buffer_handle_t ***buffers) {
    buffers = NULL;
}

void kiki_buffer_list_free(kiki_buffer_handle_t **buffers) {}

int kiki_new_buffer(kiki_handle_t *dev, size_t size, kiki_buffer_handle_t **buffer) {}


unsigned long kiki_buffer_id(kiki_buffer_handle_t *buffer) {}

int kiki_buffer_size(kiki_buffer_handle_t *buffer, size_t *out) {}

int kiki_buffer_inspect(kiki_buffer_handle_t *buffer, struct kiki_buffer_info *info) {}


ssize_t kiki_write_buffer(kiki_buffer_handle_t *buffer, const char *data, size_t length) {}

ssize_t kiki_read_buffer(kiki_buffer_handle_t *buffer, char *data, size_t length) {}


int kiki_save_buffer(kiki_buffer_handle_t *buffer, FILE *output) {}

int kiki_load_buffer(kiki_handle_t *dev, kiki_buffer_handle_t **out, FILE *input) {}

