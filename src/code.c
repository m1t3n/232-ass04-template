char *AUTHOR_NAME        = (char *) "Mikayla Iten";
char *AUTHOR_AUTHORSHIP  = (char *) "I acknowledge that I have worked on this \
assignment independently, except where explicitly noted and referenced. \
Any collaboration or use of external resources has been properly cited. \
I am fully aware of the consequences of academic dishonesty and agree to \
abide by the university's academic integrity policy.";


#include <stdio.h>
#include <stdlib.h>

// ============================================================
// Node — self-referential struct
// Every linked list is built from nodes connected by pointers.
// ============================================================

typedef struct Node {
    int value;
    struct Node *nextPtr;
} Node;

// ============================================================
// PRIVATE — forward declarations
// These functions are internal implementation details.
// They are marked static — invisible outside this file.
// Do NOT call them from tests.c or main.c.
// ============================================================

static void  _nullify   (Node **nodePtrPtr);
static Node* _findFirst (Node *headPtr);
static Node* _findLast  (Node *headPtr);
static Node* _findValue (Node *headPtr, int value);

// ============================================================
// PUBLIC — forward declarations
// These are the functions users of this API call directly.
// ============================================================

void  initNode    (Node *nodePtr, int value);
Node* createNode  (int value);
void  destroyNode (Node **nodePtrPtr);
void  destroyList (Node **headPtrPtr);

int   addFirst    (Node **headPtrPtr, Node *newNodePtr);
int   addLast     (Node **headPtrPtr, Node *newNodePtr);

Node* detachFirst (Node **headPtrPtr);
Node* detachLast  (Node **headPtrPtr);
Node* detachValue (Node **headPtrPtr, int value);

int   deleteFirst (Node **headPtrPtr);
int   deleteLast  (Node **headPtrPtr);
int   deleteValue (Node **headPtrPtr, int value);

int   printList   (Node *headPtr);
int   listLength  (Node *headPtr);


// ════════════════════════════════════════════════════════════
//  PRIVATE IMPLEMENTATIONS
//  Internal helpers — do not modify signatures.
//  These are called only by public functions below.
// ════════════════════════════════════════════════════════════


// ============================================================
// _nullify
//
// Set the pointer that nodePtrPtr points to — to NULL.
// This is the internal safe way to clear any pointer after
// detaching or freeing a node.
//
// Called by:
//   destroyNode, detachFirst, detachLast, detachValue
//
// HINT:
//   Dereference nodePtrPtr and assign NULL.
//   Guard against nodePtrPtr itself being NULL.
// ============================================================

static void _nullify(Node **nodePtrPtr)
{
    if (nodePtrPtr == NULL){
        return;
    }
    *nodePtrPtr = NULL;
}


// ============================================================
// _findFirst
//
// Return the first node in the list.
// This is simply the head — no traversal needed.
//
// Returns NULL if the list is empty.
//
// Called by:
//   detachFirst
// ============================================================

static Node* _findFirst(Node *headPtr)
{
    if (headPtr == NULL){
        return NULL;
    }
    return headPtr;
}


// ============================================================
// _findLast
//
// Walk the list from headPtr until nextPtr is NULL.
// Return a pointer to the last node.
//
// Returns NULL if the list is empty.
//
// Called by:
//   addLast, detachLast
//
// HINT:
//   Node *currentPtr = headPtr;
//   while (currentPtr->nextPtr != NULL) { ... }
// ============================================================

static Node* _findLast(Node *headPtr)
{
    if (headPtr == NULL){
        return NULL;
    }

    Node *currentPtr = headPtr;
    while (currentPtr->nextPtr != NULL){
        currentPtr = currentPtr->nextPtr; 
    }
    return currentPtr;
}


// ============================================================
// _findValue
//
// Walk the list from headPtr.
// Return a pointer to the FIRST node whose value field
// equals the given value.
//
// Returns NULL if no such node exists.
//
// Called by:
//   detachValue
//
// HINT:
//   Compare currentPtr->value to value at each step.
// ============================================================

static Node* _findValue(Node *headPtr, int value)
{
    Node *currentPtr = headPtr;
    while (currentPtr != NULL){
       if (currentPtr->value == value){
            return currentPtr;
        }
        currentPtr = currentPtr->nextPtr;
    }


    return NULL;
}


// ════════════════════════════════════════════════════════════
//  PUBLIC IMPLEMENTATIONS
//  These are the functions students and tests call directly.
// ════════════════════════════════════════════════════════════


// ============================================================
// initNode
//
// Initialize an EXISTING node — stack or heap, does not matter.
// Set value field and clear nextPtr to NULL.
//
// Does NOT allocate memory — the caller owns the node.
//
// Guard:
//   If nodePtr is NULL — return immediately, do nothing.
//
// Called by:
//   createNode (internally)
//   Student code directly for stack nodes
// ============================================================

void initNode(Node *nodePtr, int value)
{
    if (nodePtr == NULL){
        return;
    }
    nodePtr->value = value;
    nodePtr->nextPtr = NULL;
}


