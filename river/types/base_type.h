#include <malloc.h>
#include <stdio.h>

struct BaseType {

	void* content = NULL;
	int size = 0;
	bool alloc = false;
	bool temp = true;

	void clear(int size) {
		printf("Debug: Clear String, %d\n", size);
		if (size <= 0) {
			if (this->alloc) {
				free(this->content);
				this->alloc = false;
			}
			return;
		}
		if (!this->alloc) {
			this->alloc = true;
		}
		else {
			free(this->content);
		}
		this->size = size;
		this->content = malloc(size);
	}

};