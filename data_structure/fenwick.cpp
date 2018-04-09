vi f; // size of n initialize to 0
int n;

void upd(int pos, int d){ // add 'd' to pos'th index
	for(; pos < n; pos |= pos + 1)
		f[pos] += d;
}

int get(int pos){ // sum from 0 to pos
	int res = 0;
	for(; pos >= 0; pos = (pos & (pos + 1)) - 1)
		res += f[pos];
	return res;
}
