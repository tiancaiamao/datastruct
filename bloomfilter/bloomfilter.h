#ifndef _BLOOM_FILTER_H
#define _BLOOM_FILTER_H

#ifdef __cplusplus
extern "C"
{
#endif

	struct bloom
	{
		unsigned int size;
		unsigned char *map1;
		unsigned char *map2;
		unsigned char *map3;
	};

	struct bloom *bloom_init(unsigned int size);
	void bloom_cleanup(struct bloom *b);
	void bloom_add(struct bloom *b,const char *str);
	int bloom_exist(struct bloom *b,const char *str);

#ifdef __cplusplus
}
#endif

#endif
