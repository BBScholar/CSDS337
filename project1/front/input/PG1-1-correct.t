{
    int i; int n; int temp;
    int[4] data;

    n = 4;
    data[0] = 44;
    data[1] = 3;
    data[2] = 16;
    data[3] = 4;

    for(;;) {
        bool swapped;
        swapped = false;

        for(i = 0 ; i < n - 1; i = i + 1) {
            if(data[i] > data[i + 1]) {
                swapped = true;
                temp = data[i];
                data[i] = data[i + 1];
                data[i + 1] = temp;
            }
        }

        if(!swapped) break;
    }

}

