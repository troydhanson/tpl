#include "tpl.h"

struct Test {
  char *string;
};

struct Test tests[] = {{"first"}, {"second"},{"third"}};
char buffer[5000]; /* this doesn't matter- just a place to dump to */

/* this test is useful under valgrind to detect an unfreed string bug
*/

int main(int argc, char *argv[]) {
  tpl_node *tn;
  tn = tpl_map("S(s)#", &tests, 3);
  tpl_pack(tn, 0);
  tpl_dump(tn, TPL_MEM|TPL_PREALLOCD, buffer, sizeof(buffer));
  /* at the next line, when the tpl tree is freed, the string node
   * is followed by a pound node. The string node has actually had
   * its data member multiplied by the pound node's factor, but we
   * don't know that, until after we freed the string node at tpl.c:710.
   * if you run this example under valgrind --leak-check=full you can
   * see 13 bytes lost which are "second" and "third" above
   */
  tpl_free(tn);
  return 0;
}
