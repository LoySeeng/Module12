#include <iostream>
#include <string>

using namespace std;

void LPS(string& pat, int* lps);

int KMPCount(string& txt, string& pat);

bool IsDivisible(string& txt, int k) {
    if (txt.size() == k) {
        cout << "Text is divisible, but only once" << endl;
        return true;
    }
    else if ((txt.size() == 0) || (k == 0) || (k < 0)) {
        cout << "Something's gone wrong. Check text or repetition factor one more time." << endl;
        return false;
    }
    else if (txt.size() < k) {
        cout << "Repetition factor (k) can not be bigger that text size" << endl;
        return false;
    }
    else if (txt.size() % k != 0) {
        cout << "Text is not divisible by pattern of " << k << endl;
        return false;
    }
    else {
        string pat;
        pat = txt.substr(0, k);
        int K = (KMPCount(txt, pat) + 1);
        int D = txt.size() / k;
        if (K == D) {
            cout << "Text is divisible by pattern of " << k << endl;
            return true;
        }
        else {
            cout << "Text is not divisible by pattern of " << k << endl;
            return false;
        }
    }
}

void LPS(string& pat, int* lps) {
    int j = 0;
    lps[0] = 0;
    int i = 1;

    while (i < pat.size()) {
        if (pat[i] == pat[j]) {
            j++;
            lps[i] = j;
            i++;
        }
        else {
            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int KMPCount(string& txt, string& pat) {
    int* lps = new int[pat.size()];
    LPS(pat, lps);

    int i = 0;
    int j = 0;
    int res = 0;
    int next_i = 0;

    while (i < txt.size()) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
        else if (j == pat.size()) {
            j = lps[j - 1];
            res++;
            if (lps[j] != 0) {
                next_i++;
                i = next_i;
                j = 0;
            }
        }
        else if ((i < txt.size()) && (pat[j] != txt[i])) {
            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                i = i + 1;
            }
        }
    }
    if (i == txt.size() && j == pat.size()) {
        res++;
    }
    return res;
}


int main() {

    string txt;
    int k;
    cout << "Enter your text: ";
    cin >> txt;
    cout << "Enter your repetition factor: ";
    cin >> k;

    IsDivisible(txt, k);

    return 0;
}