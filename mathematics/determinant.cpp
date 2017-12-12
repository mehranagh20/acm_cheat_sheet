void getCofactor(vvll mat, vvll & temp, int p, int q, int n) {
    int i = 0, j = 0;
    for (int row = 0; row < n; row++)
        for (int col = 0; col < n; col++)
            if (row != p && col != q) {
                temp[i][j++] = mat[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
}

ll determinantOfMatrix(vvll mat, int n) {
    ll D = 0;
    if (n == 1) return mat[0][0];
    vvll temp(mat.size() , vll(mat.size()));
    int sign = 1;
    for (int f = 0; f < n; f++) {
        getCofactor(mat, temp, 0, f, n);
        D += sign * mat[0][f] * determinantOfMatrix(temp, n - 1);
        sign = -sign;
    }
    return D;
}

/*inside main

get a vvll named mat from user and its dimension then
call "determinantOfMatrix(mat , n);"*/

