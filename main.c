#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>



//#define _ALLOCATION_LIMIT 20
int __allocs = 0;
static void* my_malloc(size_t size) {
#ifdef _ALLOCATION_LIMIT
    if (__allocs > _ALLOCATION_LIMIT) return NULL;
#endif
    __allocs++;
    return malloc(size);
}
static void my_free(void *ptr) {

    __allocs--;
    free(ptr);
}
#define malloc my_malloc
#define free my_free

struct edge{
    int size;
    int first_node;
    int second_node;
};

int who_s_parent(int node,int *parent){
    if(node == parent[node]) return node;
    else parent[node]=who_s_parent(parent[node],parent);
}

int main() {
    int N;
    scanf_s("%i",&N);

    if(( N < 0) || (N > 5000)){
        printf("bad number of vertices");
        return 0;
    }
    int M;
    scanf_s("%i",&M);
    if(M < 0 || M > (N*(N+1)/2)){
        printf("bad number of edges");
        return 0;
    }
    if(M==0 && N==0){
        printf("no spanning tree");
        return 0;
    }
    struct edge *mas = malloc(M * sizeof(struct edge));
    for(int i=0; i < M;i++){
        int a,b,c;
        scanf_s("%i",&a);
        scanf_s("%i",&b);
        scanf_s("%i",&c);
        if(a == -858993460){
            printf("bad number of lines");
            return 0;
        }
        if(a<1 || a > N){
            printf("bad vertex");
            return 0;
        }
        if(b<1 || b > N){
            printf("bad vertex");
            return 0;
        }
        if(c<0 || c > INT_MAX){
            printf("bad length");
            return 0;
        }
        getchar();
        mas[i].size =c;
        mas[i].first_node=a;
        mas[i].second_node=b;
    }

    for(int i = 0 ; i < M - 1; i++) {
            for(int j = 0 ; j < M - i - 1 ; j++) {
                if(mas[j].size > mas[j+1].size) {
                    struct edge tmp = mas[j];
                    mas[j] = mas[j+1] ;
                    mas[j+1] = tmp;
                }
            }
    }

    int *parent = (int*)malloc(sizeof(int)*(N+1));

    for(int i = 0;i <= N;i++){
        parent[i]=i;
    }

    int itter = 0;
    int first, second;
    int count = 0;
    while(itter!=M){
        first = who_s_parent(mas[itter].first_node,parent);
        second= who_s_parent(mas[itter].second_node,parent);
        if(first!=second){
            count++;
            parent[first]=second;
//            printf("%i ", first);
//            printf("%i \n", second);
        }
        itter++;
    }

    if(count<N-1){
        printf("no spanning tree");
        return 0;
    }else {
        for(int i = 0;i <= N;i++){
            parent[i]=i;
        }
        itter = 0;
        count = 0;
        while (itter != M) {
            first = who_s_parent(mas[itter].first_node, parent);
            second = who_s_parent(mas[itter].second_node, parent);
            if (first != second) {
                count++;
                parent[first] = second;
                printf("%i ", mas[itter].first_node);
                printf("%i \n", mas[itter].second_node);
            }
            itter++;
        }
    }


//
//    for(int i = 0;i < M;i++){
//        printf("%i",mas[i].size);
//    }
    free(mas);
    free(parent);
    fprintf(stderr, "Allocation balance %d %s\n", __allocs, __allocs?"- Memory leaks occur!!!":"is ok");
    return 0;
}