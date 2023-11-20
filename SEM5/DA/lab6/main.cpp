#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
const double PI = acos(-1);

class BigInt {
private:
    ull size;
    static const ll BASE = 1e3;
    static const ll DIGIT = 3;
    vector<ll> data;

    void AddDigit(ll digit) {
        data.push_back(digit);
        size = data.size();
    }
public:
    using base = complex<double>;
    static string RemoveLeadingZeros(const string& str) {
        if(str[0] != '0')
            return str;
        ll zerosCnt = 0;
        while(str[zerosCnt] == '0' && static_cast<ull>(zerosCnt) < (str.size() - 1))
            ++zerosCnt;
        return str.substr(zerosCnt, str.size() - zerosCnt + 1);
    }

    static vector<ll> CreateVectorOfDigits(const string& str, ll digit = DIGIT) {
        vector<ll> data;
        string s = RemoveLeadingZeros(str);
        ll remainder = static_cast<ll>(s.size()) % digit;
        if(remainder > 0)
            data.push_back(stoll(s.substr(0, remainder)));
        for(ull i = remainder; i < s.size(); i += digit)
            data.push_back(stoll(s.substr(i, digit)));
        return data;
    }

    static void Normalize(vector<ll> & vec, ll base = BASE) {
        size_t n = vec.size();
        ll inc = 0;
        for (size_t i = 0; i < n; ++i) {
            vec[i] += inc;
            inc = vec[i] / base;
            vec[i] %= base;
        }
        if(inc)
            vec.push_back(inc);
    }

    static void RemoveEndingZeros(vector<ll>& arr) {
        while(arr.back() == 0 && arr.size() > 1)
            arr.pop_back();
    }

    static void FFT(vector<base>& a, bool invert) {
        ll n = static_cast<ll>(a.size());

        for(ll i = 1, j = 0; i < n; ++i) {
            ll bit = n >> 1;
            for(; j >= bit; bit >>= 1)
                j -= bit;
            j += bit;
            if (i < j)
                swap (a[i], a[j]);
        }

        for (ll len = 2; len <= n; len <<= 1) {
            double angle = 2 * PI / static_cast<double>(len) * (invert ? -1 : 1);
            base wlen (cos(angle), sin(angle));
            for (ll i = 0; i < n; i += len) {
                base w (1);
                for (ll j = 0; j < len/2; ++j) {
                    base u = a[i + j],  v = a[i + j + len / 2] * w;
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                    w *= wlen;
                }
            }
        }
        if (invert)
            for (ll i = 0; i < n; ++i)
                a[i] /= static_cast<double>(n);
    }

    static vector<base> transformToComplex(const BigInt& number, ull size) {
        vector<base> res(size);
        for(ull i = 0; i < number.Size(); ++i)
            res[i] = static_cast<base>(number[number.Size() - i - 1]);
        return res;
    }

    static pair<BigInt, ll> BitShift(const BigInt& number) {
        vector<ll> res;
        ll remainder = 0;
        bool flag = true;
        for(ull i = 0; i < number.Size(); ++i) {
            remainder = remainder * BASE + number[i];
            if(remainder < 2 && flag)
                continue;
            res.push_back(remainder / 2);
            remainder %= 2;
            flag = false;
        }
        BigInt div;
        if(res.empty())
            div = BigInt(0);
        else
            div = BigInt(res);
        return make_pair(div, remainder);
    }

    BigInt() : size(0) {}

    BigInt(ll number) {
        do {
            data.push_back(number % BASE);
            number /= BASE;
        } while(number > 0);
        reverse(data.begin(), data.end());
        size = data.size();
    }

    explicit BigInt(const vector<ll>& other) : data(other), size(other.size()) {

    }

    BigInt& operator=([[maybe_unused]] const BigInt& other) {
        data = other.data;
        size = data.size();
        return *this;
    }

    BigInt(const BigInt& other) : data(other.data), size(other.data.size()) {

    }

    explicit BigInt(const string& str) {
        data = CreateVectorOfDigits(str);
        size = data.size();
    }

    [[nodiscard]] ull Size() const {
        return size;
    }

    ll& operator[] (ull idx) {
        return data[idx];
    }

    const ll & operator[] (ull idx) const {
        return data[idx];
    }

    friend bool operator== (const BigInt& lhs, const BigInt& rhs) {
        if(lhs.Size() != rhs.Size())
            return false;
        for(ull i = 0; i < lhs.Size(); ++i)
            if(lhs[i] != rhs[i])
                return false;
        return true;
    }

    friend bool operator< (const BigInt& lhs, const BigInt& rhs) {
        if(lhs.Size() != rhs.Size())
            return lhs.Size() < rhs.Size();
        for(ull i = 0; i < lhs.Size(); ++i)
            if(lhs[i] != rhs[i]) {
                return lhs[i] < rhs[i];
            }
        return false;
    }

    friend bool operator> (const BigInt& lhs, const BigInt& rhs) {
        if(lhs.Size() != rhs.Size())
            return lhs.Size() > rhs.Size();
        for(ull i = 0; i < lhs.Size(); ++i)
            if(lhs[i] != rhs[i]) {
                return lhs[i] > rhs[i];
            }
        return false;
    }

    friend bool operator>= (const BigInt& lhs, const BigInt& rhs) {
        return !(lhs < rhs);
    }

    friend bool operator<= (const BigInt& lhs, const BigInt& rhs) {
        return !(lhs > rhs);
    }

    friend bool operator!= (const BigInt& lhs, const BigInt& rhs) {
        return !(lhs == rhs);
    }

