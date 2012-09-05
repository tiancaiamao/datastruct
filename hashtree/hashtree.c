int primes[] = {7,11,13,17,23,29,31,34};
struct Data {
	int size;
	int used;
	int count;
	struct Item item[0];
};
struct Node {
	int level;
	int hash;
	struct Data *data;
	struct Node *child[0];
};
struct HashTree {
	struct Node *root[7];
	int hash;
};
