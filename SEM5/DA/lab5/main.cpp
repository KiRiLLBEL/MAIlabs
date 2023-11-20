#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>

std::vector<int> CreateSuffixArray(const std::string& s, size_t ALPHABET) {
    int n = s.size();
    std::vector<int> p(n), cnt(ALPHABET), c(n);
    for(int i = 0; i != n; ++i)
        ++cnt[s[i]];
    for(int i = 1; i != ALPHABET; ++i)
        cnt[i] += cnt[i - 1];
    for(int i = n - 1; i >= 0; --i)
        p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for(int i = 1; i != n; ++i) {
        if(s[p[i]] != s[p[i - 1]])
            ++classes;
        c[p[i]] = classes - 1;
    }
    std::vector<int> pn(n), cn(n);
    for(int h = 0; (1 << h) < n; ++h) {
        std::vector<int> cnt_loc(classes);
        for(int i = 0; i != n; ++i) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0)
                pn[i] += n;
        }
        for(int i = 0; i != n; ++i)
            ++cnt_loc[c[pn[i]]];
        for(int i = 1; i != classes; ++i)
            cnt_loc[i] += cnt_loc[i - 1];
        for (int i = n - 1; i >= 0; --i)
            p[--cnt_loc[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i != n; ++i) {
            int mid1 = (p[i] + (1 << h)) % n,  mid2 = (p[i - 1] + (1 << h)) % n;
            if (c[p[i]] != c[p[i-1]] || c[mid1] != c[mid2])
                ++classes;
            cn[p[i]] = classes-1;
        }
        c = cn;
    }
    return p;
}

bool stringsEqual(const std::string& s1, const std::string& s2, int index) {
    if(s1.size() - index < s2.size()) {
        return false;
    } else {
        for(int i = 0; i < s2.size(); ++i) {
            if(s1[i + index] != s2[i]) {
                return false;
            }
        }
        return true;
    }
}

bool stringsLess(const std::string& s1, const std::string& s2, int index) {
    for(int i = 0; i < std::min(s2.size(), size_t(s1.size() - index)); ++i) {
        if(s1[i + index] < s2[i]) {
            return true;
        }
        if(s1[i + index] > s2[i]) {
            return false;
        }
    }
    if(s1.size() - index < s2.size()) {
        return true;
    } else {
        return false;
    }
}

std::vector<int> SuffixArraySearch(const std::string& pattern, const std::string& text, const std::vector<int>& suffixArray)
{
    int n = text.size();
    int m = pattern.size();
    int l = 0, r = n - 1;
    std::vector<int> indices;
    if(m == 0)
        return indices;
    while (l <= r)
    {
        int mid = l + (r - l)/2;

        if(stringsEqual(text, pattern, suffixArray[mid])) {
            indices.push_back(suffixArray[mid] + 1);
            int tmp = mid - 1;
            while(tmp >= 0 && stringsEqual(text, pattern, suffixArray[tmp])) {
                indices.push_back(suffixArray[tmp] + 1);
                --tmp;
            }
            tmp = mid + 1;
            while(tmp < n && stringsEqual(text, pattern, suffixArray[tmp])) {
                indices.push_back(suffixArray[tmp] + 1);
                ++tmp;
            }
            return indices;
        }
        if(stringsLess(text, pattern, suffixArray[mid])) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return indices;
}



int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    const int ALPHABET = 256;
    std::string s;
    std::vector<int> suffixArray;
    std::string p;
    int cnt = 0;
    auto start = std::chrono::steady_clock::now();
    while(std::getline(std::cin, p)) {
        if(cnt == 0) {
            s = p;
            suffixArray = CreateSuffixArray(s + '\0', ALPHABET);
            ++cnt;
        } else {
            std::vector<int> occur = SuffixArraySearch(p, s + '\0', suffixArray);
            if(!occur.empty()) {
                std::sort(occur.begin(), occur.end());
                std::cout << cnt << ": ";
                for(size_t i = 0; i != occur.size(); ++i) {
                    if(i != occur.size() - 1) {
                        std::cout << occur[i] << ", ";
                    } else {
                        std::cout << occur[i] << "\n";
                    }
                }
            }
            ++cnt;
        }
    }
    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    return 0;
}