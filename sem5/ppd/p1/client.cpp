#include <bits/stdc++.h>
#include <arpa/inet.h>

using namespace std;

class Client {
public:
    void run(const char* ip, int port, int index, int rounds, int blockSize, int deltaX) {
        cout << format("client {}\n", index);
        int sock = 0;
        struct sockaddr_in serv_addr;

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("Socket creation error");
            exit(EXIT_FAILURE);
        }

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);

        if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
            perror("Invalid address or Address not supported");
            exit(EXIT_FAILURE);
        }

        if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
            perror("Connection failed");
            exit(EXIT_FAILURE);
        }

        int ok;
        if (recv(sock, &ok, sizeof(ok), 0) <= 0) {
            perror("Receive failed");
            close(sock);
            exit(EXIT_FAILURE);
        }

        if (ok == 0)
            cout << format("client {} connected\n", index);

        int number = index;
        number = htonl(number);

        if (send(sock, &number, sizeof(number), 0) < 0) {
            cout << format("client {} failed\n", index);
            exit(EXIT_FAILURE);

        }

        cout << format("client {} sent their index\n", index);

        for (int i = 1;i <= rounds;++i) {
            vector<vector<pair<int, int>>> chunks;
            vector<pair<int, int>> chunk;
            ifstream cin(format("data/RezultateC{}_P{}.txt", index, i));
            int id, score;
            while (cin >> id >> score) {
                chunk.emplace_back(id, score);
                if (chunk.size() == blockSize) {
                    chunks.emplace_back(chunk);
                    chunk.clear();
                }
            }
            if (!chunk.empty()) {
                chunks.emplace_back(chunk);
            }
            for (auto& chunk : chunks) {
                stringstream ss;
                for (auto& [i, j] : chunk)
                    ss << i << ' ' << j << '\n';
                string packet = ss.str();

                int length = htonl(packet.size());
                send(sock, &length, sizeof(length), 0);

                send(sock, packet.c_str(), packet.size(), 0);
                this_thread::sleep_for(chrono::milliseconds(deltaX));
            }
            int done = -2;
            done = htonl(done);
            if (send(sock, &done, sizeof(done), 0) < 0) {
                cout << format("client {} failed\n", index);
                exit(EXIT_FAILURE);
            }

            int length = 0;
            recv(sock, &length, sizeof(length), 0);
            length = ntohl(length);
            char* buffer = new char[length + 1];
            recv(sock, buffer, length, 0);
            buffer[length] = '\0';

            string message(buffer);
            delete[] buffer;
            cout << format("{} received partial ranking from server\n", index);
        }

        int done = -1;
        done = htonl(done);

        if (send(sock, &done, sizeof(done), 0) < 0) {
            cout << format("client {} failed\n", index);
            exit(EXIT_FAILURE);

        }

        int length = 0;
        recv(sock, &length, sizeof(length), 0);
        length = ntohl(length);
        char* buffer = new char[length + 1];
        recv(sock, buffer, length, 0);
        buffer[length] = '\0';

        string message(buffer);
        delete[] buffer;
        cout << format("{} received final country ranking from server\n", index);

        length = 0;
        recv(sock, &length, sizeof(length), 0);
        length = ntohl(length);
        buffer = new char[length + 1];
        recv(sock, buffer, length, 0);
        buffer[length] = '\0';

        message = string(buffer);
        delete[] buffer;
        cout << format("{} received final individual ranking from server\n", index);


        cout << format("client {} done\n", index);
        close(sock);
    }
};