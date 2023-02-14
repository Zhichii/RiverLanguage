#include <stdio.h>
#include <fstream>
using namespace std;

int main() {
    fstream f("compile.rv");
    char tmp[256] = { 0 };
    int compile[128];
    int cur = 0;
    while (tmp[cur] != EOF) {
        f.read(tmp, 1);

    }
}