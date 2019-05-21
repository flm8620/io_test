#include <fstream>
#include <vector>
#include <random>
#include "scope_timer.h"
#include <map>
using namespace std;
const size_t N = 1024 * 1024 * 512;
const size_t bufsize = 1024 * 1024;
void fstream_write(const vector<char>& v, const string& filename) {
    vector<char> buf(bufsize);
    ios_base::sync_with_stdio(false);
    ofstream f(filename, ios_base::binary);
    f.rdbuf()->pubsetbuf(buf.data(), buf.size());
    f.write(v.data(), v.size());
    f.close();
}

void fopen_write(const vector<char>& v, const string& filename) {
    FILE* f = fopen(filename.c_str(), "wb");
    fwrite(v.data(), v.size(), 1, f);
    //for (int i = 0; i < v.size(); i++)
    //    fwrite(&v[i], 1, 1, f);
    fclose(f);
}

void fopen_write_map(const vector<map<int, vector<char>>>& vm, const string& filename) {
    FILE* f = fopen(filename.c_str(), "wb");
    for (const map<int, vector<char>>& m : vm)
        for (const auto& p : m) {
            fwrite(&p.first, sizeof(p.first), 1, f);
            fwrite(p.second.data(), sizeof(p.second[0])*p.second.size(), 1, f);
        }
    fclose(f);
}
int main() {

    vector<char> v(N);
    {
        for (int i = 0; i < 5; i++) {
            ScopeTimer t1("write file");
            fopen_write(v, "test1_" + std::to_string(i) + ".bin");
            //fstream_write(v, "test_" + std::to_string(i) + ".bin");
        }
    }

    const int n_map = 1024 * 32;
    vector<map<int, vector<char>>> data(n_map);
    //data.reserve(n_map);
    {
        ScopeTimer t("prepare map", true, false);
        default_random_engine e;
        uniform_int_distribution<int> dchar(0, 255);
        uniform_int_distribution<int> dint(0, 100);
#pragma omp parallel for
        for (int i = 0; i < n_map; i++) {
            map<int, vector<char>>& m = data[i];
            for (int j = 0; j < 128; j++)
                for (int k = 0; k < 100; k++)
                    m[dint(e)].push_back(dchar(e));
            //#pragma omp critical
                        //data.push_back(std::move(m));
        }
    }
    {
        ScopeTimer t("write map", true, false);
        fopen_write_map(data, "test_map.bin");
    }

    {
        for (int i = 0; i < 5; i++) {
            ScopeTimer t1("write file");
            fopen_write(v, "test2_" + std::to_string(i) + ".bin");
            //fstream_write(v, "test_" + std::to_string(i) + ".bin");
        }
    }

}