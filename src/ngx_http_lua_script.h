#ifndef NGX_HTTP_LUA_SCRIPT_H
#define NGX_HTTP_LUA_SCRIPT_H


#include "ngx_http_lua_common.h"


typedef struct {
    ngx_http_request_t         *request;
    ngx_str_t                  *source;

    ngx_array_t               **lengths;
    ngx_array_t               **values;

    ngx_uint_t                  variables;
    ngx_uint_t                  size;

    unsigned                    complete_lengths:1;
    unsigned                    complete_values:1;
} ngx_http_lua_script_compile_t;


typedef struct {
    ngx_str_t                   value;
    void                       *lengths;
    void                       *values;
} ngx_http_lua_complex_value_t;


typedef struct {
    ngx_http_request_t              *request;
    ngx_str_t                       *value;
    ngx_http_lua_complex_value_t    *complex_value;
} ngx_http_lua_compile_complex_value_t;


typedef struct {
    u_char                     *ip;
    u_char                     *pos;

    ngx_str_t                   buf;

    int                        *captures;
    ngx_uint_t                  ncaptures;
    u_char                     *captures_data;

    unsigned                    skip:1;

    ngx_http_request_t         *request;
} ngx_http_lua_script_engine_t;


typedef void (*ngx_http_lua_script_code_pt) (ngx_http_lua_script_engine_t *e);
typedef size_t (*ngx_http_lua_script_len_code_pt)
    (ngx_http_lua_script_engine_t *e);


typedef struct {
    ngx_http_lua_script_code_pt     code;
    uintptr_t                       len;
} ngx_http_lua_script_copy_code_t;


typedef struct {
    ngx_http_lua_script_code_pt     code;
    uintptr_t                       n;
} ngx_http_lua_script_copy_capture_code_t;


ngx_int_t ngx_http_lua_compile_complex_value(
        ngx_http_lua_compile_complex_value_t *ccv);
ngx_int_t ngx_http_lua_complex_value(ngx_http_request_t *r, ngx_str_t *subj,
        size_t offset, ngx_int_t count, int *cap,
        ngx_http_lua_complex_value_t *val, luaL_Buffer *luabuf);


#endif /* NGX_HTTP_LUA_SCRIPT_H */

