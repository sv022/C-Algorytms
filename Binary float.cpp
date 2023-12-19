ld tobinfloat(string n) {
    ld res = 0;
    for (int i = n.size() - 1; i >= 0; i--) {
        res += (n[i] == '1' ? pow(2, -(i + 1)) : 0);
    }
    return res;
}