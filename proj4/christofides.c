#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} vector;

int* distance(vector* v, int l){
    int* e = (int*)malloc(l*l*sizeof(int));
    int x1, y1, x2, y2;
    int i, j, k;
    int d;

    double s;

    for (i = 0; i < l; i++) {
        x1 = v[i].x;
        y1 = v[i].y;
        for (j = i + 1; j < l; j++) {
            x2 = v[j].x;
            y2 = v[j].y;
            d = (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
            s = sqrt(d);
            d = (int) (s + 0.5);
            e[i*l+j] = d;
            e[j*l+i] = d;
        }
    }
    return e;
}

vector* mst(int* e, int l){
    char* v = (char*)malloc(l*sizeof(char));
    int* m = (int*)malloc(l*sizeof(int));
    vector* g = (vector*)malloc((l-1)*sizeof(vector));
    vector s;
    int q;
    
    int f, i, j, k = 0;
    v[0] = 1;
    for (i = 1; i < l; i++) {
        v[i] = 0;
        m[i] = 0;
    }
    
    f = 1;
    while (f) {
        f = 0;
        q = 0;
        for (i = 0; i < l; i++) {
            if (v[i]) {
                continue;
            }
            if (!q || (e[m[i]*l+i] < q)) {
                f = 1;
                q = e[m[i]*l+i];
                s.x = m[i];
                s.y = i;
            }
        }
        if (f) {
            v[s.y] = 1;
            g[k++] = s; 

            for (i = 0; i < l; i++) {
                if (!v[i]) {
                    continue;
                }
                if (e[s.y*l+i] < e[m[i]*l+i]) {
                    m[i] = s.y;
                }
            }
        }
    }
    free(v);
    return g;
}

int main(){
    int n = 125;
    int l = n*n;
    vector* v = (vector*)malloc(l*sizeof(vector));
    vector* g;
    int* e;
    int i, j, k = 0;
    

    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            v[k].x = i;
            v[k++].y = j;
        }
    }

    e = distance(v,l);
    g = mst(e,l);

    //printf("cake");
    free(e);
    free(v);
}
