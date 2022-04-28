struct node{
    int data;
    struct node *next;
};
typedef struct node node;

typedef struct{
    int length;
    node *front;
    node *rear;
}queue;

void initialize(queue *x){
    x->length = 0;
    x->front = NULL;
    x->rear = NULL;
}

int isempty(queue *x){
    return (x->length == 0);
}

void enqueue(queue *x, int data){
    node *temp = malloc(sizeof(node));
    temp->data = data;
    temp->next = NULL;
    if (x->length > 0){
        x->rear->next = temp;
        x->rear = temp;
    }
    else{
        x->front = temp;
        x->rear = temp;
    }
    x->length++;
}

void dequeue(queue *x){
    x->front = x->front->next;
    x->length--;
}