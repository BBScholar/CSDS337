int printf(string fmt, ...);

int main() {
    int a;
    int b;

    a = 1;
    b = 2;

    if(a == 1 && b == 2) {
        printf("Bruh\n");
    } else {
        printf("NO bruh \n");
    }


    if(a == 2 && b == 2) {
        printf("Bruh\n");
    } else {
        printf("NO bruh\n");
    }

    if(a == 1 && b == 3) {
        printf("Bruh\n");
    } else {
        printf("NO bruh\n");
    }

    if(b > 1) {
        printf("hello\n");
    }

    return 0;
}