#include <fstream>
#include <vector>
#include "scope_timer.h"
using namespace std;
const int N = 1024 * 1024 * 512;
const int bufsize = 1024 * 1024;
void fstream_write(const std::vector<char>& v, const std::string& filename) {
    std::vector<char> buf(bufsize);
    std::ios_base::sync_with_stdio(false);
    ofstream f(filename, std::ios_base::binary);
    f.rdbuf()->pubsetbuf(buf.data(), buf.size());
    f.write(v.data(), v.size());
    f.close();
}

void fopen_write(const std::vector<char>& v, const std::string& filename) {
    FILE* f = fopen(filename.c_str(), "wb");
    fwrite(v.data(), v.size(), 1, f);
    fclose(f);
}
int main() {
    std::vector<char> v(N);
    {
        ScopeTimer t("write test", true, false);
        for (int i = 0; i < 15; i++) {
            ScopeTimer t1("write file");
            //fopen_write(v, "test_" + std::to_string(i) + ".bin");
            fstream_write(v, "test_" + std::to_string(i) + ".bin");
        }
    }

}