#include <bits/stdc++.h>
using namespace std;

int pin_num, net_num;
bool isHead(int i, vector<vector<int>> &vcg) {
    if (vcg[i][i] == -1) return false;
    for (int j = 1; j <= net_num; j++) {
        if (vcg[j][i] > 0 && j != i) return false;
    }
    return true;
}

bool interval_comp(pair<int, pair<int, int>> &lhs, pair<int, pair<int, int>> &rhs) {
    if (lhs.second.first > rhs.second.first) {
        return true;
    }
    else if (lhs.second.first == rhs.second.first){
        if (lhs.second.second > rhs.second.second) return true;
        else return false;
    }
    else return false;
}

unordered_map<int, pair<int, int>> sort(map<int, pair<int, int>> &interval) {
    vector<pair<int, pair<int, int>>> tmp;
    for (auto &elem: interval) {
        tmp.emplace_back(elem);
    }
    sort(tmp.begin(), tmp.end(), interval_comp);
    unordered_map<int, pair<int, int>> intervalS;
    for (auto &elem: tmp) {
        intervalS[elem.first] = elem.second;
    }
    return intervalS;
}

vector<int> X, Y;
void print_result(map<int, pair<int, int>> &interval, vector<vector<int>> &track) {
    int dig = 1; int NP = pin_num;
    while (NP/10 > 0) {
        NP = NP / 10;
        dig++;
    }
    cout << "\n(4) detailed information about each net";
    cout << "\nThe resulting routing graph: \n";
    cout << "col:";
    for (int i = 1; i <= pin_num; i++) {
        for (int j = 1; j <= 3-dig; j++) cout << " ";
        cout << setw(dig) << i; cout << "  ";
    }
    dig = 1; int NN = net_num;
    while (NN/10 > 0) {
        NN = NN / 10;
        dig++;
    }
    cout << "\npin:";
    for (int i = 1; i <= pin_num; i++) {
        for (int j = 1; j <= 3-dig; j++) cout << " ";
        cout << setw(dig) << X[i]; cout << "  ";
    }
    cout << "\n    ";
    for (int i = 1; i <= 5*pin_num; i++) cout << "-";
    cout << "\n";

    vector<vector<char>> result(track.size(), vector<char>(pin_num*5, ' '));

    for (int i = 0; i < track.size(); i++) {
        for (int n = 0; n < track[i].size(); n++) {
            int net = track[i][n];
            int start = interval[track[i][n]].first;
            int terminal = interval[track[i][n]].second;
            for (int j = start; j <= terminal; j++) {
                if (X[j] == net) {
                    for (int k = i; k >= 0; k--) {
                        if (j == start && k == i) {
                            if (k == 0) result[k][2+(j-1)*5] = '^';
                            else result[k][2+(j-1)*5] = 'R';
                        }
                        else if (j == terminal && k == i) {
                            if (k == 0) result[k][2+(j-1)*5] = '^';
                            else result[k][2+(j-1)*5] = 'L';
                        }
                        else {
                            if (k == 0) result[k][2+(j-1)*5] = '^';
                            else if (k == i) result[k][2+(j-1)*5] = '-';
                            else result[k][2+(j-1)*5] = '|';
                        }
                    }
                }
                else if (Y[j] == net) {
                    for (int k = i; k < track.size(); k++) {
                        if (j == start && k == i) {
                            if (k == track.size()-1) result[k][2+(j-1)*5] = 'v';
                            else result[k][2+(j-1)*5] = 'R';
                        }
                        else if (j == terminal && k == i) {
                            if (k == track.size()-1) result[k][2+(j-1)*5] = 'v';
                            else result[k][2+(j-1)*5] = 'R';
                        }
                        else {
                            if (k == track.size()-1) result[k][2+(j-1)*5] = 'v';
                            else if (k == i) result[k][2+(j-1)*5] = '-';
                            else result[k][2+(j-1)*5] = '|';
                        }
                    }
                }
            }
            for (int j = 0; j < pin_num*5; j++) {
                if (j < 2+(start-1)*5 || j > 2+(terminal-1)*5) continue;
                if (result[i][j] == ' ') result[i][j] = '-';
            }
        }
    }
    for (auto &row: result) {
        cout << "    ";
        for (auto &elem: row) {
            if (elem == 'U') cout << "^";
            else if (elem == 'D') cout << "v";
            else if (elem == 'R') cout << ">";
            else if (elem == 'L') cout << "<";
            else cout << elem;
        }
        cout << '\n';
    }

    cout << "    ";
    for (int i = 1; i <= 5*pin_num; i++) cout << "-";
    cout << "\n    ";
    for (int i = 1; i <= pin_num; i++) cout << "  " << Y[i] << "  ";
    cout << '\n';

    cout << "(1) Number of tracks: " << track.size() << '\n';

    int len = 0;
    for (int i = 0; i < track.size(); i++) {
        for (int j = 0; j < track[i].size(); j++) {
            int net = track[i][j];
            len += interval[net].second - interval[net].first;
            int x = 0, y = 0;
            for (int k = 1; k <= pin_num; k++) {
                if (X[k] == net) x++;
                if (Y[k] == net) y++;
            }
            len += (i+1)*x;
            len += (track.size()-i)*y;
        }
    }
    cout << "(2) Overall wire length: " << len << '\n';

    int via = 0;
    for (int k = 1; k <= pin_num; k++) {
        if (X[k] != 0) via++;
        if (Y[k] != 0) via++;
    }
    cout << "(3) Number of vias: " << via << '\n';
}

