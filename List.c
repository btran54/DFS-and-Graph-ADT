/***
* Brian Tran
* btran54
* 2024 Winter CSE101 PA2
* List.c
* List file containing the operations of List functions.
***/ 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "List.h"

// structs --------------------------------------------------------------------

typedef struct NodeObj {
    int x;
    struct NodeObj* next;
    struct NodeObj* prev;
} NodeObj;

typedef NodeObj* Node;

Node newNode(int x) {
    Node N = malloc(sizeof(NodeObj));
    N->x = x;
    N->next = NULL;
    N->prev = NULL;

    return(N);
}

void freeNode(Node* pN) {
    if (pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}

typedef struct ListObj {
    Node front;
    Node back;
    Node cursor;
    int length;
    int cursorIndex;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

List newList(void) {
    List L = malloc(sizeof(ListObj));
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->cursorIndex = -1;

    return L;
}

void freeList(List* pL) {

	Node temp = (*pL)->front;
    if (pL != NULL && *pL != NULL) {

		for (int i = 0; i < (*pL)->length; i++){
			Node next = temp->next;
			free(temp);
			temp = next;
		}
        free(*pL);
    }
}

int length(List L) {
    if (L == NULL) {
        printf("List Error: Calling length() on NULL list reference.\n");
        exit(1);
    }

    else {
        return L->length;
    }
}

int index(List L) {
    if (L == NULL) {
        printf("List Error: Calling length() on empty list.\n");
        exit(1);
    }

    else {
        return L->cursorIndex;
    }
}

int front(List L) {
    if (L == NULL) {
    printf("List Error: Calling front() on NULL list reference.\n");
    exit(1);
    }

    else {

        if (length(L) > 0) {
            return L->front->x;
        }

        else {
            printf("List Error: Calling front() on empty list.\n");
            exit(1);
        }
    }
}

int back(List L) {
    if (L == NULL) {
    printf("List Error: Calling back() on NULL list reference.\n");
    exit(1);
    }

    else {

        if (length(L) > 0) {
            return L->back->x;
        }

        else {
            printf("List Error: Calling back() on empty list.\n");
            exit(1);
        }
    }
}

int get(List L) {
    if (L == NULL) {
    printf("List Error: Calling get() on NULL list reference.\n");
    exit(1);
    }

    else {

        if (length(L) > 0 && index(L) >= 0) {
            return L->cursor->x;
        }

        else {
            printf("List Error: Calling get() on empty list.\n");
            exit(1);
        }
    }
}

bool equals(List A, List B) {
    if (A == NULL || B == NULL) {
        printf("List Error: Calling equals() on NULL list reference.\n");
        exit(1);
    }

    else {
        Node Aref = NULL;
        Node Bref = NULL;
        moveFront(A);
        moveFront(B);

        if (length(A) == length(B)) {
            Aref = A->cursor;
            Bref = B->cursor;

            for (int i = 0; i < length(A); i++) {

                if(Aref->x != Bref->x) {
                    return false;
                }

                Aref = Aref->next;
                Bref = Bref->next;
            }

            return true;
        }

        return false;
    }
}

void clear (List L) {
    if (L == NULL) {
        printf("List Error: Calling clear() NULL list reference.\n");
        exit(1);
    }

    else {
        while (length(L) > 0) {
            deleteFront(L);
        }

        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        L->length = 0;
        L->cursorIndex = -1;
    }
}

void moveFront(List L) {
    if (L == NULL) {
        printf("List Error: Calling moveFront() NULL list reference.\n");
        exit(1);
    }

    else {

        if (length(L) > 0) {
            L->cursor = L->front;
            L->cursorIndex = 0;
        }
    }
}

void moveBack(List L) {
    if (L == NULL) {
        printf("List Error: Calling moveBack() NULL list reference.\n");
        exit(1);
    }

    else {

        if (length(L) > 0) {
            L->cursor = L->back;
            L->cursorIndex = length(L) - 1;
        }

        else {
            printf("List Error: Calling moveBakc() on empty list.\n");
            exit(1);
        }
    }
}

void movePrev(List L) {
    if (L == NULL) {
    printf("List Error: Calling movePrev() on NULL list reference.\n");
    exit(1);
    }

    else {

        if (index(L) == -1) {}

        else if (index(L) == 0) {
            L->cursor = NULL;
            L->cursorIndex = -1;
        }

        else {
            L->cursor = L->cursor->prev;
            L->cursorIndex--;
        }
    }
}

void moveNext(List L) {
    if (L == NULL) {
    printf("List Error: Calling moveNext() on NULL list reference.\n");
    exit(1);
    }

    else {

        if (index(L) == -1) {}

        else if (index(L) == length(L) - 1) {
            L->cursor = NULL;
            L->cursorIndex = -1;
        }

        else {
            L->cursor = L->cursor->next;
            L->cursorIndex++;
        }
    }
}

void prepend(List L, int x) {
    if (L == NULL) {
        printf("List Error: Calling prepend() on NULL list reference.\n");
        exit(1);
    }

    else {
        Node N = newNode(x);

        if (length(L) == 0) {
            L->front = N;
            L->back = N;
        }

        else {
            Node temp = L->front;
            N->next = temp;
            temp->prev = N;
            L->front = N;
            N->prev = NULL;

            if(index(L) >= 0) {
                L->cursorIndex++;
            }
        }

        L->length++;
    }
}

void append(List L, int x) {
    if (L == NULL) {
        printf("List Error: Calling append() on NULL list reference.\n");
        exit(1);
    }

    else {
        Node N = newNode(x);

        if(length(L) == 0) {
            L->front = N;
            L->back = N;
        }

        else {
            Node temp = L->back;
            N->prev = temp;
            temp->next = N;
            L->back = N;
            N->next = NULL;
        }

        L->length++;
    }
}

void insertBefore(List L, int x) {
    if (L == NULL) {
        printf("List Error: Calling insertBefore() on NULL list reference.\n");
        exit(1);
    }

    else {

        if (length(L) > 0 && index(L) >= 0) {
            Node N = newNode(x);

            if (L->cursor->prev != NULL) {
                Node temp = L->cursor->prev;
                temp->next = N;
                N->prev = temp;
            }

			else {
				L->front = N;
			}

            N->next = L->cursor;
            L->cursor->prev = N;
        }

		L->cursorIndex++;
		L->length++;
    }
}

void insertAfter(List L, int x) {
    if (L == NULL) {
        printf("List Error: Calling insertAfter() on NULL list reference.\n");
        exit(1);
    }

    else {

        if (length(L) > 0 && index(L) >= 0) {
            Node N = newNode(x);

            if (L->cursor->next != NULL) {
                Node temp = L->cursor->next;
                N->next = temp;
                L->cursor->next = N;
                temp->prev = N;
                N->prev = L->cursor;
            }

            else {
                L->cursor->next = N;
				L->back = N;
                N->prev = L->cursor;
                N->next = NULL;
            }

            L->length++;
        }

        else {
            printf("List Error: Cannot insertAfter() on empty list.\n");
            exit(1);
        }
    }
}

void deleteFront(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: Calling deleteFront() on NULL list reference.\n");
        exit(EXIT_FAILURE);
    }

	if (L->length > 0) {
		Node N = L->front;
		if (L->cursorIndex == 0) {
			L->cursor = NULL;
		}

		if (L->length == 1) {
			L->front = L->back = NULL;
		}

		else {
			L->front = L->front->next;
			L->front->prev = NULL;
		}

		freeNode(&N);
		L->length--;
		if (L->cursorIndex >= 0) {
			L->cursorIndex--;
		}
	}
}

void deleteBack(List L) {
    if (L == NULL) {
        fprintf(stderr, "List Error: Calling deleteBack() on NULL list reference.\n");
        exit(EXIT_FAILURE);
    }

    else {

        if (length(L) > 0) {
            Node temp = L->back;
            L->back = L->back->prev;
            freeNode(&temp);
            L->length--;

            if(index(L) == length(L)) {
                L->cursor = NULL;
                L->cursorIndex = -1;
            }
        }

        else {
            fprintf(stderr, "List Error: Calling deleteBack() on empty list.\n");
            exit(EXIT_FAILURE);
        }
    }
}

void delete(List L) {
    if (L == NULL) {
        printf("List Error: Calling delete() on NULL list reference.\n");
        exit(1);
    }

    else {

        if (length(L) > 0 && index(L) >= 0) {

            if (length(L) == 1) {
                clear(L);
            }

            else if (L->cursor->prev != NULL) {
                Node deleteNode = L->cursor;
                Node temp = L->cursor->prev;
                temp->next = L->cursor->next;
                freeNode(&deleteNode);
                L->cursor = NULL;
                L->cursorIndex = -1;
                L->length--;
				L->back = temp;
            }

            else {
                deleteFront(L);
            }
        }

        else {
            printf("List Error: Calling delete() on empty list.\n");
            exit(1);
        }
    }
}

void printList (FILE* out, List L) {
    if (L == NULL) {
        printf("List Error: Calling printList() on NULL list reference.\n");
        exit(1);
    }

    else {
        Node N = L->front;
        while (N != NULL) {
            fprintf(out, "%d ", N->x);
            N = N->next;
        }
    }
}

List copyList (List L) {
    if (L == NULL) {
        printf("List Error: Calling copyList() on NULL list reference.\n");
        exit(1);
    }

    else {
        List returnList = newList();
        Node N = L->front;

        for (int i = 0; i < length(L); i++) {
            append(returnList, N->x);
            N = N->next;
        }

        return returnList;
    }
}