typedef struct dict_t_struct {
    char *key;
    int value;
    struct dict_t_struct *next;
} dict_t;

dict_t **dictAlloc();
void dictDealloc(dict_t **dict);
void incrementItem(dict_t **dict, char *key);
void delItem(dict_t **dict, char *key);
void addItem(dict_t **dict, char *key, int value);
void printDict(dict_t **dict);
int getItem(dict_t **dict, char *key) ;
void deleteDoublons(dict_t **dict);