    friend BigInt operator+ (const BigInt& lhs, const BigInt& rhs) { // NOLINT(*-no-recursion)
        if(rhs.Size() < lhs.Size())
            return rhs + lhs;

        ull minSize = min(lhs.Size(), rhs.Size());
        ull maxSize = max(lhs.Size(), rhs.Size());

        vector<ll> sum(maxSize);
        for(ull i = 0; i < minSize; ++i)
            sum[i] += lhs[lhs.Size() - i - 1] + rhs[rhs.Size() - i - 1];

        for(ull i = minSize; i < maxSize; ++i)
            sum[i] += rhs[rhs.Size() - i - 1];

        Normalize(sum);
        reverse(sum.begin(), sum.end());
        return BigInt(sum);
    }

    friend BigInt operator- (const BigInt& lhs, const BigInt& rhs) {
        ull maxSize = lhs.Size();
        ull minSize = rhs.Size();
        vector<ll> diff(lhs.data);
        reverse(diff.begin(), diff.end());

        for(ull i = 0; i < minSize; ++i)
            diff[i] -= rhs[rhs.Size() - i - 1];

        ll inc = 0;
        for(ull i = 0; i < maxSize; ++i) {
            diff[i] -= inc;
            inc = 0;
            if(diff[i] < 0) {
                diff[i] += BASE;
                inc += 1;
            }
        }
        RemoveEndingZeros(diff);
        reverse(diff.begin(), diff.end());
        return BigInt(diff);
    }

    friend BigInt operator* (const BigInt& lhs, const BigInt& rhs) {
        ull n = 1;
        while(n < max(lhs.Size(), rhs.Size()))
            n <<= 1;
        n <<= 1;
        vector<ll> mult(n);
        vector<base> lhsComplex = transformToComplex(lhs, n);
        vector<base> rhsComplex = transformToComplex(rhs, n);

        lhsComplex.resize(n),
                rhsComplex.resize(n);

        FFT(lhsComplex, false),
                FFT(rhsComplex, false);

        for (ull i = 0; i < n; ++i)
            lhsComplex[i] *= rhsComplex[i];
        FFT(lhsComplex, true);

        mult.resize(n);
        for (size_t i = 0; i < n; ++i)
            mult[i] = round(lhsComplex[i].real());
        Normalize(mult);
        RemoveEndingZeros(mult);
        reverse(mult.begin(), mult.end());
        return BigInt(mult);
    }

    friend BigInt operator/ (const BigInt& lhs, const BigInt& rhs) {
        if(rhs > lhs) {
            return {0};
        }
        vector<ll> div;
        ull i = 0;
        BigInt remainder;
        do {
            remainder.AddDigit(lhs[i]);
            ++i;
        } while(remainder < rhs);
        for(;;) {
            ll l = -1, r = BASE;
            while(l + 1 < r) {
                ll m = (l + r) / 2;
                if(rhs * m > remainder)
                    r = m;
                else
                    l = m;
            }
            div.push_back(l);
            remainder = remainder - l * rhs;
            if(i == lhs.Size())
                break;
            if(remainder == 0)
                remainder[0] = lhs[i];
            else
                remainder.AddDigit(lhs[i]);
            ++i;
        }
        return BigInt(div);
    }

    friend BigInt operator^ (BigInt& lhs, BigInt& rhs) {
        BigInt power(1);
        BigInt zero(0);
        while(rhs > zero) {
            auto [div, mod] = BitShift(rhs);
            if(mod)
                power *= lhs;
            lhs = lhs * lhs;
            rhs = div;
        }
        return power;
    }

    void operator*=(const BigInt& rhs) {
        *this = *this * rhs;
    }

    void operator/=(const BigInt& rhs) {
        *this = *this / rhs;
    }

    void operator+=(const BigInt& rhs) {
        *this = *this + rhs;
    }

    void operator-=(const BigInt& rhs) {
        *this = *this - rhs;
    }

    friend istream& operator>>(istream& in, BigInt& number) {
        string str;
        in >> str;
        number = BigInt(str);
        return in;
    }

    friend ostream& operator<<(ostream& out, const BigInt& number) {
        bool notFirst = false;
        for(ll item: number.data) {
            string str = to_string(item);
            int zerosCnt = static_cast<int>(static_cast<ull>(DIGIT) - str.size());
            if(notFirst)
                for(int i = 0; i < zerosCnt; ++i)
                    out << '0';
            out << str;
            notFirst = true;
        }
        return out;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    BigInt a, b;
    char c;
    while (cin >> a >> b >> c) {
        BigInt res;
        bool flag;
        switch (c) {
            case '+':
                cout << a + b << "\n";
                    res = a + b;
                break;
            case '*':
                cout << a * b << "\n";
                res = a * b;
                break;
            case '-':
                if (a > b || a == b) {
                    cout << a - b << "\n";
                    res = a - b;
                } else
                    cout << "Error" << "\n";
                break;
            case '/':
                if (b == 0)
                    cout << "Error" << "\n";
                else
                    cout << a / b << "\n";
                res = a / b;
                break;
            case '^':
                if (a == 0 && b == 0) {
                    cout << "Error" << "\n";
                } else {
                    BigInt d = a ^ b;
                    cout << d << "\n";
                }
                res = a ^ b;
                break;
            case '<':
                if (a < b)
                    cout << "true" << "\n";
                else
                    cout << "false" << "\n";
                flag = a < b;
                break;
            case '>':
                if (a > b)
                    cout << "true" << "\n";
                else
                    cout << "false" << "\n";
                flag = a > b;
                break;
            case '=':
                if (a == b)
                    cout << "true" << "\n";
                else
                    cout << "false" << "\n";
                flag = a == b;
                break;
            default:
                break;
        }
    }
    return 0;
}