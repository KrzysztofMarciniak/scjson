#include "scjson.h"
#include "internal/scj_add.h"
#include "internal/scj_at.h"
#include "internal/scj_bool.h"
#include "internal/scj_dump.h"
#include "internal/scj_free.h"
#include "internal/scj_get.h"
#include "internal/scj_has.h"
#include "internal/scj_len.h"
#include "internal/scj_new.h"
#include "internal/scj_num.h"
#include "internal/scj_pretty.h"
#include "internal/scj_parse.h"
#include "internal/scj_str.h"

void scj_add(scjson arr, scjson value) {
    _scj_add(arr, value);
}
scjson scj_at(scjson self, size_t index) {
    return _scj_at(self, index);
}
int scj_bool(scjson self) {
    return _scj_bool(self);
}
char* scj_dump(scjson self) {
    return _scj_dump(self);
}
void scj_free(scjson obj){
    _scj_free(obj);
}
scjson scj_get(scjson self, const char* key){
    return _scj_get(self, key);
}
int scj_has(scjson self, const char* key){
    return _scj_has(self, key);
}
size_t scj_len(scjson self){
    return _scj_len(self);
}
scjson scj_new(void){
    return _scj_new();
}
double scj_num(scjson self){
    return _scj_num(self);
}
char* scj_pretty(scjson self){
    return _scj_pretty(self);
}
scjson scj_parse(const char* text){
    return _scj_parse(text);
}
const char* scj_str(scjson self){
    return _scj_str(self);
}