// ============================================================
// createNode
//
// Allocate a NEW node on the heap using malloc.
// Initialize it by calling initNode.
// Return a pointer to the new node.
//
// Returns NULL if malloc fails — print error to stderr.
//
// Called by:
//   Student code when building heap-based lists
//
// HINT:
//   Node *newNodePtr = malloc(sizeof(Node));
//   Check for NULL before calling initNode.
// ============================================================

Node* createNode(int value)
{
    Node *newNodePtr = malloc(sizeof(Node));
    if (newNodePtr == NULL){
        fprintf(stderr, "malloc failed.\n"); 
        return NULL;
    }
    initNode(newNodePtr, value); //&newNodePtr
    return newNodePtr;
}


// ============================================================
// destroyNode
//
// Free the memory of a single heap-allocated node.
// After freeing, set the pointer to NULL by calling _nullify.
//
// This prevents dangling pointers after free.
//
// Guard:
//   If nodePtrPtr is NULL or *nodePtrPtr is NULL — return.
//
// Calls:
//   free(), _nullify()
// ============================================================

void destroyNode(Node **nodePtrPtr)
{
    if (nodePtrPtr == NULL || *nodePtrPtr == NULL){
        return;
    }

    free(nodePtrPtr);
    _nullify(nodePtrPtr);
}


// ============================================================
// addFirst
//
// Insert newNodePtr at the FRONT of the list.
// Update *headPtrPtr to point to the new node.
// New node's nextPtr points to the previous head.
//
// Works for both empty and non-empty lists.
//
// Guards:
//   headPtrPtr == NULL → stderr + return -1
//   newNodePtr == NULL → stderr + return -1
//
// Returns 0 on success, -1 on error.
//
// HINT:
//   newNodePtr->nextPtr = *headPtrPtr;
//   *headPtrPtr = newNodePtr;
// ============================================================

int addFirst(Node **headPtrPtr, Node *newNodePtr)
{
    if (headPtrPtr == NULL || newNodePtr == NULL){
        fprintf(stderr, "null.\n");
        return -1;
    }

    newNodePtr->nextPtr = *headPtrPtr;
    *headPtrPtr = newNodePtr;

    return 0;
}


// ============================================================
// addLast
//
// Insert newNodePtr at the END of the list.
// If the list is empty — newNodePtr becomes the head.
// Otherwise walk to the last node using _findLast and attach.
//
// Always set newNodePtr->nextPtr = NULL after attaching.
//
// Guards:
//   headPtrPtr == NULL → stderr + return -1
//   newNodePtr == NULL → stderr + return -1
//
// Returns 0 on success, -1 on error.
//
// Calls:
//   _findLast()
// ============================================================

int addLast(Node **headPtrPtr, Node *newNodePtr)
{
    if (headPtrPtr == NULL){
        fprintf(stderr, "head is null\n");
        return -1;
    }
    if (newNodePtr == NULL){
        fprintf(stderr, "newNodePtr is null\n");
        return -1;
    }
    if (*headPtrPtr == NULL){
        *headPtrPtr = newNodePtr;
    } else {
        Node *last = _findLast(*headPtrPtr);
        last->nextPtr = newNodePtr;
    }
    return 0;
}


// ============================================================
// detachFirst
//
// Remove the first node from the list WITHOUT freeing it.
// Update *headPtrPtr to point to the second node.
// Clear the detached node's nextPtr using _nullify.
// Return a pointer to the detached node.
//
// The CALLER decides what to do with the detached node:
//   - Stack node → do nothing
//   - Heap node  → call destroyNode
//
// Returns NULL if the list is empty.
//
// Calls:
//   _findFirst(), _nullify()
// ============================================================

Node* detachFirst(Node **headPtrPtr)
{
    Node *aNode = _findFirst(*headPtrPtr);
    if (aNode == NULL){
        return NULL;
    }
    Node **currentPtrPtr = headPtrPtr;
    while (*currentPtrPtr != NULL && *currentPtrPtr != aNode){
        currentPtrPtr = &((*currentPtrPtr)->nextPtr);
    }
    if (*currentPtrPtr == NULL) {
        return NULL;
    }
    *currentPtrPtr = aNode->nextPtr; //point to 2nd node
    // _findFirst(*headPtrPtr);
    _nullify(&aNode->nextPtr);

    //headPtrPtr = &((*headPtrPtr)->nextPtr);


    return aNode; //detached node RIGHT
}


// ============================================================
// detachLast
//
// Remove the last node from the list WITHOUT freeing it.
// Walk to the second-to-last node and set its nextPtr to NULL.
// Return a pointer to the detached node.
//
// Special case:
//   If the list has only one node — call detachFirst.
//
// Returns NULL if the list is empty.
//
// Calls:
//   detachFirst() for single-element list
//   _nullify() to clear the link
// ============================================================

