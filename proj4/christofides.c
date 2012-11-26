#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} vector;

typedef struct vector_dll_t vector_dll;

struct vector_dll_t {
    vector v;
    vector_dll* p;
    vector_dll* n;
};

typedef struct int_dll_t int_dll;

struct int_dll_t {
    int i;
    int_dll* p;
    int_dll* n;
};

int* distance(vector* vertices, int length){
    int* edges = (int*)malloc(length*length*sizeof(int));
    int x1, y1, x2, y2;
    int distance;
    int i, j, k;

    for (i = 0; i < length; i++) {
        x1 = vertices[i].x;
        y1 = vertices[i].y;
        for (j = i + 1; j < length; j++) {
            x2 = vertices[j].x;
            y2 = vertices[j].y;
            distance = (int)(sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)) + 0.5);
            edges[i*length+j] = distance;
            edges[j*length+i] = distance;
        }
    }
    return edges;
}

vector_dll* mst(int* edges, int length){
    // for vertex i, vertices[i] is whether that vertex is
    // in the current MST
    int_dll* vs = (int_dll*)malloc(sizeof(int_dll));
    vs->p = 0;
    vs->n = 0;
    int_dll* ni;
    int_dll* mi;
    // for vertex i not in the current MST, minimum[i] is the edge in the
    // current MST that is closest to i
    int* minimum = (int*)malloc(length*sizeof(int));
    // graph is the list of edges in the MST
    vector_dll* head = (vector_dll*)malloc(sizeof(vector_dll));
    head->p = 0;
    head->n = 0;
    vector_dll* n;
    vector_dll* m = head;
    // shortest is the shortest edge connecting a vertex in the MST to
    // a vertex not in the MST
    vector shortest;
    // shortest_length is the length of shortest
    int shortest_length;
    // flag and iterators
    int flag, i, j, k = 0;

    // intialize arrays

    for (i = 1; i < length; i++) {
        minimum[i] = 0;

        ni = (int_dll*)malloc(sizeof(int_dll));
        mi->n = ni;
        ni->p = mi;
        ni->n = 0;
        ni->i = i;
        mi = ni;
    }
    
    flag = 1;
    while (flag) {
        ni = vs->n;
        flag = 0;
        while (ni != 0) {
            if (!flag || (edges[minimum[ni->i]*length+ni->i] < shortest_length)) {
                flag = 1;
                shortest_length = edges[minimum[ni->i]*length+ni->i];
                shortest.x = minimum[ni->i];
                shortest.y = ni->i;
                mi = ni;
            }
            ni = ni->n;
        } 
        if (flag) {
            mi->p->n = mi->n;
            mi->n->p = mi->p;
            free(mi);
            n = (vector_dll*)malloc(sizeof(vector_dll));
            m->n = n;
            n->p = m;
            n->n = 0;
            n->v = shortest;
            m = n;

            ni = vs->n;
            while (ni != 0) {
                if (edges[shortest.y*length+ni->i] < edges[minimum[ni->i]*length+ni->i]) {
                    minimum[ni->i] = shortest.y;
                }
                ni = ni->n;
            } 
        }
    }
    while (vs != 0) {
        ni = vs;
        vs = vs->n;
        free(ni);
    }
    free(minimum);
    return head;
}

//returns the minimum perfect matching for odd degree vertices in MST
vector_dll* perfect_matching(vector_dll* MST, int length){
    int* degree = (int*)malloc(length*sizeof(int));
    int i, j = 0;
    vector_dll* head = (vector_dll*)malloc(sizeof(vector_dll));
    head->p = 0;
    head->n = 0;
    vector_dll* n;

    for (i = 0; i < length; i++) {
        degree[i] = 0;
    }
    n = MST->n;
    while (n != 0) {
        degree[n->v.x]++;
        degree[n->v.y]++;
        n = n->n;
    }
    for (i = 0; i < length; i++) {
        if ((degree[i] % 2) != 0) {
            j++;
        }
    }
    printf("Odd edges: %d\n", j);
    return head;
}

int* christofides(int* edges, int length){
    vector_dll* n;
    vector_dll* MST = mst(edges,length);
    vector_dll* PM = perfect_matching(MST, length);
    int* solution = (int*)malloc((length+2)*sizeof(int));
    int i;
    
    solution[0] = 0;
    
    while (MST != 0) {
        n = MST;
        MST = MST->n;
        free(n);
    }
    while (PM != 0) {
        n = PM;
        PM = PM->n;
        free(n);
    }
    return solution;
}

int main(){
    int n = 100;
    int length = n*n;
    vector* vertices = (vector*)malloc(length*sizeof(vector));
    int* solution;
    int* edges;
    int i, j, k = 0;
    
    // create a TSP input that is every point in a nxn matrix
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            vertices[k].x = i;
            vertices[k++].y = j;
        }
    }

    edges = distance(vertices,length);
    solution = christofides(edges,length);
    printf("length of Christofides algorithm path: %d\n", solution[0]);

    free(vertices);
    free(edges);
    free(solution);
}
