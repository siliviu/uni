#include <bits/stdc++.h>
#include <arpa/inet.h>
#include "BS_thread_pool.hpp"
#include "sync_linked_list.cpp"
#include "blocking_queue.cpp"

using namespace std;

using ti = array<int, 3>;
constexpr ti POISON{ -1,-1,-1 };

sync_linked_list<ti> final_list({ -1, -1, 0 });
sync_linked_list<int> disqualified(-1);
blocking_queue<ti, POISON> results(100'000);
map<int, mutex> mtxs;
mutex mtx;

template <typename Fut, typename Work>
auto then(Fut f, Work w) -> future<decltype(w(f.get()))>
{
    return async([=] { w(f.get()); });
}

void consume(blocking_queue<ti, POISON>& results, sync_linked_list<ti>& list, sync_linked_list<int>& disqualified) {
    while (1) {
        auto [country, id, score] = results.pop();
        if (id == -1)
            break;

        mtx.lock();
        auto& cur = mtxs[id];
        mtx.unlock();

        cur.lock();
        if (score == -1) {
            if (!disqualified.find(id)) {
                list.remove([&](ti x) {return x[1] == id;});
                disqualified.add_begin(id);
            }
        }
        else if (!disqualified.find(id)) {
            if (!list.find_and_update([&](ti x) {return x[1] == id;}, { country, id,score }))
                list.add_begin({ country,id,score });
        }
        cur.unlock();
    }
}

class Server {
public:
    void run(int p_r, int p_w, int countries, int rounds, int blockSize, int port, int deltaT) {
        int server_fd;
        struct sockaddr_in address;
        int addrlen = sizeof(address);
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
            perror("Socket failed");
            exit(EXIT_FAILURE);
        }

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);

        if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
            perror("Bind failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        int opt = 1;
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }

        if (listen(server_fd, 10) < 0) {
            perror("Listen failed");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        cout << "server listening\n";

        BS::thread_pool thread_pool(p_r);
        vector<int> sockets(countries);
        vector<pair<int, int>> pRanking, cRanking;
        chrono::time_point<chrono::system_clock> last = chrono::system_clock::now();
        sleep(1);
        optional<future<void>> currentFuture;
        mutex mutex;

        auto calculateRankings = [&](bool isFinal) {
            return std::async(std::launch::async, [&, isFinal] {
                chrono::time_point<chrono::system_clock> now = chrono::system_clock::now();
                mutex.lock();
                auto diff = chrono::duration_cast<chrono::milliseconds>(now - last);
                if (isFinal || std::chrono::milliseconds(diff) > std::chrono::milliseconds(deltaT)) {
                    last = now;
                    auto future = std::async(std::launch::async, [&] {
                        auto copy_list = final_list;
                        vector<pair<int, int>> playerRanking, countryRanking;
                        vector<int> scores(countries);
                        for (auto it = copy_list.root;it;it = it->next)
                            if (it->val[1] >= 0) {
                                playerRanking.emplace_back(it->val[1], it->val[2]);
                                scores[it->val[0] - 1] += it->val[2];
                            }
                        for (int i = 0;i < countries;++i)
                            countryRanking.emplace_back(i + 1, scores[i]);
                        sort(countryRanking.begin(), countryRanking.end(), [&](pair<int, int> val, pair<int, int> x) {return pair(val.second, val.first) > pair(x.second, x.first);});
                        sort(playerRanking.begin(), playerRanking.end(), [&](pair<int, int> val, pair<int, int> x) {return pair(val.second, val.first) > pair(x.second, x.first);});

                        tie(cRanking, pRanking) = make_pair(countryRanking, playerRanking);
                        });
                    cerr << format("recalculating {} {} {}\n", isFinal, std::chrono::milliseconds(diff), std::chrono::milliseconds(deltaT));
                    future.wait();
                    currentFuture = std::move(future);
                    mutex.unlock();
                    currentFuture = nullopt;
                }
                else {
                    mutex.unlock();
                    cerr << "reusing\n";
                    if (currentFuture.has_value())
                        currentFuture.value().wait();
                }
                });
            };

        vector<thread> tw(p_w);
        for (auto& x : tw)
            x = thread(consume, ref(results), ref(final_list), ref(disqualified));

        for (int i = 0;i < countries;++i)
            thread_pool.detach_task([&, i] {
            if ((sockets[i] = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
                perror("Accept failed");
                close(server_fd);
                exit(EXIT_FAILURE);
            }
            int ok = 0;
            ok = htonl(ok);
            if (send(sockets[i], &ok, sizeof(ok), 0) < 0) {
                cout << format("server couldnt ack client {}\n", i);
                exit(EXIT_FAILURE);
            }
            cout << "server received client\n";
            int received;
            if (recv(sockets[i], &received, sizeof(received), 0) <= 0) {
                perror("Receive failed");
                close(sockets[i]);
                close(server_fd);
                exit(EXIT_FAILURE);
            }
            received = ntohl(received);
            int index = received;
            cout << format("Received integer {} from client{}\n", received, i);

            while (true) {
                int length = 0;
                recv(sockets[i], &length, sizeof(length), 0);
                length = ntohl(length);

                if (length == -2) {
                    cout << format("client{} requested partial leaderboard\n", index);
                    auto execute = std::async(std::launch::async, [&] {
                        auto future = calculateRankings(false);
                        future.wait();
                        stringstream ss;
                        for (auto& [i, j] : cRanking)
                            ss << i << ' ' << j << '\n';
                        string packet = ss.str();

                        int length = htonl(packet.size());
                        send(sockets[i], &length, sizeof(length), 0);

                        send(sockets[i], packet.c_str(), packet.size(), 0);
                        });
                    continue;
                }

                if (length == -1) {
                    cout << format("client{} requested final leaderboard and stopped\n", index);
                    break;
                }

                char* buffer = new char[length + 1];
                recv(sockets[i], buffer, length, 0);
                buffer[length] = '\0';

                string message(buffer);
                delete[] buffer;
                stringstream ss(message);
                int id, score;
                while (ss >> id >> score) {
                    results.push({ index, id, score });
                }
            }
                });
        thread_pool.wait();
        results.stop();
        for (auto& x : tw)
            x.join();
        calculateRankings(true).wait();
        for (auto& x : sockets) {
            stringstream ss;
            for (auto& [i, j] : cRanking)
                ss << i << ' ' << j << '\n';
            string packet = ss.str();

            int length = htonl(packet.size());
            send(x, &length, sizeof(length), 0);

            send(x, packet.c_str(), packet.size(), 0);

            cout << format("server sent final country leaderboard to client\n");

            stringstream s;
            for (auto& [i, j] : pRanking)
                s << i << ' ' << j << '\n';
            packet = ss.str();

            length = htonl(packet.size());
            send(x, &length, sizeof(length), 0);

            send(x, packet.c_str(), packet.size(), 0);

            cout << format("server sent final player leaderboard to client\n");
        }
        for (auto& x : sockets)
            close(x);
        close(server_fd);
        ofstream fout("player.txt");
        for (auto& [x, y] : pRanking)
            fout << x << ' ' << y << '\n';
        ofstream ffout("country.txt");
        for (auto& [x, y] : cRanking)
            ffout << x << ' ' << y << '\n';
        cout << "server stopped\n";
    }
};