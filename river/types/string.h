#include <river\types\base_type.h>
#include <string>

struct String : public BaseType {
	
    void strcopy(char* dst, char* src) {
        for (int cur = 0; cur < strlen(src); cur++) {
            dst[cur] = src[cur];
        }
    }

	String get() {
		return *this;
	}

    void display() {
        printf("%s", (char*)this->content);
    }

	String(const char* str, bool temp = true) {
        this->temp = temp;
		this->clear(strlen(str));
        strcopy((char*)this->content, (char*)str);
	}

    void operator=(String target) {
        if (!target.alloc) {
            return;
        }
        this->clear(0);
        this->content = target.content;
        this->alloc = target.alloc;
        if (target.temp) {
            target.clear(0);
        }
    }

    void addBase(String target) {
        char* tmpStr = (char*)malloc(this->size + target.size);
        if (this->alloc) {
            strcopy(tmpStr, (char*)this->content);
        }
        if (target.alloc) {
            strcopy(tmpStr + strlen(tmpStr) - 1, (char*)target.content);
        }

    }

    String add(String target) {
        char* tmpStr = (char*)malloc(this->size + target.size);
        if (this->alloc) {
            strcopy(tmpStr, (char*)this->content);
        }
        if (target.alloc) {
            strcopy(tmpStr+strlen((const char*)this->content)-1, (char*)target.content);
        }
        String tmp(tmpStr);
        free(tmpStr);
        return tmp;
    }

    char* split(int from = 0, int to = 2147483647, int step = 1) {
        if (to == 2147483647) {
            to = this->size;
        }
        if (from < 0) from = this->size + from;
        if (to < 0) to = this->size + to;
        char* strB = (char*)malloc((to > from ? (to - from) : (from - to)) + 1);
        memset(strB, 0, (to > from ? (to - from) : (from - to)) + 1);
        int cur = 0;
        if (step == 0) {
            step = 1;
        }
        for (int i = from; from < to ? i<to : i>to; i += step) {
            strB[cur] = ((char*)(this->content))[i];
            cur++;
        }
        strB[cur] = '\0';
        return strB;
    }

};