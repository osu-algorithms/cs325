#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} vector;

typedef struct vector_dll_t vector_dll;

typedef struct {
    vector v;
    vector_dll* p;
    vector_dll* n;
} vector_dll_t;

typedef struct {
    vector_dll* first;
    vector_dll* last;
} vector_dll_head;

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

int* mst(int* edges, int length){
    // for vertex i, vertices[i] is whether that vertex is
    // in the current MST
    char* vertices = (char*)malloc(length*sizeof(char));
    // for vertex i not in the current MST, minimum[i] is the edge in the
    // current MST that is closest to i
    int* minimum = (int*)malloc(length*sizeof(int));
    // graph is the list of edges in the MST
    vector* graph = (vector*)malloc((length-1)*sizeof(vector));
    vector_dll* dll = 0;
    // alternate form for storing MST
    int* MST = (int*)malloc((length)*sizeof(int));
    MST[0] = -1;
    // shortest is the shortest edge connecting a vertex in the MST to
    // a vertex not in the MST
    vector shortest;
    // shortest_length is the length of shortest
    int shortest_length;
    // flag and iterators
    int flag, i, j, k = 0;

    // intialize arrays
    vertices[0] = 1;
    for (i = 1; i < length; i++) {
        vertices[i] = 0;
        minimum[i] = 0;
    }
    
    flag = 1;
    while (flag) {
        flag = 0;
        for (i = 0; i < length; i++) {
            if (vertices[i]) {
                continue;
            }
            if (!flag || (edges[minimum[i]*length+i] < shortest_length)) {
                flag = 1;
                shortest_length = edges[minimum[i]*length+i];
                shortest.x = minimum[i];
                shortest.y = i;
            }
        }
        if (flag) {
            vertices[shortest.y] = 1;
            MST[shortest.y] = shortest.x;
            graph[k++] = shortest; 
            // create new
            // point at old
            // update old

            for (i = 0; i < length; i++) {
                if (!vertices[i]) {
                    continue;
                }
                if (edges[shortest.y*length+i] < edges[minimum[i]*length+i]) {
                    minimum[i] = shortest.y;
                }
            }
        }
    }
    free(vertices);
    free(minimum);
    free(graph);
    return MST;
}

int* mst_tsp(int* edges, int length){
    char* vertices = (char*)malloc(length*sizeof(char));
    int* MST = mst(edges,length);
    int* solution = (int*)malloc((length+2)*sizeof(int));
    int v1 = 0, v2 = 0;
    int flag, i, j = 1;
    
    // intialize array
    vertices[0] = 1;
    for (i = 1; i < length; i++) {
        vertices[i] = 0;
    }

    solution[0] = 0; //current length
    solution[1] = 0; //first city
    
    while (v2 > -1) {
        flag = 0;
        for (i = length - 1; i >= 0; i--) {
            if ( vertices[i] ) { continue; }
            if (MST[i] == v2) {
                flag = 1;
                solution[++j] = i;
                solution[0] += edges[v1*length+i];
                v1 = i;
                v2 = i;
                vertices[i] = 1;
                break;
            }
        }
        if (!flag) {
            v2 = MST[v2];
        }
    }
    solution[++j] = 0;
    solution[0] += edges[v1*length];

    free(MST);
    return solution;
}

//returns the minimum perfect matching for odd degree vertices in MST
vector* perfect_matching(int* MST, int length){
}

int* christofides(int* edges, int length){
    int* MST = mst(edges,length);
    vector* PM = perfect_matching(MST, length-1);
    int* solution = (int*)malloc((length+2)*sizeof(int));
    
    solution[0] = 0;
    
    free(MST);
    free(PM);
    return solution;
}

int main(){
    int n = 125;
    int length = n*n;
    vector* vertices = (vector*)malloc(length*sizeof(vector));
    int* solution_mst;
    int* solution_christofides;
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
    solution_mst = mst_tsp(edges,length);
    for (i = 0; i < length + 2; i++) {
        printf("%d\n", solution_mst[i]);
    }
    //solution_christofides = christofides(edges,length);
    //printf("length of Christofides algorithm path: %d\n", solution_christofides[0]);

    free(vertices);
    free(edges);
    //free(solution_mst);
    //free(solution_christofides);
}
