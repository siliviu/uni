#include <bits/stdc++.h>
#include "client.cpp"
#include "server.cpp"

using namespace std;

const char* ip = "127.0.0.1";
int port = 5678;
const int countries = 5, rounds = 10, blockSize = 20;
int p_r, p_w, deltaT, deltaX;

void test(auto&& function) {
    auto t_start = std::chrono::high_resolution_clock::now();
    function();
    auto t_end = std::chrono::high_resolution_clock::now();
    double elapsed_time_ms = std::chrono::duration<double, std::nano>(t_end - t_start).count();
    std::cout << setprecision(10) << elapsed_time_ms << "\n";
}

int main(int argc, char** argv) {
    assert(argc >= 5);
    p_r = atoi(argv[1]);
    p_w = atoi(argv[2]);
    deltaT = atoi(argv[3]);
    deltaX = atoi(argv[4]);
    if (argc == 6)
        port = atoi(argv[5]);

    test([&]() {
        Server sv;
        thread server(&Server::run, &sv, p_r, p_w, countries, rounds, blockSize, port, deltaT);
        sleep(1);

        vector<thread> clients;
        vector<Client> cs;
        for (int i = 1;i <= countries;++i) {
            cs.emplace_back();
            Client& c = cs.back();
            clients.emplace_back(&Client::run, &c, ip, port, i, rounds, blockSize, deltaX);
            cs.emplace_back(c);
        }

        for (auto& x : clients)
            x.join();

        server.join();
        });
};