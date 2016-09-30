
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_SLAB_H_INCLUDED_
#define _NGX_SLAB_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>

// page item in pool
typedef struct ngx_slab_page_s  ngx_slab_page_t;

struct ngx_slab_page_s {
    uintptr_t         slab; // items of ngx_slab_page_t
    ngx_slab_page_t  *next; // queue list
    uintptr_t         prev; // prev
};

// slab pool
typedef struct {
    ngx_shmtx_sh_t    lock;

    size_t            min_size;
    size_t            min_shift;

    ngx_slab_page_t  *pages; // slab start
    ngx_slab_page_t  *last;  // last slab
    ngx_slab_page_t   free;  // unused slab

    u_char           *start; // data start, with page-size ngx_slab_page_t
    u_char           *end;   // data end, may have junk

    ngx_shmtx_t       mutex;

    u_char           *log_ctx; // log message str
    u_char            zero;    // zero str

    unsigned          log_nomem:1;

    void             *data;
    void             *addr;
} ngx_slab_pool_t;


void ngx_slab_init(ngx_slab_pool_t *pool);
void *ngx_slab_alloc(ngx_slab_pool_t *pool, size_t size);
void *ngx_slab_alloc_locked(ngx_slab_pool_t *pool, size_t size);
void *ngx_slab_calloc(ngx_slab_pool_t *pool, size_t size);
void *ngx_slab_calloc_locked(ngx_slab_pool_t *pool, size_t size);
void ngx_slab_free(ngx_slab_pool_t *pool, void *p);
void ngx_slab_free_locked(ngx_slab_pool_t *pool, void *p);


#endif /* _NGX_SLAB_H_INCLUDED_ */
