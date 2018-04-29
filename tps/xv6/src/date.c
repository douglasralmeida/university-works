#include "types.h"
#include "user.h"
#include "date.h"

int stdout = 1;
int stderr = 2;

int main(int argc, char *argv[]) {
  struct rtcdate r;

  if (date(&r)) {
    printf(stderr, "Erro ao consultar a data do sistema.\n");
    exit();
  }

  // Imprima a data aqui
  printf(stdout, "%d/%d/%d %d:%d:%d\n", r.day, r.month, r.year, r.hour, r.minute, r.second);
  exit();
}
