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

void vector_dll_add(vector_dll* head, vector_dll* place, vector data) {
    vector_dll* new = (vector_dll*)malloc(sizeof(vector_dll));
    new->v = data;
    if (new) {
        if (place->n) {
            place->n->p = new;
            new->n = place->n;
        } else {
            head->p = new;
            new->n = 0;
        }
        place->n = new;
        new->p = place;
    } else {
        printf("malloc error\n");
        exit(1);
    }
}

void vector_dll_remove(vector_dll* head, vector_dll* place) {
    if (place->n) {
        place->n->p = place->p;
        place->p->n = place->n;
        free(place);
    } else {
        head->p = place->p;
        place->p->n = 0;
        free(place);
    }
}

void vector_dll_insert_list(vector_dll* head, vector_dll* place, vector_dll* head2) {
    if (head2->n) {
        if (place->n) {
            place->n->p = head2->p;
            head2->p->n = place->n;
        } else {
            head->p = head2->p;
        }
        place->n = head2->n;
        head2->n->p = place;
    }
    free(head2);
}

vector_dll* vector_dll_new() {
    vector_dll* new = (vector_dll*)malloc(sizeof(vector_dll));
    if (new) {
        new->n = 0;
        new->p = new;
        return new;
    } else {
        printf("malloc error\n");
        exit(1);
    }
}

void vector_dll_free(vector_dll* head) {
    vector_dll* n;
    while (head) {
        n = head;
        head = head->n;
        free(n);
    }
}

vector_dll* vector_dll_copy(vector_dll* head) {
    vector_dll* new = vector_dll_new();
    vector_dll* n;
    n = head->n;
    while (n) {
        vector_dll_add(new,new->p,n->v);
        n = n->n;
    }
    return new;
}

typedef struct int_dll_t int_dll;

struct int_dll_t {
    int i;
    int_dll* p;
    int_dll* n;
};

void int_dll_add(int_dll* head, int_dll* place, int data) {
    int_dll* new = (int_dll*)malloc(sizeof(int_dll));
    new->i = data;
    if (new) {
        if (place->n) {
            place->n->p = new;
            new->n = place->n;
        } else {
            head->p = new;
            new->n = 0;
        }
        place->n = new;
        new->p = place;
    } else {
        printf("malloc error\n");
        exit(1);
    }
}

void int_dll_remove(int_dll* head, int_dll* place) {
    if (place->n) {
        place->n->p = place->p;
        place->p->n = place->n;
        free(place);
    } else {
        head->p = place->p;
        place->p->n = 0;
        free(place);
    }
}

void int_dll_insert_list(int_dll* head, int_dll* place, int_dll* head2) {
    if (head2->n) {
        if (place->n) {
            place->n->p = head2->p;
            head2->p->n = place->n;
        } else {
            head->p = head2->p;
        }
        place->n = head2->n;
        head2->n->p = place;
    }
    free(head2);
}

int_dll* int_dll_new() {
    int_dll* new = (int_dll*)malloc(sizeof(int_dll));
    if (new) {
        new->n = 0;
        new->p = new;
        return new;
    } else {
        printf("malloc error\n");
        exit(1);
    }
}

void int_dll_free(int_dll* head) {
    int_dll* n;
    while (head) {
        n = head;
        head = head->n;
        free(n);
    }
}

