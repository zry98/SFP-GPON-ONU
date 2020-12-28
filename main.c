#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int GetTagParam(int tag_id, char *bytes, int _bytes_length, int *bytes_length);
int SETTagParam(int tag_id, char *bytes, int bytes_length);

int main(int argc, char *argv[]) {
  int err, bytes_length = 0;
  char bytes[1024];

  if (argc == 3 && strcmp(argv[1], "2") == 0) {  // get
    err = GetTagParam(atoi(argv[2]), bytes, 1024, &bytes_length);
    if (err) {
      printf("GetTagParam Error: %d\n", err);
      return 1;
    }

    for (int i = 0; i < bytes_length; i++) {
      printf("%02x ", bytes[i]);
    }
    printf("\n");

  } else if (argc == 4 && strcmp(argv[1], "1") == 0) {  // set
    bytes_length = ((int) strlen(argv[3]) + 1) / 3;
    char *pos = argv[3];

    for (int i = 0; i < bytes_length; i++) {
      if (sscanf(pos, "%02x", &bytes[i]) != 1) {
        printf("Error parsing bytes");
        return 1;
      }
      pos += 3;
    }

    err = SETTagParam(atoi(argv[2]), bytes, bytes_length);
    if (err) {
      printf("SetTagParam Error: %d\n", err);
      return 1;
    }

  } else {
    // TODO: print usage
  }

  return 0;
}
