#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
union Fun {
	  uint8_t u[4];
	    int8_t i[4];
	      char s[4];
	        int t;
};

int main() {
	  union Fun* fun = calloc(1, sizeof(union Fun));
	    fun->i[0] = -1;
	      printf("%u\n", fun->u[0]);
	        fun->u[0] *= 2;
		  printf("%u\n", fun->i[0]);
		    return 0;
}
