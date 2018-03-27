// Answers offline range query problems in N * sqrt(N)

int BLOCK = sqrt(n); // set in main or somewhere :)

struct node {
    int L, R, i;
};

bool cmp(node x, node y) {
    if(x.L/BLOCK != y.L/BLOCK)
        return x.L/BLOCK < y.L/BLOCK;
    return x.R < y.R;
}

void add(int position) {
    // implement here
}

void remove(int position) {
    // implement here
}

int main() {
    int m;
    scanf("%d", &m);
    for(int i=0; i<m; i++) {
        scanf("%d%d", &q[i].L, &q[i].R); // q is array of nodes
        q[i].L--; q[i].R--;
        q[i].i = i;
    }

    sort(q, q + m, cmp);

    int currentL = 0, currentR = 0;
    for(int i=0; i<m; i++) {
        int L = q[i].L, R = q[i].R;
        while(currentL < L) remove(currentL), currentL++;
        while(currentL > L) add(currentL-1), currentL--;
        while(currentR <= R) add(currentR), currentR++;
        while(currentR > R+1) remove(currentR-1), currentR--;

        ans[q[i].i] = answer; // answer is updated in add and remove
    }

    for(int i=0; i<m; i++)
        printf("%d\n", ans[i]);
}