int* distance_squared(vector* vertices, int length){
    int* edges = (int*)malloc(length*length*sizeof(int));
    int x1, y1, x2, y2;
    int distance;
    int i, j;

    for (i = 0; i < length; i++) {
        x1 = vertices[i].x;
        y1 = vertices[i].y;
        for (j = i + 1; j < length; j++) {
            x2 = vertices[j].x;
            y2 = vertices[j].y;
            distance = (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
            edges[i*length+j] = distance;
            edges[j*length+i] = distance;
        }
    }
    return edges;
}

void distance_approx(int* edges, int length){
    int distance;
    int i, j;

    for (i = 0; i < length; i++) {
        for (j = i + 1; j < length; j++) {
            distance = (int)(sqrt(edges[i*length+j]) + 0.5);
            edges[i*length+j] = distance;
            edges[j*length+i] = distance;
        }
    }
}

vector_dll* mst(int* edges_squared, int length){
    // vs is a list of vertices not yet in the MST
    int_dll* vs = int_dll_new();
    int_dll* ni;
    int_dll* mi;
    // for vertex i not in the current MST, minimum[i] is the edge in the
    // current MST that is closest to i
    int* minimum = (int*)malloc(length*sizeof(int));
    if (!minimum) { printf("malloc fail"); exit(1); }
    // head is the head of the doubly linked list of edges in the MST
    vector_dll* head = vector_dll_new();
    // shortest is the shortest edge connecting a vertex in the MST to
    // a vertex not in the MST
    vector v;
    // shortest is the shortest edge attached to the MST
    int shortest;
    
    int i;
    for (i = 1; i < length; i++) {
        int_dll_add(vs,vs->p,i);
    } 

    while (vs->n) {
        ni = vs->n;
        shortest = edges_squared[minimum[ni->i]*length+ni->i];
        mi = ni;
        while (ni) {
            if (edges_squared[minimum[ni->i]*length+ni->i] < shortest) {
                shortest = edges_squared[minimum[ni->i]*length+ni->i];
                mi = ni;
            }
            ni = ni->n;
        } 

        // add new edges to the MST
        v.y = mi->i;
        v.x = minimum[mi->i];
        vector_dll_add(head, head->p, v);

        // update the minimum jumps
        ni = vs->n;
        while (ni) {
            if (edges_squared[v.y*length+ni->i] < edges_squared[minimum[ni->i]*length+ni->i]) {
                minimum[ni->i] = v.y;
            }
            ni = ni->n;
        }

        // remove new vertex in the MST from the list of vertexes not in the MST
        int_dll_remove(vs, mi);
    }

    int_dll_free(vs);
    free(minimum);
    return head;
}

//returns the minimum perfect matching for odd degree vertices in MST
vector_dll* minimum_perfect_matching(int* edges_squared, vector_dll* MST, int length){
    int* degree = (int*)malloc(length*sizeof(int));
    int i;
    vector_dll* head = vector_dll_new();
    vector_dll* n;
    int_dll* odd_vertices = int_dll_new();
    int_dll* ni;
    int_dll* mi = odd_vertices;
    vector v;

    for (i = 0; i < length; i++) {
        degree[i] = 0;
    }

    n = MST->n;
    while (n) {
        degree[n->v.x]++;
        degree[n->v.y]++;
        n = n->n;
    }

    for (i = 0; i < length; i++) {
        if (degree[i] % 2) {
            int_dll_add(odd_vertices, odd_vertices->p, i);
        }
    }


    // find PM
    // for now we only find *a* perfect matching
    while (odd_vertices->n) {
        v.x = odd_vertices->n->i;
        v.y = odd_vertices->n->n->i;
        vector_dll_add(head,head->p,v);
        int_dll_remove(odd_vertices,odd_vertices->n);
        int_dll_remove(odd_vertices,odd_vertices->n);
    }
    int_dll_free(odd_vertices);

    return head;
}

int* christofides(vector* cities, int length){
    char* visited = (char*)malloc(length*sizeof(char));
    int* edges = distance_squared(cities, length);

    vector_dll* n;
    vector_dll* head = mst(edges,length);
    
    // one of these lines should induce an MST solution, the other a christofides solution.
    // i don't know why the MPM solution works, when the MST solution doesn't. don't ask.
    vector_dll* reverse = minimum_perfect_matching(edges,head,length);
    //vector_dll* reverse = vector_dll_copy(head);
    
    vector_dll_insert_list(head,head->p,reverse);

    distance_approx(edges,length);


    int* solution = (int*)malloc((length+2)*sizeof(int));
    int_dll* s = int_dll_new();
    int_dll* l = int_dll_new();
    int_dll* ni;
    int start, end;
    int i;

    for (i = 0; i < length; i++) {
        visited[i] = 0;
    }

    // calculate solution here
    //while missing edges
    while (head->n) {
        //find loop

        //modify to find a loop starting at a point in s;
        if (s->n) {
            //find a vector in head that starts in s
            n = head->n;
        } else {
            n = head->n;
        }

        start = n->v.x;
        end = n->v.y;
        int_dll_add(l, l->p, start);
        int_dll_add(l, l->p, end);

        while ( start != end ) {
            n = head->n;
            if (!n) {
                printf("Error, non-looping vertices remain.");
                exit(1);
            }
            while (n) {
                if (n->v.x == end) {
                    end = n->v.y;
                    int_dll_add(l, l->p, end);

                    vector_dll_remove(head,n);
                    break;
                } else if (n->v.y == end) {
                    end = n->v.x;
                    int_dll_add(l, l->p, end);

                    vector_dll_remove(head,n);
                    break;
                } else {
                    n = n->n;
                }
            }
        }

        //add to existing solution
        if (!s->n) {
            int_dll_insert_list(s,s,l);
            l = int_dll_new();
        } else {
            //find l->n->i in s
            ni = s->n;
            while (ni->n && ni->i != l->n->i) {
                ni = ni->n;
            }
            int_dll_insert_list(s,ni,l);
            l = int_dll_new();
        }
    }

    // march through s and skip previously visited nodes
    solution[0] = 0;
    i = 1;
    while (s->n) {
        if (!visited[s->n->i]) {
            solution[i] = s->n->i;
            solution[0] += edges[solution[i]*length+solution[i-1]];
            visited[s->n->i] = 1;
            i++;
        }
        int_dll_remove(s,s->n);
    }
    solution[i] = solution[1];
    solution[0] += edges[solution[i]*length+solution[i-1]];
    
    //vector_dll_free(head);
    free(edges);
    return solution;
}

int main(int argc, char *argv[]){
    int length;
    vector* vertices;

    int* solution;
    int i, j, k, n = 0;
    int this_x;
    int this_y;
    int this_n;
    FILE *fp;

    if(argc < 2){
        printf("Missing argument: name of test file\n");
        return 0;
    }

    // determine length of problem
    fp = fopen(argv[1], "r");
    if (fp == NULL){
        printf("input file %s not found! Aborting.\n", argv[1]);
        return 0;
    }
    //printf("successfully opened file\n");
    k = 0;
    while (fscanf(fp, "%i %i %i", &this_n, &this_x, &this_y) == 3){k++;}
    fclose(fp);
    length = k;

    // length determined, alloc mem for it, load cities 
    vertices = (vector*)malloc(length*sizeof(vector));
    fp = fopen(argv[1], "r");
    k = 0;
    while (fscanf(fp, "%i %i %i", &this_n, &this_x, &this_y) == 3){
        vertices[k].x = this_x;
        vertices[k++].y = this_y;
    }

    //calculate solution
    solution = christofides(vertices,length);
    //printf("length: %d\n", solution[0]);
    for (i = 0; i < length + 1; i++) {
        printf("%d\n", solution[i]);
    }

    free(vertices);
    //free(solution);
}
