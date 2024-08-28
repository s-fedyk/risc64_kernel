char _try_lock(char* lock);
char _release_lock(char* lock);

struct mutex {
  char lock;
};

