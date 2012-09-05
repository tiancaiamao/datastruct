#include <stdlib.h>
#include <string.h>
#include "bloomfilter.h"

static unsigned int bloom_hash1(const char *str)
{
	unsigned int i=0;
	unsigned int ret = 0;
	const char *p = str;
	while(*p != '\0' && i++ < 30)
	{
		ret = (ret<<4)^(ret>>28)^(*p);
		p++;
	}
	return ret;
}
static unsigned int bloom_hash2(const char *str)
{
	unsigned int i=0;
	unsigned int ret = 0;
	const char *p = str;
	while(*p != '\0' && i++ < 20)
	{
		ret = ret*33 + (*p);
		p++;
	}
	return ret;
}
static unsigned int bloom_hash3(const char *str)
{
	unsigned int ret = 2166136261;
	const char *p = str;
	while(*p != '\0')
	{
		ret = (ret^(*p)) * (*p);
		ret += ret<<13;
		ret ^= ret>>7;
		ret += ret<<3;
		ret ^= ret>>17;
		ret += ret<<5;
		p++;
	}
	return ret;

}

struct bloom *bloom_init(unsigned int size)
{
	struct bloom *ret;
	ret = (struct bloom*)malloc(sizeof(struct bloom));
	ret->size = size;
	ret->map1 = (unsigned char*)malloc(size);
	memset(ret->map1,0,size);
	ret->map2 = (unsigned char*)malloc(size);
	memset(ret->map2,0,size);
	ret->map3 = (unsigned char*)malloc(size);
	memset(ret->map3,0,size);
	return ret;
}
void bloom_cleanup(struct bloom *b)
{
	free(b->map1);
	free(b->map2);
	free(b->map3);
	free(b);
}
void bloom_add(struct bloom *b,const char *str)
{
	unsigned int pos1,pos2,pos3;
	unsigned int ofst,idx;
	pos1 = (bloom_hash1(str) % b->size);
	ofst = pos1 >>3;
	idx = pos1 & 7;
	b->map1[ofst] |= (((unsigned char)1)<<idx);

	pos2 = (bloom_hash2(str) % b->size);
	ofst = pos2 >>3;
	idx = pos2 & 7;
	b->map2[ofst] |= (((unsigned char)1)<<idx);

	pos3 = (bloom_hash3(str) % b->size);
	ofst = pos3 >>3;
	idx = pos3 & 7;
	b->map3[ofst] |= (((unsigned char)1)<<idx);
}
int bloom_exist(struct bloom *b,const char *str)
{
	unsigned int pos1,pos2,pos3;
	unsigned int ofst,idx;
	pos1 = (bloom_hash1(str) % b->size);
	ofst = pos1 >>3;
	idx = pos1 & 7;
	if((b->map1[ofst] & (((unsigned char)1)<<idx)) == 0)
		return 0;
	pos2 = (bloom_hash2(str) % b->size);
	ofst = pos2 >>3;
	idx = pos2 & 7;
	if((b->map2[ofst] & (((unsigned char)1)<<idx)) == 0)
		return 0;
	pos3 = (bloom_hash3(str) % b->size);
	ofst = pos3 >>3;
	idx = pos3 & 7;
	if((b->map3[ofst] & (((unsigned char)1)<<idx)) == 0)
		return 0;
	return 1;
}
