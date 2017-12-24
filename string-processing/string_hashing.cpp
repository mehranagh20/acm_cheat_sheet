class hashh {
public:
    vi p, h;
    ll mod1;
    hashh(string &str, ll pp = 10, ll mod1 = 1e9 + 21) { // pp is a number bigger than len of different characters in our language, better be a big prime like 1e9 + 7
        // pp is base in case that str is a number for example pp = 10 if str is number
        this->mod1 = mod1;
        p.assign(str.size() + 100, 1), h.assign(str.size() + 100, 0);
        for(int i = 1; i <= str.size(); i++) {
            h[i] = (h[i - 1] * pp + str[i - 1] - '0') % mod1;
            // if str is not number remove - '0'
            p[i] = (p[i - 1] * pp) % mod1;
            h[i] = (h[i] + mod1) % mod1;
            p[i] = (p[i] + mod1) % mod1;
        }
    }

    ll sub_hash(int a, int b) { // 'a' and 'b' are one based and inclusive.
        ll ret = (h[b] - h[a - 1] * p[b - a + 1]) % mod1;
        return (ret + mod1) % mod1;
    }

};
