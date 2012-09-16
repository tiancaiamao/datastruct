struct list_node {
	struct list_node *next;
	struct list_node *prev;
};
void list_insert_after(struct list_node *p,struct list_node *q) {
	q->next = p->next;
	q->before = p;
	p->next->prev = q;
	p->next = q;
}
void list_insert_before(struct list_node *p,struct list_node *q) {
	list_insert_after(p->prev,q);
}
void list_init(struct list_node *p) {
	p->next = p;
	p->prev = p;
}
