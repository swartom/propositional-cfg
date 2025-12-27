#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>



#define ALPHABET 3

struct gamma {
    void* previous;
    uint8_t k;
    uint8_t lb;
    uint8_t ub;
    uint8_t f;
};
double get_random() { return (double)rand() / (double)RAND_MAX; }
int rewrite(struct gamma* c) {
    uint8_t midpoint = (c->ub - c->lb)/2 + 1;

    if(c->lb != c->ub){
    switch (c->k) {
        case 'Q':
            struct gamma* second = malloc(sizeof(struct gamma));
            second->k = 'Q';
            second->previous = c->previous;
            second->lb = c->lb;
            second->ub = c->lb + midpoint - 1;

            struct gamma* not = malloc(sizeof(struct gamma));
            not->lb = c->lb + midpoint ;
            not->ub = c->ub;
            not->previous = second;
            not->k = 'Q';
            rewrite(not);
            c->ub =0 ;
            c->lb =0 ;
            if (get_random() > 0.5) { // OR
                c->k = 'v';
                not->f = midpoint;
                not->k = 'L';
                // if its a not, then the inverse of this is valid in the other half
            } else { // AND
                c->k = '^';
                // if its a and then a tautology in the other side is an annihilation.

            }
            c->previous = not;
            rewrite(second);
            rewrite(not);
            break;
        case 'L':
                if (get_random() > 0.5){
                    struct gamma* not = malloc(sizeof(struct gamma));
                    not->k = '!';
                    not->previous = c->previous;

                    struct gamma* not2 = malloc(sizeof(struct gamma));
                    not2->previous = not;
                    not2->k =  64+c->f;

                    struct gamma* comparsion = malloc(sizeof(struct gamma));
                    comparsion->k = 'Q'; // must be and other-wise tautology!
                    comparsion->lb = c->lb;
                    comparsion->ub = c->ub;
                    comparsion->previous = not2;

                    c->f = 0;
                    c->k = '^';
                    c->previous = comparsion;

                    rewrite(comparsion);
            } else {
                c->f = 0;
                c->k = 'Q';
                rewrite(c);
            }
            break;
    case 'S':
            c->k = 'Q'; // Q can be any element in the set if its an $OR$ then switch to A which
                        // has only one
            break;
                }
    } else{
        switch (c->k) {
            case 'Q':
                c->k = 64+c->lb;
                break;
            case 'L':
                if (get_random() > 0.5){
                    struct gamma* not = malloc(sizeof(struct gamma));
                    not->k = '!';
                    not->previous = c->previous;

                    struct gamma* not2 = malloc(sizeof(struct gamma));
                    not2->previous = not;
                    not2->k =  64+c->f;

                    struct gamma* comparsion = malloc(sizeof(struct gamma));
                    comparsion->k = 'Q'; // must be and other-wise tautology!
                    comparsion->lb = c->lb;
                    comparsion->ub = c->ub;
                    comparsion->previous = not2;

                    c->f = 0;
                    c->k = '^';
                    c->previous = comparsion;

                    rewrite(comparsion);
            } else {
                c->f = 0;
                c->k = 'Q';
                rewrite(c);
            }
            break;
        }

    }
    return 0;
}


int main(){
    // assume that $&$ is \land
    // assume that $~$ is \lor
    // assume that $!$ is \knot

    // So each subset of the grammar has a 'bound' on the ordered alphabet

    // The grammars take the form of
    //


    struct gamma* chomsky_standard = (struct gamma*) malloc(sizeof(struct gamma));
    chomsky_standard->k = 'Q';
    chomsky_standard->f = 0;
    chomsky_standard->lb = 1;
    chomsky_standard->ub = ALPHABET;
    rewrite(chomsky_standard);
    struct gamma* chain = chomsky_standard;

    do {
        printf("%c(%d,%d)",chain->k,chain->lb,chain->ub);
        chain = chain->previous;
    }while(chain != NULL);
    chain = chomsky_standard;
    printf("\n");
    do {
        printf("%c",chain->k);
        chain = chain->previous;
    }while(chain != NULL);
}
