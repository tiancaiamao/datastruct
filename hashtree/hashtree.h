#ifndef _HASHTREE_H
struct Item {
	int bucketId;
	int offset;
	int ver;
	int hash;
	int length;
	char key[0];
};
struct HashTree* htNew();
void htFree(struct HashTree*);
void htAdd(struct HashTree*,const char *key,int bucketID,int offset,int ver,int hash);
void htRemove(struct HashTree*,const char *key);
struct Item* htGet(struct HashTree*,const char *key);

#endif
