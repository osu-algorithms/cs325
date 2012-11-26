#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} vector;

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
    //int* edges = (int*)malloc(length*length*sizeof(int));
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

int* mst(int* edges_squared, int length){
    // for vertex i, vertices[i] is whether that vertex is
    // in the current MST
    char* vertices = (char*)malloc(length*sizeof(char));
    // for vertex i not in the current MST, minimum[i] is the edge in the
    // current MST that is closest to i
    int* minimum = (int*)malloc(length*sizeof(int));
    // tree of edges in the MST
    int* MST = (int*)malloc((length)*sizeof(int));
    MST[0] = -1;
    // shortest is the shortest edge connecting a vertex in the MST to
    // a vertex not in the MST
    vector shortest;
    // shortest_length is the length of shortest
    int shortest_length, mst_length = 0;
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
            if (!flag || (edges_squared[minimum[i]*length+i] < shortest_length)) {
                flag = 1;
                shortest_length = edges_squared[minimum[i]*length+i];
                shortest.x = minimum[i];
                shortest.y = i;
            }
        }
        if (flag) {
            vertices[shortest.y] = 1;
            MST[shortest.y] = shortest.x;
            mst_length += (int)sqrt(edges_squared[shortest.y*length+shortest.x] + 0.5);

            for (i = 0; i < length; i++) {
                if (vertices[i]) {
                    continue;
                }
                if (edges_squared[shortest.y*length+i] < edges_squared[minimum[i]*length+i]) {
                    minimum[i] = shortest.y;
                }
            }
        }
    }
    free(vertices);
    free(minimum);
    return MST;
}

int* mst_tsp(vector* cities, int length){
    int* edges = distance_squared(cities, length);
    char* vertices = (char*)malloc(length*sizeof(char));
    int* MST = mst(edges,length);
    distance_approx(edges,length);
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

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Missing arguments: Name of test file, number of lines\n");
        return 0;
    }

    int length;
    vector* vertices;
    int* solution;
    int i, j, k = 0;

    FILE* fp = fopen(argv[1], "r");
    int this_n, this_x, this_y;

    if (fp == NULL){
        printf("input file %s not found! Aborting.", argv[1]);
        return 0;
    }
    while(fscanf(fp, "%i %i %i", &this_n, &this_x, &this_y) == 3) {}
    fclose(fp);

    length = this_n + 1;
    vertices = (vector*)malloc(length*sizeof(vector));
    fp = fopen(argv[1], "r");
    while(fscanf(fp, "%i %i %i", &this_n, &this_x, &this_y) == 3) {
        vertices[k].x = this_x;
        vertices[k++].y = this_y;
    }

    solution = mst_tsp(vertices,length);

    for (i = 0; i < length + 1; i++) {
        printf("%d\n", solution[i]);
    }

    free(vertices);
    free(solution);
}
