

void test() {
}

void bruh(int a, int b) {
    int x;
    x = a + b;
    return x;
}

int main() {
    int x;
    int y;
    int z;
    bool b;
    float f;
    string s;

    b = true;

    f = 3.4858345;
    
    x = 2;
    y = 1;
    z = x + y;

    s = "bruh";

    test();

    while(b == true) {
        x = x + 1;

        if(x >= 42) {
            break;
        }
    }

    if (b >= y) {
        test();
    } else {
        bruh(x, y);
    }

    return 0;
}
