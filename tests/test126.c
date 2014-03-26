#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tpl.h"

struct ms_t {
    char c;
    char *x;
    int i;
};

int main() {
    tpl_node *tn;
    struct ms_t ms = {/*.c =*/ 'a', /*.x =*/ (char*)1, /*.i =*/ 2 };
    struct ms_t ms2;

    tn = tpl_map("S(cpi)", &ms);
    tpl_pack(tn,0);
    tpl_dump(tn,TPL_FILE,"/tmp/test126.tpl");
    tpl_free(tn);

    memset(&ms2,0,sizeof(struct ms_t));
    tn = tpl_map("S(cpi)", &ms2);
    tpl_load(tn,TPL_FILE,"/tmp/test126.tpl");
    tpl_unpack(tn,0);
    tpl_free(tn);
    printf("%c\n%p\n%d\n", ms2.c, ms2.x, ms2.i);
    return(0);
}
