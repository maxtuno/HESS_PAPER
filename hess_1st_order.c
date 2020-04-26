/*
///////////////////////////////////////////////////////////////////////////////
//        Copyright (c) 2012-2020 Oscar Riveros. all rights reserved.        //
//                        oscar.riveros@peqnp.science                        //
//                                                                           //
//   without any restriction, Oscar Riveros reserved rights, patents and     //
//  commercialization of this knowledge or derived directly from this work.  //
///////////////////////////////////////////////////////////////////////////////

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct cpu {
    int n;
    int m;
    int k;
    int c;
    int o;
    int *sz;
    unsigned char *mod;
    unsigned char *opt;
    int **cls;
};

int o(struct cpu *cpu) {
    int i, j, c = 0;
    cpu->o++;
    for (i = 0; i < cpu->m; i++) {
        for (j = 0; j < cpu->sz[i]; j++) {
            if (cpu->cls[i][j] > 0 == cpu->mod[abs(cpu->cls[i][j]) - 1] || cpu->cls[i][j] < 0 == !cpu->mod[abs(cpu->cls[i][j]) - 1]) {
                c++;
                break;
            }
        }
    }
    return c;
}

void s(int k, struct cpu *cpu) {
    cpu->mod[k] = !cpu->mod[k];
}

void h(struct cpu *cpu) {
    int k, loc;
    cpu->c = 0;
    cpu->o = 0;
    for (k = 0; k < cpu->n; k++) {
        oo:
        s(k, cpu);
        loc = o(cpu);
        if (loc > cpu->c) {
            cpu->c = loc;
            memcpy(cpu->opt, cpu->mod, sizeof(unsigned char) * cpu->n);
            if (cpu->c == cpu->m) {
                return;
            }
            goto oo;
        } else if (loc < cpu->c) {
            goto oo;
        }
    }
}

int main(int argc, char **argv) {
    int i, j;
    char buffer[2048];
    struct cpu cpu;

    if (argc != 2) {
        printf("c /////////////////////////////////////////////////////////////////////////////\n");
        printf("c //       Copyright (c) 2012-2020 Oscar Riveros. all rights reserved.       //\n");
        printf("c //                       oscar.riveros@peqnp.science                       //\n");
        printf("c //                                                                         //\n");
        printf("c //  without any restriction, Oscar Riveros reserved rights, patents and    //\n");
        printf("c // commercialization of this knowledge or derived directly from this work. //\n");
        printf("c /////////////////////////////////////////////////////////////////////////////\n");
        printf("c                                                                              \n");
        printf("c usage: %s <instance>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (strcmp(buffer, "c") == 0) {
        while (strcmp(buffer, "\n") != 0) {
            fscanf(file, "%s", buffer);
        }
    }
    while (strcmp(buffer, "p") != 0) {
        fscanf(file, "%s", buffer);
    }
    fscanf(file, " cnf %i %i", &cpu.n, &cpu.m);
    cpu.sz = (int *) calloc((size_t) cpu.m, sizeof(int));
    cpu.cls = (int **) calloc((size_t) cpu.m, sizeof(int *));
    cpu.k = 0;

    for (i = 0; i < cpu.m; i++) {
        j = 0;
        cpu.cls[i] = (int *) calloc((size_t) cpu.n, sizeof(int));
        do {
            fscanf(file, "%s", buffer);
            if (strcmp(buffer, "c") == 0) {
                continue;
            }
            cpu.cls[i][j++] = atoi(buffer);
        } while (strcmp(buffer, "0") != 0);
        j--;
        cpu.cls[i] = (int *) realloc(cpu.cls[i], j * sizeof(int));
        cpu.sz[i] = j;
        if (cpu.sz[i] > cpu.k) {
            cpu.k = cpu.sz[i];
        }
    }
    fclose(file);

    cpu.mod = (unsigned char *) calloc((size_t) cpu.n, sizeof(unsigned char));
    cpu.opt = (unsigned char *) calloc((size_t) cpu.n, sizeof(unsigned char));

    clock_t start_time = clock();
    h(&cpu);
    clock_t end_time = clock();

    printf("%s,%d,%d,%d,%lf,%lf,%d,%lf,", argv[1], cpu.n, cpu.m, cpu.k, (double) cpu.m / cpu.n, (double) cpu.c / cpu.m, cpu.o, (double) (end_time - start_time) / CLOCKS_PER_SEC);
    for (i = 0; i < cpu.n; i++) {
        printf("%d", cpu.opt[i]);
    }
    printf("0\n");

    free(cpu.mod);
    free(cpu.sz);
    free(cpu.cls);

    return EXIT_SUCCESS;
}