Node* detachLast(Node **headPtrPtr)
{
    if (headPtrPtr == NULL || *headPtrPtr == NULL){
        return NULL;
    }

    Node *currentPtr = *headPtrPtr;

    if (currentPtr->nextPtr == NULL){
        return detachFirst(&currentPtr);
    }
    while (currentPtr->nextPtr->nextPtr != NULL){ //check 2nd to last
        currentPtr = currentPtr->nextPtr;
    }
    Node *lastPtr = currentPtr->nextPtr;
    _nullify(&currentPtr->nextPtr);
    
    return lastPtr;
}


// ============================================================
// detachValue
//
// Find the first node whose value equals the given value.
// Remove it from the list WITHOUT freeing it.
// Clear the detached node's nextPtr using _nullify.
// Return a pointer to the detached node.
//
// Special case:
//   If the matching node is the head — call detachFirst.
//
// Returns NULL if value not found — print warning to stderr.
//
// Calls:
//   detachFirst() if value is at head
//   _nullify() to clear the link
// ============================================================

Node* detachValue(Node **headPtrPtr, int value)
{
    Node *valNode = _findValue(*headPtrPtr, value); //to find the val
    if (valNode == NULL){
        fprintf(stderr, "not found.\n");
        return NULL;
    }
    if (*headPtrPtr == valNode){ //if it's at head
        return detachFirst(headPtrPtr);
    }
    Node *currentPtr = *headPtrPtr;
    while (currentPtr->nextPtr != valNode){
        currentPtr = currentPtr->nextPtr; //go thru list until we find the val
    }

    currentPtr->nextPtr = valNode->nextPtr;
    _nullify(&valNode->nextPtr);

    return valNode;
}



// ============================================================
// deleteFirst
//
// Remove AND free the first node.
// This is the heap version of detachFirst.
//
// Internally:
//   1. Call detachFirst to remove the node.
//   2. Call destroyNode to free it.
//
// Returns 0 on success, -1 if list is empty.
//
// Calls:
//   detachFirst(), destroyNode()
// ============================================================

int deleteFirst(Node **headPtrPtr)
{
    if (headPtrPtr == NULL || *headPtrPtr == NULL){
        return -1;
    }
    Node *aNode = detachFirst(headPtrPtr); 
    if (aNode == NULL){
        return -1;
    }
    destroyNode(&aNode); 
    return 0;
    
}


// ============================================================
// deleteLast
//
// Remove AND free the last node.
// This is the heap version of detachLast.
//
// Internally:
//   1. Call detachLast to remove the node.
//   2. Call destroyNode to free it.
//
// Returns 0 on success, -1 if list is empty.
//
// Calls:
//   detachLast(), destroyNode()
// ============================================================

int deleteLast(Node **headPtrPtr)
{
    if (headPtrPtr == NULL){
        return -1;
    }
    Node *aNode = detachLast(headPtrPtr); 
    destroyNode(&aNode); 
    return 0;
}


// ============================================================
// deleteValue
//
// Find, remove AND free the first node with the given value.
// This is the heap version of detachValue.
//
// Internally:
//   1. Call detachValue to remove the node.
//   2. Call destroyNode to free it.
//
// Returns 0 on success, -1 if value not found.
//
// Calls:
//   detachValue(), destroyNode()
// ============================================================

int deleteValue(Node **headPtrPtr, int value)
{
    Node *aNode = detachValue(headPtrPtr, value);
    if (aNode == NULL){
        return -1;
    }
    destroyNode(&aNode);
    return 0;
}


// ============================================================
// destroyList
//
// Free ALL nodes in the list one by one.
// After the call *headPtrPtr must be NULL.
//
// Internally:
//   Call deleteFirst in a loop until the list is empty.
//
// Guard:
//   headPtrPtr == NULL → return immediately.
//
// Calls:
//   deleteFirst()
// ============================================================

void destroyList(Node **headPtrPtr)
{
    if (headPtrPtr == NULL){
        return;
    }
    while (*headPtrPtr != NULL){
        deleteFirst(headPtrPtr);
    }
}


// ============================================================
// printList
//
// Print every value in the list, one per line.
// If the list is empty — print "List is empty." to stdout.
//
// Returns 0 on success, -1 if list is empty.
// ============================================================

int printList(Node *headPtr)
{
    if (headPtr == NULL){
        fprintf(stdout, "List is empty.\n");
        return -1;
    }
    while (headPtr != NULL){
        printf("%d", headPtr->value);
        headPtr = headPtr->nextPtr;
    }
    return 0;
}


// ============================================================
// listLength
//
// Count and return the number of nodes in the list.
// Returns 0 for an empty list.
// ============================================================

int listLength(Node *headPtr)
{
    if (headPtr == NULL){
        return 0;
    }
    int count = 0;
    while (headPtr != NULL){
        headPtr = headPtr->nextPtr;
        count++;
    }
    return count;
}


//referred to stack overflow for stderr format
//referred to geeks for geeks's linked list printing example
//gemini/google ai overview helped with the return statements in the detach functions, listLength, & some unity tests