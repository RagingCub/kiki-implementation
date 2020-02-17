#include "kiki_api.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

struct kiki_handle_t {
  int fd;
};

int kiki_device_init(kiki_handle_t **dev) {
  kiki_handle_t *out = NULL;
  int fd;

  out = malloc(sizeof(kiki_handle_t));

  if (!out) {
    return -1;
  }

  fd = open("/dev/kiki", O_RDWR);

  if (fd < 0) {
    free(out);
    return -1;
  }

  out->fd = fd;
  (*dev) = out;

  return 0;
}

/* de-initialize the device after use */
void kiki_device_deinit(kiki_handle_t *dev) {
  close(dev->fd);
  free(dev);
}


int kiki_device_get_status(kiki_handle_t *dev, struct kiki_status *out) {
  return ioctl(dev->fd, KIKIIO_GETSTATUS, out);
}


int kiki_count_buffers(kiki_handle_t *dev, size_t *amount) {
  unsigned long count;
  int ret;

  do {
    ret = ioctl(dev->fd, KIKIIO_COUNTBUF, &count);
  } while (ret);

  *amount = count;

  return 0;
}