string T, P; // T = text, P = pattern
int n, m; // size of text, size of pattern
vi b;

void kmpPreprocess() {
        b.assign(n + 1, 0);
            int i = 0, j = -1; b[0] = -1;
                while (i < m) {
                            while (j >= 0 && P[i] != P[j]) j = b[j];
                                    i++; j++;
                                            b[i] = j;
                                                }
}

void kmpSearch() {
        int i = 0, j = 0;
            while (i < n) {
                        while (j >= 0 && T[i] != P[j]) j = b[j]; // different, reset j using b
                                i++; j++;
                                        if (j == m) {
                                                        printf("P is found at index %d in T\n", i - j);
                                                                    j = b[j]; // prepare j for the next possible match
                                                                            }
                                            }
}
                                        }
            }
}
                }
}
