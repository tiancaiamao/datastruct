#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>

struct Store{
	char *path;
	struct HashTree *htree;
	int curr;
	FILE *f;	//use libc's cache	
};

struct Store* NewStore(char *path) {
	struct Store *ret;
	struct stat state;
	char filename[255];

	if(stat(path,&state) != 0) {
		fprintf(stderr,"%s not exists!\n",path);
		return NULL;
	}
	if(!S_ISDIR(state.st_mode)) {
		fprintf(stderr,"%s already exists and it's not a dir\n",path);
		return NULL;
	}
	ret = malloc(sizeof(struct Store));
	ret->curr = 0;
	sprintf(filename,"%s/%d",path,ret->curr);
	ret->f = fopen(filename,"rw");
	if(ret->f == NULL) {
		fprintf(stderr,"create bucket error\n");
		goto free;
	}
	ret->path = malloc(strlen(path)+1);
	strcpy(ret->path,path);
	ret->htree = NewHashTree();
	if(ret->htree == NULL) {
		fprintf(stderr,"create hashtree error\n");
		goto closeFile;
	}
	return ret;
closeFile:
	fclose(ret->f);
free:
	free(ret);
	return NULL;
}

struct Record* StoreGet(struct Store *store,const char *key) {
	struct Item *itm;
	struct Record *record;

	itm = HtGet(store->htree,key);
	if(itm == NULL || itm->ver<0)
		return NULL;
	
}

void StoreSet(struct Store *store,const char *key,const char *value,int lenValue) {
	struct Item *itm;
	long offset;
	int hashVal;
	char filename[255];

	offset = ftell(store->f);
	if(offset + lenValue > (1<<31)) {
		fclose(store->f);
		store->curr++;
		sprintf(filename,"%s/%d",path,store->curr);
		store->f = fopen(filename,"rw");
	}
	hashVal = hash(value);
	itm = HtGet(store->htree,key);
	if(itm == NULL) {
		HtSet(store->htree,key,ret->curr,offset,hashVal);
	}
	itm->ver++;
	itm->bucketId = store->curr;
	itm->offset = offset;
	itm->hash = hashVal;
	fwrite(value,lenValue,1,store->f);
}
