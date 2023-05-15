#include <stdio.h>
#include <string>
using namespace std;

int parseExpression(char* list, int* mark, const int lvl, const int len, int p, int* pH, int*pT, int* pC) {
	int h = -1, t = -1;
	for (int i = 0; i < len; i++) {

		if (list[i] == '(')
			if (mark[i] == lvl + 1) {
				h = i;
				for (int j = i; j < len; j++) {

					if (list[j] == ')')
						if (mark[j] == lvl + 1) {
							t = j;
							parseExpression(list+h, mark+h, lvl+1, t-h+1, h, pH, pT, pC);
							(*pC)++;
							pH[*pC - 1] = p + h;
							pT[*pC - 1] = p + t;
							for (int k = h; k <= t; k++) printf("%c", list[k]);
							printf("\nA pattern, %d-%d, level: %d. \n", pH[*pC-1], pT[*pC-1], mark[h]);
							break;
						}
				}
				continue;
			}
	}
	if (h == -1) /*printf("\nA LEAF FOUND\n")*/;
	char cs[12] = {};
	int ptr = 0;
	int oo = 0; // Output
	char oS = ' '; // Operator State
	int oB = 0; // Operation number B
	int s = 0;
	for (int i = 0; i < len; i++) {
		if (list[i] == '+' || list[i] == '-' || list[i] == '*' || list[i] == '/') {
			cs[ptr] = 0;
			oo = atoi(cs);
			s = i;
			break;
		}
		else if (i == len-1) {
			cs[ptr++] = list[i];
			cs[ptr] = 0;
			oo = atoi(cs);
			s = i;
			return oo;
		}
		else {
			cs[ptr++] = list[i];
		}
	}
	memset(cs, 0, 10);
	ptr = 0;
	oS = ' '; // Operator State
	oB = 0; // Operation number B
	for (int i = s; i < len; i++) {
		if (list[i] == '+' || list[i] == '-' || list[i] == '*' || list[i] == '/') {
			cs[ptr] = 0;
			ptr = 0;
			oB = atoi(cs);
			if (oS == '+') oo += oB;
			else if (oS == '-') oo -= oB;
			else if (oS == '*') oo *= oB;
			else if (oS == '/') {
				printf("Current Not Support Dividing! \n");
				continue;
			}
			oS = list[i];
		}
		else {
			cs[ptr++] = list[i];
		}
	}
	cs[ptr] = 0;
	ptr = 0;
	oB = atoi(cs);
	if (oS == '+') oo += oB;
	else if (oS == '-') oo -= oB;
	else if (oS == '*') oo *= oB;
	else if (oS == '/') {
		printf("Current Not Support Dividing! \n");
		return 0;
	}
	return oo;
}

int main() {
	printf("RiverLanguage v0.1. \nType \"help\" for more information. This is case-sensitive! \n");
	char cmd[512] = {};
	while (1) {
		printf("> ");
		fgets(cmd, 512, stdin);
		cmd[strlen(cmd) - 1] = 0;
		if (strcmp(cmd, "exit") == 0) {
			break;
		}
		if (strcmp(cmd, "help") == 0) {
			printf("This is RiverLanguage. \nThis currently has 3 functions: \"exit\", \"help\" and \"clear\". \nInput other thing will be parse as a expression. \n");
		}
		else if (strcmp(cmd, "clear") == 0) {
			system("cls");
		}
		else {
			int mark[512] = {};
			int m = 0;
			for (int i = 0; i < strlen(cmd); i++) {
				if (m < 0) break;
				if (cmd[i] == '(') mark[i] = ++m;
				if (cmd[i] == ')') mark[i] = m--;
			}
			if (m != 0) {
				printf("Parse Error: Unable to match patterns! \n");
				continue;
			}
			int pH[512], pT[512];
			int pC = 0;
			printf("%d\n", parseExpression(cmd, mark, 0, strlen(cmd), 0, pH, pT, &pC));
		}
	}
	return 0;
}