int main(int argc, char** argv) {
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    
    ifstream in(argv[1]);
    
    X.emplace_back(0), Y.emplace_back(0);
    in >> pin_num >> net_num;
    vector<vector<int>> vcg(pin_num, vector<int>(pin_num, 0));
    map<int, pair<int, int>> interval;
    int tmp = pin_num;
    int col = 1;
    while (tmp--) {
        int ix, iy;
        in >> ix >> iy; X.emplace_back(ix); Y.emplace_back(iy);
        if (interval.count(ix)) {
            if (col > interval[ix].second) interval[ix].second = col;
        }
        else if (ix != 0) interval[ix] = make_pair(col, 0);
        if (interval.count(iy)) {
            if (col > interval[iy].second) interval[iy].second = col;
        }
        else if (iy != 0) interval[iy] = make_pair(col, 0);
        col++;

        if (ix == 0 || iy == 0) continue;
        vcg[ix][iy] = 1;
    }

    cout << "Sorted intervals of nets: \n";
    auto intervalS = sort(interval);
    for (auto &elem: intervalS) {
        cout << "  I" << elem.first << "[" << elem.second.first << ", " << elem.second.second << "]\n";
    }

    cout << "\nVertical constraint: " << '\n';
    for (int i = 0; i < pin_num; i++) {
        for (int j = 0; j < pin_num; j++) {
            if (vcg[i][j]) cout << "  I" << i << "->I" << j << '\n';
        }
    }

    int watermark = 0;
    vector<vector<int>> track;
    while (!intervalS.empty()) {
        if (track.size() > pin_num) break;
        cout << "\ntrack_" << track.size()+1 << ":\n";
        cout << "  head(s): ";
        for (int i = 1; i <= net_num; i++) {
            if (isHead(i, vcg)) cout << "I" << i << ", ";
        }
        cout << '\n';
        vector<int> nets; nets.reserve(100);
        for (auto &elem: intervalS) {
            if (elem.second.first <= watermark) continue;
            if (!isHead(elem.first, vcg)) continue;
            for (auto &elem: vcg[elem.first]) elem = -1;
            nets.emplace_back(elem.first);
            watermark = elem.second.second;
            cout << "  route I" << elem.first << "[" << elem.second.first << ", " << elem.second.second << "]: watermark = " << watermark << ";\n";
        }
        track.emplace_back(nets);
        for (auto &elem: nets) intervalS.erase(elem);
        watermark = 0; 
    }

    print_result(interval, track);
}