#ifndef _PROC_SLAB_H
#define _PROC_SLAB_H

#define SLAB_INFO_NAME_LEN      128

struct slab_node {
	char name[SLAB_INFO_NAME_LEN];  /* name of this cache */
	struct slab_node *next;
	unsigned long cache_size;       /* size of entire cache */
	unsigned nr_objs;               /* number of objects in this cache */
	unsigned nr_active_objs;        /* number of active objects */
	unsigned obj_size;              /* size of each object */
	unsigned objs_per_slab;         /* number of objects per slab */
	unsigned pages_per_slab;        /* number of pages per slab */
	unsigned nr_slabs;              /* number of slabs in this cache */
	unsigned nr_active_slabs;       /* number of active slabs */
	unsigned use;                   /* percent full: total / active */
};

struct procps_slabinfo {
	struct slab_node *slab_list;  /* linked list of slab nodes */

	struct slab_node *free_head; /* pool of free slab nodes */
	struct slab_node *free_next; /* next available free slabnode */

	/* overall stats */
	unsigned long total_size;       /* size of all objects */
	unsigned long active_size;      /* size of all active objects */
	unsigned nr_objs;               /* number of objects, among all caches */
	unsigned nr_active_objs;        /* number of active objects, among all caches */
	unsigned nr_pages;              /* number of pages consumed by all objects */
	unsigned nr_slabs;              /* number of slabs, among all caches */
	unsigned nr_active_slabs;       /* number of active slabs, among all caches */
	unsigned nr_caches;             /* number of caches */
	unsigned nr_active_caches;      /* number of active caches */
	unsigned avg_obj_size;          /* average object size */
	unsigned min_obj_size;          /* size of smallest object */
	unsigned max_obj_size;          /* size of largest object */
};

int procps_slabinfo_new(struct procps_slabinfo **slabinfo);
int procps_slabinfo_read(struct procps_slabinfo *slabinfo, const char *filename);
void procps_slabinfo_clear(struct procps_slabinfo *slabinfo);
void procps_slabinfo_free(struct procps_slabinfo *slabinfo);

void procps_slabinfo_active_objs_get(const struct procps_slabinfo *slabinfo);
void procps_slabinfo_objs_get(const struct procps_slabinfo *slabinfo);
void procps_slabinfo_active_slabs_get(const struct procps_slabinfo *slabinfo);
void procps_slabinfo_slabs_get(const struct procps_slabinfo *slabinfo);
void procps_slabinfo_active_caches_get(const struct procps_slabinfo *slabinfo);
void procps_slabinfo_caches_get(const struct procps_slabinfo *slabinfo);
void procps_slabinfo_active_size_get(const struct procps_slabinfo *slabinfo);
void procps_slabinfo_total_size_get(const struct procps_slabinfo *slabinfo);
void procps_slabinfo_min_obj_size_get(const struct procps_slabinfo *slabinfo);
void procps_slabinfo_avg_obj_size_get(const struct procps_slabinfo *slabinfo);
void procps_slabinfo_max_obj_size_get(const struct procps_slabinfo *slabinfo);
#endif /* _PROC_SLAB_H */
